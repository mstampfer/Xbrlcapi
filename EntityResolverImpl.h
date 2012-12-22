

#pragma once
#include "Logger.h"

#include "Cache.h"
#include "HashFunctions.h"

#include <fstream>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/XMLResourceIdentifier.hpp>
#include <xercesc/framework/URLInputSource.hpp>


/**
* Entity resolver that dynamically adds to the local document
* cache if it is set up and that gives preference to the local 
* cache (if it is set up) as resources are identified by the 
* resolution process.

*/

namespace xbrlcapi
{
	class EntityResolverImpl 
	{
	private:


		/**
		* The local document cache.
		*/
		Cache cache;
		/**
		* @return true if the resolver has a cache and false otherwise.
		*/
		bool hasCache();

	public:
		/**
		* Construct the entity resolver without a cache.
		*/
		EntityResolverImpl();

		/**
		* Construct the entity resolver by storing the cache root.
		* @param cacheFile The root directory of the local cache.
		* @throws XBRLException if the cache cannot be initialised.
		*/
		EntityResolverImpl(CacheFile& cacheFile);

		/**
		* Construct the entity resolver by storing the cache itself.
		* @param cache The local cache to use.
		* @throws XBRLException if the cache cannot be initialised.
		*/
		EntityResolverImpl(Cache& cache);

		void setCache(Cache& cache);

		/**
		* Create the entity resolver with a set of local URIs 
		* to be used by the loader in place of actual URIs.  
		* These local URIs, pointing to resources on the local file system, are used
		* by the loader's entity resolver to swap the local resource for the  
		* original resource at the original URI.  Such substitutions are used by the 
		* entity resolver when doing SAX parsing and when building XML Schema grammar
		* models.
		* @param cacheFile The root directory of the local cache.
		* @param uriMap The map from original URIs to local URIs.
		* @throws XBRLException if any of the objects in the list of URIs is not a 
		* java.net.URI object.
		*/
		EntityResolverImpl(CacheFile& cacheFile, 
			std::unordered_map<Poco::URI, 
			Poco::URI> uriMap);

		EntityResolverImpl& operator=(const EntityResolverImpl&);

		/**
		* Resolve the entity for a SAX parser using the system identifier.
		* @param publicId The public identifier.
		* @param systemId The system identifier that gets resolved.
		*/

		xercesc::InputSource* resolveEntity(const std::wstring& publicId, const std::wstring& systemId);


		/**
		* Implements the resolveEntity method defined in the org.apache.xerces.xni.parser.XMLEntityResolver
		* interface, incorporating interactions with the local document cache (if it exists) to ensure that any
		* new documents are cached and any documents already in the cache are sourced from the cache.
		* @param resource The XML Resource Identifier used to identify the XML resource to be converted
		* into an XML input source and to be cached if it is not already cached.
		* @see org.apache.xerces.xni.parser.XMLEntityResolver#resolveEntity(org.apache.xerces.xni.XMLResourceIdentifier)
		*/

		xercesc::InputSource* resolveEntity(const xercesc::XMLResourceIdentifier& resource);

		/**
		* @param originalURI the URI to be resolved.
		* @return the XMLInputSource for the given URI.
		*/
		xercesc::InputSource* resolveSchemaURI(const Poco::URI& uri); 

		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
		//			   bool equals(Object obj); 

		private:
Logger logger;
};
}
