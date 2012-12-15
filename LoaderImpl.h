#include "Stdafx.h"
#pragma once

#include <deque>
#include <stack>

#include <Poco/URI.h>
#include "Store.h"
#include "HistoryImpl.h"
#include "Cache.h"
#include "XLinkProcessor.h"
#include "EntityResolver.h"
#include <xercesc/sax/ErrorHandler.hpp>


namespace xbrlcapi
{
	class ContentHandler;
	/**
	* Implementation of the XBRL API LoaderImpl interface that validates using
	* a pool of preparsed XML Schemas for XBRL documents.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
	class LoaderImpl 
	{
		friend class Loader;
	private:

		//static const Logger logger = Logger.getLogger(LoaderImpl.class);

		bool _useSchemaLocationAttributes;

		/**
		* The data store to be used to hold the DTS.
		*/
		Store store;

		/**
		* The cache to use when discovering XML materials specified as a String
		* rather than just via a Poco::URI that resolves to the required XML.
		*/
		Cache cache;

		/**
		* The Xlink processor
		*/
		XLinkProcessor xlinkProcessor;

		/**
		* The entity resolver to use for resolution of entities (XMLUris etc) during
		* the loading/discovery process.
		*/
		EntityResolver entityResolver;

		/**
		* The queue of documents remaining to load.
		*/
		std::deque<Poco::URI> documentQueue;

		/**
		* The document history recording system used to track the
		* documents being loaded, their URIs and their document
		* identifiers.  This defaults to a simple one that does basic logging.
		*/
		HistoryImpl history;// = new HistoryImpl();

		/**
		* The stack of fragments that are being built
		*/
		//transient private:

		std::stack<Fragment> fragments();

		/**
		* A stack of element states, one per root element
		* of a fragment currently undergoing construction.
		*/
		//transient private:

		//std::stack<ElementState> states = new std::stack<ElementState>();

		/**
		* The absolute Poco::URI of the document currently being parsed. Used to record
		* this metadata in each fragment.
		*/
		//transient private:

		Poco::URI documentXMLUri;

		/**
		* The document Id (including the document hash and its counter)
		*/
		//transient private:

		std::string documentId;

		/**
		* The sorted map of documents that have failed to load.
		* Each Poco::URI points to value that is the reason for the failure.
		*/
		//transient private:

		std::unordered_map<Poco::URI, std::string> failures;

		/**
		* The sorted set of documents that have successfully been loaded.
		*/
		//transient private:

		std::deque<Poco::URI> successes;

		/**
		* The unique fragment ID, that will be one for the first fragment. This is
		* incremented just before as it is retrieved for use with a new fragment
		* created during the loading process.
		*/

		int fragmentId;

		/**
		* The flag, discovering, equals false if the loader is not currently doing document
		* discovery and equals true otherwise.
		*/
		//transient private:

		bool discovering;

		/**
		* bool flag that it set to true by an discovery interrupt request.
		*/
		//transient private:

		bool interrupt;

		/**
		* The XML DOM used by this loader's fragment builders.
		* This is initialised on creation of the loader.
		*/
		//transient private:

		std::shared_ptr<xercesc::DOMDocument> dom;

		/**
		* @return the stack of element states for the root
		* elements of the fragments currently being built.
		*/
		//		std::stack<ElementState> getStates();

		/**
		* Remove a fragment from the stack of fragments that 
		* are being built by the loader.
		* @throws XBRLException if their are no fragments being built.
		*/
		Fragment removeFragment();

		/**
		* Retrieve Poco::URI of the next document to parse from the list of starting
		* point URIs provided or URIs found during the discovery process.
		* @return the Poco::URI of the next document to explore or null if there are none.
		* @throws XBRLException
		*/
		Poco::URI getNextDocumentToExplore();

		//		void cleanupFailedLoad(const Poco::URI& uri, std::string reason, Exception e);

		/**
		* Handles object inflation.
		* @param in The input object stream used to access the object's serialization.
		* @throws IOException
		* @throws ClassNotFoundException
		*/
		//		void readObject(ObjectInputStream in);

