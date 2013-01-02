#include "EntityResolver.h"
#include "HashFunctions.h"
#include "XBRLException.h"
#include "XercesStrings.h"
#include <Poco/Exception.h>
#include <memory>
#include <unordered_map>  
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/XMLString.hpp>
#include "Cache.h"
#include "CacheFile.h"

namespace xbrlcapi
{
	struct EntityResolver::Impl 
	{
		Cache cache;
		CacheFile cacheFile;

		Impl() : cache(Cache()), cacheFile(CacheFile()) {}

		Impl(Cache& cache) 
		{}    

		Impl(CacheFile& cacheFile) : cache(Cache(cacheFile))
		{}

		Impl(CacheFile& cacheFile, std::unordered_map<Poco::URI, Poco::URI> uriMap) 
			: cache(Cache(cacheFile, uriMap))
		{}

		//Impl& operator=(Impl&& rhs)
		//{
		//	if (this != &rhs)
		//	{
		//		cache = std::move(cache);
		//		cacheFile = std::move(cacheFile);
		//	}
		//	return *this;
		//}

		bool operator==(Impl& rhs)
		{
			return ( 
				cache == rhs.cache &&
				cacheFile == rhs.cacheFile
				);
		}

		xercesc::InputSource* resolveEntity(const XMLCh *const publicId, const XMLCh *const systemId) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("SAX: Resolving the entity for " + xerces_util::toNative(systemId));
			Poco::URI uri(xerces_util::toNative(systemId));
			try {
				if (hasCache()) 
				{ 
					uri = cache.getCacheURI(uri);
				}
			} 
			catch (const XBRLException& e) 
			{
				logger.warn("Cache handling for " + xerces_util::toNative(systemId) + "failed.");
				//	return new InputSource(systemId);
			} 
			catch (Poco::SyntaxException e) 
			{
				logger.warn(xerces_util::toNative(systemId) + " is a malformed URI.");
				//	return new InputSource(systemId);
			}
			auto wc_uri = xercesc::XMLString::transcode(uri.toString().c_str());
			return new xercesc::URLInputSource(wc_uri);
		}

		bool hasCache() 
		{
			return (cache);
		}

		xercesc::InputSource* resolveEntity(const xercesc::XMLResourceIdentifier& resource)
		{
			//try {
			//	logger.debug("SCHEMA: Resolving the entity for " + resource.getExpandedSystemId());
			xercesc::XMLPlatformUtils::Initialize();
			std::string id = xerces_util::toNative(resource.getSystemId());
			Poco::URI uri(id);
			if (hasCache()) 
			{
				uri = cache.getCacheURI(uri);
			}
			//			logger.debug("... so resolving the entity for URI " + uri);
			auto w_uri = xercesc::XMLString::transcode(uri.toString().c_str());
			return new xercesc::URLInputSource(w_uri);
			//} catch (XBRLException e) {
			//	logger.warn("Cache handling for " + resource.getExpandedSystemId() + "failed.");
			//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
			//} catch (URISyntaxException e) {
			//	logger.warn(resource.getExpandedSystemId() + " is a malformed URI.");
			//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
			//}
		}

		//std::shared_ptr<xercesc::InputSource> resolveSchemaURI(const Poco::URI& uri) 
		//{
		//	try {

		//		Poco::URI uri = originalURI;
		//		if (hasCache()) 
		//		{
		//			uri = cache.getCacheURI(originalURI);
		//		}

		//		return xercesc::XMLInputSource(NULL,uri.toString(), uri.toString());

		//	} 

		//	catch (XBRLException e) 
		//	{
		//		logger.warn("Cache handling for " + originalURI.toString() + "failed.");
		//		return std::shared_ptr(new xercesc::XMLInputSource(NULL, originalURI.toString(), originalURI.toString()));
		//	}
		//}

		int hashCode() 
		{
			//final int prime = 31;
			//int result = 1;
			//result = prime 		//return result;
			return 0;
		}



		//		   public:
		//			   bool equals(Object obj) {
		//if (this == obj)
		//    return true;
		//if (obj == null)
		//    return false;
		//if (getClass() != obj.getClass())
		//    return false;
		//EntityResolver::Impl other = (EntityResolver::Impl) obj;
		//if (cache == null) {
		//    if (other.cache != null)
		//        return false;
		//} else if (!cache.equals(other.cache))
		//    return false;
		//return true;
		//		   }

	};

	EntityResolver::EntityResolver() {}
	EntityResolver::~EntityResolver() {}

	EntityResolver::EntityResolver(const EntityResolver& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	EntityResolver& EntityResolver::operator=(const EntityResolver& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	EntityResolver::EntityResolver(EntityResolver&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	EntityResolver& EntityResolver::operator=(EntityResolver&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	EntityResolver::EntityResolver(CacheFile& cacheFile) : pImpl(cacheFile)
	{}

	EntityResolver::EntityResolver(CacheFile& cacheFile, std::unordered_map<Poco::URI,Poco::URI>& map)
		: pImpl(cacheFile, map)
	{}

	EntityResolver::EntityResolver(Cache& cache) : pImpl(cache)
	{}


	bool EntityResolver::operator==(const EntityResolver& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool EntityResolver::operator!=(const EntityResolver& rhs)
	{
		return !this->operator==(rhs);
	}

	xercesc::InputSource* EntityResolver::resolveEntity(const XMLCh *const publicId, const XMLCh *const systemId) 
	{
		return pImpl->resolveEntity(publicId, systemId);
	}

	xercesc::InputSource* EntityResolver::resolveEntity(xercesc::XMLResourceIdentifier* resourceIdentifier) 
	{
		return pImpl->resolveEntity(std::ref(*resourceIdentifier));
	}

	//xercesc::InputSource* EntityResolver::resolveSchemaURI(const Poco::URI& uri) 
	//{
	//	return pImpl->resolveSchemaURI(uri);
	//}

	bool EntityResolver::hasCache() 
	{
		return pImpl->hasCache();
	}
}
