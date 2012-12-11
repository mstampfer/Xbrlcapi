
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
#include <memory>

#include "BaseStoreImpl.h"

#include "dbxml/XmlManager.hpp"
#include "dbxml/XmlResults.hpp"
#include "dbxml/XmlQueryContext.hpp"
#include "db_cxx.h"
#include "dbxml/DbXml.hpp"
#include "Poco/URI.h"

namespace xbrlcapi
{
	struct XML;
	class Loader;

	class StoreImpl : public BaseStoreImpl
	{
	private:
		// The indexing specification of a container
		//DbXml::XmlIndexSpecification xis;

		static const long long serialVersionUID = 668818404270811849L;
		//    private static const Logger logger = Logger.getLogger(StoreImpl.class); 
		std::string computerIdentity;

		std::string locationName;
		std::string containerName;
		//	transient 
		std::unique_ptr<DbEnv> environment;
		int cacheSize;
		/**
		* @return The unique identifier for the computer running this data store.
		* @throws XBRLException
		*/
		/**
		* Defines the default evaluation approach.
		*/
		int queryEvaluationType;
		static const 	u_int32_t env_flags = DB_CREATE     |  // If the environment does not exist, create it.
										  DB_INIT_LOCK  |  // Initialize locking
					   				      DB_INIT_LOG   |  // Initialize logging
										  DB_INIT_MPOOL |  // Initialize the cache
										  DB_INIT_TXN	|  // Initialize transactions
										  DB_THREAD;	   // 
		std::string getComputerName(); 
		void initialize(const std::string& location, const std::string& container);
		void initManager();

		/**
		* Initialises the database container.
		* @throws XBRLException
		*/
		void initContainer(); 
		void createContainer();
		void closeContainer();
		void closeManager();
		DbXml::XmlResults runQuery(std::string& myQuery, 
											  const DbXml::XmlQueryContext::EvaluationType& evaluationType
											  );

		/**
		* Performs a lazy query evaluation
		* @param myQuery The query to be performed.
		* @return the results of the query.
		* @throws XBRLException if the query fails to execute.
		*/
		DbXml::XmlResults performLazyQuery(const std::string& myQuery);



		/**
		* @return a XQuery context, prepared with namespace declarations etc.
		* @throws XBRLException
		*/
		DbXml::XmlQueryContext createQueryContext();

		/**
		* Ensures that the database container is flushed to disk.
		* @see Store#sync()
		*/
		//transient private 
		long lastSync;
		/**
		* Handles object inflation.
		* @param in The input object stream used to access the object's serialization.
		* @throws IOException
		* @throws ClassNotFoundException
		*/
		void readObject(std::istream in);

	public:

		StoreImpl(){}
		StoreImpl(const StoreImpl& rhs);
		StoreImpl& operator=(const StoreImpl& rhs);
		virtual ~StoreImpl(){}

		//	transient public 
		std::unique_ptr<DbXml::XmlManager> dataManager;
		//	transient public 
		DbXml::XmlContainer dataContainer;
		//	
		/**
		* This uses the default 1 GB cache size.
		* @param location The location of the database (The path to where the database exists)
		* @param container The name of the container to hold the data in the store.
		* @throws XBRLException
		*/
	StoreImpl(const std::string& location, const std::string& container) 
			: BaseStoreImpl(), 
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
		StoreImpl(const std::string& location, const std::string& container, int cacheSize) 
			: BaseStoreImpl(), 
			locationName(location), 
			containerName(container),
			cacheSize(cacheSize * 1024*1024),
			queryEvaluationType(DbXml::XmlQueryContext::Eager)
		{
			initialize(location,container);
		}    

		/**
		* Log information about all the indexes in the data store.
		*/
		void logIndexes();
		/**
		* @see org.xbrlapi.data.Store#persist(XML)
		*/
		//synchronized 
		int getSize();
		/**
		* Initialises the database environment.
		* @throws XBRLException if the environment files are not found or 
		* there is a database problem.
		*/
		void initEnvironment();

		/**
		* Initialises the database manager
		* @throws XBRLException
		*/

		/**
		* The closure operation entails closing the XML container and the XML data manager
		* that are used by the store.
		* @see org.xbrlapi.data.Store#close()
		*/
		void close();
		/**
		* @see org.xbrlapi.data.Store#delete()
		*/

		//synchronized 
		void del();
		/**
		* @see org.xbrlapi.data.Store#persist(XML)
		*/
		//synchronized 
		void persist(const XML& xml);

		//
		/**
		* @see org.xbrlapi.data.Store#hasXMLResource(String)
		*/
		//synchronized 
		bool hasXMLResource(const std::string& index);

		/**
		* @see org.xbrlapi.data.Store#getXMLResource(String)
		*/
		//synchronized 
		template <typename F> 
		F getXMLResource(const std::string& index);

		/**
		* @see org.xbrlapi.data.Store#remove(String)
		*/
		//synchronized 
		void remove(XML fragment);

		/**
		* @see org.xbrlapi.data.Store#queryForXMLResources(String)
		*/
		//synchronized 
//		template <typename F>
		std::vector<Stub> queryForXMLResources(std::string& query);

		/**
		* @see org.xbrlapi.data.Store#queryForIndices(String)
		*/
		//synchronized 
		std::unordered_set<std::string> queryForIndices(const std::string& query) ;

		bool StoreImpl::hasDocument(const Poco::URI& uri);
		
		/**
		* @see org.xbrlapi.data.Store#queryForStrings(String)
		*/
		//synchronized 
		std::unordered_set<std::string> queryForStrings(std::string& query); 

		/**
		* @see Store#queryCount(String)
		*/
		//synchronized 
		long queryCount(std::unordered_set<std::string> query);


		/**
		* TODO provide a means of investigating namespace bindings for the query configuration.
		* Provides direct access to the query mechanism so that we can use
		* queries without constructing fragments for each query result.
		* @param myQuery The query to be performed.
		* @return the results of the query.
		* @throws XBRLException if the query fails to execute.
		*/
		//synchronized 
		void sync();

		/**
		* @param namespace The namespace of the node to index or null if the node does not have a namespace.
		* @param name The local name of the node to index.
		* @param type The index type.  See the Oracle Berkeley DB documentation for details on what strings to use.
		* @throws XBRLException
		*/
		void addIndex(const std::string& Namespace, const std::string& name, const std::string& type);



		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();


		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
//		bool equals(Object obj);


		std::string toString();

		//bool requestLoadingRightsFor(LoaderImpl& loader, const Poco::URI& document);
	};
}

