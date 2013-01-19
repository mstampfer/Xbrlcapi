#pragma once
#include "Constants.h"
#include "FragmentFactory.h"
#include "Loader.h"
#include "Store.h"
#include "Stub.h"
#include "Winsock2.h"
#include "XBRLException.h"
#include "XML.h"
#include "XercesString.h"
#include "HashFunctions.h"
#include "Analyser.h"

#include "XmlInputStreamWrapper.hpp"
#include "DefaultMatcher.h"
#include "XBRLException.h"
#include "XMLDOMSerializer.h"
#include "Builder.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <Poco/URI.h>
#include <db_cxx.h>
#include <dbxml/DbXml.hpp>
#include <dbxml/XmlException.hpp>
#include <dbxml/XmlManager.hpp>
#include <dbxml/XmlQueryContext.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSException.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>

#include <stdexcept>
#include <exception> //ecxeption (base class)
#include <new>       //bad_alloc
#include <typeinfo>  //bad_cast und bad_typeid
#include <ios>       //ios_base::failure  

namespace xbrlcapi
{ 

	struct Store::Impl
	{
		const Store* outer;
		std::shared_ptr<xercesc::DOMImplementationLS> domImplementationRegistry;
		int loadingStatus;
		//			std::map<Poco::URI,boost::uuids::uuid> loadingRights;
		std::unordered_set<Poco::URI> uris;
		std::shared_ptr<xercesc::DOMDocument> storedom;
		std::shared_ptr<xercesc::DOMImplementationLS> domimplementation;
		/**
		* This property is used to co-ordinate the document
		* loading activities of loaders that are operating in
		* parallel on the one data store.  It is used to 
		* prevent the same document from being simultaneously
		* loaded by several of the loaders.
		*/
		std::unordered_map<Poco::URI,boost::uuids::uuid> loadingRights;		    	    
		/**
		* resource matcher
		*/
		DefaultMatcher matcher;
		/**
		* Namespace bindings map from prefix to namespace.
		*/
		std::unordered_map<std::string,std::string> namespaceBindings;   
		// The indexing specification of a container
		//DbXml::XmlIndexSpecification xis;
		std::string computerIdentity;
		std::string locationName;
		std::string containerName;
		std::shared_ptr<DbEnv> environment;
		int cacheSize;
		std::shared_ptr<DbXml::XmlManager> dataManager;
		std::chrono::time_point<std::chrono::system_clock> lastSync;
		DbXml::XmlContainer dataContainer;
		/**
		* Defines the default evaluation approach.
		*/
		int queryEvaluationType;
		Analyser analyser;
		static const 	u_int32_t env_flags = DB_CREATE     |  // If the environment does not exist, create it.
			DB_INIT_LOCK  |  // Initialize locking
			DB_INIT_LOG   |  // Initialize logging
			DB_INIT_MPOOL |  // Initialize the cache
			DB_INIT_TXN	|  // Initialize transactions
			DB_THREAD ;	   // 
		boost::uuids::uuid loader;

		Impl() {}

		/**
		* This uses the default 1 GB cache size.
		* @param location The location of the database (The path to where the database exists)
		* @param container The name of the container to hold the data in the store.
		* @throws XBRLException
		*/
		Impl(const Store* store, const std::string& location, const std::string& container, const boost::uuids::uuid& loader) :
			outer(store),
			locationName(location), 
			containerName(container),
			cacheSize(1024 * 1024 * 1024),
			queryEvaluationType(DbXml::XmlQueryContext::Eager),
			loader(loader)
		{
			initialize(location,container);
		}

		/**
		* @param location The location of the database (The path to where the database exists)
		* @param container The name of the container to hold the data in the store.
		* @param cacheSize The number of megabytes to use for the cache size.
		* @throws XBRLException
		*/
		Impl(const Store* store, const std::string& location, const std::string& container, int cacheSize, const boost::uuids::uuid& loader) :
			outer(store),
			locationName(location), 
			containerName(container),
			cacheSize(cacheSize * 1024*1024),
			queryEvaluationType(DbXml::XmlQueryContext::Eager),
			loader(loader)
		{
			initialize(location,container);
		} 

		/**
		* This uses the default 1 GB cache size.
		* @param location The location of the database (The path to where the database exists)
		* @param container The name of the container to hold the data in the store.
		* @throws XBRLException
		*/
		Impl(const Store* store, const std::string& location, const std::string& container) :
			outer(store),
			locationName(location), 
			containerName(container),
			cacheSize(1024 * 1024 * 1024),
			queryEvaluationType(DbXml::XmlQueryContext::Eager)
		{
			initialize(location,container);
		}

		/**
		* @param location The location of the database (The path to where the database exists)
		* @param container The name of the container to hold the data in the store.
		* @param cacheSize The number of megabytes to use for the cache size.
		* @throws XBRLException
		*/
		Impl(const Store* store, const std::string& location, const std::string& container, int cacheSize) :
			outer(store),
			locationName(location), 
			containerName(container),
			cacheSize(cacheSize * 1024*1024),
			queryEvaluationType(DbXml::XmlQueryContext::Eager)
		{
			initialize(location,container);
		} 

		Impl(const Impl& rhs) :	
			cacheSize(rhs.cacheSize),
			computerIdentity(rhs.computerIdentity),
			containerName(rhs.containerName),
			dataContainer(rhs.dataContainer),
			dataManager(rhs.dataManager),
			domimplementation(rhs.domimplementation),
			domImplementationRegistry(rhs.domImplementationRegistry),
			environment(rhs.environment),
			lastSync(rhs.lastSync),
			loadingRights(rhs.loadingRights),
			loadingStatus(rhs.loadingStatus),
			locationName(rhs.locationName),
			matcher(rhs.matcher),
			namespaceBindings(rhs.namespaceBindings),
			queryEvaluationType(rhs.queryEvaluationType),
			storedom(rhs.storedom),
			uris(rhs.uris),
			loader(rhs.loader)
		{
			//		outer = rhs.outer;
		}

		//Impl& operator=(Impl&& rhs)
		//{
		//	if (this != &rhs)
		//	{
		//		outer = std::move(rhs.outer);
		//		cacheSize = std::move(rhs.cacheSize);
		//		computerIdentity = std::move(rhs.computerIdentity);
		//		containerName = std::move(rhs.containerName);
		//		dataContainer = std::move(rhs.dataContainer);
		//		dataManager = rhs.dataManager;
		//		domimplementation = std::move(rhs.domimplementation);
		//		domImplementationRegistry = std::move(rhs.domImplementationRegistry);
		//		environment = std::move(rhs.environment);
		//		lastSync = std::move(rhs.lastSync);
		//		loadingRights = std::move(rhs.loadingRights);
		//		loadingStatus = std::move(rhs.loadingStatus);
		//		locationName = std::move(rhs.locationName);
		//		//			logger = rhs.logger;
		//		matcher = std::move(rhs.matcher);
		//		namespaceBindings = std::move(rhs.namespaceBindings);
		//		queryEvaluationType = std::move(rhs.queryEvaluationType);
		//		storedom = std::move(rhs.storedom);
		//		uris = std::move(rhs.uris);
		//		loader = rhs.loader
		//	}
		//	return *this;
		//}

		void setLoader( const boost::uuids::uuid& rhs)
		{
			loader = rhs;
		}
		std::string getComputerName()
		{
			//try
			WSADATA WSAData;;
			// Initialize winsock dll
			if(::WSAStartup(MAKEWORD(1, 0), &WSAData))
				std::cout << "Failed to find the WinSock DLL" << std::endl;

			char szHostName[128] = "";
			if(::gethostname(szHostName, sizeof(szHostName)))   
				std::cout << "Failed to resolve the host name" <<std::endl;

			struct hostent *pHost = 0;
			struct sockaddr_in SocketAddress;
			pHost = ::gethostbyname(szHostName);
			if(!pHost)
				std::cout << "Failed to resolve the host IP address" <<std::endl;

			char aszIPAddresses[10][16]; // maximum of ten IP addresses

			for(int nCount = 0; ((pHost->h_addr_list[nCount]) && (nCount < 10)); ++nCount)
			{
				memcpy(&SocketAddress.sin_addr, pHost->h_addr_list[nCount], pHost->h_length);
				strcpy(aszIPAddresses[nCount], inet_ntoa(SocketAddress.sin_addr));
			}
			//        } catch (UnknownHostException e) {
			//            throw XBRLException("The computer identity could not be obtained.", e);
			//        }
			return std::string(szHostName) + "." + std::string(aszIPAddresses[0]);
		}

		void initialize(const std::string& location, const std::string& container)
		{
			computerIdentity = getComputerName();

			if (!location.empty() && location != "") locationName = location;
			else throw XBRLException("The Berkeley DB XML database location must be specified.");

			if (!container.empty() && container != "")  containerName = container;
			else throw XBRLException("The Berkeley DB XML database container must be specified.");

			initContainer();

			//			logIndexes();

		}

		void logIndexes()
		{
			try {
				DbXml::XmlIndexSpecification xis = dataContainer.getIndexSpecification();
				int count = 0;
				std::string uri, name, index;		         
				while(xis.next(uri,name,index)) 
				{
					log4cpp::Category& logger = log4cpp::Category::getInstance( std::string("log_sub1") );
					logger.debug("For node '" + uri + ":" + name + "', found index: '" + index + "'.");
					count ++;
				}
				std::cout << count;
				std::cout << " indices found." << std::endl;
			} catch (...) {
				;
			}        
		}

		//	synchronized 
		int getSize()
		{
			//        try {
			//            return this.dataContainer.getNumDocuments();
			//        } catch (XmlException e) {
			//            throw XBRLException("Failed to get the number of fragments in the data store.",e);
			//        }
			return 0;
		}

		void initEnvironment() 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );

