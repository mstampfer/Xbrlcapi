
#include "Stdafx.h"
#pragma once

///**
// * Implementation of the data store using the Oracle 
// * Berkeley Database.  Note that this store implementation
// * does not use the XML:DB API and so does not require
// * a DBConnection implementation.
// * @author Geoffrey Shuetrim (geoff@galexy.net)
// */
#include <string>
#include <algorithm>
#include "Store.h"
#include "StoreImpl.h"
#include "dbxml/XmlManager.hpp"
#include "db_cxx.h"
#include "Winsock2.h"
#include "dbxml/DbXml.hpp"
#include "XML.h"
#include "Constants.h"
#include "dbxml/XmlQueryContext.hpp"
//#include "XMLDomBuilder.h"
#include <xercesc/dom/DOMLSParser.hpp>
#include "FragmentFactory.h"

namespace xbrlcapi
{ 

	StoreImpl::StoreImpl(const StoreImpl& rhs) 
	{
		DbXml::XmlManager* dm = new DbXml::XmlManager();
		*dm = *rhs.dataManager; 
		dataManager.reset(dm);

		DbEnv* dbenv = new DbEnv(rhs.env_flags);
		environment.reset(dbenv);

		computerIdentity = rhs.computerIdentity;
		containerName = rhs.containerName;
		dataContainer = rhs.dataContainer;
		domimplementation = rhs.domimplementation;
		lastSync = rhs.lastSync;
		//		rhs.loadingStatus;
		locationName = rhs.locationName;
		matcher = rhs.matcher;
		//		rhs.pimpl;
		queryEvaluationType = rhs.queryEvaluationType;
		//		rhs.serialversionuid;
		storedom = rhs.storedom;
		cacheSize = rhs.cacheSize;
	}
	StoreImpl& StoreImpl::operator=(const StoreImpl& rhs)
	{
		if (this != &rhs)
		{
			DbXml::XmlManager* dm = new DbXml::XmlManager();
			*dm = *rhs.dataManager; 
			dataManager.reset(dm);

			DbEnv* dbenv = new DbEnv(rhs.env_flags);
			environment.reset(dbenv);

			computerIdentity = rhs.computerIdentity;
			containerName = rhs.containerName;
			dataContainer = rhs.dataContainer;
			domimplementation = rhs.domimplementation;
			lastSync = rhs.lastSync;
			//		rhs.loadingStatus;
			locationName = rhs.locationName;
			matcher = rhs.matcher;
			//		rhs.pimpl;
			queryEvaluationType = rhs.queryEvaluationType;
			//		rhs.serialversionuid;
			storedom = rhs.storedom;
			cacheSize = rhs.cacheSize;
		}
		return *this;
	}

	/**
	* @return The unique identifier for the computer running this data store.
	* @throws XBRLException
	*/

