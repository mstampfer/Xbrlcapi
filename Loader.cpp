#include "Cache.h"
#include "Constants.h"
#include "ContentHandler.h"
#include "EntityResolver.h"
#include "Fragment.h"
#include "History.h"
#include "Loader.h"
#include "Store.h"
#include "Storer.h"
#include "Util.h"
#include "XBRLException.h"
#include "XLinkProcessor.h"
#include "XercesString.h"

#include "ElementState.h"

#include <algorithm>
#include <chrono>
#include <deque>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <thread>
#include <unordered_set>
#include <utility>
#include <stack>

#include <Poco/Exception.h>
#include <boost/lexical_cast.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/BinOutputStream.hpp>
#include <xercesc/framework/MemoryManager.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/internal/BinFileOutputStream.hpp>
#include <xercesc/internal/MemoryManagerImpl.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace xbrlcapi
{
	class ContentHandler;
	class Loader;

	struct Loader::Impl 
	{
		std::weak_ptr<Loader> outer;
		Store store;
		XLinkProcessor xlinkProcessor;
		EntityResolver entityResolver;
		std::deque<Poco::URI> documentQueue;
		History history;// = new History();
		Poco::URI documentURI;
		std::string documentId;
		std::unordered_map<Poco::URI, std::string> failures;
		std::deque<Poco::URI> successes;
		int fragmentId;
		bool discovering;
		bool interrupt;
		bool _useSchemaLocationAttributes;
		std::shared_ptr<xercesc::DOMDocument> dom;
		std::stack<ElementState> states;
		std::stack<Fragment> fragments;
		boost::uuids::uuid uuid;

		Impl() :
			discovering(false),
			fragmentId(0),
			interrupt(false),
			_useSchemaLocationAttributes(false),
			uuid(boost::uuids::random_generator()())
		{
		}

		Impl(const Impl& rhs) : 
			discovering(rhs.discovering),
			documentId(rhs.documentId),
			documentQueue(rhs.documentQueue),
			documentURI(rhs.documentURI),
			dom(rhs.dom),
			entityResolver(rhs.entityResolver),
			failures(rhs.failures),
			fragmentId(rhs.fragmentId),
			history(rhs.history),
			interrupt(rhs.interrupt),
			store(rhs.store),
			successes(rhs.successes),
			xlinkProcessor(rhs.xlinkProcessor),
			_useSchemaLocationAttributes(rhs._useSchemaLocationAttributes),
			uuid(rhs.uuid)
		{
		}

		Impl(const Store& store) :
			store(store),
			discovering(false),
			fragmentId(0),
			interrupt(false),
			_useSchemaLocationAttributes(false),
			uuid(boost::uuids::random_generator()())
		{
		}

		Impl(
			const Store& store,
			const XLinkProcessor& xlinkProcessor, 
			const EntityResolver& entityResolver)
			:
		discovering(false),
			fragmentId(0),
			interrupt(false),
			_useSchemaLocationAttributes(false),
			store(store),
			xlinkProcessor(xlinkProcessor),
			entityResolver(entityResolver),
			uuid(boost::uuids::random_generator()())
		{
		}

		Impl(
			const Store& store,
			const XLinkProcessor& xlinkProcessor, 
			const EntityResolver& entityResolver,	
			const std::vector<Poco::URI>& uris) :
		discovering(false),
			fragmentId(0),
			interrupt(false),
			_useSchemaLocationAttributes(false),
			store(store),
			xlinkProcessor(xlinkProcessor),
			entityResolver(entityResolver),
			uuid(boost::uuids::random_generator()())
		{
			stashURIs(uris);								
		}

		Impl& operator=(Impl&& rhs)
		{
			if (this != &rhs)
			{
				outer = rhs.outer;
				discovering = rhs.discovering;
				documentId = rhs.documentId;
				documentQueue = rhs.documentQueue;
				documentURI = rhs.documentURI;
				dom = rhs.dom;
				entityResolver = std::move(rhs.entityResolver);
				failures = rhs.failures;
				fragmentId = rhs.fragmentId;
				interrupt = rhs.interrupt;
				store = std::move(rhs.store);
				successes = rhs.successes;
				xlinkProcessor = std::move(rhs.xlinkProcessor);
				_useSchemaLocationAttributes = rhs._useSchemaLocationAttributes;
				uuid = rhs.uuid;
			}
			return *this;
		}

		bool operator==(const Impl& rhs)
		{
			//	//if (cache == rhs.cache &&
			//	//discovering == rhs.discovering &&
			//	//documentId == rhs.documentId &&
			//	//documentQueue == rhs.documentQueue &&
			//	//documentURI == rhs.documentURI &&
			//	//dom == rhs.dom &&
			//	//entityResolver == rhs.entityResolver &&
			//	//failures == rhs.failures &&
			//	//fragmentId == rhs.fragmentId &&
			//	//history == rhs.history &&
			//	//interrupt == rhs.interrupt &&
			//	//store == rhs.store &&
			//	//successes == rhs.successes &&
			//	//xlinkProcessor == rhs.xlinkProcessor &&
			//	//_useSchemaLocationAttributes == rhs._useSchemaLocationAttributes)
			//	//	return true;
			return false;
		}  

		boost::uuids::uuid tag()
		{
			return uuid;
		}

		bool interruptRequested()
		{
			return interrupt;
		}

		void cancelInterrupt() 
		{
			interrupt = false;
		}

		std::shared_ptr<xercesc::DOMDocument> getBuilderDOM() {
			//        if (this.dom == null) {
			//            this.dom = (new XMLDOMBuilder()).newDocument();
			//        }
			return dom;
		}

		void setDiscovering(bool value) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			std::string thread_id(boost::lexical_cast<std::string>(std::this_thread::get_id()));
			if (value) logger.debug("thread id " + thread_id + " starting discovery.");
			else logger.debug("thread id " + thread_id + " stopping discovery.");
			discovering = value;
		}

		bool isDiscovering() 
		{
			return discovering;
		}

		void setStore(Store& s)
		{
			store = s; 
		}

		Store getStore() 
		{
			return store;
		}

		void setDocumentURI(const Poco::URI& uri)
		{
			documentURI = uri;
			std::string identifier = history.getIdentifier(uri);
			if (identifier == "") 
			{
				documentId = store.getId(uri.toString());
				history.addRecord(uri,documentId);
			} else {
				documentId = identifier;
			}
		}
		//    
		//    
		//    
		//    /**
		//     * @return the document ID for the document being analysed or
		//     * null if no document is being analysed.
		//     */
		//    private std::string getDocumentId() {
		//        return documentId;
		//    }

		/**
		* Get the Poco::URI for the document being parsed.
		* @return The original (non-cache) Poco::URI of the document being parsed.
		*/
		Poco::URI getDocumentURI() 
		{
			return documentURI;
		}

		void setXlinkProcessor(XLinkProcessor& xlp)
		{
			xlinkProcessor = xlp;
		}

		XLinkProcessor getXlinkProcessor() {
			return xlinkProcessor;
		}

		void setOuter(const std::weak_ptr<Loader>& loader)
		{
			outer = loader;
		}
		void updateState(const ElementState& state) 
		{

			if (states.top() == state) 
			{
				removeFragment();
			}
		}

		//    private std::stack<ElementState> getStates() {
		//        return this.states;
		//    }        

		Fragment getFragment() 
		{
			if (fragments.empty()) return Fragment();
			return fragments.top();
		}

		//    public void replaceCurrentFragment(const Fragment& replacement) {
		//        if (fragments.isEmpty()) throw XBRLException("There is no current fragment to replace.");
		//        fragments.pop();
		//        fragments.push(replacement);
		//    }    

		bool isBuildingAFragment() 
		{
			return (!fragments.empty());
		}

		void add(const Fragment& fragment, const ElementState& state)
		{
			//
			//        // Get the XPointer expressions that identify the root of this fragment
			//        // TODO Should the following xpointer code be contingent on children != null?
			//        Vector<std::string> pointers = state.getElementSchemePointers();
			//        for (const std::string& pointer : pointers) {
			//            fragment.appendElementSchemeXPointer(pointer);
			//        }
			//
			//        // Set the document reconstruction metadata for the fragment
			//        Fragment parent = getFragment();
			//        if (parent != null) {
			//            std::string parentIndex = parent.getIndex();
			//            if (parentIndex == null) throw XBRLException("The parent index is null.");
			//            fragment.setParentIndex(parentIndex);
			//            fragment.setSequenceToParentElement(parent);
			//        } else {
			//            fragment.setParentIndex("");
			//        }
			//
			//        fragment.setURI(getDocumentURI());
			//
			//        // Push the fragment onto the stack of fragments
			//        fragments.add(fragment);
			//
			//        // Push the element state onto the stack of fragment root element states
			//        getStates().add(state);
			//
		}

		Fragment removeFragment() 
		{
			//try {
			//	states.pop();
			//	getChildrenStack().pop();
			//	Fragment f = fragments.pop();
			//	store.persist(f);
			//	return f;
			//} catch (EmptyStackException e) {
			//	throw XBRLException(this.getDocumentURI() + " There are no fragments being built.  The stack of fragments is empty.",e);
			//}
			return Fragment();
		}

		void discover(const std::vector<Poco::URI>& startingURIs, std::weak_ptr<Loader>& loader)
		{
			for (auto uri : startingURIs) 
				stashURI(uri);
			discover(loader);
		}

		void discover(const Poco::URI& uri, std::weak_ptr<Loader>& loader)
		{
			stashURI(uri);
			discover(loader);
		}

		void discover(wchar_t* uri)
		{
			try 
			{
				discover(uri);
			} 
			catch (...) 
			{
				throw std::exception("The Uri to discover is malformed.");
			}
		}

		//    public std::vector<Poco::URI> getDocumentsStillToAnalyse() {
		//        std::vector<Poco::URI> documents = new Vector<Poco::URI>();
		//        documents.addAll(documentQueue);
		//        return documents;
		//    }

		void discover(std::weak_ptr<Loader>& loader)
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			store.startLoading();

			std::vector<Poco::URI> newDocuments;

			int discoveryCount = 1;

			if (isDiscovering()) 
			{
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.warn("The loader is already doing discovery so starting discovery achieves nothing.");
				return;
			}
			setDiscovering(true);

			for (const Poco::URI& uri : store.getDocumentsToDiscover()) 
			{
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.info(uri.toString() + " stashed for discovery.");
				stashURI(uri);
			}

			Poco::URI uri = getNextDocumentToExplore();
			while (!uri.empty()) 
			{
				bool documentClaimedByThisLoader = store.requestLoadingRightsFor(uri);
				if (! documentClaimedByThisLoader) 
				{
					markDocumentAsExplored(uri);
					uri = getNextDocumentToExplore();
					continue;
				}

				std::chrono::time_point<std::chrono::system_clock> start, end;
				start = std::chrono::system_clock::now();
				if (!store.hasDocument(uri)) 
				{
					setDocumentURI(uri);
					setNextFragmentId("1");
					try {
						parse(uri, loader);
						end = std::chrono::system_clock::now();
						long long duration = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
						logger.info("#" + std::to_string(discoveryCount) + " took " 
							+ std::to_string(duration) + " seconds. " 
							+ std::to_string(fragmentId-1) + " fragments in " + uri.toString());
						discoveryCount++;
						markDocumentAsExplored(uri);
						newDocuments.push_back(uri);
						store.sync();
					} 
					catch (const XBRLException& e) 
					{
						logger.error(e.what());
						//					this.cleanupFailedLoad(uri,"XBRL-API related problems occurred: " + e.getMessage(),e);
					} 
					catch (const xercesc::SAXException& e) 
					{	
						logger.error(to_string(e.getMessage()));
						//					this.cleanupFailedLoad(uri,"The document could not be parsed.",e);
					} 
					catch (...) 
					{
						logger.error("Unknown exception occured");
						//					this.cleanupFailedLoad(uri,"The document could not be accessed.",e);
					}
				} 
				else 
				{
					logger.debug(uri.toString() + " is already in the data store.");
					markDocumentAsExplored(uri);
				}

				if (interruptRequested()) 
				{
					cancelInterrupt();
					break;
				}

				uri = getNextDocumentToExplore();
			}

			storeDocumentsToAnalyse();
			setDiscovering(false);

			if (documentQueue.size() == 0 && failures.size() == 0) 
			{
				logger.debug("Document discovery completed successfully.");
			} else 
			{
				if (failures.size() > 0) 
				{
					//			logger.warn("Some documents failed to load.");
				}
				if (documentQueue.size() > 0) 
				{
					//		logger.info("Document discovery exited without completing.");
				}
			}

			store.stopLoading(); 

			//try {
			if (store.isPersistingRelationships() && (newDocuments.size() > 0)) 
			{

				// Wait till other loaders using the store have finished with their loading activities.
				while (store.isLoading()) 
				{
					//	logger.debug("Still doing some loading into the store ... ");
					//					Thread.sleep(10000); //TODO
				}
				Storer storer(store);
				storer.storeRelationships(newDocuments); 
			}
			//} catch (InterruptedException e) 
			//{
			//	logger.error("Failed to persist relationships.");
			//	std::unordered_map<Poco::URI,std::string> map = new HashMap<Poco::URI,std::string>();
			//	for (const Poco::URI& document : newDocuments) 
			//	{
			//		map.put(store.getMatcher().getMatch(document),"Failed to store relationships.");
			//	}
			//	store.persistLoaderState(map);
			//}

			std::map<Poco::URI,std::string> failures;
			std::deque<Poco::URI> documentQueue;

		}



		//    public void discoverNext() {
		//
		//        Store store = this.store;
		//        
		//        if (isDiscovering()) {
		//            logger.warn("Already discovering data with this loader so loader will not discover next document as requested.");
		//            return;
		//        }
		//        setDiscovering(true);
		//
		//        Poco::URI uri = getNextDocumentToExplore();
		//        bool documentClaimedByThisLoader = store.requestLoadingRightsFor(uri,*this);
		//        while ((store.hasDocument(uri) || !documentClaimedByThisLoader) && (uri != null)) {
		//            if (documentClaimedByThisLoader) {
		//                store.recindLoadingRightsFor(uri, *this);
		//            } else {
		//                this.markDocumentAsExplored(uri);
		//            }
		//            uri = getNextDocumentToExplore();
		//        }
		//
		//        if (uri != null) {
		//            logger.debug("Now parsing " + uri);
		//            setDocumentURI(uri);
		//            this.setNextFragmentId("1");
		//            try {
		//                parse(uri);
		//                markDocumentAsExplored(uri);
		//                store.sync();
		//                logger.info((this.fragmentId-1) + " fragments in " + uri);
		//            } catch (XBRLException e) {
		//                this.cleanupFailedLoad(uri,"XBRL Problem: " + e.getMessage(),e);
		//            } catch (SAXException e) {
		//                this.cleanupFailedLoad(uri,"SAX Problem: " + e.getMessage(),e);
		//            } catch (IOException e) {
		//                this.cleanupFailedLoad(uri,"IO Problem: " + e.getMessage(),e);
		//            }
		//        }
		//
		//        logger.info("Finished discovery of " + uri);
		//        this.storeDocumentsToAnalyse();
		//        
		//        setDiscovering(false);
		//
		//    }
		//    
		//    
		//
		//    public void discover(const Poco::URI& uri, const std::string& xml) {
		//
		//        logger.debug("Discovering a resource supplied as a string and with URI: " + uri);
		//
		//        if (!uri.isAbsolute()) throw XBRLException("The Poco::URI " + uri + " must be absolute.");
		//
		//        if (uri.isOpaque()) throw XBRLException("The Poco::URI " + uri + " must NOT be opaque.");
		//
		//        // Copy the XML to the local cache even if it is there already (possibly over-writing existing documents)
		//        this.getCache().copyToCache(uri, xml);
		//
		//        try {
		//            this.stashURI(new URI("http://www.xbrlapi.org/xbrl/xbrl-2.1-roles.xsd"));
		//        } catch (XMLUriSyntaxException e) {
		//            throw XBRLException("The standard roles Poco::URI could not be formed for discovery.",e);
		//        }
		//        
		//        discover(uri);
		//    }
		//

		Poco::URI getNextDocumentToExplore() 
		{
			if (documentQueue.empty()) return Poco::URI();
			auto ret = documentQueue.front();
			//		documentQueue.pop_front();
			return ret;
		}

		void markDocumentAsExplored(const Poco::URI& uri) 
		{
			if(!documentQueue.empty())
				documentQueue.pop_front();
			successes.push_back(uri);
			store.recindLoadingRightsFor(uri); 
		}

		void parse(const Poco::URI& uri, std::weak_ptr<Loader>& loader) 
		{
			xercesc::InputSource* inputSource =  entityResolver.resolveEntity(L"", getWC(uri.toString()).c_str());
			ContentHandler contentHandler(loader.lock(), uri);
			parse(uri, *inputSource, contentHandler);
		}

		//   void parse(const Poco::URI& uri, const std::string& xml)
		//{
		//       xercesc::InputSource* inputSource = new InputSource(new StringReader(xml));
		//       ContentHandler contentHandler = new ContentHandlerImpl(this, uri, xml);
		//       parse(uri, inputSource, contentHandler);
		//   }

		void setStartingURIs(const std::vector<Poco::URI>& uris) 
		{
			if (uris.empty())
				throw XBRLException("Null list of URIs is not permitted.");

			for (const auto e : uris ) 
			{
				stashURI(e);
			}
		}

		//synchronized 
		void stashURI(const Poco::URI& uri)
		{

			// Validate the URI
			if (uri.isRelative()) 
			{
				//throw XBRLException("The URI: " + uri + " must be absolute.");
				std::cout << "The URI: " <<  uri.toString() << " must be absolute." << std::endl;
			}

			if (uri.getScheme()[0] == '/') 
			{
				//				throw XBRLException("The URI: " + uri + " must not be opaque.");                
				std::cout << "The URI: " <<  uri.toString() << " must not be opaque." << std::endl;
			}

			try {

				Poco::URI dereferencedXMLUri(uri.getScheme(),uri.getAuthority(), uri.getPath());

				// Stash the Poco::URI if it has not already been stashed
				if (std::find(successes.begin(), successes.end(), dereferencedXMLUri) == successes.end()) 
				{
					// Queue up the original Poco::URI - ignoring issues of whether it matches another document.
					documentQueue.push_back(dereferencedXMLUri);
				}
			} 
			catch (Poco::SyntaxException e) 
			{
				throw XBRLException("Malformed Poco::URI found in DTS discovery process: " + uri.toString(), e.name());
			}

		}

		void stashURIs(const std::vector<Poco::URI>& uris) 
		{
			for (const Poco::URI& uri: uris) 
			{
				stashURI(uri);
			}
		}

		void setEntityResolver(EntityResolver& resolver) 
		{
			entityResolver = resolver;
		}

		//public std::string getNextFragmentId() {
		//    std::string id = getCurrentFragmentId();
		//    incrementFragmentId();
		//    return id;
		//}

		//public std::string getCurrentFragmentId() {
		//    return getDocumentId() + "_" + (new Integer(fragmentId)).toString();
		//}

		//public void incrementFragmentId() {
		//    fragmentId++;
		//}

		void setNextFragmentId(const std::string& id) 
		{
			fragmentId = std::stoi(id);
		}

		EntityResolver getEntityResolver() 
		{
			return entityResolver;
		}

		/**
		* @see org.xbrlapi.loader.Loader#useSchemaLocationAttributes()
		*/
		bool useSchemaLocationAttributes() 
		{
			return _useSchemaLocationAttributes;
		}

		//    /**
		//     * @see org.xbrlapi.loader.Loader#setSchemaLocationAttributeUsage(bool)
		//     */
		//    public void setSchemaLocationAttributeUsage(bool useThem) {
		//        this.useSchemaLocationAttributes = useThem;
		//    }

		/**
		* @see org.xbrlapi.loader.Loader#storeDocumentsToAnalyse()
		*/
		void storeDocumentsToAnalyse() 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );

			std::unordered_map<const Poco::URI,std::string> map;
			for (const Poco::URI& document : documentQueue) 
			{
				if (document == store.getMatcher().getMatch(document))
				{
					map[document] = "Document has not yet been analysed";
				}
			}

			std::vector<std::pair<Poco::URI, std::string>> kvpairs(failures.begin(), failures.end());			
			for (std::pair<Poco::URI, std::string>& document : kvpairs) 
			{
				map[document.first] = failures[document.first];
			}

			if (map.size() > 0)  
			{
				logger.warn("Storing details of " + std::to_string(map.size()) + " documents that are yet to be loaded.");
				store.persistLoaderState(map);
			}
		}

		//    
		//    private void cleanupFailedLoad(const Poco::URI& uri, const std::string& reason, Exception e) {
		//        logger.error(getDocumentURI() + " encountered a loading problem: " + e.getMessage());
		//        failures.put(uri,reason);
		//        documentQueue.remove(uri);
		//        store.recindLoadingRightsFor(getDocumentURI(), *this);
		//        try {
		//            store.deleteDocument(getDocumentURI());
		//            logger.info("Purged " + uri + " from the data store.");
		//        } catch (Exception exception) {
		//            logger.error("Failed to clean up the document from the data store. " + exception.getMessage());
		//        }
		//        fragments = new std::stack<Fragment>();
		//        states = new std::stack<ElementState>();
		//    }
		//
		//    /**
		//     * @see java.lang.Object#hashCode()
		//     */
		//    @Override
		//    public int hashCode() {
		//        final int prime = 31;
		//        int result = 1;
		//        result = prime * result + ((cache == null) ? 0 : cache.hashCode());
		//        result = prime * result + ((entityResolver == null) ? 0 : entityResolver.hashCode());
		//        result = prime * result + ((store == null) ? 0 : store.hashCode());
		//        result = prime * result + ((documentQueue == null) ? 0 : documentQueue.hashCode());
		//        result = prime * result + (useSchemaLocationAttributes ? 1231 : 1237);
		//        result = prime * result + ((xlinkProcessor == null) ? 0 : xlinkProcessor.hashCode());
		//        return result;
		//    }
		//
		//    /**
		//     * @see java.lang.Object#equals(java.lang.Object)
		//     */
		//    @Override
		//    public bool equals(Object obj) {
		//        if (this == obj)
		//            return true;
		//        if (obj == null)
		//            return false;
		//        if (getClass() != obj.getClass())
		//            return false;
		//        Impl other = (Impl) obj;
		//        if (cache == null) {
		//            if (other.cache != null)
		//                return false;
		//        } else if (!cache.equals(other.cache))
		//            return false;
		//        if (entityResolver == null) {
		//            if (other.entityResolver != null)
		//                return false;
		//        } else if (!entityResolver.equals(other.entityResolver))
		//            return false;
		//        if (store == null) {
		//            if (other.store != null)
		//                return false;
		//        } else if (!store.equals(other.store))
		//            return false;
		//        if (documentQueue == null) {
		//            if (other.documentQueue != null)
		//                return false;
		//        } else if (!documentQueue.equals(other.documentQueue))
		//            return false;
		//        if (useSchemaLocationAttributes != other.useSchemaLocationAttributes)
		//            return false;
		//        if (xlinkProcessor == null) {
		//            if (other.xlinkProcessor != null)
		//                return false;
		//        } else if (!xlinkProcessor.equals(other.xlinkProcessor))
		//            return false;
		//        return true;
		//    }
		//
		//    /**
		//     * Handles object inflation.
		//     * @param in The input object stream used to access the object's serialization.
		//     * @throws IOException
		//     * @throws ClassNotFoundException
		//     */
		//    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		//        in.defaultReadObject( );
		//        try {
		//            this.dom = (new XMLDOMBuilder()).newDocument();
		//            this.initialize();
		//        } catch (XBRLException e) {
		//            throw new IOException("The XML resource builder could not be instantiated.",e);
		//        }
		//    }
		//    
		//    /**
		//     * Handles object serialization
		//     * @param out The input object stream used to store the serialization of the object.
		//     * @throws IOException if the loader is still doing discovery.
		//     */
		//    private void writeObject(java.io.ObjectOutputStream out) throws IOException {
		//        if (this.isDiscovering()) throw new IOException("The loader could not be serialized because it is still loading data.");
		//        out.defaultWriteObject();
		//    }    
		void setHistory(History& h) {
			history = h;
		}
		//
		/**
		* @see Loader#getHistory()
		*/
		//History getHistory() 
		//{
		//	return history;
		//}
		//    
		//    /**
		//     * @see Loader#hasHistory()
		//     */
		//    public bool hasHistory() {
		//        return (history != null);
		//    }
		//    
		//    private transient XMLGrammarPoolImpl grammarPool = new XMLGrammarPoolImpl();
		//    private transient SymbolTable symbolTable = new SymbolTable(BIG_PRIME);
		void initialize() 
		{
			auto memMgr = std::shared_ptr<xercesc::MemoryManager>(new xercesc::MemoryManagerImpl());
			auto grammarPool = std::shared_ptr<xercesc::XMLGrammarPoolImpl>(new xercesc::XMLGrammarPoolImpl(memMgr.get()));
			auto preparser = std::shared_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader(
				memMgr.get(), grammarPool.get()));

			// Cache the grammar in the pool for re-use in subsequent parses.
			preparser->setFeature(xercesc::XMLUni::fgXercesCacheGrammarFromParse,true);
			//preparser->registerPreparser(XMLGrammarDescription.XML_SCHEMA, null);
			//preparser->setProperty(GRAMMAR_POOL, grammarPool);

			// Perform Namespace processing.  
			preparser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);

			//Report all validation errors
			preparser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation,true);

			// note we can set schema features just in case ...
			// Enable the parser's schema support.
			preparser->setFeature(xercesc::XMLUni::fgXercesSchema,true);  

			//Enable full schema constraint checking, including checking which may be 
			// time-consuming or memory intensive.
			preparser->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking,true);  

			// Validate the document even if a grammar is not specified
			preparser->setFeature(XMLUni::fgXercesDynamic, false);

			// Enable grammar caching 
			preparser->setFeature(XMLUni::fgXercesCacheGrammarFromParse, true);

			// All schema location hints will be used to locate the 
			// components for a given target namespace
			//parser->setFeature(L"http://apache.org/xml/features/honour-all-schemaLocations", true);
			// fgXercesSchemaExternalNoNameSpaceSchemaLocation  or fgXercesSchemaExternalSchemaLocation  ?

			// Specify the entity resolver to use for the schemas.
			//preparser->setEntityResolver(&entityResolver);

			// parse the grammars
			std::vector<Poco::URI> schemas;
			schemas.push_back(Poco::URI("http://www.xbrlapi.org/xml/schemas/s4s.xsd"));
			schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xbrl-instance-2003-12-31.xsd"));
			schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xbrl-linkbase-2003-12-31.xsd"));
			schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xl-2003-12-31.xsd"));
			schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xlink-2003-12-31.xsd"));

			try {
				for (const Poco::URI& schema : schemas) 
				{
					// This loads the schemas into the grammar pool
					std::shared_ptr<ContentHandler> contentHandler(new ContentHandler(outer.lock(), schema));
					contentHandler->initialize();
					preparser->setContentHandler(contentHandler.get());
					preparser->setErrorHandler(contentHandler.get());
					auto inputSource = entityResolver.resolveSchemaURI(schema);
					preparser->loadGrammar(*inputSource, xercesc::Grammar::SchemaGrammarType, true);
					entityResolver.setGrammarPool(grammarPool);
					if (entityResolver.hasCache())
						entityResolver.copyToCache(schema);
					preparser->parse(*inputSource);
				}
			} 
			catch (const std::exception& e) 
			{
				throw XBRLException("The XBRL and related schemas could not be preloaded.", e.what());
			}
			grammarPool->lockPool();
		}


		void parse(const Poco::URI& uri, 
			/*const*/ xercesc::InputSource& inputSource,  
			xercesc::ErrorHandler& contentHandler)
		{
			auto memMgr = std::shared_ptr<xercesc::MemoryManager>(new xercesc::MemoryManagerImpl());
			auto grammarPool = std::shared_ptr<xercesc::XMLGrammarPoolImpl>(new xercesc::XMLGrammarPoolImpl(memMgr.get()));
			auto parser = std::shared_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader(
				memMgr.get(), grammarPool.get()));

			// now must reset features for actual parsing:
			try
			{
				parser->setFeature(L"http://xml.org/sax/features/namespace-prefixes", true);
				parser->setFeature(L"http://xml.org/sax/features/namespaces", true);
				parser->setFeature(L"http://xml.org/sax/features/validation", true);
				parser->setFeature(L"http://apache.org/xml/features/validation/schema", true);
				parser->setFeature(L"http://apache.org/xml/features/validation/schema-full-checking", true);
				// parser->setFeature(L"http://apache.org/xml/features/honour-all-schemaLocations", false); //TODO uncomment
			} 
			catch 
				(const std::exception& e) 
			{
				throw XBRLException("The parser features could not be set.", e.what());
			}

			parser->setEntityResolver(&entityResolver);
			parser->setErrorHandler(&contentHandler);        
			parser->setContentHandler(dynamic_cast<xercesc::ContentHandler*>(&contentHandler));     
			parser->parse(inputSource);

		}

	};

	Loader::Loader() {}

	Loader::~Loader() {}

	Loader::Loader(const Loader& rhs) : pImpl(rhs.pImpl)
	{}

	Loader& Loader::operator=(const Loader& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Loader::Loader(Loader&& rhs) : pImpl(std::move(rhs.pImpl))
	{} 

	Loader::Loader(const Store& store) : pImpl(store)
	{}

	Loader::Loader(
		const Store& store, 
		const XLinkProcessor& xlinkProcessor, 
		const EntityResolver& entityResolver)
		: 
	pImpl( 
		store, 
		xlinkProcessor, 
		entityResolver) 
	{}
	Loader::Loader(
		const Store& store, 
		const XLinkProcessor& xlinkProcessor, 
		const EntityResolver& entityResolver, 
		const std::vector<Poco::URI>& uris)
		: 
	pImpl(
		store, 
		xlinkProcessor, 
		entityResolver, 
		uris)
	{}

	Loader& Loader::operator=(Loader&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Loader::operator==(const Loader& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Loader::operator!=(const Loader& rhs)
	{
		return !this->operator==(rhs);
	}

	XLinkProcessor Loader::getXlinkProcessor()
	{
		return pImpl->getXlinkProcessor();
	}

	void Loader::setEntityResolver(EntityResolver& resolver)
	{
		pImpl->setEntityResolver(resolver);
	}

	std::shared_ptr<xercesc::DOMDocument> Loader::getBuilderDOM()
	{
		return pImpl->getBuilderDOM();
	}

	//std::vector<Poco::URI> Loader::getDocumentsStillToAnalyse()
	//{
	//	pImpl->getDocumentsStillToAnalyse();
	//}

	void Loader::discover()
	{
		pImpl->discover(getPtr());
	}

	//void Loader::discoverNext()
	//{
	//	pImpl->discoverNext();
	//}

	//void Loader::discover(const Poco::URI& uri, const std::string& xml)
	//{
	//	pImpl->discover(uri, xml);
	//}

	void Loader::discover(const std::vector<Poco::URI>& startingURIs)
	{
		pImpl->discover(startingURIs, getPtr());
	}

	void Loader::discover(const Poco::URI& uri)
	{
		pImpl->discover(uri, getPtr());
	}

	void Loader::discover(const std::string& uri)
	{
		//			pImpl->discover(uri);
	}	

	void Loader::stashURI(const Poco::URI& uri)
	{
		pImpl->stashURI(uri);
	}

	void Loader::stashURIs(const std::vector<Poco::URI>& uris)
	{
		pImpl->stashURIs(uris);
	}

	Fragment Loader::getFragment()
	{
		return pImpl-> getFragment();
	}

	//void Loader::replaceCurrentFragment(const Fragment& replacement)
	//{
	//pImpl->replaceCurrentFragment(replacement);
	//}	

	bool Loader::isBuildingAFragment()
	{
		return pImpl->isBuildingAFragment();
	}

	bool Loader::isDiscovering()
	{
		return pImpl->isDiscovering();
	}

	void Loader::add(const Fragment& fragment, const ElementState& state)
	{
		pImpl->add(fragment, state);
	}

	/*	 bool addedAFragment()
	{
	pImpl->addedAFragment();
	}*/

	void Loader::updateState(const ElementState& state)
	{
		pImpl->updateState(state);
	}

	//std::string Loader::getNextFragmentId()
	//{
	//	pImpl->getNextFragmentId();
	//}

	//std::string Loader::getCurrentFragmentId()
	//{
	//	pImpl->getCurrentFragmentId();
	//}	

	Poco::URI Loader::getDocumentURI()
	{
		return pImpl->getDocumentURI();
	}

	EntityResolver Loader::getEntityResolver()
	{
		return pImpl->getEntityResolver();
	}

	bool Loader::useSchemaLocationAttributes()
	{
		return pImpl->useSchemaLocationAttributes();
	}

	//void Loader::setSchemaLocationAttributeUsage(bool useThem)
	//{
	//	pImpl->setSchemaLocationAttributeUsage(useThem);
	//}

	void Loader::requestInterrupt()
	{
		//			pImpl->requestInterrupt();
	}

	void Loader::cancelInterrupt()
	{
		pImpl->cancelInterrupt();
	}

	//void Loader::storeDocumentsToAnalyse()
	//{
	//	pImpl->storeDocumentsToAnalyse();
	//}


	void Loader::setHistory(History& history)
	{
		pImpl->setHistory(history);
	}

	//History Loader::getHistory()
	//{
	//	return pImpl->getHistory(); 
	//}

	//bool Loader::hasHistory()
	//{
	//	pImpl->hasHistory();
	//}

	boost::uuids::uuid Loader::tag()
	{
		return pImpl->tag();
	}

	std::weak_ptr<Loader> Loader::getPtr()
	{
		return shared_from_this();
	}

	void Loader::initialize()
	{
		pImpl->setOuter(getPtr());
		pImpl->initialize();
	}

}