		/**
		* Handles object serialization
		* @param out The input object stream used to store the serialization of the object.
		* @throws IOException if the loader is still doing discovery.
		*/
		//void writeObject(java.io.ObjectOutputStream out);

		//XMLGrammarPoolImpl grammarPool = new XMLGrammarPoolImpl();
		//SymbolTable symbolTable = new SymbolTable(BIG_PRIME);

		void initialize();

		/**
		* Set the Poco::URI of the document now being parsed and set the
		* document ID for the document being parsed by using the store
		* to generate the ID from the URI.  The document ID is used as
		* part of the fragment naming scheme in the data store.
		* @param uri The Poco::URI of the document now being parsed.
		* @throws XBRLException.
		*/
		void LoaderImpl::setDocumentURI(const Poco::URI& uri);
		/**
		* @return true if an interrupt to the loading process 
		* has been requested and false otherwise.
		*/
		bool LoaderImpl::interruptRequested();
	protected:
		/**
		* Flag the document as being explored.  Ensure that loading
		* rights for this document have been recinded so that other
		* loaders can act as they deem appropriate.
		* @throws XBRLException
		*/
		void markDocumentAsExplored(const Poco::URI& uri);

		/**
		* Parse an XML Document supplied as a URI.
		* @param uri The Poco::URI of the document to parse.
		* @throws XBRLException IOException ParserConfigurationException SAXException
		* @throws ParserConfigurationException 
		*/
		void parse(const Poco::URI& uri);

		/**
		* Parse an XML Document supplied as a string the next part of the DTS.
		* @param uri The Poco::URI to associate with the supplied XML.
		* @param xml The XML document as a string.
		* @throws XBRLException IOException SAXException ParserConfigurationException
		*/
		void parse(const Poco::URI& uri, const std::string& xml);


		/**
		* Set the starting points for DTSImpl discovery using a linked list
		* @param uris A list of starting point document URIs for DTSImpl discovery
		* @throws XBRLException
		*/
		void setStartingURIs(const std::vector<Poco::URI>& uris);

		/**
		* Parse the supplied input source.
		* @param uri The Poco::URI to be associated with the supplied input source.
		* @param inputSource The input source to parse.
		* @param contentHandler The content handler to use for SAX parsing.
		* @throws XBRLException SAXException IOException
		*/
		void parse(const Poco::URI& uri, /*const*/ xercesc::InputSource& inputSource, xercesc::ErrorHandler& contentHandler);

		void setDiscovering(bool value);

		/**
		* Used to set the next fragment id using the information in the data store.
		* This is useful when coming back to an existing data store to add
		* additional documents.
		* 
		* @param id
		* @throws XBRLException
		*/
		void setNextFragmentId(const std::string& id);

	public:
		LoaderImpl& LoaderImpl::operator=(LoaderImpl&& rhs);
		bool LoaderImpl::operator==(LoaderImpl& rhs);
		virtual ~LoaderImpl() {}

		/**
		* @param store The data store to hold the DTS
		* @param xlinkProcessor The XLink processor to use for link resolution
		* @throws XBRLException if the loader cannot be instantiated.
		*/
		LoaderImpl();
		LoaderImpl(Store& store);
		LoaderImpl(const LoaderImpl& rhs); // TODO make private
		LoaderImpl(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver);

		/**
		* @param store The data store to hold the DTS
		* @param xlinkProcessor The XLink processor to use for link resolution
		* @param entityResolver The entity resolver to use for resources being loaded.
		* @param uris The array of URIs for loading.
		* @throws XBRLException if the loader cannot be instantiated.
		*/
		LoaderImpl(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver,		
			const std::vector<Poco::URI> uris);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#setCache(Cache)
		*/
		void setCache(Cache& cache);

		void setCache(Cache&& cache);

		/**
		* Set the data store to be used by the loader.
		* @throws XBRLException if the given store is null.
		*/
		void setStore(Store& store);

		/**
		* Get the data store used by a loader.
		*/
		Store getStore();
		/**
		* Set the XLink processor used by the loader.
		* @throws XBRLException if the given XLink processor is null.
		*/
		void setXlinkProcessor(XLinkProcessor& xlinkProcessor);