	std::string StoreImpl::getComputerName()
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
		//            throw new XBRLException("The computer identity could not be obtained.", e);
		//        }
		return std::string(szHostName) + "." + std::string(aszIPAddresses[0]);
	}

	void StoreImpl::initialize(const std::string& location, const std::string& container)
	{
		lastSync = 0;

		computerIdentity = getComputerName();

		if (location != "") locationName = location;
		//			else throw new XBRLException("The Berkeley DB XML database location must be specified.");

		if (container != "")  containerName = container;
		//			else throw new XBRLException("The Berkeley DB XML database container must be specified.");

		//			try {
		//			DbXml::XmlManager.setLogLevel(DbXml::XmlManager.LEVEL_ALL, false);
		//			DbXml::XmlManager.setLogCategory(DbXml::XmlManager.CATEGORY_ALL, false);     
		//			} catch (...) {
		//			throw new XBRLException("The BDB XML log levels could not be initialised.", e);
		//			}

		initContainer();

		//		logIndexes();

	}

	/**
	* Log information about all the indexes in the data store.
	*/
	void StoreImpl::logIndexes()
	{
		try {
			DbXml::XmlIndexSpecification xis = dataContainer.getIndexSpecification();
			int count = 0;
			std::string uri, name, index;		         
			while(xis.next(uri,name,index)) 
			{
				//		                logger.info("For node '" + idxDecl.uri + ":" + idxDecl.name + "', found index: '" + idxDecl.index + "'.");
				std::cout << "For node '" + uri + ":" + name + "', found index: '" + index + "'." << std::endl;
				count ++;
			}
			std::cout << count;
			std::cout << " indices found." << std::endl;
		} catch (...) {
			;
		}        
	}

	/**
	* @see org.xbrlapi.data.Store#persist(XML)
	*/
	//	synchronized 
	int StoreImpl::getSize()
	{
		//        try {
		//            return this.dataContainer.getNumDocuments();
		//        } catch (XmlException e) {
		//            throw new XBRLException("Failed to get the number of fragments in the data store.",e);
		//        }
		return 0;
	}

	/**
	* Initialises the database environment.
	* @throws XBRLException if the environment files are not found or 
	* there is a database problem.
	*/
	void StoreImpl::initEnvironment() 
	{
		//	try {								

		environment.reset(new DbEnv(env_flags));
		int dberr = environment->set_cachesize(0, this->cacheSize, 0);
		if (dberr)
		{
			environment->close(0);
			//return (EXIT_FAILURE);
		}

		environment->set_error_stream(&std::cerr);

		environment->open(locationName.c_str(), env_flags, 0);
		//environment->memp_trickle(20); // ensure that 20% of cache is free

		//    logger.debug("Initialised the environment.");
		//} catch (FileNotFoundException e) {
		//    throw new XBRLException("The physical location of the BDB XML database could not be found.", e);
		//} catch (DatabaseException e) {
		//    throw new XBRLException("The BDB XML database environment could not be set up.", e);
		//}	    
	}

	/**
	* Initialises the database manager
	* @throws XBRLException
	*/
	void StoreImpl::initManager() 
	{
		if (environment == nullptr) initEnvironment();
		//      try {
		DbEnv* released = environment.release();
		dataManager.reset(new DbXml::XmlManager(released->get_DB_ENV(), DbXml::DBXML_ADOPT_DBENV |
			DbXml::DBXML_ALLOW_EXTERNAL_ACCESS |
			DbXml::DBXML_ALLOW_AUTO_OPEN));
		//			);
		/*           logger.debug("Initialised the data manager.");
		} catch (XmlException e) {
		throw new XBRLException("The Berkeley XML database manager could not be set up.", e);
		}	    */
	}

	/**
	* Initialises the database container.
	* @throws XBRLException
	*/
	void StoreImpl::initContainer() 
	{
		if (dataManager == nullptr) initManager();
		//        try {
		if (dataManager->existsContainer(containerName) != 0) {
			dataContainer = dataManager->openContainer(containerName);
		} else {
			createContainer();
		}
		//            logger.debug("Initialised the data container.");
		//        } catch (XmlException e) {
		//            throw new XBRLException("The database container, " + containerName + ", could not be opened.");
		//        }
	}

	void StoreImpl::createContainer()
	{
		if (dataManager == nullptr) initManager();
		//try {
		DbXml::XmlContainerConfig config;
		config.setStatistics(DbXml::XmlContainerConfig::On);
		dataContainer = dataManager->createContainer(containerName,config);

		//} catch (XmlException e) {
		//    throw new XBRLException("The data container could not be created.", e);
		//} 

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
		//    throw new XBRLException("The indexes could not be configured.", e);
		//} finally {
		//    if (xmlIndexSpecification != null) xmlIndexSpecification.delete();
		//}

	}        
	//
	//	
	//
	/**
	* The closure operation entails closing the XML container and the XML data manager
	* that are used by the store.
	* @see org.xbrlapi.data.Store#close()
	*/
	//synchronized 
	void StoreImpl::close()
	{
		//	    super.close();
		//	    closeContainer();
		//	    closeManager();
	}
	//	
	//
	//	
	void StoreImpl::closeContainer()
	{
		//        if (dataContainer == null) return;
		//	    if (dataManager == null) initManager();
		//        dataContainer.delete();
		//        dataContainer = null;
	}
	//	
	void StoreImpl::closeManager()
	{
		//        if (dataManager == null) return;
		//        dataManager.delete();
	}	
	//	
	void deleteContainer()
	{
		//        if (dataManager == null) initManager();
		//        closeContainer();
		//        try {
		//            if (dataManager.existsContainer(containerName) != 0) {
		//                dataManager.removeContainer(containerName);
		//            }
		//        } catch (XmlException e) {
		//            throw new XBRLException("The BDB XML database container could not be deleted.");
		//        }
	}	

	/**
	* @see org.xbrlapi.data.Store#delete()
	*/
	//synchronized 
	void StoreImpl::del()
	{
		//	    deleteContainer();
		//	    closeManager();
	}
	//	
	/**
	* @see org.xbrlapi.data.Store#persist(XML)
	*/
	//synchronized 
	void StoreImpl::persist(const XML& xml)
	{
		//
		//        XmlUpdateContext xmlUpdateContext = null;
		//	    try {
		//	        
		//             std::string index = xml.getIndex();
		//            if (hasXMLResource(index)) remove(index);
		//
		//             std::string content = serialize(xml.getMetadataRootElement());
		//            xmlUpdateContext = dataManager.createUpdateContext();
		//            XmlDocumentConfig documentConfiguration = new XmlDocumentConfig();
		//            documentConfiguration.setWellFormedOnly(true);
		//            dataContainer.putDocument(index, content, xmlUpdateContext, null);
		//
		//            if (xml.getStore() == null) {
		//                if (xml.getBuilder() != null) xml.setResource(xml.getBuilder().getMetadata());
		//                xml.setStore(this);
		//	        }
		//	        	        
		//        } catch (XmlException e) {
		//            throw new XBRLException("The fragment could not be added to the BDB XML data store.", e);
		//	    } finally {
		//            //if (xmlUpdateContext != null) xmlUpdateContext.delete();
		//	    }
	}

	/**
	* @see org.xbrlapi.data.Store#hasXMLResource(String)
	*/
	//synchronized 
	bool StoreImpl::hasXMLResource(const std::string& index)
	{
		//
		//	    try {
		//	        dataContainer.getDocument(index);
		//			return true;
		//        } catch (XmlException e) {
		//            return false;
		//        }
		return false;
	}

	/**
	* @see org.xbrlapi.data.Store#getXMLResource(String)
	*/
	//synchronized 
	template <typename F> 
	F StoreImpl::getXMLResource(const std::string& index) 
	{
		//
		//         try {
		//            XmlDocument xmlDocument = dataContainer.getDocument(index);
		//            Document document = (new XMLDOMBuilder()).newDocument(xmlDocument.getContentAsInputStream());
		//            return FragmentFactory.<F>newFragment(this, document.getDocumentElement());
		//        } catch (XmlException e) { // Thrown if the document is not found
		//            throw new XBRLException("The fragment " + index + " could not be retrieved from the store.",e);
		//        }
		//
	}
	/**
	* @see org.xbrlapi.data.Store#remove(String)
	*/
	//synchronized 
	void StoreImpl::remove(XML fragment)
	{
		//		remove(fragment.getIndex());
		//	}
		//
		//	/**
		//	 * @see org.xbrlapi.data.Store#remove(String)
		//	 */
		//     public synchronized void remove( std::string index) {
		//
		//        XmlUpdateContext xmlUpdateContext = null;
		//        try {
		//            xmlUpdateContext = dataManager.createUpdateContext();
		//            dataContainer.deleteDocument(index,xmlUpdateContext);
		//        } catch (XmlException e) {
		//            throw new XBRLException("The fragment removal failed.", e);
		//        } finally {
		//            //if (xmlUpdateContext != null) xmlUpdateContext.delete();
		//        }
	}

	/**
	* @see org.xbrlapi.data.Store#queryForXMLResources(String)
	*/
	//synchronized 
