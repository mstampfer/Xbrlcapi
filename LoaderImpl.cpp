#include "Stdafx.h"

#include "LoaderImpl.h"
#include "Constants.h"
#include "Storer.h"
#include "StorerImpl.h"
#include "Util.h"
#include "ContentHandler.h"
#include <iostream>
#include <algorithm>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/MemoryManager.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/BinOutputStream.hpp>
#include <xercesc/internal/MemoryManagerImpl.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/internal/BinFileOutputStream.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/framework/URLInputSource.hpp>

namespace xbrlcapi
{

	//static const std::string SYMBOL_TABLE =
	//		xercesc::XERCES_PROPERTY_PREFIX + xercesc::SYMBOL_TABLE_PROPERTY;
	//static const std::string GRAMMAR_POOL =
	//		xercesc::XERCES_PROPERTY_PREFIX + xercesc::XMLGRAMMAR_POOL_PROPERTY;


	/**
	* Implementation of the XBRL API Loader interface that validates using
	* a pool of preparsed XML Schemas for XBRL documents.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
	LoaderImpl::LoaderImpl() :
		cache(Cache()),
		discovering(false),
		documentId(""),
		documentQueue(std::deque<Poco::URI>()),
		documentXMLUri(Poco::URI()),
		dom(std::shared_ptr<xercesc::DOMDocument>()),
		entityResolver(EntityResolver()),
		failures(std::unordered_map<Poco::URI, std::string>()),
		fragmentId(0),
		history(HistoryImpl()),
		interrupt(false),
		store(Store()),
		successes(std::deque<Poco::URI>()),
		xlinkProcessor(XLinkProcessor()),
		_useSchemaLocationAttributes(false)
	{
	}
	LoaderImpl::LoaderImpl(Store& store) : LoaderImpl()
	{
		setStore(store);
	}

	bool LoaderImpl::operator==(LoaderImpl& rhs)
	{

		//if (cache == rhs.cache &&
		//discovering == rhs.discovering &&
		//documentId == rhs.documentId &&
		//documentQueue == rhs.documentQueue &&
		//documentXMLUri == rhs.documentXMLUri &&
		//dom == rhs.dom &&
		//entityResolver == rhs.entityResolver &&
		//failures == rhs.failures &&
		//fragmentId == rhs.fragmentId &&
		//history == rhs.history &&
		//interrupt == rhs.interrupt &&
		//store == rhs.store &&
		//successes == rhs.successes &&
		//xlinkProcessor == rhs.xlinkProcessor &&
		//_useSchemaLocationAttributes == rhs._useSchemaLocationAttributes)
		//	return true;
		return false;
	}
	LoaderImpl::LoaderImpl(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver) 
		: LoaderImpl()
	{
		setStore(store);
		setXlinkProcessor(xlinkProcessor);
		setEntityResolver(entityResolver);
		initialize();
	}

	/**
	* @param store The data store to hold the DTS
	* @param xlinkProcessor The XLink processor to use for link resolution
	* @param entityResolver The entity resolver to use for resources being loaded.
	* @param uris The array of URIs for loading.* @throws XBRLException if the loader cannot be instantiated.
	*/
	LoaderImpl::LoaderImpl(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver,		
		const std::vector<Poco::URI> uris) : 
		xlinkProcessor(std::move(xlinkProcessor)), 
		entityResolver(std::move(entityResolver))	
	{
		setStore(store);
		stashURIs(uris);								
	}
	LoaderImpl& LoaderImpl::operator=(LoaderImpl&& rhs)
	{
		if (this != &rhs)
		{
			setCache(rhs.cache);
			discovering = rhs.discovering;
			documentId = rhs.documentId;
			documentQueue = rhs.documentQueue;
			documentXMLUri = rhs.documentXMLUri;
			dom = rhs.dom;
			entityResolver = std::move(rhs.entityResolver);
			failures = rhs.failures;
			fragmentId = rhs.fragmentId;
			interrupt = rhs.interrupt;
			store = rhs.store;
			successes = rhs.successes;
			xlinkProcessor = std::move(rhs.xlinkProcessor);
			_useSchemaLocationAttributes = rhs._useSchemaLocationAttributes;
		}
		return *this;
	}
	//
	//    /**
	//     * @see Loader#requestInterrupt()
	//     */
	//    public void requestInterrupt() {
	//        interrupt = true;
	//    }
	//    
	/**
	* @return true if an interrupt to the loading process 
	* has been requested and false otherwise.
	*/
	bool LoaderImpl::interruptRequested()
	{
		return interrupt;
	}
	