			try {								

				environment.reset(new DbEnv(env_flags));
				int dberr = environment->set_cachesize(0, this->cacheSize, 0);
				if (dberr)
				{
					environment->close(0);
					//return (EXIT_FAILURE); //TODO
				}

				int nwrotep = 0;
				environment->set_error_stream(&std::cerr);
				environment->open(locationName.c_str(), env_flags, 0);
				environment->memp_trickle(20,&nwrotep); // ensure that 20% of cache is free

				logger.debug("Initialised the environment.");
			} 
			catch (...) 
			{
				throw XBRLException("The BDB XML database environment could not be set up.");
			}	    
		}

		void initManager() 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );

			if (environment == nullptr) initEnvironment();
			try {
				dataManager = std::make_shared<DbXml::XmlManager>(DbXml::XmlManager(environment->get_DB_ENV(), DbXml::DBXML_ADOPT_DBENV |
					DbXml::DBXML_ALLOW_EXTERNAL_ACCESS |
					DbXml::DBXML_ALLOW_AUTO_OPEN));
				logger.debug("Initialised the data manager.");
			} catch (DbXml::XmlException e) {
				throw XBRLException("The Berkeley XML database manager could not be set up.", e);
			}	    
		}

		void initContainer() 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );

			if (!dataManager) initManager();
			try {
				if (dataManager->existsContainer(containerName)) {
					dataContainer = dataManager->openContainer(containerName);
				} else {
					createContainer();
				}
				logger.debug("Initialised the data container.");
			} 
			catch (const DbXml::XmlException& e) 
			{
				throw XBRLException("The database container, " + containerName + ", could not be opened.", e);
			}
		}

		void createContainer()
		{
			if (!dataManager) initManager();
			try 
			{
				DbXml::XmlContainerConfig config;
				config.setStatistics(DbXml::XmlContainerConfig::On);
				dataContainer = dataManager->createContainer(containerName,config);

			} 
			catch (const DbXml::XmlException& e) 
			{
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.error("The data container could not be created.", e.getQueryFile());
				throw;
			} 

			DbXml::XmlIndexSpecification xmlIndexSpecification;
			DbXml::XmlUpdateContext xmlUpdateContext;

			//try {
			xmlIndexSpecification = dataContainer.getIndexSpecification();
			xmlIndexSpecification.setAutoIndexing(false);
			xmlIndexSpecification.replaceDefaultIndex("node-element-presence");

			// TODO Remove these indices - they are redundant given the default index.
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPINamespace,"fragment","node-element-presence");
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPINamespace,"data","node-element-presence");
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPINamespace,"xptr","node-element-presence");
			/*            xmlIndexSpecification.addIndex(XMLConstants::XBRLAPINamespace,"match","node-element-presence");
			*/
			xmlIndexSpecification.addIndex("","stub","node-attribute-presence");

			xmlIndexSpecification.addIndex("","index", "unique-node-attribute-equality-string");

			xmlIndexSpecification.addIndex(XMLConstants::XBRL21LinkNamespace,"label","node-element-substring-string");
			xmlIndexSpecification.addIndex(XMLConstants::GenericLabelNamespace,"label","node-element-substring-string");
			xmlIndexSpecification.addIndex("","name","node-attribute-substring-string");
			xmlIndexSpecification.addIndex("","name","node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","signature", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","arcIndex", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcName", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcNamespace", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcRole", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcOrder", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcPriority", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","use", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","linkName", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","linkNamespace", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","linkRole", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","sourceIndex", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","sourceType", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","sourceName", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","sourceNamespace", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","sourceRole", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","sourceLanguage", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","targetIndex", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetType", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetName", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetNamespace", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetRole", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetLanguage", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","label", "node-attribute-presence");
			xmlIndexSpecification.addIndex("","reference", "node-attribute-presence");
			xmlIndexSpecification.addIndex("","use", "node-attribute-presence");
			xmlIndexSpecification.addIndex("","use", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","parentIndex", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","uri", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","uri", "node-attribute-presence");

			xmlIndexSpecification.addIndex("","type", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetDocumentURI", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetPointerValue", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","absoluteHref", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","id","node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","value", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","arcroleURI", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","roleURI", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","name", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","targetNamespace", "node-attribute-equality-string");

			xmlIndexSpecification.addIndex("","contextRef", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","unitRef", "node-attribute-equality-string");

			// Entity identification indexes
			xmlIndexSpecification.addIndex("","scheme", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex("","value", "node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XBRL21Namespace,"identifier", "node-element-equality-string");            

			xmlIndexSpecification.addIndex(XMLConstants::XMLNamespace,"lang","node-attribute-equality-string");

			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"label","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"from","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"to","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"type","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"arcrole","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"role","node-attribute-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XLinkNamespace,"label","node-attribute-equality-string");

			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPILanguagesNamespace,"language","node-element-presence");
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPILanguagesNamespace,"code","node-element-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPILanguagesNamespace,"value","node-element-equality-string");
			xmlIndexSpecification.addIndex(XMLConstants::XBRLAPILanguagesNamespace,"encoding","node-element-equality-string");

			xmlUpdateContext = dataManager->createUpdateContext();
			dataContainer.setIndexSpecification(xmlIndexSpecification,xmlUpdateContext);

			//} catch (XmlException e) {
			//    throw XBRLException("The indexes could not be configured.", e);
			//} finally {
			//    if (xmlIndexSpecification != null) xmlIndexSpecification.delete();
			//}

		}        

		//synchronized 
		void close()
		{
			closeContainer();
		}

		void closeContainer()
		{
			//     if (dataContainer == NULL) return;
			//dataContainer.delete();
			dataContainer = NULL;
		}

		void deleteContainer()
		{
			//        if (!dataManager) initManager();
			//        closeContainer();
			//        try {
			//            if (dataManager->existsContainer(containerName) != 0) {
			//                dataManager->removeContainer(containerName);
			//            }
			//        } catch (XmlException e) {
			//            throw XBRLException("The BDB XML database container could not be deleted.");
			//        }
		}	

		//synchronized 
		void del()
		{
			//	    deleteContainer();
			//	    closeManager();
		}

		//synchronized 
		void persist(XML& xml, const Store& store)
		{			
			DbXml::XmlUpdateContext xmlUpdateContext;
			try {

				std::string index = xml.getIndex();
				if (hasXMLResource(index)) remove(index);

				std::string content = serialize(xml.getMetadataRootElement());
				xmlUpdateContext = dataManager->createUpdateContext();
				//DbXml::XmlDocumentConfig documentConfiguration = new XmlDocumentConfig();
				//documentConfiguration.setWellFormedOnly(true);
				dataContainer.putDocument(index, content, xmlUpdateContext, NULL);

				//if (xml.getStore() == null) {
				//	if (xml.getBuilder() != null) 
				xml.setResource(xml.getBuilder().getMetadata());
				xml.setStore(store);
				//}

			} catch (const DbXml::XmlException& e) {
				throw XBRLException("The fragment could not be added to the BDB XML data store.", e.what());
				//			} finally {
				//if (xmlUpdateContext != null) xmlUpdateContext.delete();
				//			}
			}

		}
		//synchronized 
		bool hasXMLResource(const std::string& index)
		{

			try {
				dataContainer.getDocument(index); 
				//				throw DbXml::XmlException(1, "error"); //TODO remove comments
				return true;
			} 
			catch (DbXml::XmlException& e)  //TODO log error
			{
				return false;
			}
			catch (std::exception& e)   //TODO log error
			{
				std::string s = e.what();	
				return false;
			}
			return false;
		}


		//synchronized 
		template <typename F> 
		F getXMLResource(const std::string& index) 
		{
			//
			//         try {
			//            XmlDocument xmlDocument = dataContainer.getDocument(index);
			//            Document document = (new XMLDOMBuilder()).newDocument(xmlDocument.getContentAsInputStream());
			//            return FragmentFactory.<F>newFragment(this, document.getDocumentElement());
			//        } catch (XmlException e) { // Thrown if the document is not found
			//            throw XBRLException("The fragment " + index + " could not be retrieved from the store.",e);
			//        }
			//
			return F();
		}

		//synchronized 
		void remove(XML& fragment)
		{
			remove(fragment.getIndex());
		}

		void remove(const std::string& index) {

			DbXml::XmlUpdateContext xmlUpdateContext;
			try {
				xmlUpdateContext = dataManager->createUpdateContext();
				dataContainer.deleteDocument(index,xmlUpdateContext);
			} 
			catch (const DbXml::XmlException& e) 
			{
				throw XBRLException("The fragment removal failed.", e);
			} 
			//finally {
			//	//if (xmlUpdateContext != null) xmlUpdateContext.delete();
			//}
		}

		//synchronized 
		template <typename T>
		std::vector<std::shared_ptr<T>> queryForXMLResources(std::string& query) 
		{

			DbXml::XmlResults xmlResults;

			try {
				xmlResults = runQuery(query);
				std::chrono::time_point<std::chrono::system_clock> start, end;
				start = std::chrono::system_clock::now();

				DbXml::XmlValue xmlValue; 
				xmlResults.next(xmlValue);
				std::vector<std::shared_ptr<T>> fragments;
				while (xmlValue) 
				{
					DbXml::XmlDocument XmlDoc = xmlValue.asDocument();

					xercesc::DOMLSParser* builder = domimplementation->createLSParser(
						xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, NULL);

					DbXml::XmlInputStream* inputStream =  XmlDoc.getContentAsXmlInputStream();
					DbXml::XmlInputStreamWrapper inputSource(&inputStream);
					xercesc::Wrapper4InputSource LSInputSource(&inputSource);

					xercesc::DOMDocument* document = builder->parse(&LSInputSource);					
					xercesc::DOMElement* root = document->getDocumentElement();

					std::shared_ptr<T> frag = std::make_shared<T>();//FragmentFactory::newFragment<T>(*this, *root);
					fragments.push_back(frag);
					xmlResults.next(xmlValue);
				}

				end = std::chrono::system_clock::now();
				long long duration = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.debug(std::to_string(duration) + " milliseconds to create fragment list from" + query);

				return fragments;

			} 
			catch (xercesc::DOMLSException e) 
			{
				throw XBRLException("Failed query: Parser busy" + query,toNative(e.getMessage()));
			}
			catch (xercesc::DOMException e) 
			{
				throw XBRLException("Failed query: Parser was unable to load the XML document" + query,toNative(e.getMessage()));
			}
			//} finally {
			//if (xmlResults != nullptr) delete xmlResults; //TODO
			//}
		}

		//synchronized 
		std::unordered_set<std::string> queryForIndices(const std::string& query) 
		{
			//
			//        query = "for $fragment in " + query + " return string($fragment/@index)";
			//        
			//        XmlResults xmlResults = null;
			//        try {
			//    
			//            try {
			//                xmlResults = runQuery(query);
			//                XmlValue xmlValue = xmlResults.next();
			//                Set<String> indices = new HashSet<String>();
			//
			//                while (xmlValue != null) {
			//                    indices.add(xmlValue.asString());
			//                    xmlValue = xmlResults.next();
			//                }
			//                return indices;
			//    
			//            } catch (XmlException e) {
			//                throw XBRLException("Failed query: " + query,e);
			//            } catch (IllegalStateException e) {
			//                throw XBRLException("Failed query: " + query,e);
			//            }
			//            
			//        } finally {
			//            if (xmlResults != null) xmlResults.delete();
			//        }
			//
			std::unordered_set<std::string> xx;
			return xx;
		}

		bool hasDocument(const Poco::URI& uri) 
		{
			Poco::URI matchURI;
			try 
			{
				matchURI = matcher.getMatch(uri);
			} 
			catch (XBRLException e) 
			{
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.warn(uri.toString() + " could not be matched. " + e.getMessage());
				matchURI = uri;
			}
			std::string query = "for $root in #roots# where $root/@uri='" + matchURI.toString() + "' and $root/@parentIndex='' return string($root/@index)";
			std::unordered_set<std::string> rootIndices =  queryForStrings(query);
			if (rootIndices.size() == 1) return true;
			if (rootIndices.size() == 0) return false;
			throw; //new XBRLException("There are two root fragments in the store for " + uri);
			return false;
		}

		//synchronized 
		std::unordered_set<std::string> queryForStrings(std::string& query)
		{

			DbXml::XmlResults xmlResults;
			//try {

			//try {
			xmlResults = runQuery(query);
			//		                double startTime = System.currentTimeMillis();
			DbXml::XmlValue xmlValue; 
			xmlResults.next(xmlValue);
			std::unordered_set<std::string> strings;
			while (xmlValue) {
				if (xmlValue.isNode())
					strings.insert(xmlValue.getNodeValue());
				else if (xmlValue.isString())
					strings.insert(xmlValue.asString());
				xmlResults.next(xmlValue);
			}

			//Double time = new Double((System.currentTimeMillis()-startTime));
			//logger.debug(time + " milliseconds to create  std::string list from" + query);
			return strings;

			/*		            } catch (XmlException e) {
			throw XBRLException("Failed query: " + query,e);
			}

			} finally {
			if (xmlResults != null) xmlResults.delete();
			} */      
		}

		//synchronized 
		long queryCount(std::unordered_set<std::string> query)
		{

			//      XmlResults xmlResults = null;
			//      try {
			//          xmlResults = runQuery(query, XmlQueryContext.Eager);
			//          return xmlResults.size();
			//      } catch (XmlException e) {
			//          logger.error("The query stuffed up. " + query);
			//          throw XBRLException("Failed query: " + query,e);
			//      } finally {
			//          if (xmlResults != null) xmlResults.delete();
			//      }
			return 0L;
		}    

		DbXml::XmlResults runQuery(std::string& myQuery, 
			const DbXml::XmlQueryContext::EvaluationType& evaluationType = DbXml::XmlQueryContext::Eager)
		{
			DbXml::XmlQueryExpression xmlQueryExpression;
			//try {
			std::string roots = "collection('" + dataContainer.getName() + "')/*" + getURIFilteringPredicate();
			std::string expr("#roots#");
			size_t pos = myQuery.find(expr);
			myQuery.replace(pos, expr.size(), roots);//TODO use boost::algorithm::replace here
			DbXml::XmlQueryContext xmlQueryContext = createQueryContext();
			xmlQueryContext.setEvaluationType(evaluationType);
			xmlQueryExpression = dataManager->prepare(myQuery,xmlQueryContext);
			//logger.debug(xmlQueryExpression.getQueryPlan());
			//double startTime = System.currentTimeMillis();
			DbXml::XmlResults xmlResults = xmlQueryExpression.execute(xmlQueryContext);
			//Double time = new Double((System.currentTimeMillis()-startTime));
			//logger.debug(time + " milliseconds to evaluate " + myQuery);
			return xmlResults;

			//} catch (XmlException e) {
			//    throw XBRLException("Failed query: " + myQuery,e);
			//} finally {
			//    if (xmlQueryExpression != null) xmlQueryExpression.delete();
			//}
		}	

		DbXml::XmlResults performLazyQuery(const std::string& myQuery) 
		{
			//        // TODO provide a means of adding additional namespaces for querying.
			//        // TODO provide a means of investigating namespace bindings for the query configuration.
			//        
			//        XmlQueryExpression xmlQueryExpression = null;
			//        try {
			//             std::string query = "collection('" + dataContainer.getName() + "')" + myQuery;
			//            XmlQueryContext xmlQueryContext = createQueryContext();
			//            xmlQueryContext.setEvaluationType(XmlQueryContext.Lazy);
			//            xmlQueryExpression = dataManager->prepare(query,xmlQueryContext);
			//            double startTime = System.currentTimeMillis();
			//            XmlResults xmlResults = xmlQueryExpression.execute(xmlQueryContext);
			//            Double time = new Double((System.currentTimeMillis()-startTime));
			//            logger.debug(time + " milliseconds to evaluate " + myQuery);
			//            return xmlResults;
			//
			//        } catch (XmlException e) {
			//            throw XBRLException("Failed query: " + myQuery,e);
			//        } finally {
			//            if (xmlQueryExpression != null) xmlQueryExpression.delete();
			//        }
			//        
			DbXml::XmlResults xx;
			return xx;

		}	

		DbXml::XmlQueryContext createQueryContext()
		{
			DbXml::XmlQueryContext xmlQueryContext;
			std::vector<std::string> keys;
			//try {
			xmlQueryContext = dataManager->createQueryContext();
			xmlQueryContext.setReturnType(xmlQueryContext.LiveValues);
			xmlQueryContext.setNamespace(XMLConstants::XLinkPrefix, XMLConstants::XLinkNamespace);
			//	xmlQueryContext.setNamespace(XMLConstants::XMLSchemaPrefix, XMLConstants::XMLSchemaNamespace); TODO
			xmlQueryContext.setNamespace(XMLConstants::XBRL21Prefix, XMLConstants::XBRL21Namespace);
			xmlQueryContext.setNamespace(XMLConstants::XBRL21LinkPrefix, XMLConstants::XBRL21LinkNamespace);
			xmlQueryContext.setNamespace(XMLConstants::XBRLAPIPrefix, XMLConstants::XBRLAPINamespace);
			xmlQueryContext.setNamespace(XMLConstants::XBRLAPILanguagesPrefix, XMLConstants::XBRLAPILanguagesNamespace);

			std::transform(namespaceBindings.begin(), namespaceBindings.end(), std::back_inserter(keys),
				[](const std::unordered_map<std::string,std::string>::value_type &pair)
			{
				return pair.first;
			});
			for ( std::string prefix : keys) 
				xmlQueryContext.setNamespace(prefix,namespaceBindings[prefix]);
			// xmlQueryContext.setEvaluationType(XmlQueryContext.Lazy); 
			return xmlQueryContext;
			/*	        } catch (XmlException e) {
			throw XBRLException("Failed to create query context.",e);
			}*/
		}
		//synchronized 
		void sync()
		{
			try
			{
				dataContainer.sync();
				lastSync = std::chrono::system_clock::now();
			} 
			catch (const DbXml::XmlException& e) 
			{
				throw XBRLException("The database updates could not be flushed to disk using the sync method.",e);
			}
		}

		void addIndex(const std::string& Namespace, const std::string& name, const std::string& type)
		{
			//
			//        XmlIndexSpecification xmlIndexSpecification = null;
			//        XmlUpdateContext xmlUpdateContext = null;
			//
			//        try {
			//            xmlIndexSpecification = dataContainer.getIndexSpecification();
			//             std::string ns = "";
			//            if (namespace != null) ns = namespace;
			//            xmlIndexSpecification.addIndex(ns,name,type);
			//            logger.info("Adding index for " + ns + ":" + name + " " + type);
			//            xmlUpdateContext = dataManager->createUpdateContext();
			//            dataContainer.setIndexSpecification(xmlIndexSpecification,xmlUpdateContext);
			//        } catch (XmlException e) {
			//            throw XBRLException("The new index could not be configured.", e);
			//        } finally {
			//            if (xmlIndexSpecification != null) xmlIndexSpecification.delete();
			//        }        
		}

		void readObject(std::istream in)
		{
			//        in.defaultReadObject();
			//        try {
			//            if (! this.computerIdentity.equals(this.getComputerName())) {
			//                throw new IOException("The data store is being deserialized on the wrong computer.");
			//            }
			//            initialize(locationName, containerName);
			//        } catch (XBRLException e) {
			//            throw new IOException("The data store could not be deserialized.",e);
			//        }
		}

		int hashCode()
		{
			//        final int prime = 31;
			//        int result = super.hashCode();
			//        result = prime * result + ((computerIdentity == null) ? 0 : computerIdentity.hashCode());
			//        result = prime * result + ((containerName == null) ? 0 : containerName.hashCode());
			//        result = prime * result + ((locationName == null) ? 0 : locationName.hashCode());
			//        return result;
			return 0;
		}

		//		bool equals(Object obj)
		//		{
		//        if (this == obj)
		//            return true;
		//        if (!super.equals(obj))
		//            return false;
		//        if (getClass() != obj.getClass())
		//            return false;
		//        Impl other = (Impl) obj;
		//        if (computerIdentity == null) {
		//            if (other.computerIdentity != null)
		//                return false;
		//        } else if (!computerIdentity.equals(other.computerIdentity))
		//            return false;
		//        if (containerName == null) {
		//            if (other.containerName != null)
		//                return false;
		//        } else if (!containerName.equals(other.containerName))
		//            return false;
		//        if (locationName == null) {
		//            if (other.locationName != null)
		//                return false;
		//        } else if (!locationName.equals(other.locationName))
		//            return false;
		//        return true;
		//    }    

		std::string toString()
		{
			//        return "Oracle Berkeley XML database at " + this.computerIdentity + " " + this.locationName + " " + this.containerName;
			return "";
		}

		//    public long getNumberOfXMLResources(Class<?> specifiedClass)
		//            {
		//         std::string query = "for $root in #roots# where $root/@type='" + specifiedClass.getName() + "' return $root";
		//        return this.queryCount(query);
		//    }


		//    

		//     * @see org.xbrlapi.data.Store#setMatcher(Matcher)
		//     */
		//    public synchronized void setMatcher(Matcher matcher) {
		//        if (matcher == null) throw XBRLException("The matcher cannot be null");
		//        this.matcher = matcher;
		//    }
		//
		DefaultMatcher getMatcher()
		{
			return matcher;
		}    

		//

		//     * @see org.xbrlapi.data.Store#setNamespaceBinding(String,String)
		//     */
		//    public synchronized void setNamespaceBinding( std::string namespace,  std::string prefix) {
		//        this.namespaceBindings.put(prefix, namespace);
		//    }
		//

		//     * @see org.xbrlapi.data.Store#removeNamespaceBinding(String)
		//     */
		//    public synchronized void removeNamespaceBinding( std::string prefix) {
		//        this.namespaceBindings.remove(prefix);
		//    }
		//

		//     * Set of URIs to use when filtering query results to only get matches
		//     * to a specific set of documents.
		//     */

		//    public synchronized void setFilteringURIs(Set<URI> uris) {
		//        if (uris == null) this.uris = new HashSet<URI>();
		//        else this.uris = uris;
		//    }
		//    

		std::unordered_set<Poco::URI> getFilteringURIs() 
		{
			return uris;
		}    

		//    public void clearFilteringURIs() {
		//        this.uris = new HashSet<URI>();
		//    }

		//synchronized 
		bool isFilteringByURIs() 
		{
			return (! uris.empty());
		}

		//synchronized  
		std::string getURIFilteringPredicate() 
		{

			if (isFilteringByURIs()) {
				std::string uriFilter = "0";
				for (const Poco::URI& uri : getFilteringURIs()) 
				{
					uriFilter = uriFilter + std::string(" or @uri='") + uri.toString() + std::string("'");
				}
				uriFilter = "[" + uriFilter + "]";
				//         logger.debug(uriFilter);
				return uriFilter;
			}
			return "";
		}
		//

		//	 * Does nothing.
		//	 * @see Store#close()
		//	 */
		//	public void close() {
		//	    ;
		//	}
		//	
		/*
		//* @see org.xbrlapi.data.Store#persistLoaderState(Map)
		*/
		void persistLoaderState(std::unordered_map<const Poco::URI,std::string>& documents) 
		{
			std::vector<std::pair<Poco::URI, std::string>> kvpairs(documents.begin(), documents.end());
			try {
				for (std::pair<Poco::URI, std::string>& kv : kvpairs) 
				{
					persistStub(kv.first, documents[kv.first]);
				}
			} 
			catch (XBRLException e) 
			{
				throw XBRLException("The loader state could not be stored.",e);
			}
		}


		/*
		* @see Store#persistStub(URI,String)
		*/
		void persistStub(const Poco::URI& uri,  std::string& reason) {

			try 
			{
				deleteDocument(uri);
			} 
			catch (const XBRLException& e) 
			{
				reason += " (NB: Failed to delete the document from the data store. " + e.getMessage() + ")";
			}

			std::string documentId = getId(uri.toString() + "_stub");
			Stub stub(documentId, uri, reason);
			persist(stub, *outer);
		}

		/*

		//     * Default implementation does nothing.
		//     * @see Store#sync()
		//     */
		//    public synchronized void sync() {
		//    }
		//

		std::string getId(const std::string& input) 
		{

			// The document is not in the data store so generate a new document ID.
			std::string randomString(random()); 
			while (hasXMLResource(randomString + "_1") || hasXMLResource(randomString)) 
			{
				randomString = random(); 
			}
			return randomString;
			return false;
		}

		std::string random() 
		{
			char s[7];
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			for (int i = 0; i < 6; ++i) 
			{
				s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
			}

			s[6] = '\0';
			return std::string(s);
		}
		//    
		/*

		//     * Generate a random string.
		//     * @return a randomly generated string consisting of digits and
		//     * a-z or A-Z only.
		//     */
		//    private  std::string random() {
		//         std::string random = "";
		//        for (int i=0; i<6; i++) {
		//            int code = (new Long(Math.round(Math.random()*61))).intValue();
		//            code = code + 48;
		//            if (code < 58) {
		//                random = random + new Character((char)code).toString();
		//            } else {
		//                code = code + 7;
		//                if (code < 91) {
		//                    random = random + new Character((char)code).toString();
		//                } else {
		//                    code = code + 6;
		//                    random = random + new Character((char)code).toString();
		//                }
		//            }
		//        }
		//        return random;
		//    }
		//    

		//     * @param bs The given byte array.
		//     * @return a hex string representation of the given byte array.
		//     */
		//    private  std::string bytesToHex(byte[] bs) {
		//        StringBuffer ret = new StringBuffer(bs.length);
		//        for (int i = 0; i < bs.length; i++) {
		//             std::string hex = Integer.toHexString(0x0100 + (bs[i] & 0x00FF)).substring(1);
		//            ret.append((hex.length() < 2 ? "0" : "") + hex);
		//        }
		//        return ret.toString();
		//    }    
		//

		void serialize(const xercesc::DOMElement& what, std::ofstream& destination) {

			try 
			{
				//XMLDOMSerializer::serialize(what, destination);
				//xercesc::LSSerializer writer = domImplementation.createLSSerializer();
				//writer.getDomConfig().setParameter("format-pretty-print",true);
				//xercesc::LSOutput output = domImplementation.createLSOutput();
				//output.setByteStream(destination);
				//writer.write(what,output);
			} 
			catch (const std::exception& e) 
			{
				throw XBRLException("The XML subtree could not be serialised.", e);
			}
		}





		/*

		/* @see Store#serialize(xercesc::DOMElement)
		*/
		std::string serialize(const std::shared_ptr<xercesc::DOMElement>& what) 
		{
			//ByteArrayOutputStream baos = new ByteArrayOutputStream();
			//serialize(what, baos);
			//return baos.toString();
			return std::string();
		}


		/*
		* Algorithm:
		* <ol>
		*  <li>Check if the matcher indicate that the URI has matching URIs.</li>
		*  <li>If the URI has matching URIs:
		*   <li>If the URI is the one used for the document in the data store:
		*    <li>Delete the URI from the matcher, getting the new matching URI back as
		*    a result of the deletion operation and update the document fragments to use 
		*    the new matching URI instead of the deleted URI.</li>
		*   </li>
		*   <li>Otherwise, just delete the URI from the matcher and we are done.</li>
		*  </li>
		*  <li>Otherwise, the URI does not have matching URIs so just delete the
		*  URI from the matcher and delete the relevant fragments from the data store.</li>
		* </ol>
		* @see org.xbrlapi.data.Store#deleteDocument(URI)
		*/
		void deleteDocument(const Poco::URI& uri) 
		{
			log4cpp::Category& logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("Deleting " + uri.toString() + " from the data store.");

			Poco::URI matchURI = getMatcher().getMatch(uri);
			Poco::URI newMatchURI = getMatcher().del(uri);

			std::string query = "for $fragment in #roots# where $fragment/@uri='" 
				+ matchURI.toString()
				+ "' return $fragment";

			if (newMatchURI.empty()) 
			{
				std::unordered_set<std::string> indices = queryForIndices(query);
				for ( std::string index: indices) 
				{
					remove(index);
				}
				return;
			} 
			else if (matchURI == newMatchURI) 
			{
				return;
			}

			std::unordered_set<std::string> indices = queryForIndices(query);
			for ( const std::string& index : indices) 
			{
				Fragment fragment = getXMLResource<Fragment>(index);
				fragment.setURI(newMatchURI);
				persist(fragment, *outer);
			}

			// Eliminate any document stub
			std::vector<std::shared_ptr<Stub>> stubs = getStubs(/*uri*/);
			for (const std::shared_ptr<Stub>& stub : stubs) 
			{
				removeStub(*stub);
			}

		}


		//     * @see Store#deleteRelatedDocuments(URI)
		//     */
		//    public void deleteRelatedDocuments(URI uri) {
		//        
		//        HashMap<URI,bool> documentsToDelete = new HashMap<URI,bool>();    	
		//        
		//        deleteDocument(uri);
		//    	
		//        std::vector<Fragment> fragments = this.<Fragment>queryForXMLResources("#roots#[@targetDocumentURI='"+ uri + "']");
		//    	
		//        for (const Fragment& fragment: fragments) {
		//            if (! documentsToDelete.containsKey(fragment.getURI())) {
		//                documentsToDelete.put(fragment.getURI(),new bool(true));
		//            }
		//    		Iterator<URI> iterator = documentsToDelete.keySet().iterator();
		//    		while (iterator.hasNext()) {
		//    			URI myURI = iterator.next();
		//    			if (documentsToDelete.get(myURI)) {
		//        			deleteRelatedDocuments(myURI);
		//        			documentsToDelete.put(myURI,new bool(false));
		//    			}
		//    		}
		//    	}
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getReferencingDocuments(URI)
		//     */
		//    public std::vector<URI> getReferencingDocuments(URI uri) {
		//         std::string query = "for $root in #roots#[@targetDocumentURI='"+ uri + "'] return string($root/@uri)";
		//        Set<String> strings = queryForStrings(query);
		//
		//        std::vector<URI> uris = new Vector<URI>();
		//        for ( std::string string: strings) {
		//            try {
		//                uris.add(new URI(string));
		//            } catch (URISyntaxException e) {
		//                throw XBRLException(string + " is an invalid URI.",e);
		//            }
		//        }
		//
		//        return uris;
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getReferencingFragments(URI)
		//     */
		//    public std::vector<Fragment> getReferencingFragments(URI uri) {
		//         std::string query = "for $root in #roots#[@targetDocumentURI='"+ uri + "'] return $root";
		//        std::vector<Fragment> fragments = this.<Fragment>queryForXMLResources(query);
		//        return fragments;
		//    }    
		//    

		//     * @see org.xbrlapi.data.Store#getReferencedDocuments(URI)
		//     */
		//    public Set<URI> getReferencedDocuments(URI uri) {
		//        Set<URI> result = new HashSet<URI>(); 
		//         std::string query = "for $root in #roots#[@uri='" + uri + "' and @targetDocumentURI] return concat('',$root/@targetDocumentURI)";
		//        for ( std::string targetURI: queryForStrings(query)) {
		//            result.add(URI.create(targetURI));
		//        }
		//        return result;
		//    }
		//

		//public void serialize(const xercesc::DOMElement& what, File destination) 
		//		{
		//
		//			//File parentFile = destination.getParentFile();
		//			//
		//			//if (parentFile != null) parentFile.mkdirs();
		//
		//			//try {
		//			//	FileOutputStream fileOutputStream = new FileOutputStream(destination.toString());
		//			//	serialize(what, fileOutputStream);
		//			//} catch (FileNotFoundException e) {
		//			//	throw XBRLException("The file to be written to cannot be found.", e);
		//			//}
		//
		//		}


		//	

		//     * @see Store#getDocumentURIs()
		//     */
		//    public Set<URI> getDocumentURIs() {
		//
		//        Set<URI> uris = new HashSet<URI>();
		//        
		//        Set<String> uriStrings =  this.queryForStrings("for $root in #roots#[@parentIndex=''] return string($root/@uri)");
		//
		//        try {
		//            for ( std::string uriString: uriStrings) {
		//                uris.add(new URI(uriString));
		//            }
		//        } catch (URISyntaxException e) {
		//            throw XBRLException("A document URI has invalid syntax.",e);
		//        }
		//        return uris;
		//    }
		//

		//
		//    

		//     * @see Store#getDocumentAsDOM(URI)
		//     */
		//    public xercesc::DOMElement getDocumentAsDOM(URI uri) {
		//    	return getSubtree(this.getRootFragmentForDocument(uri));
		//    }
		//	

		//     * Get a single document in the store as a DOM including annotations.
		//     * @param uri The string representation of the URI of the 
		//     * document to be retrieved.
		//     * @return an annotated DOM Document containing the XML representation of the
		//     * file at the specified URI.  Returns null if the store does not
		//     * contain a document with the given URI.
		//     * @throws XBRLException if more or less than one document is found in the store matching 
		//     * the supplied URI.
		//     */
		//    private xercesc::DOMElement getAnnotatedDocumentAsDOM(URI uri) {
		//        URI matchURI = getMatcher().getMatch(uri);
		//        std::vector<Fragment> fragments = queryForXMLResources("#roots#[@uri='" + matchURI + "' and @parentIndex='']");
		//        if (fragments.size() > 1) throw XBRLException("More than one document was found in the data store.");
		//        if (fragments.size() == 0) throw XBRLException("No documents were found in the data store.");
		//        Fragment fragment = fragments.get(0);
		//        xercesc::DOMElement document = this.getAnnotatedSubtree(fragment);
		//        document.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index",fragment.getIndex());
		//        return document;
		//    }
		//    

		//	 * @see Store#getSubtree(Fragment)
		//	 */
		//	public xercesc::DOMElement getSubtree(const Fragment& f) {
		//
		//	    if (f == null) {
		//	        throw XBRLException("The fragment must not be null.");
		//	    }
		//	    
		//		// Make sure that the DOM is initialised.
		//		if (storeDOM == null) {
		//			storeDOM = (new XMLDOMBuilder()).newDocument();
		//		}
		//
		//		// Get the DOM representation of the fragment
		//		xercesc::DOMElement d = null;
		//		try {
		//		    d = (xercesc::DOMElement) storeDOM.importNode(f.getDataRootElement(), true);
		//		} catch (Exception e) {
		//		    e.printStackTrace();
		//		    throw XBRLException("The data could not be plugged into the DOM for fragment " + f.getIndex(),e);
		//		}
		//		    
		//		// Get the child fragment IDs
		//		List<Fragment> unorderedFragments = this.queryForXMLResources("#roots#[@parentIndex='" + f.getIndex() + "']");
		//		
		//		// With no children, just return the fragment
		//		if (unorderedFragments.size() == 0) {
		//			return d;
		//		}
		//
		//		// Sort the child fragments into insertion order
		//		TreeSet<Fragment> sortedFragments = new TreeSet<Fragment>(new FragmentComparator());
		//    	for (const Fragment& fragment: unorderedFragments) {
		//    		sortedFragments.add(fragment);
		//    	}
		//    	
		//    	// Iterate sorted child fragments in insertion order, inserting them
		//    	for (const Fragment& childFragment: sortedFragments) {
		//
		//    		// Get XML DOM for child fragment
		//    		xercesc::DOMElement child = getSubtree(childFragment);
		//
		//    		// Get parent element of child fragment in current fragment
		//    		xercesc::DOMElement parentElement = childFragment.getParentElement(d);
		//
		//            // Do the fragment insertion
		//    		parentElement.appendChild(child);
		//
		//    	}
		//		return d;
		//	}
		//	

		//     * Get the following sibling of this fragment's root in the parent fragment's data.
		//     * @param parentElement The parent element in the parent fragment's data.
		//     * @param precedingSiblings The number of sibling elements preceding the element of interest.
		//     * @return the following sibling of this fragment's root (or null if there is no preceding sibling).
		//     */
		//    protected xercesc::DOMElement getFollowingSibling(xercesc::DOMElement parentElement, int precedingSiblings) {
		//    	
		//    	// Traverse the parent data DOM to find the relevant child node
		//		int siblingCount = 0;
		//		NodeList children = parentElement.getChildNodes();
		//		for (int i=0; i<children.getLength(); i++) {
		//			Node child = children.item(i);
		//			if (child.getNodeType() == Node.ELEMENT_NODE) {
		//				siblingCount++;  // We have found a sibling element
		//				if (siblingCount > precedingSiblings) return (xercesc::DOMElement) child;
		//			}
		//		}
		//		return null;
		//    	
		//    }	
		//

		//	 * Returns the root element of the annotated subtree starting with the
		//	 * fragment with the specified index.  All subtrees for a given store
		//	 * instance are produced from the one XML DOM and so can be appended
		//	 * to eachother as required.
		//	 * @param f The fragment at the root of the subtree.
		//	 * @return the root element of the subtree headed by the fragment
		//	 * with the specified index.
		//	 * @throws XBRLException if the subtree cannot be constructed.
		//	 */
		//	private xercesc::DOMElement getAnnotatedSubtree(const Fragment& f) {
		//		
		//    	//logger.debug((new Date()) + ":Getting fragment " + f.getIndex());
		//    	
		//		// Make sure that the DOM is initialised.
		//		if (storeDOM == null) {
		//			storeDOM = (new XMLDOMBuilder()).newDocument();
		//		}
		//
		//		// Get the DOM representation of the fragment
		//		xercesc::DOMElement d = (xercesc::DOMElement) storeDOM.importNode(f.getDataRootElement(), true);
		//		
		//		// Get the child fragment IDs
		//		List<Fragment> fs = this.queryForXMLResources("/"+ Constants.XBRLAPIPrefix+ ":" + "fragment[@parentIndex='" + f.getIndex() + "']");
		//		
		//		// With no children, just return the fragment
		//		if (fs.size() == 0) {
		//			return d;
		//		}
		//
		//		// Sort the child fragments into insertion order
		//		TreeSet<Fragment> fragments = new TreeSet<Fragment>(new FragmentComparator());
		//		for (int i=0; i<fs.size(); i++) {
		//    		fragments.add(fs.get(i));
		//    	}
		//    	
		//    	// Iterate child fragments in insertion order, inserting them
		//    	Iterator<Fragment> iterator = fragments.iterator();
		//    	while (iterator.hasNext()) {
		//    		
		//    		// Get child fragment
		//    		Fragment childFragment = iterator.next();
		//
		//    		// Get XML DOM for child fragment using recursion
		//    		xercesc::DOMElement child = getAnnotatedSubtree(childFragment);
		//	    	child.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index",childFragment.getIndex());
		//
		//    		// Get parent element of child fragment in current fragment
		//    		xercesc::DOMElement parentElement = childFragment.getParentElement(d);
		//
		//    		// Do the fragment insertion
		//            parentElement.appendChild(child);
		//    		
		//    	}
		//		return d;
		//	}
		//	
		//	

		//     * @see Store#getStoreAsDOM()
		//     */
		//    public Document getStoreAsDOM() {
		//
		//		if (storeDOM == null) {
		//			storeDOM = (new XMLDOMBuilder()).newDocument();
		//		}
		//		
		//    	xercesc::DOMElement root = storeDOM.createElementNS(Constants.XBRLAPINamespace.toString(),Constants.XBRLAPIPrefix + ":dts");
		//		
		//		Set<URI> uris = getDocumentURIs();
		//		for (URI uri: uris) {
		//			xercesc::DOMElement e = getDocumentAsDOM(uri);
		//			root.appendChild(e);			
		//		}
		//    	storeDOM.appendChild(root);
		//    	return storeDOM;
		//    }
		//		

		//     * @see Store#getCompositeDocument()
		//     */
		//    public Document getCompositeDocument() {
		//    	
		//		if (storeDOM == null) {
		//			storeDOM = (new XMLDOMBuilder()).newDocument();
		//		}
		//		
		//    	xercesc::DOMElement root = storeDOM.createElementNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":dts");
		//		
		//		Set<URI> uris = getDocumentURIs();
		//		long counter = 1;
		//		for (URI uri: uris) {
		//	    	xercesc::DOMElement file = storeDOM.createElementNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":file");
		//	    	file.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":uri", uri.toString());
		//	    	file.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index","composite_" + new Long(counter++).toString());
		//			root.appendChild(file);
		//			file.appendChild(getAnnotatedDocumentAsDOM(uri));
		//		}
		//    	root.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index","composite_" + new Long(counter++).toString());
		//    	storeDOM.appendChild(root);
		//    	return storeDOM;
		//    	
		//    }

		std::vector<std::shared_ptr<Stub>> getStubs() 
		{
			std::vector<std::shared_ptr<Stub>> stubs = getXMLResources<Stub>("Stub");
			return stubs;
		}
		//    

		//     * @see org.xbrlapi.data.Store#getStubs(URI)
		//     */
		//    public std::vector<Stub> getStubs(URI uri) {
		//        return this.<Stub>queryForXMLResources("#roots#[@type='org.xbrlapi.impl.StubImpl' and @resourceURI='" + uri + "']");
		//    }
		//    
		/*
		* @see Store#removeStub(Stub)
		*/
		void removeStub(Stub& stub) 
		{
			if ( hasXMLResource(stub.getIndex()) )
				remove(stub);
		}


		//     * @see org.xbrlapi.data.Store#remove(XML)
		//     */
		//    public void remove(const XML& xml) {
		//        remove(xml.getIndex());
		//    }    
		//
		//synchronized 
		std::vector<Poco::URI> getDocumentsToDiscover() 
		{
			std::vector<std::shared_ptr<Stub>> stubs = getStubs();
			std::vector<Poco::URI> v;
			for (auto stub : stubs) {
				v.push_back(stub->getResourceURI());
			}
			return v;
		}
		//    

		//     * @see Store#saveDocuments(File)
		//	 */
		//	public void saveDocuments(File destination) {
		//		saveDocuments(destination, "");
		//	}
		//	

		//     * @see Store#saveDocuments(File, String)
		//	 */
		//	public void saveDocuments(File destination,  std::string uriPrefix) {
		//		
		//		if (! destination.exists()) throw XBRLException("The specified directory does not exist.");
		//		
		//		if (! destination.isDirectory()) throw XBRLException("A directory rather than a file must be specified.");
		//		
		//		Set<URI> uris = getDocumentURIs();
		//		Iterator<URI> iterator = uris.iterator();
		//		while (iterator.hasNext()) {			
		//			URI uri = iterator.next();
		//			if (uri.toString().startsWith(uriPrefix)) {
		//				Cache cache = new CacheImpl(destination);
		//				File file = cache.getCacheFile(uri);
		//				xercesc::DOMElement e = getDocumentAsDOM(uri);
		//				serialize(e,file);
		//			}
		//		}
		//		
		//	}
		//	

		//	 * @see Store#saveStoreAsSingleDocument(File)
		//	 */
		//	public void saveStoreAsSingleDocument(File file) {
		//		serialize(getStoreAsDOM().getDocumentElement(),file);
		//	}
		//    

		//     * Convert a DOM element (and its descendents) to a string.
		//     * @param element The element to convert to a string.
		//     * @return The string that is the serialised element.
		//     * @throws XBRLException if an IO exception occurs.
		//     */
		//    protected  std::string DOM2String(xercesc::DOMElement element) {
		//        try {
		//            LSSerializer writer = domImplementation.createLSSerializer();
		//            return writer.writeToString(element);
		//        } catch (Exception e) {
		//            throw XBRLException("The XML DOM element could not be written to a string for persisting.",e);
		//        }
		//    }

		template <typename T>
		std::vector<std::shared_ptr<T>> getXMLResources(const std::string& interfaceName) 
		{
			std::string query = "for $root in #roots# where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
			if (interfaceName.find(".") > -1) {
				query = "for $root in #roots# where $root/@type='" + interfaceName + "' return $root";
			}
			return queryForXMLResources<T>(query);
		}
		//    

		//     * @see org.xbrlapi.data.Store#getXMLResources(Class)
		//     */
		//    public <F extends XML> std::vector<F> getXMLResources(Class<?> specifiedClass) {
		//         std::string query = "for $root in #roots# where $root/@type='" + specifiedClass.getName() + "' return $root";
		//        return this.<F>queryForXMLResources(query);
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getChildFragments(String, String)
		//     */
		//    public <F extends Fragment> std::vector<F> getChildFragments( std::string interfaceName,  std::string parentIndex) {
		//    	return this.<F>queryForXMLResources("#roots#[@type='org.xbrlapi.impl." + interfaceName + "Impl' and @parentIndex='" + parentIndex + "']");
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getChildFragments(Class, String)
		//     */
		//    public <F extends Fragment> std::vector<F> getChildFragments(Class<?> childClass,  std::string parentIndex) {
		//        return this.<F>queryForXMLResources("#roots#[@type='" + childClass.getName() + "' and @parentIndex='" + parentIndex + "']");
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getNetworks()
		//     */
		//    public Networks getNetworks() {
		//
		//        Networks networks = new NetworksImpl(this);
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = new AllAnalyserImpl(this);
		//            std::vector<Relationship> relationships = analyser.getAllRelationships();
		//            networks.addRelationships(relationships);
		//            return networks;
		//        }
		//        
		//        // First get the set of arcs using the arc role
		//        Set<String> arcIndices = getArcIndices();
		//        for ( std::string index: arcIndices) {
		//            Arc arc = this.getXMLResource(index);
		//            std::vector<ArcEnd> sources = arc.getSourceFragments();
		//            std::vector<ArcEnd> targets = arc.getTargetFragments();
		//            for (ArcEnd source: sources) {
		//                for (ArcEnd target: targets) {
		//                    Fragment s = null;
		//                    Fragment t = null;
		//                    if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                        s = ((xercesc::Locator) source).getTarget();
		//                    else s = source;
		//                    if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                        t = ((xercesc::Locator) target).getTarget();
		//                    else t = target;
		//                    networks.addRelationship(new Relationship(arc,s,t));
		//                }
		//            }
		//        }
		//        return networks;        
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getNetworks(String)
		//     */
		//    public Networks getNetworks( std::string arcrole) {
		//
		//        Networks networks = new NetworksImpl(this);
		//    	
		//        for ( std::string linkRole: getLinkRoles(arcrole)) {
		//            Set<String> linkIndices = getExtendedLinkIndices(linkRole);
		//            for ( std::string linkIndex: linkIndices) {
		//
		//                Set<String> arcIndices = getArcIndices(arcrole,linkIndex);
		//                for ( std::string index: arcIndices) {
		//                    Arc arc = this.getXMLResource(index);
		//                    std::vector<ArcEnd> sources = arc.getSourceFragments();
		//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
		//                    for (ArcEnd source: sources) {
		//                        for (ArcEnd target: targets) {
		//                            Fragment s = null;
		//                            Fragment t = null;
		//                            if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                                s = ((xercesc::Locator) source).getTarget();
		//                            else s = source;
		//                            if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                                t = ((xercesc::Locator) target).getTarget();
		//                            else t = target;
		//                            networks.addRelationship(new Relationship(arc,s,t));
		//                        }
		//                    }
		//                }
		//            }
		//        }
		//        
		//        logger.debug("network size = " + networks.getSize());
		//    	return networks;    	
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getNetworks(String,String)
		//     */
		//    public Networks getNetworks( std::string linkRole,  std::string arcrole) {
		//
		//        Networks networks = new NetworksImpl(this);
		//
		//        // Use persisted relationships if they are being used.
		//        if (this.isPersistingRelationships()) {
		//            networks.addRelationships(getAnalyser().getRelationships(linkRole,arcrole));
		//            return networks;
		//        }
		//        
		//        Set<String> linkIndices = getExtendedLinkIndices(linkRole);
		//        logger.debug(linkIndices.size() + " extended links with given link and arc roles.");
		//        for ( std::string linkIndex: linkIndices) {
		//
		//            Set<String> arcIndices = getArcIndices(arcrole,linkIndex);
		//            logger.debug(arcIndices.size() + " arcs with arcrole in given extended link.");
		//            for ( std::string index: arcIndices) {
		//                Arc arc = this.getXMLResource(index);
		//                std::vector<ArcEnd> sources = arc.getSourceFragments();
		//                std::vector<ArcEnd> targets = arc.getTargetFragments();
		//                for (ArcEnd source: sources) {
		//                    for (ArcEnd target: targets) {
		//                        Fragment s = null;
		//                        Fragment t = null;
		//                        if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                            s = ((xercesc::Locator) source).getTarget();
		//                        else s = source;
		//                        if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
		//                            t = ((xercesc::Locator) target).getTarget();
		//                        else t = target;
		//                        networks.addRelationship(new Relationship(arc,s,t));
		//                    }
		//                }
		//            }
		//        } 
		//        
		//        logger.debug("network size = " + networks.getSize());
		//        return networks;        
		//    }
		//
		//    

		//     * @param arcrole The arcrole to use to identify the arcs to retrieve.
		//     * @return the list of arc fragments with a given arc role value.
		//     * @throws XBRLException
		//     */
		//    private std::vector<Arc> getArcsWithArcrole( std::string arcrole) {
		//    	 std::string query = "#roots#[*/*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]";
		//    	List<Arc> arcs = this.<Arc>queryForXMLResources(query);
		//    	logger.debug("#arcs with given arcrole = " + arcs.size());
		//    	return arcs;
		//    }
		//    

		std::vector<LabelResource> getLabels( const std::string& fragment,  
			const std::string& linkRole,  
			const std::string& resourceRole,  
			const std::string& language) 
		{

			//if (this.isPersistingRelationships()) {
			//     std::string query = "#roots#[@label and @type='" + Relationship.class.getName() + "' and @sourceIndex='" + fragment + "'";
			//    if (linkRole != null) query += " and @linkRole='" + linkRole + "'"; 
			//    if (resourceRole != null) query += " and @targetRole='" + resourceRole + "'"; 
			//    if (language != null) query += " and @targetLanguage='" + language + "'"; 
			//    query += "]";
			//    
			//    std::vector<Relationship> relationships = this.<Relationship>queryForXMLResources(query);
			//    std::vector<LabelResource> labels = new Vector<LabelResource>();
			//    for (const Relationship& relationship: relationships) {
			//        labels.add(relationship.<LabelResource>getTarget());
			//    }
			//    return labels;
			//}

			//try {

			//    Networks labelNetworks = this.getNetworksFrom(fragment,linkRole,Constants.LabelArcrole);
			//    labelNetworks.addAll(this.getNetworksFrom(fragment,linkRole,Constants.GenericLabelArcrole));
			//    
			//    std::vector<LabelResource> labels = new Vector<LabelResource>();
			//    for (const Network& network: labelNetworks) {
			//        RELATIONSHIPS: for (const Relationship& relationship: network.getAllActiveRelationships()) {
			//            LabelResource label = (LabelResource) relationship.getTarget();
			//            if (resourceRole == null && language == null) {
			//                labels.add(label);
			//                continue RELATIONSHIPS;
			//            }
			//            bool languagesMatch = false;
			//            bool resourceRolesMatch = false;
			//             std::string l = label.getLanguage();
			//             std::string r = label.getResourceRole();
			//            
			//            if (language == null) languagesMatch = true;
			//            else if (l != null && l.equals(language)) languagesMatch = true; 

			//            if (resourceRole == null) resourceRolesMatch = true;
			//            else if (resourceRole != null && resourceRole != null && r.equals(resourceRole)) resourceRolesMatch = true; 

			//            if (languagesMatch && resourceRolesMatch) labels.add(label); 
			//        }
			//    }
			//    return labels;            
			//} catch (XBRLException e) {
			//    throw e;
			//}

			return std::vector<LabelResource>();
		}

		std::vector<LabelResource> getLabels( const std::string& fragment,  
			const std::string& resourceRole,  
			const std::string& language) 
		{
			return getLabels(fragment,NULL,resourceRole,language);
		}


		std::vector<LabelResource> getLabelsWithLanguage( const std::string& fragment,  
			const std::string& language) 
		{
			return getLabels(fragment,NULL,NULL,language);
		}


		//     * @see Store#getLabels(String)
		//     */
		//    public std::vector<LabelResource> getLabels( std::string fragment) {
		//        return this.getLabels(fragment,null,null,null);
		//    }    
		//    

		//     * @see Store#getLabelsWithResourceRole(String, String)
		//     */
		//    public std::vector<LabelResource> getLabelsWithResourceRole( std::string fragment,  std::string resourceRole) {
		//        return this.getLabels(fragment,null,resourceRole,null);
		//    }
		//    

		//     * @see Store#getReferences(String, String, String, String)
		//     */
		//    public std::vector<ReferenceResource> getReferences( std::string fragment,  std::string linkRole,  std::string resourceRole,  std::string language) {
		//
		//        if (this.isPersistingRelationships()) {
		//             std::string query = "#roots#[@reference and @sourceIndex='" + fragment + "'";
		//            if (linkRole != null) query += " and @linkRole='" + linkRole + "'"; 
		//            if (resourceRole != null) query += " and @targetRole='" + resourceRole + "'"; 
		//            if (language != null) query += " and @targetLanguage='" + language + "'"; 
		//            query += "]";
		//            std::vector<Relationship> relationships = this.<Relationship>queryForXMLResources(query);
		//            std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
		//            for (const Relationship& relationship: relationships) {
		//                references.add(relationship.<ReferenceResource>getTarget());
		//            }
		//            return references;
		//        }
		//
		//        try {
		//
		//            Networks referenceNetworks = this.getNetworksFrom(fragment,linkRole,Constants.ReferenceArcrole);
		//            referenceNetworks.addAll(this.getNetworksFrom(fragment,linkRole,Constants.GenericReferenceArcrole));
		//            
		//            std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
		//            for (const Network& network: referenceNetworks) {
		//                RELATIONSHIPS: for (const Relationship& relationship: network.getAllActiveRelationships()) {
		//                    ReferenceResource reference = (ReferenceResource) relationship.getTarget();
		//                    if (resourceRole == null && language == null) {
		//                        references.add(reference);
		//                        continue RELATIONSHIPS;
		//                    }
		//                    bool languagesMatch = false;
		//                    bool resourceRolesMatch = false;
		//                     std::string l = reference.getLanguage();
		//                     std::string r = reference.getResourceRole();
		//                    
		//                    if (language == null) languagesMatch = true;
		//                    else if (l != null && l.equals(language)) languagesMatch = true; 
		//
		//                    if (resourceRole == null) resourceRolesMatch = true;
		//                    else if (resourceRole != null && resourceRole != null && r.equals(resourceRole)) resourceRolesMatch = true; 
		//
		//                    if (languagesMatch && resourceRolesMatch) references.add(reference); 
		//                }
		//            }
		//            return references;            
		//        } catch (XBRLException e) {
		//            throw e;
		//        }        
		//    }
		//        

		//     * @see Store#getReferences(String, String, String)
		//     */
		//    public std::vector<ReferenceResource> getReferences( std::string fragment,  std::string resourceRole,  std::string language) {
		//        return this.getReferences(fragment,null,resourceRole,language);
		//    }
		//    

		std::vector<ReferenceResource> getReferencesWithLanguage( const std::string& fragment,  const std::string& language) {
			//		        return this.getReferences(fragment,null,null,language);
			return std::vector<ReferenceResource>();
		}


		//     * @see Store#getReferences(String)
		//     */
		//    public std::vector<ReferenceResource> getReferences( std::string fragment) {
		//        return this.getReferences(fragment,null,null,null);
		//    }        
		//    

		//     * @see Store#getReferencesWithResourceRole(String, String)
		//     */
		//    public std::vector<ReferenceResource> getReferencesWithResourceRole( std::string fragment,  std::string resourceRole) {
		//        return this.getReferences(fragment,null,resourceRole,null);
		//    }
		//    

		//     * @see Store#getArcs(URI, String)
		//     */
		//    public std::vector<Arc> getArcs(URI arcrole,  std::string linkIndex) {
		//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]";
		//        std::vector<Arc> arcs = this.<Arc>queryForXMLResources(query);
		//        logger.debug("#arcs with given arcrole in given extended link = " + arcs.size());
		//        return arcs;
		//    }
		//    

		//     * @see Store#getArcs(String)
		//     */
		//    public std::vector<Arc> getArcs( std::string linkIndex) {
		//         std::string query = "#roots#[@type='org.xbrlapi.impl.ArcImpl' and @parentIndex='" + linkIndex + "']";
		//        std::vector<Arc> arcs = this.<Arc>queryForXMLResources(query);
		//        return arcs;
		//    }    
		//    

		//     * @see Store#getArcIndicesWithArcrole(String)
		//     */
		//    public Set<String> getArcIndicesWithArcrole( std::string arcrole) {
		//         std::string query = "#roots#[*/*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]/@index";
		//        return this.queryForStrings(query);
		//    }
		//    

		//     * @param arcrole The arcrole to use to identify the arcs to retrieve.
		//     * @param linkIndex The index of the extended link containing the arcs to retrieve.
		//     * @return the list of indices of arcs matching the selection criteria.
		//     * @throws XBRLException
		//     */
		//    private Set<String> getArcIndices( std::string arcrole,  std::string linkIndex) {
		//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]/@index";
		//        Set<String> indices = this.queryForStrings(query);
		//        return indices;
		//    }
		//    

		//     * @see Store#getArcIndicesWithLinkIndex(String)
		//     */
		//    public Set<String> getArcIndicesWithLinkIndex( std::string linkIndex) {
		//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*/@xlink:type='arc']/@index";
		//        Set<String> indices = this.queryForStrings(query);
		//        return indices;
		//    }    
		//    

		//     * @see Store#getExtendedLinkIndices(String)
		//     */
		//    public Set<String> getExtendedLinkIndices( std::string linkRole) {
		//         std::string query = "#roots#[*/*[@xlink:role='" + linkRole + "' and @xlink:type='extended']]/@index";
		//        Set<String> indices = this.queryForStrings(query);
		//        logger.debug("# extended links with given link role = " + indices.size());
		//        return indices;
		//    }
		//

		//     * @return the list of indices of arcs in the data store.
		//     * @throws XBRLException
		//     */
		//    private Set<String> getArcIndices() {
		//         std::string query = "for $root in #roots#[@type='"+ArcImpl.class.getName()+"'] return $root/@index";
		//        return this.queryForStrings(query);
		//    }    
		//

		//     * @see Store#getFragmentsFromDocument(URI, String)
		//     */
		//    public <F extends Fragment> std::vector<F> getFragmentsFromDocument(URI uri,  std::string interfaceName) {
		//        URI matchURI = getMatcher().getMatch(uri);
		//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='org.xbrlapi.impl." + interfaceName + "Impl']";        
		//        if (interfaceName.indexOf(".") > -1) {
		//            query = "#roots#[@uri='"+ matchURI + "' and @type='" + interfaceName + "']";
		//        }
		//        return this.<F>queryForXMLResources(query);
		//    }
		//    

		//     * @see Store#getFragmentsFromDocument(URI, Class)
		//     */
		//    public <F extends Fragment> std::vector<F> getFragmentsFromDocument(URI uri, Class<?> fragmentClass) {
		//        URI matchURI = getMatcher().getMatch(uri);
		//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='"+fragmentClass.getName()+"']";        
		//        return this.<F>queryForXMLResources(query);
		//    }
		//    

		//     * @see Store#getFragmentIndicesFromDocument(URI, String)
		//     */
		//    public Set<String> getFragmentIndicesFromDocument(URI uri,  std::string interfaceName) {
		//        URI matchURI = getMatcher().getMatch(uri);
		//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='org.xbrlapi.impl." + interfaceName + "Impl']";        
		//        if (interfaceName.indexOf(".") > -1) {
		//            query = "#roots#[@uri='"+ matchURI + "' and @type='" + interfaceName + "']";
		//        }
		//        Set<String> result = this.queryForIndices(query);
		//        return result;
		//    }
		//    

		//     * @see Store#getFragmentIndicesFromDocument(URI)
		//     */
		//    public Set<String> getFragmentIndicesFromDocument(URI uri) {
		//        URI matchURI = getMatcher().getMatch(uri);
		//         std::string query = "#roots#[@uri='"+ matchURI + "']";
		//        Set<String> result = this.queryForIndices(query);
		//        return result;
		//        
		//    }
		//    

		//     * @see Store#getFragmentIndices(String)
		//     */
		//    public Set<String> getFragmentIndices( std::string interfaceName) {
		//        long start = System.currentTimeMillis();
		//         std::string query = "#roots#[@type='org.xbrlapi.impl." + interfaceName + "Impl']";        
		//        if (interfaceName.indexOf(".") > -1) {
		//            query = "#roots#[@type='" + interfaceName + "']";
		//        }
		//        query += "/@index";
		//        Set<String> result = this.queryForStrings(query);
		//        Double seconds = new Double(System.currentTimeMillis() - start) / new Double(1000);
		//        logger.debug("Seconds required = " + seconds);
		//        return result;
		//    }    
		//

		//     * @see Store#getFacts()
		//     */
		//    public list<Fact&> getFacts() {
		//    	List<Instance> instances = this.<Instance>getXMLResources("Instance");
		//    	return getFactsFromInstances(instances);
		//    }
		//

		//     * Helper method for common code in the getTuple methods.
		//     * @param instances The instances to retrieve tuples for.
		//     * @return a list of root tuples in the instances.
		//     * @throws XBRLException
		//     */
		//    private std::vector<Tuple> getTuplesFromInstances(List<Instance> instances) {
		//        std::vector<Tuple> tuples = new Vector<Tuple>();
		//        for (Instance instance: instances) {
		//            tuples.addAll(instance.getTuples());
		//        }
		//        return tuples;
		//    }    
		//

		//     * @see Store#getFacts(URI)
		//     */
		//    public list<Fact&> getFacts(URI uri) {
		//    	List<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
		//    	return this.getFactsFromInstances(instances);
		//    }
		//    

		//     * @see Store#getAllFacts(URI)
		//     */
		//    public list<Fact&> getAllFacts(URI uri) {
		//         std::string query = "for $root in #roots#[@uri='"+ uri +"' ] where $root/@fact return $root";
		//        return this.<Fact>queryForXMLResources(query);
		//    }
		//    

		//     * @see Store#getAllFacts()
		//     */
		//    public list<Fact&> getAllFacts() {
		//         std::string query = "for $root in #roots# where $root/@fact return $root";
		//        return this.<Fact>queryForXMLResources(query);
		//    }    
		//

		//     * @see org.xbrlapi.data.Store#getRootFragmentForDocument(URI)
		//     */
		//    public <F extends Fragment> F getRootFragmentForDocument(URI uri) {
		//    	List<F> fragments = this.<F>queryForXMLResources("#roots#[@uri='" + uri + "' and @parentIndex='']");
		//    	if (fragments.size() == 0) return null;
		//    	if (fragments.size() > 1) throw XBRLException("Two fragments identify themselves as roots of the one document.");
		//    	return fragments.get(0);
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getRootFragments()
		//     */
		//    public <F extends Fragment> std::vector<F> getRootFragments() {
		//    	List<F> roots =  this.<F>queryForXMLResources("#roots#[@uri and @parentIndex='']");
		//    	return roots;
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getRootFragments(String)
		//     */
		//    public <F extends Fragment> std::vector<F> getRootFragments( std::string interfaceName) {
		//         std::string query = "for $root in #roots#[@parentIndex=''] where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
		//        if (interfaceName.indexOf(".") > -1) {
		//            query = "for $root in #roots#[@parentIndex=''] where $root/@type='" + interfaceName + "' return $root";
		//        }
		//        return this.<F>queryForXMLResources(query);
		//    }    
		//

		//     * @see org.xbrlapi.data.Store#getLanguage(String, String)
		//     */
		//    public Language getLanguage( std::string encoding,  std::string code) {
		//        if (encoding == null) throw XBRLException("The language code must not be null.");
		//        if (code == null) throw XBRLException("The language name encoding must not be null.");
		//         std::string query = "#roots#[@type='org.xbrlapi.impl.LanguageImpl' and "+ Constants.XBRLAPIPrefix+ ":" + "data/lang:language/lang:encoding='" + encoding + "' and " + Constants.XBRLAPIPrefix + ":" + "data/lang:language/lang:code='" + code + "']";
		//        std::vector<Language> languages = this.<Language>queryForXMLResources(query);
		//        if (languages.size() == 0) return null;
		//        return languages.get(0);
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getLanguages(String)
		//     */
		//    public std::vector<Language> getLanguages( std::string code) {
		//        if (code == null) throw XBRLException("The language code must not be null.");
		//         std::string query = "#roots#[@type='org.xbrlapi.impl.LanguageImpl' and */lang:language/lang:code='" + code + "']";
		//        return this.<Language>queryForXMLResources(query);
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getLanguageMap(String)
		//     */
		//    public Map<String,Language> getLanguageMap( std::string code) {
		//        std::vector<Language> languages = this.getLanguages(code);
		//        Map<String,Language> result = new HashMap<String,Language>();
		//        for (Language language: languages) {
		//            result.put(language.getEncoding(),language);
		//        }
		//        return result;
		//    }    
		//

		//     * @see Store#queryForString(String)
		//     */
		//    public  std::string queryForString( std::string query) {
		//        Set<String> strings = queryForStrings(query);
		//        if (strings.size() == 0) return null;
		//        if (strings.size() > 1) throw XBRLException(query + " returned more than one string.");
		//        for ( std::string string: strings) return string;
		//        throw XBRLException("This exception cannot be thrown. There is a bug in the software.");
		//    }
		//

		//     * This method is provided as a helper method for the getFact methods.
		//     * @param instances The list of instance fragments to extract facts from.
		//     * @return The list of facts in the instances.
		//     * @throws XBRLException
		//     */
		//    private list<Fact&> getFactsFromInstances(List<Instance> instances) {
		//        list<Fact&> facts = new Vector<Fact>();
		//        for (Instance instance: instances) {
		//            facts.addAll(instance.getChildFacts());
		//        }
		//        return facts;
		//    }
		//    

		//     * Helper method for common code in the getItem methods.
		//     * @param instances The instances to retrieve items for.
		//     * @return a list of root items in the instances.
		//     * @throws XBRLException
		//     */
		//    private std::vector<Item> getItemsFromInstances(List<Instance> instances) {
		//        std::vector<Item> items = new Vector<Item>();
		//        for (Instance instance: instances) {
		//            items.addAll(instance.getChildItems());
		//        }
		//        return items;
		//    }
		//

		//     * @see Store#getItems()
		//     */
		//    public std::vector<Item> getItems() {
		//        std::vector<Instance> instances = this.<Instance>getXMLResources("Instance");
		//        return getItemsFromInstances(instances);
		//    }
		//    

		//     * @see Store#getTuples()
		//     */
		//    public std::vector<Tuple> getTuples() {
		//        return this.<Tuple>getXMLResources(TupleImpl.class);
		//    }
		//

		//     * @see Store#getItems(URI)
		//     */
		//    public std::vector<Item> getItems(URI uri) {
		//        std::vector<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
		//        return this.getItemsFromInstances(instances);
		//    }
		//    

		//     * @see Store#getTuples(URI)
		//     */
		//    public std::vector<Tuple> getTuples(URI uri) {
		//        std::vector<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
		//        return this.getTuplesFromInstances(instances);
		//    }
		//

		//     * @see Store#getNetworkRoots(String, String)
		//     */
		//    public <F extends Fragment> Set<F> getNetworkRoots( std::string linkRole,  std::string arcrole) {
		//        
		//        if (this.isPersistingRelationships()) {
		//            return getAnalyser().<F>getRoots(linkRole,arcrole);
		//        }
		//        
		//        // Get the links that contain the network declaring arcs.
		//         std::string linkQuery = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl' and "+ Constants.XBRLAPIPrefix+ ":" + "data/*[@xlink:role='" + linkRole + "']]";
		//        std::vector<ExtendedLink> links = this.<ExtendedLink>queryForXMLResources(linkQuery);
		//        
		//        // Get the arcs that declare the relationships in the network.
		//        // For each arc map the ids of the fragments at their sources and targets.
		//        HashMap<String,String> sourceIds = new HashMap<String,String>();
		//        HashMap<String,String> targetIds = new HashMap<String,String>();
		//        for (int i=0; i<links.size(); i++) {
		//            ExtendedLink link = links.get(i);
		//            std::vector<Arc> arcs = link.getArcs();
		//            for (const Arc& arc: arcs) {
		//                if (arc.getArcrole().equals(arcrole)) {
		//                    std::vector<ArcEnd> sources = arc.getSourceFragments();
		//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
		//                    for (int k=0; k<sources.size(); k++) {
		//                        sourceIds.put(sources.get(k).getIndex(),"");
		//                    }
		//                    for (int k=0; k<sources.size(); k++) {
		//                        targetIds.put(targets.get(k).getIndex(),"");
		//                    }
		//                }
		//            }
		//        }
		//        
		//        // Get the root resources in the network
		//        Set<F> roots = new TreeSet<F>();
		//        for ( std::string id: sourceIds.keySet()) {
		//            if (! targetIds.containsKey(id)) {
		//                roots.add(this.<F>getXMLResource(id));
		//            }
		//        }
		//        return roots;
		//    }    
		//    
		//    

		//     * @see Store#getConcept(String, String)
		//     */
		//    public Concept getConcept( std::string namespace,  std::string name) {
		//        return this.<Concept>getGlobalDeclaration(namespace,name);
		//    }
		//    

		//     * @see Store#getGlobalDeclaration(String, String)
		//     */
		//    public <D extends SchemaDeclaration> D getGlobalDeclaration( std::string namespace,  std::string name) {
		//        Schema schema = this.getSchema(namespace);
		//        D declaration = schema.<D>getGlobalDeclaration(name);
		//        if (declaration == null) {
		//            throw XBRLException("No matching global schema declarations were found for " + namespace + ":" + name + ".");
		//        }
		//        return declaration;
		//    }    
		//

		//     * @return a list of roleType fragments
		//     * @throws XBRLException
		//     */
		//    public std::vector<RoleType> getRoleTypes() {
		//        return this.<RoleType>getXMLResources("RoleType");
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getRoleTypes(String)
		//     */
		//    public std::vector<RoleType> getRoleTypes( std::string uri) {
		//         std::string query = "#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/link:roleType/@roleURI='" + uri + "']";
		//        return this.<RoleType>queryForXMLResources(query);
		//    }    
		//    

		//     * @see Store#getArcroleTypes()
		//     */
		//    public std::vector<ArcroleType> getArcroleTypes() {
		//        return this.<ArcroleType>getXMLResources("ArcroleType");
		//    }
		//    

		//     * @see Store#getArcroleTypes(String)
		//     */
		//    public std::vector<ArcroleType> getArcroleTypes( std::string uri) {
		//         std::string query = "#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/link:arcroleType/@arcroleURI='" + uri + "']";
		//        return this.<ArcroleType>queryForXMLResources(query);
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getResourceRoles()
		//     */
		//    public std::vector<String> getResourceRoles() {
		//        HashMap<String,String> roles = new HashMap<String,String>();
		//        list<Resource> resources = this.<Resource>queryForXMLResources("#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/*/@xlink:type='resource']");
		//        for (Resource resource: resources) {
		//        	 std::string role = resource.getResourceRole();
		//            if (! roles.containsKey(role)) roles.put(role,"");
		//        }
		//        std::vector<String> result = new Vector<String>();
		//        result.addAll(roles.keySet());
		//        return result;
		//    }    
		//

		//     * @see org.xbrlapi.data.Store#getMinimumDocumentSet(URI)
		//     */
		//    public Set<URI> getMinimumDocumentSet(URI uri) {
		//        std::vector<URI> starters = new Vector<URI>();
		//        starters.add(uri);
		//        return this.getMinimumDocumentSet(starters);
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getMinimumDocumentSet(Collection)
		//     */
		//    public Set<URI> getMinimumDocumentSet(Collection<URI> starters) {
		//        
		//        Set<URI> minimumDocumentSet = new HashSet<URI>();
		//        Set<URI> checkThese = new HashSet<URI>();
		//        checkThese.addAll(starters);
		//        
		//        while (checkThese.size() > 0) {
		//            URI document = checkThese.iterator().next();
		//            for (URI referencedDocument: getReferencedDocuments(document)) {
		//                if ((! minimumDocumentSet.contains(referencedDocument)) && (! checkThese.contains(referencedDocument)))
		//                    checkThese.add(referencedDocument);
		//            }
		//            
		//            minimumDocumentSet.add(document);
		//            checkThese.remove(document);
		//        }
		//        
		//        return minimumDocumentSet;
		//
		//    }
		// 

		//     * @see Store#getExtendedLinks(String)
		//     */
		//    public std::vector<ExtendedLink> getExtendedLinks( std::string linkrole) {
		//         std::string query = "#roots#[*/*[@xlink:type='extended' and @xlink:role='" + linkrole + "']]";
		//        std::vector<ExtendedLink> links = this.<ExtendedLink>queryForXMLResources(query);
		//        return links;
		//    }
		//

		//     * @see Store#getMinimalNetworksWithArcrole(Fragment, String)
		//     */
		//    public synchronized Networks getMinimalNetworksWithArcrole(const Fragment& fragment,  std::string arcrole) {
		//        Set<Fragment> set = new HashSet<Fragment>();
		//        set.add(fragment);
		//        return this.getMinimalNetworksWithArcrole(set,arcrole);
		//    }    
		//    

		//     * @see Store#getMinimalNetworksWithArcrole(Set, String)
		//     */
		//    public synchronized Networks getMinimalNetworksWithArcrole(Set<Fragment> fragments,  std::string arcrole) {
		//
		//        try {
		//            Networks networks = new NetworksImpl(this);
		//            for (const Fragment& fragment: fragments) {
		//                augmentNetworksForFragment(fragment,arcrole,networks);
		//            }
		//            return networks;
		//        } catch (Throwable t) {
		//            throw XBRLException("There was a problem getting minimal networks with arcrole " + arcrole,t);
		//        }
		//    }
		//    

		//     * @see Store#augmentNetworksForFragment(Fragment, String, Networks)
		//     */
		//    public synchronized void augmentNetworksForFragment(const Fragment& fragment,  std::string arcrole, Networks networks) {
		//        for (const Network& network: networks.getNetworks(arcrole)) {
		//            if (network.hasActiveRelationshipsTo(fragment.getIndex())) return;
		//        }
		//        
		//        for (const Relationship& relationship: this.getRelationshipsTo(fragment.getIndex(),null,arcrole)) {
		//            networks.addRelationship(relationship);
		//        }
		//        
		//        for (const Network& network: networks.getNetworks(arcrole)) {
		//            SortedSet<Relationship> activeRelationships = network.getActiveRelationshipsTo(fragment.getIndex());
		//            for (const Relationship& activeRelationship: activeRelationships) {
		//                Fragment source = activeRelationship.getSource();
		//                augmentNetworksForFragment(source,arcrole,networks);
		//            }
		//        }
		//    }
		//    

		//     * @see Store#augmentNetworkForFragment(Fragment, Network)
		//     */
		//    public synchronized void augmentNetworkForFragment(const Fragment& fragment, const Network& network) {
		//
		//        if (network.hasActiveRelationshipsTo(fragment.getIndex())) return;
		//                
		//        for (const Relationship& relationship: this.getRelationshipsTo(fragment.getIndex(),network.getLinkRole(),network.getArcrole())) {
		//            network.addRelationship(relationship);
		//        }
		//        SortedSet<Relationship> activeRelationships = network.getActiveRelationshipsTo(fragment.getIndex());
		//        for (const Relationship& activeRelationship: activeRelationships) {
		//            Fragment source = activeRelationship.getSource();
		//            augmentNetworkForFragment(source,network);
		//        }
		//    }
		//    

		//     * @see Store#getMinimalNetwork(Set, String, String)
		//     */
		//    public Network getMinimalNetwork(Set<Fragment> fragments,  std::string linkRole,  std::string arcrole) {
		//
		//        try {
		//            Network network = new NetworkImpl(this, linkRole, arcrole);
		//            for (const Fragment& fragment: fragments) {
		//                augmentNetworkForFragment(fragment,network);
		//            }
		//            return network;
		//        } catch (Throwable t) {
		//            throw XBRLException("There was a problem getting minimal networks with arcrole " + arcrole,t);
		//        }    
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getArcroles()
		//     */
		//    public Set<String> getArcroles() {
		//         std::string query = "#roots#/*/*[@xlink:type='arc']/@xlink:arcrole";
		//        Set<String> values = this.queryForStrings(query);
		//        Set<String> arcroles = new TreeSet<String>();
		//        for ( std::string value: values) arcroles.add(value);
		//        return arcroles;
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getLinkRoles()
		//     */
		//    public Set<String> getLinkRoles() {
		//         std::string query = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl']/*/*/@xlink:role";
		//        Set<String> values = this.queryForStrings(query);
		//        Set<String> linkRoles = new TreeSet<String>();
		//        for ( std::string value: values) linkRoles.add(value);
		//        return linkRoles;
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getLinkRoles(String)
		//     */
		//    public Set<String> getLinkRoles( std::string arcrole) {
		//        
		//         std::string query = "#roots#[*/*[@xlink:type='arc' and @xlink:arcrole='" + arcrole + "']]/@parentIndex";
		//        Set<String> linkIndices = this.queryForStrings(query);
		//        Set<String> linkRoles = new TreeSet<String>();
		//        for ( std::string index: linkIndices) {
		//            ExtendedLink link = this.getXMLResource(index);
		//            linkRoles.add(link.getLinkRole());
		//        }
		//        return linkRoles;
		//    }
		//    

		//     * @see org.xbrlapi.data.Store#getArcroles(String)
		//     */
		//    public Set<String> getArcroles( std::string linkRole) {
		//        
		//         std::string query = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl' and */*/@xlink:role='" + linkRole + "']/@index";
		//        Set<String> linkIndices = this.queryForStrings(query);
		//        Set<String> arcroles = new TreeSet<String>();
		//        for ( std::string linkIndex: linkIndices) {
		//            query = "#roots#[@parentIndex='" + linkIndex + "' and */*/@xlink:type='arc']/*/*/@xlink:arcrole";
		//            Set<String> candidates = queryForStrings(query);
		//            arcroles.addAll(candidates);
		//        }
		//        Set<String> result = new TreeSet<String>();
		//		for ( std::string arcrole : arcroles) result.add(arcrole);
		//
		//        return result;
		//
		//    }
		//

		//     * @see Store#getTargets(String, String, String)
		//     */
		//    @SuppressWarnings("unchecked")
		//    public <F extends Fragment> std::vector<F> getTargets( std::string sourceIndex,  std::string linkRole,  std::string arcrole) {
		//        
		//        SortedSet<Relationship> relationships = this.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
		//        Set<F> targets = new HashSet<F>();
		//        for (const Relationship& relationship: relationships) {
		//            try {
		//                targets.add((F) relationship.getTarget());
		//            } catch (ClassCastException e) {
		//                throw XBRLException("A target fragment is of the wrong type: " + relationship.getTarget().getType(),e);
		//            }
		//        }
		//        return new Vector<F>(targets);
		//        
		//    }
		//    

		//     * @see Store#getSources(String, String, String)
		//     */
		//    @SuppressWarnings("unchecked")
		//    public <F extends Fragment> std::vector<F> getSources( std::string targetIndex,  std::string linkRole,  std::string arcrole) {
		//        
		//        SortedSet<Relationship> relationships = this.getRelationshipsTo(targetIndex,linkRole,arcrole);
		//        Set<F> sources = new HashSet<F>();
		//        for (const Relationship& relationship: relationships) {
		//            try {
		//                sources.add((F) relationship.getSource());
		//            } catch (ClassCastException e) {
		//                throw XBRLException("A source fragment is of the wrong type: " + relationship.getSource().getType(),e);
		//            }
		//        }
		//        return new Vector<F>(sources);        
		//
		//    }
		//    

		//     * @see Store#getSourceIndices(String, String, String)
		//     */
		//    public Set<String> getSourceIndices( std::string targetIndex,  std::string linkRole,  std::string arcrole) {
		//        if (this.isPersistingRelationships()) {
		//             std::string lr = "";
		//             std::string ar = "";
		//            if (linkRole != null) {
		//                lr = " and @linkRole='"+ linkRole +"'";            
		//            }
		//            if (arcrole != null) {
		//                ar = " and @arcRole='"+ arcrole +"'";            
		//            }
		//             std::string query = "for $root in #roots#[@targetIndex='"+ targetIndex +"'" + ar + lr + "] return string($root/@sourceIndex)";
		//            return this.queryForStrings(query);
		//        } 
		//        
		//        Set<String> indices = new HashSet<String>();
		//        Networks networks = this.getNetworksTo(targetIndex,linkRole,arcrole);
		//        for (const Network& network: networks) {
		//            for (const Relationship& r: network.getActiveRelationshipsTo(targetIndex)) {
		//                indices.add(r.getSourceIndex());                    
		//            }
		//        }
		//        return indices;
		//
		//    }
		//    

		//     * @see Store#getRelationshipsFrom(String,String,String)
		//     */
		//    public SortedSet<Relationship> getRelationshipsFrom( std::string sourceIndex, std::string linkRole,  std::string arcrole) {
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = this.getAnalyser();
		//            return analyser.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
		//        }
		//
		//        SortedSet<Relationship> relationships = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//        Networks networks = this.getNetworksFrom(sourceIndex,linkRole,arcrole);
		//        for (const Network& network: networks) {
		//            relationships.addAll(network.getActiveRelationshipsFrom(sourceIndex));
		//        }
		//        return relationships;
		//    }
		//    

		//     * @see Store#hasAllRelationships(URI)
		//     */
		//    public bool hasAllRelationships(URI document) {
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = this.getAnalyser();
		//            return analyser.hasAllRelationships(document);
		//        }
		//        return false;
		//
		//    }    
		//

		//     * @see Store#getRelationshipsTo(String, String, String)
		//     */
		//    public SortedSet<Relationship> getRelationshipsTo( std::string targetIndex, std::string linkRole,  std::string arcrole) {
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = this.getAnalyser();
		//            return analyser.getRelationshipsTo(targetIndex,linkRole,arcrole);
		//        }
		//        SortedSet<Relationship> relationships = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//        Networks networks = this.getNetworksTo(targetIndex,linkRole,arcrole);
		//        logger.debug("# networks = " + networks.getSize());
		//        for (const Network& network: networks) {
		//            relationships.addAll(network.getActiveRelationshipsTo(targetIndex));
		//        }
		//        
		//        return relationships;
		//    }    
		//    

		//     * @see Store#getNetworksFrom(String,String,String)
		//     */
		//    public Networks getNetworksFrom( std::string sourceIndex, std::string linkRole,  std::string arcrole) {
		//
		//        Networks networks = new NetworksImpl(this);
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = new AllAnalyserImpl(this);
		//            SortedSet<Relationship> relationships = analyser.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
		//            logger.debug("# relationships from = " + relationships.size());
		//            networks.addRelationships(relationships);
		//            return networks;
		//        }
		//        
		//        Fragment source = this.getXMLResource(sourceIndex);
		//
		//        Relationship relationship = null;
		//
		//        // If we have a resource, it could be related directly via arcs to relatives.
		//        if (source.isa(ResourceImpl.class)) {
		//            if ((linkRole == null) || ((Resource) source).getExtendedLink().getLinkRole().equals(linkRole)) {
		//                
		//                std::vector<Arc> arcs = null;
		//                if (arcrole == null) arcs = ((ArcEnd) source).getArcsFrom();
		//                else  arcs = ((ArcEnd) source).getArcsFromWithArcrole(arcrole);
		//
		//                for (const Arc& arc: arcs) {
		//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
		//                    for (ArcEnd end: targets) {
		//                        if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
		//                            Fragment target = ((xercesc::Locator) end).getTarget();
		//                            relationship = new Relationship(arc,source,target);
		//                        } else {
		//                            relationship = new Relationship(arc,source,end);
		//                        }               
		//                        networks.addRelationship(relationship);
		//                    }
		//                }
		//            }
		//        }
		//
		//        HashMap<String,ExtendedLink> links = new HashMap<String,ExtendedLink>();
		//        
		//        // Next get the locators for the fragment to find indirect relatives
		//        std::vector<xercesc::Locator> locators = source.getReferencingLocators();
		//        
		//        LOCATORS: for (xercesc::Locator locator: locators) {
		//            if (linkRole != null) {
		//                ExtendedLink link = null;
		//                 std::string parentIndex = locator.getParentIndex();
		//                if (links.containsKey(parentIndex)) {
		//                    link = links.get(parentIndex);
		//                } else {
		//                    link = locator.getExtendedLink();
		//                    links.put(parentIndex,link);
		//                }
		//                if (! link.getLinkRole().equals(linkRole)) continue LOCATORS;
		//            }
		//            std::vector<Arc> arcs = locator.getArcsFromWithArcrole(arcrole);
		//            for (const Arc& arc: arcs) {
		//                std::vector<ArcEnd> targets = arc.getTargetFragments();
		//                for (ArcEnd end: targets) {
		//                    if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
		//                        Fragment target = ((xercesc::Locator) end).getTarget();
		//                        relationship = new Relationship(arc,source,target);
		//                    } else {
		//                        relationship = new Relationship(arc,source,end);
		//                    }
		//                    networks.addRelationship(relationship);
		//                }
		//            }
		//        }
		//        return networks;        
		//
		//    }
		//    
		//    public Networks getNetworksTo( std::string targetIndex, std::string linkRole,  std::string arcrole) {
		//        
		//        Networks networks = new NetworksImpl(this);
		//
		//        if (this.isPersistingRelationships()) {
		//            Analyser analyser = new AllAnalyserImpl(this);
		//            SortedSet<Relationship> relationships = analyser.getRelationshipsTo(targetIndex,linkRole,arcrole);
		//            logger.debug("# relationships to = " + relationships.size());
		//            networks.addRelationships(relationships);
		//            return networks;
		//        }
		//
		//        Fragment target = this.getXMLResource(targetIndex);
		//
		//        Relationship relationship = null;
		//
		//        // If we have a resource, it could be related directly via arcs to relatives.
		//        if (target.isa(ResourceImpl.class)) {
		//            if ((linkRole == null) || ((Resource) target).getExtendedLink().getLinkRole().equals(linkRole)) {
		//                std::vector<Arc> arcs = null;
		//                if (arcrole == null) arcs = ((ArcEnd) target).getArcsTo();
		//                else  arcs = ((ArcEnd) target).getArcsToWithArcrole(arcrole);
		//
		//                for (const Arc& arc: arcs) {
		//                    std::vector<ArcEnd> targets = arc.getSourceFragments();
		//                    for (ArcEnd end: targets) {
		//                        if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
		//                            Fragment source = ((xercesc::Locator) end).getTarget();
		//                            relationship = new Relationship(arc,source,target);
		//                        } else {
		//                            relationship = new Relationship(arc,end,target);
		//                        }               
		//                        networks.addRelationship(relationship);
		//                    }
		//                }
		//            }
		//        }
		//
		//        HashMap<String,ExtendedLink> links = new HashMap<String,ExtendedLink>();
		//        
		//        // Next get the locators for the fragment to find indirect relatives
		//        std::vector<xercesc::Locator> locators = target.getReferencingLocators();
		//        logger.debug("# locators to " + targetIndex + " = " + locators.size());
		//        LOCATORS: for (xercesc::Locator locator: locators) {
		//            
		//            if (linkRole != null) {
		//                
		//                // Make extended link retrieval use simple caching.
		//                ExtendedLink link = null;
		//                 std::string parentIndex = locator.getParentIndex();
		//                if (links.containsKey(parentIndex)) {
		//                    link = links.get(parentIndex);
		//                } else {
		//                    link = locator.getExtendedLink();
		//                    links.put(parentIndex,link);
		//                }
		//                
		//                // Ignore locator if the link role does not match.
		//                if (! link.getLinkRole().equals(linkRole)) continue LOCATORS;
		//            }
		//            
		//            std::vector<Arc> arcs = locator.getArcsToWithArcrole(arcrole);
		//            logger.debug("# arcs to " + targetIndex + " = " + arcs.size());
		//            for (const Arc& arc: arcs) {
		//                std::vector<ArcEnd> sources = arc.getSourceFragments();
		//                for (ArcEnd end: sources) {
		//                    if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
		//                        Fragment source = ((xercesc::Locator) end).getTarget();
		//                        relationship = new Relationship(arc,source,target);
		//                    } else {
		//                        relationship = new Relationship(arc,end,target);
		//                    }
		//                    networks.addRelationship(relationship);
		//                }
		//            }
		//        }
		//
		//        return networks;        
		//
		//    }    
		//
		//    // The persisted networks analyser
		//    transient private Analyser analyser = null;
		//    

		//     * @see Store#getAnalyser()
		//     */
		//    public Analyser getAnalyser() {
		//        return analyser;
		//    }
		//    

		//     * @see Store#setAnalyser(Analyser)
		//     */
		//    public void setAnalyser(Analyser analyser) {
		//        this.analyser = analyser;
		//    }
		//    

		/*
		* @see Store#isPersistingRelationships()
		*/
		bool isPersistingRelationships() 
		{
			return (analyser);
		}


		//     * @see org.xbrlapi.data.Store#getNetworksFrom(java.lang.String, String)
		//     */
		//    public Networks getNetworksFrom( std::string sourceIndex,  std::string arcrole) {
		//        return getNetworksFrom(sourceIndex,null,arcrole);       
		//    }
		//    

		//     * @see Store#getNetworksFrom(String)
		//     */
		//    public Networks getNetworksFrom( std::string sourceIndex) {
		//        return getNetworksFrom(sourceIndex,null,null);       
		//    }    
		//

		//     * @see Store#getNetworksTo(String, String)
		//     */
		//    public Networks getNetworksTo( std::string targetIndex,  std::string arcrole) {
		//        return getNetworksTo(targetIndex,null,arcrole);
		//    }
		//    

		//     * @see Store#getNetworksTo(String)
		//     */
		//    public Networks getNetworksTo( std::string targetIndex) {
		//        return getNetworksTo(targetIndex,null,null);
		//    }
		//

		//     * @see Store#getMissingDocumentURIs()
		//     */
		//    public Set<URI> getMissingDocumentURIs() {
		//        Set<URI> result = new HashSet<URI>();
		//         std::string query = "for $targetURI in #roots#[*/*[@xlink:type='locator' or @xlink:type='simple'], return distinct-values(string($fragment/@targetDocumentURI))";
		//        Set<String> uris = this.queryForStrings(query);
		//        for ( std::string uri: uris) {
		//            try {
		//                result.add(new URI(uri));
		//            } catch (URISyntaxException e) {
		//                throw XBRLException(uri + " has invalid syntax.",e);
		//            }
		//        }
		//        Set<URI> storedURIs = this.getDocumentURIs();
		//        result.removeAll(storedURIs);
		//        return result;
		//    }
		//

		//     * Set of loaders that are currently loading data into this store.
		//     */
		//    transient private int loadingStatus = 0;
		//    
		//public synchronized 
		bool requestLoadingRightsFor(const Poco::URI& document) 
		{
			if (loadingRights.find(document) == loadingRights.end()) 
			{
				loadingRights.insert(std::make_pair(document, loader));
				return true;
			}

			if (loadingRights[document] == loader) 
			{
				return true;
			}
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("Two loaders have been seeking loading rights for " + document.toString());
			return false;
		}

		void recindLoadingRightsFor(const Poco::URI& document) 
		{
			if (loadingRights.find(document) == loadingRights.end()) return;
			if (loadingRights[document] == loader) loadingRights.erase(document); //TODO remove erase??
		}

		//    
		//    protected void finalize() throws Throwable {
		//        try {
		//            sync();
		//            close();
		//        } finally {
		//            super.finalize();
		//        }
		//    }
		//

		//     * @see java.lang.Object#hashCode()
		//     */
		//    @Override
		//    public int hashCode() {
		//        final int prime = 31;
		//        int result = 1;
		//        result = prime * result
		//                + ((analyser == null) ? 0 : analyser.hashCode());
		//        result = prime * result + ((matcher == null) ? 0 : matcher.hashCode());
		//        result = prime
		//                * result
		//                + ((namespaceBindings == null) ? 0 : namespaceBindings
		//                        .hashCode());
		//        result = prime * result + ((uris == null) ? 0 : uris.hashCode());
		//        return result;
		//    }
		//

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
		//        if (matcher == null) {
		//            if (other.matcher != null)
		//                return false;
		//        } else if (matcher instanceof InStoreMatcherImpl) {
		//            // Avoid using Matcher.equals() test to prevent infinite recursion.
		//            if (! (other.matcher instanceof InStoreMatcherImpl)) return false;
		//            if (((InStoreMatcherImpl) matcher).getStore() != this) return false;
		//            if (((InStoreMatcherImpl) other.matcher).getStore() != other) return false;
		//        }
		//        if (namespaceBindings == null) {
		//            if (other.namespaceBindings != null)
		//                return false;
		//        } else if (!namespaceBindings.equals(other.namespaceBindings))
		//            return false;
		//        if (uris == null) {
		//            if (other.uris != null)
		//                return false;
		//        } else if (!uris.equals(other.uris))
		//            return false;
		//        return true;
		//    }
		//

		/*
		* @see Store#isLoading()
		*/
		bool isLoading() 
		{
			return (loadingStatus > 0);
		}

		void startLoading() 
		{
			loadingStatus++;
		}

		//synchronized
		void stopLoading()
		{
			loadingStatus--;
		}
		//    

		//     * @see Store#getSchemaContent(String, String)
		//     */
		//    public <F extends SchemaContent> F getSchemaContent( std::string namespace,  std::string name) {
		//        try {
		//
		//            // Get the uris of the containing schemas.
		//             std::string query = "for $root in #roots#[@parentIndex=''] where $root/xbrlapi:data/xsd:schema/@targetNamespace='" + namespace + "' return string($root/@uri)";
		//            Set<String> uris = this.queryForStrings(query);
		//            if (uris.size() == 0) throw XBRLException("The namespace does not match a schema in the data store.");
		//             std::string uriCriteria = "";
		//            for ( std::string uri: uris) {
		//                uriCriteria += " or @uri='"+uri+"'";
		//            }
		//            uriCriteria = uriCriteria.substring(4);// Delete the first or.
		//            uriCriteria = "(" + uriCriteria + ")";
		//            query = "for $root in #roots#["+uriCriteria+"] where $root/xbrlapi:data/*/@name='" + name + "' return $root";
		//            std::vector<F> candidates = this.<F>queryForXMLResources(query);
		//            if (candidates.size() == 0) throw XBRLException("The local name does not match content in a schema with the given namespace.");
		//            for (F candidate: candidates) {
		//                Schema schema = candidate.getSchema();
		//                if (namespace.equals(schema.getTargetNamespace()) && schema.isAncestorOf(candidate)) 
		//                    return candidate;
		//            }
		//        } catch (Throwable e) {
		//            logger.error(e.getMessage());
		//        }
		//        return null;
		//    }
		//

		//     * @see org.xbrlapi.data.Store#getSchema(String)
		//     */
		//    public Schema getSchema( std::string targetNamespace) {
		//        if (targetNamespace == null) throw XBRLException("The target namespace of the schema must not be null.");
		//         std::string query = "for $root in #roots#[@type='"+SchemaImpl.class.getName()+"'] where $root/*/xsd:schema/@targetNamespace='" + targetNamespace + "' return $root";
		//        std::vector<Schema> candidates = this.<Schema>queryForXMLResources(query);
		//        if (candidates.size() == 1) return candidates.get(0);
		//        if (candidates.size() == 0) return null;
		//         std::string message = "";
		//        for (Schema schema: candidates) {
		//            message += ": " + schema.getURI();
		//        }
		//        throw XBRLException("Schemas with URLs" + message + ", have the target namespace " + targetNamespace);
		//    }
		//

		//     * @param fragmentClass The full name of the class of fragment being handled
		//     * @return a map from fragment index to parent fragment index for all fragments with the given class name (type).
		//     * @throws XBRLException
		//     */
		//    private Map<String,String> getIndexMap(Class<?> fragmentClass) {
		//         std::string query = "for $root in #roots#[@type='" + fragmentClass.getName() + "'] return concat($root/@index,'#',$root/@parentIndex)";
		//        Set<String> pairs = this.queryForStrings(query);
		//        Map<String,String> map = new HashMap<String,String>();
		//        for ( std::string pair: pairs) {
		//            String[] indices = pair.split("#");
		//            map.put(indices[0],indices[1]);
		//        }
		//        return map;
		//    }
		//    

		//     * @see Store#getFactIndices()
		//     */
		//    public Set<String> getFactIndices() {
		//        
		//        // Build a map from fact indices to their parent fragment indices
		//        Map<String,String> factMap = getIndexMap(SimpleNumericItemImpl.class);
		//        factMap.putAll(getIndexMap(FractionItemImpl.class));
		//        factMap.putAll(getIndexMap(NonNumericItemImpl.class));
		//        Map<String,String> tupleMap = getIndexMap(TupleImpl.class);
		//        factMap.putAll(tupleMap);
		//        factMap.putAll(getIndexMap(FractionItemImpl.class));
		//        
		//        // Choose only fact indices where their parent indices are not tuple indices
		//        Set<String> result = new HashSet<String>();
		//        Set<String> factIndices = factMap.keySet();
		//        Set<String> tupleIndices = tupleMap.keySet();
		//        for ( std::string index: factIndices) {
		//            if (! tupleIndices.contains(factMap.get(index))) {
		//                result.add(index);
		//            }
		//        }
		//        return result;
		//    }
		//

		//     * @param fragmentClass The full name of the class of fragment being handled
		//     * @return a map from fragment index to parent fragment index for all fragments with the given class name (type).
		//     * @throws XBRLException
		//     */
		//    private Set<String> getIndexSet(Class<?> fragmentClass) {
		//         std::string query = "for $root in #roots#[@type='" + fragmentClass.getName() + "'] return $root";
		//        Set<String> indices = this.queryForIndices(query);
		//        return indices;
		//    }
		//    

		//     * @see Store#getAllFactIndices()
		//     */
		//    public Set<String> getAllFactIndices() {
		//        Set<String> indices = getIndexSet(SimpleNumericItemImpl.class);
		//        indices.addAll(getIndexSet(FractionItemImpl.class));
		//        indices.addAll(getIndexSet(NonNumericItemImpl.class));
		//        indices.addAll(getIndexSet(TupleImpl.class));
		//        indices.addAll(getIndexSet(FractionItemImpl.class));
		//        return indices;
		//    }
		//

		//     * @see Store#getRootFragmentIndices(String)
		//     */
		//    public Set<String> getRootFragmentIndices( std::string interfaceName)
		//            {
		//         std::string query = "for $root in #roots#[@parentIndex=''] where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
		//        if (interfaceName.indexOf(".") > -1) {
		//            query = "for $root in #roots#[@parentIndex=''] where $root/@type='" + interfaceName + "' return $root";
		//        }
		//        return this.queryForIndices(query);
		//    }    
		//

		//     * @see Store#getFacts(String, String)
		//     */
		//    public list<Fact&> getFacts( std::string namespace,  std::string localname)
		//            {
		//        if (namespace == null) throw XBRLException("The namespace must not be null.");
		//        if (localname == null) throw XBRLException("The local name must not be null.");
		//        this.setNamespaceBinding(namespace,"xbrlapi_factNamespacePrefix");
		//         std::string query = "for $root in #roots#[@fact and xbrlapi:data/xbrlapi_factNamespacePrefix:" + localname + "] return $root";
		//		return this.queryForXMLResources(query); 
		//    }
		//    

		//     * @see Store#getFacts(Concept)
		//     */
		//    public list<Fact&> getFacts(const Concept& concept)
		//            {
		//        if (concept == null) throw XBRLException("The concept must not be null.");
		//        return this.getFacts(concept.getTargetNamespace(), concept.getName());
		//    }    
		//    
	};

	Store::Store()  {}
	Store::Store(const std::string& database, const std::string& container) 
		: pImpl(this, database,container)
	{}
	Store::Store(const std::string& database, const std::string& container, const int size) 
		: pImpl(this,database,container,size)
	{}
	Store::Store(const std::string& database, const std::string& container,  const boost::uuids::uuid& loader) 
		: pImpl(this, database,container, loader)
	{}
	Store::Store(const std::string& database, const std::string& container, const int size,  const boost::uuids::uuid& loader) 
		: pImpl(this,database,container,size, loader)
	{}
	Store::~Store() {} 
	Store::Store(const Store& rhs) : pImpl(rhs.pImpl)
	{}

	void Store::setLoader( const boost::uuids::uuid& loader)
	{
		pImpl->setLoader(loader);

	}
	Store& Store::operator=(const Store& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Store::Store(Store&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Store& Store::operator=(Store&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Store::operator==(const Store& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Store::operator!=(const Store& rhs)
	{
		return !this->operator==(rhs);
	}

	void Store::close()
	{
		pImpl->close();
	}

	void Store::persist(XML& xml)
	{
		pImpl->persist(xml, *this);
	}    

	bool Store::hasXMLResource(const std::string& index)
	{
		return pImpl->hasXMLResource(index);
	}

	//		//F getXMLResource(const std::string& index)
	//		//{
	//		//	pImpl->getXMLResource(index);
	//		//}
	//

	//		void Store::remove(const std::string& index)
	//		{
	//			pImpl->remove(index);
	//		}
	//

	//		void Store::remove(const XML& xml)
	//		{
	//			pImpl->remove(xml);
	//		}	
	//

	//		void Store::setNamespaceBinding(const std::string& Namespace, const std::string& prefix)
	//		{
	//			pImpl->setNamespaceBinding(Namespace,prefix);
	//		}
	//

	//		void Store::removeNamespaceBinding(const std::string& prefix)
	//		{
	//			pImpl->removeNamespaceBinding(prefix);
	//		}
	//

	//		void Store::deleteDocument(const Poco::URI& uri)
	//		{
	//			pImpl->deleteDocument(uri);
	//		}
	//

	//		void Store::deleteRelatedDocuments (const Poco::URI&  uri)
	//		{
	//			pImpl->deleteRelatedDocuments(uri);
	//		}
	//

	//		//std::vector<F> queryForXMLResources(const std::string& query)
	//		//{
	//		//	pImpl->queryForXMLResources(query);
	//		//}
	//

	//		std::unordered_set<std::string>  queryForIndices(const std::string& query)
	//		{
	//			pImpl->queryForIndices(query);
	//		}
	//

	//		long queryCount(const std::string& query)
	//		{
	//			pImpl->queryCount(query);
	//		}    

	std::unordered_set<std::string> Store::queryForStrings(std::string& query)
	{
		return pImpl->queryForStrings(query);
	}

	//		std::string queryForString(const std::string& query)
	//		{
	//			pImpl->(query);
	//		}
	//

	void Store::serialize(const xercesc::DOMElement& what, std::ofstream& destination)
	{
		//				pImpl->serialize(destination);
	}


	//void Store::serialize(const xercesc::DOMElement& what, const File& destination)
	//{
	//	pImpl->serialize(destination);
	//}


	std::string Store::serialize(const xercesc::DOMElement& what)
	{
		//				pImpl->serialize(what);
		return std::string();
	}    


	//		//xercesc::DOMElement getDocumentAsDOM(const Poco::URI& uri)
	//		//{
	//		//	pImpl->getDocumentAsDOM(uri);
	//		//}
	//

	//		void Store::saveDocuments(const File& destination)
	//		{
	//			pImpl->saveDocuments(destination);
	//		}
	//

	//		void Store::saveDocuments(const File& destination, const std::string& uriPrefix)
	//		{
	//			pImpl->saveDocuments(destination, uriPrefix);
	//		}
	//

	//		void Store::saveStoreAsSingleDocument(const File& file)
	//		{
	//			pImpl->saveStoreAsSingleDocument(file);
	//		}
	//

	//		//xercesc::DOMElement getSubtree(const Fragment& f)
	//		//{
	//		//	pImpl->getSubtree(f);
	//		//}
	//

	//		std::shared_ptr<xercesc::DOMDocument> getStoreAsDOM()
	//		{
	//			pImpl->getStoreAsDOM();
	//		}
	//

	//		std::shared_ptr<xercesc::DOMDocument> getCompositeDocument()
	//		{
	//			pImpl->getCompositeDocument();
	//		}
	//

	//		std::unordered_set<Poco::URI> Store::getDocumentURIs()
	//		{
	//			pImpl->getDocumentURIs();
	//		}

	bool Store::hasDocument(const Poco::URI& uri)
	{
		return pImpl->hasDocument(uri);
	}

	void Store::persistLoaderState(std::unordered_map<const Poco::URI,std::string> documents)
	{
		pImpl->persistLoaderState(documents);
	}    


	//		int getSize()
	//		{
	//			pImpl->getSize();
	//		}

	std::vector<Poco::URI> Store::getDocumentsToDiscover()
	{
		return pImpl->getDocumentsToDiscover();
	}
	//

	//		std::vector<Stub> getStubs()
	//		{
	//			pImpl->getStubs();
	//		}
	//

	//		std::vector<Stub> getStubs(const Poco::URI& uri)
	//		{
	//			pImpl->getStubs(uri);
	//		}
	//

	//		void Store::persistStub(const Poco::URI& document, const std::string& reason)
	//		{
	//			pImpl->persistStub(document, reason);
	//		}    
	//

	//		void Store::removeStub(const Stub& stub)
	//		{
	//			pImpl->removeStub(stub);
	//		}
	//

	//		template <typename F>
	//		std::vector<F> getXMLResources(const std::string& interfaceName)
	//		{
	//			pImpl->getXMLResources(interfaceName);
	//		}
	//

	//		//std::vector<F> getXMLResources(F specifiedClass)
	//		//{
	//		//	pImpl->getXMLResources(specifiedClass);
	//		//}
	//

	//		//long getNumberOfXMLResources(F specifiedClass)
	//		//{
	//		//	pImpl->getNumberOfXMLResources(specifiedClass);
	//		//}
	//

	//		//std::vector<F> getChildFragments(const std::string& interfaceName, const std::string& parentIndex)
	//		//{
	//		//	pImpl->getChildFragments(interfaceName, parentIndex);
	//		//}
	//

	//		//Networks getNetworks(const std::string& linkRole, const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworks(linkRole, arcrole);
	//		//}
	//

	//		//Networks getNetworks(const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworks(arcrole);
	//		//}
	//

	///*		Networks getNetworks()
	//		{
	//			pImpl->getNetworks();
	//

	//		template <typename F>
	//		std::vector<F> getTargets(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
	//		{
	//			pImpl->getTargets(sourceIndex, linkRole, arcrole);
	//		}
	//

	//		//std::vector<F> getSources(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
	//		//{
	//		//	pImpl->getSources(targetIndex, linkRole, arcrole);
	//		//}
	//

	//		std::unordered_set<std::string>  getSourceIndices(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
	//		{
	//			pImpl->getSourceIndices(targetIndex, linkRole, arcrole);
	//		}    
	//

	//		void Store::setAnalyser(Analyser analyser)
	//		{
	//			pImpl->setAnalyser(analyser);
	//		}
	//

	//		//Analyser getAnalyser()
	//		//{
	//		//	pImpl->getAnalyser();
	//		//} 
	//

	bool Store::isPersistingRelationships()
	{
		return pImpl->isPersistingRelationships();
	}    


	//		//std::vector<F> getFragmentsFromDocument (const Poco::URI&  uri, const std::string& interfaceName)
	//		//{
	//		//	pImpl->getFragmentsFromDocument(uri, interfaceName);
	//		//}
	//

	///*		std::vector<F> getFragmentsFromDocument (const Poco::URI&  uri, F fragmentClass)
	//		{
	//			pImpl->getFragmentsFromDocument(uri, fragmentClass);
	//
	//

	//		std::unordered_set<std::string>  getFragmentIndices(const std::string& interfaceName)
	//		{
	//			pImpl->getFragmentIndices(interfaceName);
	//		}
	//

	//		std::unordered_set<std::string>  getRootFragmentIndices(const std::string& interfaceName)
	//		{
	//			pImpl->getRootFragmentIndices(interfaceName);
	//		}    
	//

	//		std::unordered_set<std::string>  getFragmentIndicesFromDocument(const Poco::URI& uri, const std::string& interfaceName)
	//		{
	//			pImpl->getFragmentIndicesFromDocument(uri, interfaceName);
	//		}
	//

	//		std::unordered_set<std::string>  getFragmentIndicesFromDocument(const Poco::URI& uri)
	//		{
	//			pImpl->getFragmentIndicesFromDocument(uri);
	//		}    
	//

	//		//F getRootFragmentForDocument (const Poco::URI&  uri)
	//		//{
	//		//	pImpl->getRootFragmentForDocument(uri);
	//		//}
	//

	//		//std::vector<F> getRootFragments()
	//		//{
	//		//	pImpl->getRootFragments();
	//		//}
	//

	///*		std::vector<F> getRootFragments(const std::string& type)
	//		{
	//			pImpl->getRootFragments(type);
	//

	//		void Store::Delete()
	//		{
	//			pImpl->Delete();
	//		}    
	//

	std::string Store::getId(const std::string& input)
	{
		return pImpl->getId(input);
	}

	//		//Language getLanguage(const std::string& encoding, const std::string& code)
	//		//{
	//		//	pImpl->getLanguage(encoding, code);
	//		//}
	//

	//		std::vector<Language> getLanguages(const std::string& code)
	//		{
	//			pImpl->getLanguages(code);
	//		}
	//

	//		std::unordered_map<std::string,Language> getLanguageMap(const std::string& code)
	//		{
	//			pImpl->getLanguageMap(code);
	//		}
	//

	//		void Store::setMatcher(const Matcher& matcher)
	//		{
	//			pImpl->setMatcher(matcher);
	//		}
	//

	DefaultMatcher Store::getMatcher()
	{
		return pImpl->getMatcher();
	}


	//		std::vector<Poco::URI> getReferencingDocuments(const Poco::URI& uri)
	//		{
	//			pImpl->getReferencingDocuments(uri);
	//		}
	//

	//		std::vector<Fragment> getReferencingFragments(const Poco::URI& uri)
	//		{
	//			pImpl->getReferencingFragments(uri);
	//		}    
	//

	//		std::unordered_set<Poco::URI> Store::getReferencedDocuments(const Poco::URI& uri)
	//		{
	//			pImpl->getReferencedDocuments(uri);
	//		}    
	//

	//		void Store::setFilteringURIs(std::unordered_set<Poco::URI> Store::uris)
	//		{
	//			pImpl->setFilteringURIs(uris);
	//		}
	//

	std::unordered_set<Poco::URI> Store::getFilteringURIs()
	{
		return pImpl->getFilteringURIs();
	}

	//		void Store::clearFilteringURIs()
	//		{
	//			pImpl->clearFilteringURIs();
	//		}
	//

	bool Store::isFilteringByURIs()
	{
		return pImpl->isFilteringByURIs();
	}

	void Store::sync()
	{
		return pImpl->sync();
	}
	//
	//

	//		std::vector<Fact&> Store::getFacts()
	//		{
	//			pImpl->getFacts();
	//		}
	//

	//		std::unordered_set<std::string>  getFactIndices()
	//		{
	//			pImpl->getFactIndices();
	//		}
	//

	//		std::unordered_set<std::string>  getAllFactIndices()
	//		{
	//			pImpl->getAllFactIndices();
	//		}        
	//

	//		std::vector<Item> getItems()
	//		{
	//			pImpl->getItems();
	//		}
	//

	//		std::vector<std::tuple<std::string>> getTuples()
	//		{
	//			pImpl->getTuples();
	//		}
	//

	//		//Schema getSchema(const std::string& targetNamespace)
	//		//{
	//		//	pImpl->getSchema(targetNamespace);
	//		//}
	//

	//		std::vector<Fact&> Store::getFacts (const Poco::URI&  uri)
	//		{
	//			pImpl->getFacts(uri);
	//		}
	//

	//		std::vector<Fact&> Store::getAllFacts (const Poco::URI&  uri)
	//		{
	//			pImpl->getAllFacts(uri);
	//		}
	//

	//		std::vector<Fact&> Store::getAllFacts()
	//		{
	//			pImpl->getAllFacts();
	//		}
	//

	//		std::vector<Item> getItems (const Poco::URI&  uri)
	//		{
	//			pImpl->getItems(uri);
	//		}
	//

	//		std::vector<std::tuple<std::string>> getTuples (const Poco::URI&  uri)
	//		{
	//			pImpl->getTuples(uri);
	//		}
	//

	//		//std::unordered_set<F> getNetworkRoots(const std::string& linkRole, const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworkRoots(linkRole, arcrole);
	//		//}
	//

	//		//Concept getConcept(const std::string& Namespace, const std::string& name)
	//		//{
	//		//	pImpl->getConcept(Namespace, name);
	//		//}
	//

	//		template <typename D>
	//		D getGlobalDeclaration(const std::string& Namespace, const std::string& name)
	//		{
	//			pImpl->getGlobalDeclaration(Namespace, name);
	//		}    
	//

	//		std::vector<ArcroleType> getArcroleTypes()
	//		{
	//			pImpl->getArcroleTypes();
	//		}
	//

	//		std::vector<ArcroleType> getArcroleTypes(const std::string& uri)
	//		{
	//			pImpl->getArcroleTypes(uri);
	//		}
	//

	//		std::vector<RoleType> getRoleTypes()
	//		{
	//			pImpl->getRoleTypes();
	//		}
	//

	//		std::vector<RoleType> getRoleTypes(const std::string& uri)
	//		{
	//			pImpl->getRoleTypes(uri);
	//		}    
	//

	//		std::vector<std::string> getResourceRoles()
	//		{
	//			pImpl->getResourceRoles();
	//		}    
	//

	//		//std::unordered_set<Poco::URI> Store::getMinimumDocumentSet(Collection<Poco::URI> starters)
	//		//{
	//		//	pImpl->getMinimumDocumentSet(starters);
	//		//}
	//
	//

	//		std::unordered_set<Poco::URI> Store::getMinimumDocumentSet (const Poco::URI&  uri)
	//		{
	//			pImpl->getMinimumDocumentSet(uri);
	//		}
	//

	//		std::vector<ExtendedLink> getExtendedLinks(const std::string& linkrole)
	//		{
	//			pImpl->getExtendedLinks(linkrole);
	//		}
	//

	//		std::unordered_set<std::string>  getExtendedLinkIndices(const std::string& linkRole)
	//		{
	//			pImpl->getExtendedLinkIndices(linkrole);
	//		}
	//

	//		std::vector<Arc> getArcs (const Poco::URI&  arcrole, const std::string& linkIndex)
	//		{
	//			pImpl->getArcs(arcrole, linkIndex);
	//		}
	//

	//		std::unordered_set<std::string>  getArcIndicesWithLinkIndex(const std::string& linkIndex)
	//		{
	//			pImpl->getArcIndicesWithLinkIndex(linkIndex);
	//		}
	//

	//		std::unordered_set<std::string>  getArcIndicesWithArcrole(const std::string& arcrole)
	//		{
	//			pImpl->getArcIndicesWithArcrole(arcrole);
	//		}    
	//
	//

	//		std::vector<Arc> getArcs(const std::string& linkIndex)
	//		{
	//			pImpl->getArcs(linkIndex);
	//		}    
	//
	//

	//		//Networks getMinimalNetworksWithArcrole(std::unordered_set<Fragment> fragments, const std::string& arcrole)
	//		//{
	//		//	pImpl->getMinimalNetworksWithArcrole(fragments, arcrole);
	//		//}
	//

	//		//Networks getMinimalNetworksWithArcrole(const Fragment& fragment, const std::string& arcrole)
	//		//{
	//		//	pImpl->getMinimalNetworksWithArcrole(fragment, arcrole);
	//		//}
	//

	//		//Network getMinimalNetwork(std::unordered_set<Fragment> fragments, const std::string& linkRole, const std::string& arcrole)
	//		//{
	//		//	pImpl->getMinimalNetwork(fragments, linkRole, arcrole);
	//		//}
	//

	//		void Store::augmentNetworkForFragment(const Fragment& fragment, const Network& network)
	//		{
	//			pImpl->augmentNetworkForFragment(fragment, network);
	//		}
	//

	//		void Store::augmentNetworksForFragment(const Fragment& fragment, const std::string& arcrole, Networks networks)
	//		{
	//			pImpl->augmentNetworksForFragment(fragment, arcrole, networks);
	//		}
	//

	//		std::unordered_set<std::string>  getArcroles()
	//		{
	//			pImpl->getArcroles();
	//		}
	//

	//		std::unordered_set<std::string>  getArcroles(const std::string& linkRole)
	//		{
	//			pImpl->getArcroles(linkRole);
	//		}    
	//

	//		std::unordered_set<std::string>  getLinkRoles()
	//		{
	//			pImpl->getLinkRoles();
	//		}
	//

	//		std::unordered_set<std::string>  getLinkRoles(const std::string& arcrole)
	//		{
	//			pImpl->getLinkRoles(arcrole);
	//		}    
	//

	//		//Networks getNetworksFrom(const std::string& sourceIndex, const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworksFrom(sourceIndex, arcrole);
	//		//}
	//

	///*		Networks getNetworksFrom(const std::string& sourceIndex)
	//		{
	//			pImpl->getNetworksFrom(sourceIndex);
	//

	///*		Networks getNetworksFrom(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
	//		{
	//			pImpl->getNetworksFrom(sourceIndex, linkRole, arcrole);
	//

	//		//Networks getNetworksTo(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworksTo(targetIndex, linkRole, arcrole);
	//		//}
	//

	//		//Networks getNetworksTo(const std::string& targetIndex, const std::string& arcrole)
	//		//{
	//		//	pImpl->getNetworksTo(targetIndex, arcrole);
	//		//}
	//

	///*		Networks getNetworksTo(const std::string& targetIndex)
	//		{
	//			pImpl->getNetworksTo(targetIndex);
	//

	//		std::set<Relationship> getRelationshipsFrom(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
	//		{
	//			pImpl->getRelationshipsFrom(sourceIndex, linkRole, arcrole);
	//		}
	//

	//		bool Store::hasAllRelationships (const Poco::URI&  document)
	//		{
	//			pImpl->hasAllRelationships(document);
	//		}    
	//

	//		std::set<Relationship> getRelationshipsTo(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
	//		{
	//			pImpl->getRelationshipsTo(targetIndex, linkRole, arcrole);
	//		}    
	//

	std::vector<LabelResource> Store::getLabels(const std::string& fragment, 
		const std::string& linkRole, 
		const std::string& resourceRole, 
		const std::string& language)
	{
		return pImpl->getLabels(fragment, linkRole, resourceRole, language);
	}


	std::vector<LabelResource> Store::getLabels(const std::string& fragment, const std::string& resourceRole, const std::string& language)
	{
		return pImpl->getLabels(fragment, resourceRole, language);
	}


	std::vector<LabelResource> Store::getLabelsWithLanguage(const std::string& fragment, const std::string& language)
	{
		return pImpl->getLabelsWithLanguage(fragment, language);
	}

	//		std::vector<LabelResource> getLabels(const std::string& fragment)
	//		{
	//			pImpl->getLabels(fragment);
	//		}    
	//

	//		std::vector<LabelResource> getLabelsWithResourceRole(const std::string& fragment, const std::string& resourceRole)
	//		{
	//			pImpl->getLabelsWithResourceRole(fragment, resourceRole);
	//		}
	//

	//		std::vector<ReferenceResource> getReferences(const std::string& fragment, const std::string& linkRole, const std::string& resourceRole, const std::string& language)
	//		{
	//			pImpl->getReferences(fragment, linkRole, resourceRole, language);
	//		}
	//

	//		std::vector<ReferenceResource> getReferences(const std::string& fragment, const std::string& resourceRole, const std::string& language)
	//		{
	//			pImpl->getReferences(fragment, resourceRole, language);
	//		}
	//

	std::vector<ReferenceResource> Store::getReferencesWithLanguage(const std::string& fragment, const std::string& language)
	{
		return pImpl->getReferencesWithLanguage(fragment, language);
	}

	//		std::vector<ReferenceResource> getReferences(const std::string& fragment)
	//		{
	//			pImpl->getReferences(fragment);
	//		}    
	//

	//		std::vector<ReferenceResource> getReferencesWithResourceRole(const std::string& fragment, const std::string& resourceRole)
	//		{
	//			pImpl->(fragment, resourceRole);
	//		}    
	//

	//		std::unordered_set<Poco::URI> Store::getMissingDocumentURIs()
	//		{
	//			pImpl->getReferencesWithResourceRole();
	//		}
	//

	bool Store::requestLoadingRightsFor(const Poco::URI& document)
	{
		return pImpl->requestLoadingRightsFor(document);
	}


	void Store::recindLoadingRightsFor(const Poco::URI& document)
	{
		pImpl->recindLoadingRightsFor(document);
	}


	void Store::startLoading()
	{
		pImpl->startLoading();
	}


	void Store::stopLoading()
	{
		pImpl->stopLoading();
	}


	bool Store::isLoading()
	{
		return pImpl->isLoading();
	}    


	//		//F getSchemaContent(const std::string& Namespace, const std::string& name)
	//		//{
	//		//	pImpl->getSchemaContent(Namespace, name);
	//		//}
	//

	//		//std::vector<F> Store::getChildFragments(F childClass, const std::string& parentIndex)
	//		//{
	//		//	pImpl->getChildFragments(childClass, parentIndex);
	//		//}
	//

	//		std::vector<Fact&> Store::getFacts(const std::string& Namespace, const std::string& localname)
	//		{
	//			pImpl->getFacts(Namespace, localname);
	//		}    
	//

	//		std::vector<Fact&> Store::getFacts(const Concept& concept)
	//		{
	//			pImpl->getFacts(concept);
	//		}    
}