//	template <typename F>
	std::vector<Stub> StoreImpl::queryForXMLResources(std::string& query) 
	{

		DbXml::XmlResults xmlResults;
		//try {

			//try {
				xmlResults = runQuery(query);

			//	double startTime = System.currentTimeMillis();

				DbXml::XmlValue xmlValue; 
				xmlResults.next(xmlValue);
				std::vector<Stub*> fragments;
				while (xmlValue) 
				{
					DbXml::XmlDocument doc = xmlValue.asDocument();
					xercesc::DOMLSParser* builder = domimplementation->createLSParser(
													xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, NULL);
					xercesc::DOMDocument* document = builder->parse(doc.getContentAsXmlInputStream());
					xercesc::DOMElement* root = document->getDocumentElement();
					fragments.push_back(FragmentFactory::newFragment(this, root));
					xmlResults.next(xmlValue);
				}

			//	Double time = new Double((System.currentTimeMillis()-startTime));
				//       logger.debug(time + " milliseconds to create fragment list from" + query);
				return fragments;

			//} catch (XmlException e) {
			//	throw new XBRLException("Failed query: " + query,e);
			//}

		//} finally {
			if (xmlResults != nullptr) delete xmlResults;
		//}
	}

	/**
	* @see org.xbrlapi.data.Store#queryForIndices(String)
	*/
	//synchronized 
	std::unordered_set<std::string> StoreImpl::queryForIndices(const std::string& query) 
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
		//                throw new XBRLException("Failed query: " + query,e);
		//            } catch (IllegalStateException e) {
		//                throw new XBRLException("Failed query: " + query,e);
		//            }
		//            
		//        } finally {
		//            if (xmlResults != null) xmlResults.delete();
		//        }
		//
		std::unordered_set<std::string> xx;
		return xx;
	}

	bool StoreImpl::hasDocument(const Poco::URI& uri) 
	{
		Poco::URI matchURI;
		//		        try {
		matchURI = getMatcher().getMatch(uri);
		//		        } catch (XBRLException e) {
		//		            logger.warn(uri + " could not be matched. " + e.getMessage());
		//		            matchURI = uri;
		//		        }
		std::string query = "for $root in #roots# where $root/@uri='" + matchURI.toString() + "' and $root/@parentIndex='' return string($root/@index)";
		std::unordered_set<std::string> rootIndices =  queryForStrings(query);
		if (rootIndices.size() == 1) return true;
		if (rootIndices.size() == 0) return false;
		throw; //new XBRLException("There are two root fragments in the store for " + uri);
		return false;
	}
	/**
	* @see org.xbrlapi.data.Store#queryForStrings(String)
	*/
	//synchronized 
	std::unordered_set<std::string> StoreImpl::queryForStrings(std::string& query)
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
		throw new XBRLException("Failed query: " + query,e);
		}

		} finally {
		if (xmlResults != null) xmlResults.delete();
		} */      
		std::unordered_set<std::string> xx;
		return xx;
	}

	/**
	* @see Store#queryCount(String)
	*/
	//synchronized 
	long StoreImpl::queryCount(std::unordered_set<std::string> query)
	{

		//      XmlResults xmlResults = null;
		//      try {
		//          xmlResults = runQuery(query, XmlQueryContext.Eager);
		//          return xmlResults.size();
		//      } catch (XmlException e) {
		//          logger.error("The query stuffed up. " + query);
		//          throw new XBRLException("Failed query: " + query,e);
		//      } finally {
		//          if (xmlResults != null) xmlResults.delete();
		//      }
		return 0L;
	}    


	/**
	* TODO provide a means of investigating namespace bindings for the query configuration.
	* Provides direct access to the query mechanism so that we can use
	* queries without constructing fragments for each query result.
	* @param myQuery The query to be performed.
	* @return the results of the query.
	* @throws XBRLException if the query fails to execute.
	*/

	DbXml::XmlResults StoreImpl::runQuery(std::string& myQuery, 
		const DbXml::XmlQueryContext::EvaluationType& evaluationType=DbXml::XmlQueryContext::Lazy)
	{
		DbXml::XmlQueryExpression xmlQueryExpression;
		//try {
		std::string roots = "collection('" + dataContainer.getName() + "')/*" + getURIFilteringPredicate();
		std::string expr("#roots#");
		size_t pos = myQuery.find(expr);
		myQuery.replace(pos, pos+expr.size(), roots);
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
		//    throw new XBRLException("Failed query: " + myQuery,e);
		//} finally {
		//    if (xmlQueryExpression != null) xmlQueryExpression.delete();
		//}
	}	

	/**
	* Performs a lazy query evaluation
	* @param myQuery The query to be performed.
	* @return the results of the query.
	* @throws XBRLException if the query fails to execute.
	*/
	DbXml::XmlResults StoreImpl::performLazyQuery(const std::string& myQuery) 
	{
		//        // TODO provide a means of adding additional namespaces for querying.
		//        // TODO provide a means of investigating namespace bindings for the query configuration.
		//        
		//        XmlQueryExpression xmlQueryExpression = null;
		//        try {
		//             std::string query = "collection('" + dataContainer.getName() + "')" + myQuery;
		//            XmlQueryContext xmlQueryContext = createQueryContext();
		//            xmlQueryContext.setEvaluationType(XmlQueryContext.Lazy);
		//            xmlQueryExpression = dataManager.prepare(query,xmlQueryContext);
		//            double startTime = System.currentTimeMillis();
		//            XmlResults xmlResults = xmlQueryExpression.execute(xmlQueryContext);
		//            Double time = new Double((System.currentTimeMillis()-startTime));
		//            logger.debug(time + " milliseconds to evaluate " + myQuery);
		//            return xmlResults;
		//
		//        } catch (XmlException e) {
		//            throw new XBRLException("Failed query: " + myQuery,e);
		//        } finally {
		//            if (xmlQueryExpression != null) xmlQueryExpression.delete();
		//        }
		//        
		DbXml::XmlResults xx;
		return xx;

	}	

	/**
	* @return a XQuery context, prepared with namespace declarations etc.
	* @throws XBRLException
	*/
	DbXml::XmlQueryContext StoreImpl::createQueryContext()
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
		throw new XBRLException("Failed to create query context.",e);
		}*/
		DbXml::XmlQueryContext xx;
		return xx;
	}

	/**
	* Ensures that the database container is flushed to disk.
	* @see Store#sync()
	*/

	//synchronized 
	void StoreImpl::sync()
	{
		//    if ((System.currentTimeMillis() - lastSync) < 10000) return;
		//if (!dataContainer) throw new XBRLException("The database container cannot be synced because it is null.");
		//try {
		dataContainer.sync();
		//		            lastSync = System.currentTimeMillis();
		//} catch (XmlException e) {
		//    throw new XBRLException("The database updates could not be flushed to disk using the sync method.",e);
		//}
	}
	//
	/**
	* @param namespace The namespace of the node to index or null if the node does not have a namespace.
	* @param name The local name of the node to index.
	* @param type The index type.  See the Oracle Berkeley DB documentation for details on what strings to use.
	* @throws XBRLException
	*/
	void StoreImpl::addIndex(const std::string& Namespace, const std::string& name, const std::string& type)
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
		//            xmlUpdateContext = dataManager.createUpdateContext();
		//            dataContainer.setIndexSpecification(xmlIndexSpecification,xmlUpdateContext);
		//        } catch (XmlException e) {
		//            throw new XBRLException("The new index could not be configured.", e);
		//        } finally {
		//            if (xmlIndexSpecification != null) xmlIndexSpecification.delete();
		//        }        
	}
	//    
	/**
	* Handles object inflation.
	* @param in The input object stream used to access the object's serialization.
	* @throws IOException
	* @throws ClassNotFoundException
	*/
	void StoreImpl::readObject(std::istream in)
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
	//
	/**
	* @see java.lang.Object#hashCode()
	*/
	int StoreImpl::hashCode()
	{
		//        final int prime = 31;
		//        int result = super.hashCode();
		//        result = prime * result + ((computerIdentity == null) ? 0 : computerIdentity.hashCode());
		//        result = prime * result + ((containerName == null) ? 0 : containerName.hashCode());
		//        result = prime * result + ((locationName == null) ? 0 : locationName.hashCode());
		//        return result;
		return 0;
	}

	/**
	* @see java.lang.Object#equals(java.lang.Object)
	*/
	//		bool StoreImpl::equals(Object obj)
	//		{
	//        if (this == obj)
	//            return true;
	//        if (!super.equals(obj))
	//            return false;
	//        if (getClass() != obj.getClass())
	//            return false;
	//        StoreImpl other = (StoreImpl) obj;
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

	std::string StoreImpl::toString()
	{
		//        return "Oracle Berkeley XML database at " + this.computerIdentity + " " + this.locationName + " " + this.containerName;
		return "";
	}
	//    
}

