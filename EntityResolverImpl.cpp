
#include "Stdafx.h"
#include "EntityResolverImpl.h"
#include "Poco/URI.h"
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/XMLString.hpp>
#include <memory>


namespace xbrlcapi
{
	EntityResolverImpl::EntityResolverImpl() : cache(Cache())
	{}

	EntityResolverImpl::EntityResolverImpl(CacheFile& cacheFile) : cache(Cache(cacheFile))
	{}

	EntityResolverImpl::EntityResolverImpl(Cache& cache) 
	{
		setCache(cache);
	}    

	void EntityResolverImpl::setCache(Cache& rhs)
	{
		cache.swap(rhs);
	}

	EntityResolverImpl::EntityResolverImpl(CacheFile& cacheFile, std::unordered_map<Poco::URI, Poco::URI> uriMap) 
		: cache(Cache(cacheFile, uriMap))
	{}

	std::shared_ptr<xercesc::InputSource> EntityResolverImpl::resolveEntity(const std::wstring& publicId, const std::wstring& systemId) 
	{
		//logger.debug("SAX: Resolving the entity for " + systemId);
	//	try {
			std::string id(systemId.begin(), systemId.end());
			Poco::URI uri(id);
			if (hasCache()) 
			{ 
				uri = cache.getCacheURI(uri);
			}
			auto wc_uri = xercesc::XMLString::transcode(uri.toString().c_str());
			return std::shared_ptr<xercesc::InputSource>(new xercesc::URLInputSource(wc_uri));
		//} catch (XBRLException e) {
		//	logger.warn("Cache handling for " + systemId + "failed.");
		//	return new InputSource(systemId);
		//} catch (URISyntaxException e) {
		//	logger.warn(systemId + " is a malformed URI.");
		//	return new InputSource(systemId);
		//}
	}

	bool EntityResolverImpl::hasCache() 
	{
		//return (cache != null);
		return false;
	}

	std::shared_ptr<xercesc::InputSource> EntityResolverImpl::resolveEntity(const xercesc::XMLResourceIdentifier& resource)
	{
		//try {
		//	logger.debug("SCHEMA: Resolving the entity for " + resource.getExpandedSystemId());
		xercesc::XMLPlatformUtils::Initialize();
		std::wstring systemId = resource.getSystemId();
		Poco::URI uri(std::string(systemId.begin(), systemId.end()));
		if (hasCache()) 
		{
			uri = cache.getCacheURI(uri);
		}
		//			logger.debug("... so resolving the entity for URI " + uri);
		auto w_uri = xercesc::XMLString::transcode(uri.toString().c_str());
		return std::shared_ptr<xercesc::InputSource>(new xercesc::URLInputSource(w_uri));
		//} catch (XBRLException e) {
		//	logger.warn("Cache handling for " + resource.getExpandedSystemId() + "failed.");
		//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
		//} catch (URISyntaxException e) {
		//	logger.warn(resource.getExpandedSystemId() + " is a malformed URI.");
		//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
		//}
	}

	//std::shared_ptr<xercesc::InputSource> EntityResolverImpl::resolveSchemaURI(const Poco::URI& uri) 
	//{
	//try {
	//    
	//    URI uri = originalURI;
	//    if (hasCache()) {
	//        uri = cache.getCacheURI(originalURI);
	//    }
	//    
	//    return new xercesc::XMLInputSource(null,uri.toString(), uri.toString());
	//    
	//} catch (XBRLException e) {
	//    logger.warn("Cache handling for " + originalURI + "failed.");
	//    return new xercesc::XMLInputSource(null,originalURI.toString(), originalURI.toString());
	//}
	//}

	int EntityResolverImpl::hashCode() 
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
	//EntityResolverImpl other = (EntityResolverImpl) obj;
	//if (cache == null) {
	//    if (other.cache != null)
	//        return false;
	//} else if (!cache.equals(other.cache))
	//    return false;
	//return true;
	//		   }

}