	    /**
	     * @see org.xbrlapi.loader.Loader#cancelInterrupt()
	     */
	    void LoaderImpl::cancelInterrupt() 
		{
	        interrupt = false;
	    }
	   
	/**
	* @see org.xbrlapi.loader.Loader#setCache(Cache)
	*/
	void LoaderImpl::setCache(Cache& rhs)
	{
			//if (cache != nullptr)
			//	cache = std::move(rhs);
			//else
				cache.swap(rhs);
	}

	void LoaderImpl::setCache(Cache&& cache)
	{
		setCache(std::ref(cache));
	}

	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#getCache()
	//     */
	//    public Cache getCache() {
	//        if (this.cache == null)
	//            throw new XBRLException(
	//                    "The loader cache is null and so cannot be used.");
	//        return this.cache;
	//    }
	//    
	//    /**
	//     * @see Loader#getBuilderDOM()
	//     */
	//    public Document getBuilderDOM() {
	//        if (this.dom == null) {
	//            this.dom = (new XMLDOMBuilder()).newDocument();
	//        }
	//        return this.dom;
	//    }
	//    

	void LoaderImpl::setDiscovering(bool value) 
	{
		//if (value) logger.debug(Thread.currentThread().getName() + " starting discovery.");
		//else logger.debug(Thread.currentThread().getName() + " stopping discovery.");
		discovering = value;
	}
	    
	    /**
	     * @see Loader#isDiscovering()
	     */
	    bool LoaderImpl::isDiscovering() 
		{
	        return discovering;
	    }
	
	/**
	* Set the data store to be used by the loader.
	* @throws XBRLException if the given store is null.
	*/
	void LoaderImpl::setStore(Store& store)
	{
		this->store = store; 
	}

	/**
	* Get the data store used by a loader.
	*/
	Store LoaderImpl::getStore() 
	{
		return std::move(store);
	}