		/**
		* @see LoaderImpl#getXlinkProcessor()
		*/
		XLinkProcessor getXlinkProcessor();

		/**
		* @see LoaderImpl#updateState(ElementState)
		*/
		//		void updateState(const ElementState& state);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#getFragment()
		*/
		Fragment getFragment();

		/**
		* @see org.xbrlapi.loader.LoaderImpl#replaceCurrentFragment(Fragment)
		*/
		void replaceCurrentFragment(const Fragment& replacement);
		/**
		* @see org.xbrlapi.loader.LoaderImpl#isBuildingAFragment()
		*/
		bool isBuildingAFragment();

		bool LoaderImpl::isDiscovering();

		/**
		* @see org.xbrlapi.loader.LoaderImpl#add(Fragment, ElementState)
		*/
		//		void add(const Fragment& fragment, const ElementState& state);

		/**
		* @see LoaderImpl#discover(List)
		*/
		void discover(const std::vector<Poco::URI>& startingURIs);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#discover(Poco::URI)
		*/
		void discover(const Poco::URI& uri);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#discover(String)
		*/
		void discover(wchar_t* uri);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#getDocumentsStillToAnalyse()
		*/
		std::vector<Poco::URI> getDocumentsStillToAnalyse();


		/**
		* @see org.xbrlapi.loader.LoaderImpl#discover()
		*/
		void discover();

		/**
		* @see org.xbrlapi.loader.LoaderImpl#discoverNext()
		*/
		void discoverNext();

		/**
		* Perform a discovery starting with an XML document that is represented as
		* a string.
		* 
		* @param uri
		*            The Poco::URI to be used for the document that is supplied as a
		*            string. This Poco::URI MUST be an absolute URI.
		* @param xml
		*            The string representation of the XML document to be parsed.
		* @throws XBRLException
		*             if the discovery process fails or if the supplied Poco::URI is not
		*             absolute or is not a valid Poco::URI syntax or the loader does not
		*             have a cache.
		*/
		void discover(const Poco::URI& uri, const std::string& xml);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#stashURI(Poco::URI)
		*/
		//synchronized 
		void stashURI(const Poco::URI& uri);

		/**
		* @see LoaderImpl#stashURIs(List)
		*/
		void stashURIs(const std::vector<Poco::URI>& uris);

		/**
		* Set the resolver for the resolution of entities found during the loading
		* and XLink processing.
		* @param resolver An entity resolver implementation or null if you want to use 
		* a default entity resolver (without any caching facilities)
		*/
		void setEntityResolver(EntityResolver& resolver);

		//public:
		std::string getNextFragmentId();

		//public:
		std::string getCurrentFragmentId();

		//public:
		void incrementFragmentId();


		/**
		* Return the entity resolver being used by the loader.
		* 
		* @return the entity resolver being used by the loader.
		*/
		EntityResolver* getEntityResolver();

		/**
		* @see org.xbrlapi.loader.LoaderImpl#useSchemaLocationAttributes()
		*/
		bool useSchemaLocationAttributes();

		/**
		* @see org.xbrlapi.loader.LoaderImpl#setSchemaLocationAttributeUsage(bool)
		*/
		void setSchemaLocationAttributeUsage(bool useThem);

		/**
		* @see org.xbrlapi.loader.LoaderImpl#storeDocumentsToAnalyse()
		*/
		void storeDocumentsToAnalyse();

		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
//		bool equals(Object obj);

		/**
		* @see LoaderImpl#setHistory(HistoryImpl)
		*/
		void setHistory(const HistoryImpl& newHistory);

		/**
		* @see LoaderImpl#getHistory()
		*/
		HistoryImpl getHistory();

		/**
		* @see LoaderImpl#hasHistory()
		*/
		bool hasHistory();

		void cancelInterrupt();


		/** Property identifier: symbol table. */
		static const std::string SYMBOL_TABLE;

		/** Property identifier: grammar pool. */
		static const std::string GRAMMAR_POOL;

		// a larg(ish) prime to use for a symbol table to be shared
		// among
		// potentially man parsers.  Start one as close to 2K (20
		// times larger than normal) and see what happens...
		static const int BIG_PRIME = 2039;
	};
}