	/**
	* Set the Poco::URI of the document now being parsed and set the
	* document ID for the document being parsed by using the store
	* to generate the ID from the URI.  The document ID is used as
	* part of the fragment naming scheme in the data store.
	* @param uri The Poco::URI of the document now being parsed.
	* @throws XBRLException.
	*/
	void LoaderImpl::setDocumentURI(const Poco::URI& uri)
	{
		documentXMLUri = uri;
		std::string identifier = getHistory().getIdentifier(uri);
		if (identifier == "") 
		{
			documentId = store.getId(uri.toString());
			getHistory().addRecord(uri,documentId);
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
	//
	//    /**
	//     * Get the Poco::URI for the document being parsed.
	//     * @return The original (non-cache) Poco::URI of the document being parsed.
	//     */
	//    public Poco::URI getDocumentURI() {
	//        return this.documentURI;
	//    }1 mnw
	//
	/**
	* Set the XLink processor used by the loader.
	* @throws XBRLException if the given XLink processor is null.
	*/
	void LoaderImpl::setXlinkProcessor(XLinkProcessor& xlp)
	{
		xlinkProcessor = std::move(xlp);
	}
	//
	//    /**
	//     * @see Loader#getXlinkProcessor()
	//     */
	//    public LoaderImpl::XLinkProcessor getXlinkProcessor() {
	//        return xlinkProcessor;
	//    }
	//
	//    /**
	//     * @see Loader#updateState(ElementState)
	//     */
	//    public void LoaderImpl::updateState(ElementState state) {
	//
	//        if (getStates().peek() == state) {
	//            this.removeFragment();
	//        }
	//    }
	//    
	//    /**
	//     * @return the stack of element states for the root
	//     * elements of the fragments currently being built.
	//     */
	//    private std::stack<ElementState> LoaderImpl::getStates() {
	//        return this.states;
	//    }        
	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#getFragment()
	//     */
	//    public Fragment LoaderImpl::getFragment() {
	//        if (fragments.isEmpty()) return null;
	//        return fragments.peek();
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.loader.Loader#replaceCurrentFragment(Fragment)
	//     */
	//    public void LoaderImpl::replaceCurrentFragment(const Fragment& replacement) {
	//        if (fragments.isEmpty()) throw new XBRLException("There is no current fragment to replace.");
	//        fragments.pop();
	//        fragments.push(replacement);
	//    }    
	//    /**
	//     * @see org.xbrlapi.loader.Loader#isBuildingAFragment()
	//     */
	//    public bool LoaderImpl::isBuildingAFragment() {
	//        return (!fragments.isEmpty());
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#add(Fragment, ElementState)
	//     */
	//    public void LoaderImpl::add(const Fragment& fragment, ElementState state)
	//            {
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
	//            if (parentIndex == null) throw new XBRLException("The parent index is null.");
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
	//    }
	//    
	//
	//
	//    /**
	//     * Remove a fragment from the stack of fragments that 
	//     * are being built by the loader.
	//     * @throws XBRLException if their are no fragments being built.
	//     */
	//    private Fragment LoaderImpl::removeFragment() {
	//        try {
	//            
	//            getStates().pop();
	////            getChildrenStack().pop();
	//            Fragment f = fragments.pop();
	//            store.persist(f);
	//            return f;
	//        } catch (EmptyStackException e) {
	//            throw new XBRLException(this.getDocumentURI() + " There are no fragments being built.  The stack of fragments is empty.",e);
	//        }
	//    }
	//
	/**
	* @see Loader#discover(List)
	*/
	void LoaderImpl::discover(const std::vector<Poco::URI>& startingURIs)
	{
		for (auto uri : startingURIs) 
			stashURI(uri);
		discover();
	}

	/**
	* @see org.xbrlapi.loader.Loader#discover(Poco::URI)
	*/
	void LoaderImpl::discover(const Poco::URI& uri)
	{
		stashURI(uri);
		discover();
	}

	/**
	* @see org.xbrlapi.loader.Loader#discover(String)
	*/
	void LoaderImpl::discover(wchar_t* uri)
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

	//    /**
	//     * @see org.xbrlapi.loader.Loader#getDocumentsStillToAnalyse()
	//     */
	//    public std::vector<Poco::URI> getDocumentsStillToAnalyse() {
	//        std::vector<Poco::URI> documents = new Vector<Poco::URI>();
	//        documents.addAll(documentQueue);
	//        return documents;
	//    }


	/**
	* @see org.xbrlapi.loader.Loader#discover()
	*/
	void LoaderImpl::discover()
	{
		store.startLoading();

		std::set<Poco::URI> newDocuments;

		int discoveryCount = 1;

		if (isDiscovering()) 
		{
			//							logger.warn("The loader is already doing discovery so starting discovery achieves nothing.");
			std::cout<< "The loader is already doing discovery so starting discovery achieves nothing." << std::endl;
			return;
		}
		setDiscovering(true);

		for (const Poco::URI& uri : store.getDocumentsToDiscover()) 
		{
			//	logger.info(uri + " stashed for discovery.");
			stashURI(uri);
		}

		Poco::URI uri = getNextDocumentToExplore();
		while (&uri != nullptr) 
		{
			bool documentClaimedByThisLoader = store.requestLoadingRightsFor(*this,uri);
			if (! documentClaimedByThisLoader) 
			{
				markDocumentAsExplored(uri);
				uri = getNextDocumentToExplore();
				continue;
			}

			//	long start = System.currentTimeMillis(); //TODO use <chrono> here

			if (!store.hasDocument(uri)) 
			{
				setDocumentURI(uri);
				setNextFragmentId("1");
				//	try {
				parse(uri);
				//			long duration = (System.currentTimeMillis() - start) / 1000; //TODO use <chrono> here
				//	logger.info("#" + discoveryCount + " took " + duration + " seconds. " + (fragmentId-1) + " fragments in " + uri);
				discoveryCount++;
				markDocumentAsExplored(uri);
				newDocuments.insert(uri);
				store.sync();
				//} catch (XBRLException e) {
				//	this.cleanupFailedLoad(uri,"XBRL-API related problems occurred: " + e.getMessage(),e);
				//} catch (SAXException e) {
				//	this.cleanupFailedLoad(uri,"The document could not be parsed.",e);
				//} catch (IOException e) {
				//	this.cleanupFailedLoad(uri,"The document could not be accessed.",e);
				//}
			} 
			else 
			{
				//		logger.debug(uri + " is already in the data store.");
				markDocumentAsExplored(uri);
			}

			if (interruptRequested()) 
			{
				cancelInterrupt();
				break;
			}

			uri = getNextDocumentToExplore();
		}

		//storeDocumentsToAnalyse();
		//setDiscovering(false);

		//if (documentQueue.size() == 0 && failures.size() == 0) 
		//{
		//	//		logger.debug("Document discovery completed successfully.");
		//} else 
		//{
		//	if (failures.size() > 0) 
		//	{
		//		//			logger.warn("Some documents failed to load.");
		//	}
		//	if (documentQueue.size() > 0) 
		//	{
		//		//		logger.info("Document discovery exited without completing.");
		//	}
		//}

//		store.stopLoading(*this); //TODO

		//	try {
		//if (store.isPersistingRelationships() && (newDocuments.size() > 0)) 
		//{

		//	// Wait till other loaders using the store have finished with their loading activities.
		//	while (store.isLoading()) 
		//	{
		//		//	logger.debug("Still doing some loading into the store ... ");
		//		//					Thread.sleep(10000); //TODO
		//	}
		//	StorerImpl storer(store);
		//	storer.storeRelationships(newDocuments);
		//}
		/*	} catch (InterruptedException e) 
		{
		logger.error("Failed to persist relationships.");
		std::unordered_map<Poco::URI,std::string> map = new HashMap<Poco::URI,std::string>();
		for (const Poco::URI& document : newDocuments) 
		{
		map.put(store.getMatcher().getMatch(document),"Failed to store relationships.");
		}
		store.persistLoaderState(map);
		}*/

		std::map<Poco::URI,std::string> failures;
		std::deque<Poco::URI> documentQueue;

	}

	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#discoverNext()
	//     */
	//    public void LoaderImpl::discoverNext() {
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
	//        bool documentClaimedByThisLoader = store.requestLoadingRightsFor(*this,uri);
	//        while ((store.hasDocument(uri) || !documentClaimedByThisLoader) && (uri != null)) {
	//            if (documentClaimedByThisLoader) {
	//                store.recindLoadingRightsFor(this,uri);
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
	//    /**
	//     * Perform a discovery starting with an XML document that is represented as
	//     * a string.
	//     * 
	//     * @param uri
	//     *            The Poco::URI to be used for the document that is supplied as a
	//     *            string. This Poco::URI MUST be an absolute URI.
	//     * @param xml
	//     *            The string representation of the XML document to be parsed.
	//     * @throws XBRLException
	//     *             if the discovery process fails or if the supplied Poco::URI is not
	//     *             absolute or is not a valid Poco::URI syntax or the loader does not
	//     *             have a cache.
	//     */
	//    public void LoaderImpl::discover(const Poco::URI& uri, const std::string& xml) {
	//
	//        logger.debug("Discovering a resource supplied as a string and with URI: " + uri);
	//
	//        if (!uri.isAbsolute()) throw new XBRLException("The Poco::URI " + uri + " must be absolute.");
	//
	//        if (uri.isOpaque()) throw new XBRLException("The Poco::URI " + uri + " must NOT be opaque.");
	//
	//        // Copy the XML to the local cache even if it is there already (possibly over-writing existing documents)
	//        this.getCache().copyToCache(uri, xml);
	//
	//        try {
	//            this.stashURI(new URI("http://www.xbrlapi.org/xbrl/xbrl-2.1-roles.xsd"));
	//        } catch (XMLUriSyntaxException e) {
	//            throw new XBRLException("The standard roles Poco::URI could not be formed for discovery.",e);
	//        }
	//        
	//        discover(uri);
	//    }
	//

	/**
	* Retrieve Poco::URI of the next document to parse from the list of starting
	* point URIs provided or URIs found during the discovery process.
	* @return the Poco::URI of the next document to explore or null if there are none.
	* @throws XBRLException
	*/
	Poco::URI LoaderImpl::getNextDocumentToExplore() 
	{
		if (documentQueue.empty()) return Poco::URI();
		auto ret = documentQueue.front();
		documentQueue.pop_front();
		return ret;
	}

	/**
	* Flag the document as being explored.  Ensure that loading
	* rights for this document have been recinded so that other
	* loaders can act as they deem appropriate.
	* @throws XBRLException
	*/
	void LoaderImpl::markDocumentAsExplored(const Poco::URI& uri) 
	{
		documentQueue.pop_front();
		successes.push_back(uri);
//		store.recindLoadingRightsFor(*this,uri); //TODO
	}
	
	    /**
	     * Parse an XML Document supplied as a URI.
	     * @param uri The Poco::URI of the document to parse.
	     * @throws XBRLException IOException ParserConfigurationException SAXException
	     * @throws ParserConfigurationException 
	     */
		void LoaderImpl::parse(const Poco::URI& uri)
		{
			xercesc::InputSource* inputSource =  entityResolver.resolveEntity(L"", getWC(uri.toString()).c_str());
	        ContentHandler contentHandler(*this, uri);
	        parse(uri, *inputSource, contentHandler);
	    }
	
	    /**
	     * Parse an XML Document supplied as a string the next part of the DTS.
	     * @param uri The Poco::URI to associate with the supplied XML.
	     * @param xml The XML document as a string.
	     * @throws XBRLException IOException SAXException ParserConfigurationException
	     */
	 //   void LoaderImpl::parse(const Poco::URI& uri, const std::string& xml)
		//{
	 //       xercesc::InputSource* inputSource = new InputSource(new StringReader(xml));
	 //       ContentHandler contentHandler = new ContentHandlerImpl(this, uri, xml);
	 //       parse(uri, inputSource, contentHandler);
	 //   }



	/**
	* Set the starting points for DTSImpl discovery using a linked list
	* @param uris A list of starting point document URIs for DTSImpl discovery
	* @throws XBRLException
	*/
	void LoaderImpl::setStartingURIs(const std::vector<Poco::URI>& uris) 
	{
		//if (uris == null)
		//    throw new XBRLException("Null list of URIs is not permitted.");

		for (const auto e : uris ) 
		{
			stashURI(e);
		}
	}

	/**
	* @see org.xbrlapi.loader.Loader#stashURI(Poco::URI)
	*/
	//synchronized 
	void LoaderImpl::stashURI(const Poco::URI& uri)
	{

		// Validate the URI
		if (uri.isRelative()) 
		{
			//throw new XBRLException("The URI: " + uri + " must be absolute.");
			std::cout << "The URI: " <<  uri.toString() << " must be absolute." << std::endl;
		}

		if (uri.getScheme()[0] == '/') 
		{
			//				throw new XBRLException("The URI: " + uri + " must not be opaque.");                
			std::cout << "The URI: " <<  uri.toString() << " must not be opaque." << std::endl;
		}

		//try {

		Poco::URI dereferencedXMLUri(uri.getScheme(),uri.getAuthority(), uri.getPath());
		//} catch (XMLUriSyntaxException e) {
		//	throw new XBRLException("Malformed Poco::URI found in DTS discovery process: " + uri, e);
		//}

		// Stash the Poco::URI if it has not already been stashed
		if (std::find(successes.begin(), successes.end(), dereferencedXMLUri) == successes.end()) 
		{
			// Queue up the original Poco::URI - ignoring issues of whether it matches another document.
			documentQueue.push_back(dereferencedXMLUri);
		}

	}

	/**
	* @see Loader#stashURIs(List)
	*/
	void LoaderImpl::stashURIs(const std::vector<Poco::URI>& uris) 
	{
		for (const Poco::URI& uri: uris) 
		{
			stashURI(uri);
		}
	}

	/**
	* Set the resolver for the resolution of entities found during the loading
	* and XLink processing.
	* @param resolver An entity resolver implementation or null if you want to use 
	* a default entity resolver (without any caching facilities)
	*/
	void LoaderImpl::setEntityResolver(EntityResolver& resolver) 
	{
		//	if (&resolver == nullptr) entityResolver = new EntityResolverImpl();
		entityResolver = std::move(resolver);
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

	/**
	* Used to set the next fragment id using the information in the data store.
	* This is useful when coming back to an existing data store to add
	* additional documents.
	* 
	* @param id
	* @throws XBRLException
	*/
	void LoaderImpl::setNextFragmentId(const std::string& id) 
	{
	    fragmentId = std::stoi(id);
	}

	/**
	* Return the entity resolver being used by the loader.
	* 
	* @return the entity resolver being used by the loader.
	*/
	EntityResolver* LoaderImpl::getEntityResolver() 
	{
		return &entityResolver;
	}
	//
	//    private bool useSchemaLocationAttributes = false;
	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#useSchemaLocationAttributes()
	//     */
	//    public bool useSchemaLocationAttributes() {
	//        return this.useSchemaLocationAttributes;
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#setSchemaLocationAttributeUsage(bool)
	//     */
	//    public void setSchemaLocationAttributeUsage(bool useThem) {
	//        this.useSchemaLocationAttributes = useThem;
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.loader.Loader#storeDocumentsToAnalyse()
	//     */
	//    public void LoaderImpl::storeDocumentsToAnalyse() {
	//        Map<Poco::URI,std::string> map = new HashMap<Poco::URI,std::string>();
	//        for (const Poco::URI& document : documentQueue) {
	//            if (document.equals(store.getMatcher().getMatch(document))) {
	//                map.put(document,"Document has not yet been analysed");
	//            }
	//        }
	//        for (const Poco::URI& document : failures.keySet()) {
	//            map.put(document,failures.get(document));
	//        }
	//        if (map.size() > 0)  {
	//            logger.warn("Storing details of " + map.size() + " documents that are yet to be loaded.");
	//            store.persistLoaderState(map);
	//        }
	//    }
	//    
	//    private void LoaderImpl::cleanupFailedLoad(const Poco::URI& uri, const std::string& reason, Exception e) {
	//        logger.error(getDocumentURI() + " encountered a loading problem: " + e.getMessage());
	//        failures.put(uri,reason);
	//        documentQueue.remove(uri);
	//        store.recindLoadingRightsFor(this,getDocumentURI());
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
	//    public int LoaderImpl::hashCode() {
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
	//    public bool LoaderImpl::equals(Object obj) {
	//        if (this == obj)
	//            return true;
	//        if (obj == null)
	//            return false;
	//        if (getClass() != obj.getClass())
	//            return false;
	//        LoaderImpl other = (LoaderImpl) obj;
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
	//    private void LoaderImpl::readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
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
	//    private void LoaderImpl::writeObject(java.io.ObjectOutputStream out) throws IOException {
	//        if (this.isDiscovering()) throw new IOException("The loader could not be serialized because it is still loading data.");
	//        out.defaultWriteObject();
	//    }    
	// 
	//    /**
	//     * @see Loader#setHistory(History)
	//     */
	//    public void LoaderImpl::setHistory(const HistoryImpl& newHistory) {
	//        if (newHistory == null) this.history = new HistoryImpl();
	//        this.history = newHistory;
	//    }
	//
	/**
	* @see Loader#getHistory()
	*/
	HistoryImpl LoaderImpl::getHistory() 
	{
		return history;
	}
	//    
	//    /**
	//     * @see Loader#hasHistory()
	//     */
	//    public bool LoaderImpl::hasHistory() {
	//        return (history != null);
	//    }
	//    
	//    private transient XMLGrammarPoolImpl grammarPool = new XMLGrammarPoolImpl();
	//    private transient SymbolTable symbolTable = new SymbolTable(BIG_PRIME);

	void LoaderImpl::initialize() 
	{

		xercesc::MemoryManager *memMgr = new xercesc::MemoryManagerImpl();
		xercesc::XMLGrammarPool* grammarPool = new xercesc::XMLGrammarPoolImpl(memMgr);
		xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader(memMgr, grammarPool);

		parser->setFeature(xercesc::XMLUni::fgXercesCacheGrammarFromParse,true);
		//parser->registerPreparser(XMLGrammarDescription.XML_SCHEMA, null);

		//parser->setProperty(GRAMMAR_POOL, grammarPool);

		parser->setFeature(L"http://xml.org/sax/features/namespaces", true);
		parser->setFeature(L"http://xml.org/sax/features/validation", true);

		// note we can set schema features just in case ...
		parser->setFeature(L"http://apache.org/xml/features/validation/schema", true);
		// Checking of constraints on a schema grammar which are either time-consuming 
		// or memory intensive such as unique particle attribution
		parser->setFeature(L"http://apache.org/xml/features/validation/schema-full-checking", true);
		// All schema location hints will be used to locate the 
		// components for a given target namespace
		//parser->setFeature(L"http://apache.org/xml/features/honour-all-schemaLocations", true);

		// Specify the entity resolver to use for the schemas.
		parser->setEntityResolver(getEntityResolver());

		// parse the grammars
		std::vector<Poco::URI> schemas;
		schemas.push_back(Poco::URI("http://www.xbrlapi.org/xml/schemas/s4s.xsd"));
		schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xbrl-instance-2003-12-31.xsd"));
		schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xbrl-linkbase-2003-12-31.xsd"));
		schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xl-2003-12-31.xsd"));
		schemas.push_back(Poco::URI("http://www.xbrl.org/2003/xlink-2003-12-31.xsd"));
		//try {
			for (const Poco::URI& schema : schemas) 
			{
				// This loads the schemas into the grammar pool TODO
				//parser->loadGrammar(schema.getScheme().c_str(), xercesc::Grammar::SchemaGrammarType, false);
			}
		//} catch (Exception e) {
		//	e.printStackTrace();
		//	throw new XBRLException("The XBRL and related schemas could not be preloaded.");
		//}
		grammarPool->lockPool();
	}
	//
	//    /** Property identifier: symbol table. */
	//    public static final std::string SYMBOL_TABLE =
	//        Constants.XERCES_PROPERTY_PREFIX + Constants.SYMBOL_TABLE_PROPERTY;
	//
	//    /** Property identifier: grammar pool. */
	//    public static final std::string GRAMMAR_POOL =
	//        Constants.XERCES_PROPERTY_PREFIX + Constants.XMLGRAMMAR_POOL_PROPERTY;
	//
	//
	//
	//
	//
	//
	//
	//
	//    
	//
	//
	//    // a larg(ish) prime to use for a symbol table to be shared
	//    // among
	//    // potentially man parsers.  Start one as close to 2K (20
	//    // times larger than normal) and see what happens...
	//    public static final int BIG_PRIME = 2039;
	//    
	//    
	//    
	    /**
	     * Parse the supplied input source.
	     * @param uri The Poco::URI to be associated with the supplied input source.
	     * @param inputSource The input source to parse.
	     * @param contentHandler The content handler to use for SAX parsing.
	     * @throws XBRLException SAXException IOException
	     */
	    void LoaderImpl::parse(const Poco::URI& uri, 
							  const xercesc::InputSource& inputSource,  
							  xercesc::ContentHandler& contentHandler)
		{
			xercesc::MemoryManager *memMgr = new xercesc::MemoryManagerImpl();
			xercesc::XMLGrammarPool* grammarPool = new xercesc::XMLGrammarPoolImpl(memMgr);
			xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader(memMgr, grammarPool);
	
	        // now must reset features for actual parsing:
	        //try{
	            parser->setFeature(L"http://xml.org/sax/features/namespace-prefixes", true);
	            parser->setFeature(L"http://xml.org/sax/features/namespaces", true);
	            parser->setFeature(L"http://xml.org/sax/features/validation", true);
	            parser->setFeature(L"http://apache.org/xml/features/validation/schema", true);
	            parser->setFeature(L"http://apache.org/xml/features/validation/schema-full-checking", true);
	           // parser->setFeature(L"http://apache.org/xml/features/honour-all-schemaLocations", false); //TODO uncomment
	        //} catch (Exception e) {
	        //    throw new XBRLException("The parser features could not be set.",e);
	        //}
	        
	        parser->setEntityResolver(getEntityResolver());
			parser->setErrorHandler(static_cast<xercesc::DefaultHandler*>(&contentHandler));        
	        parser->setContentHandler(&contentHandler);        
	        parser->parse(inputSource);
	        
	    }
	
}
