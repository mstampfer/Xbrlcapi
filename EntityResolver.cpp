#include "EntityResolver.h"
#include "HashFunctions.h"
#include "XBRLException.h"
#include <Poco/Exception.h>
#include <memory>
#include <unordered_map>  
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/util/XMLString.hpp>
#include "Cache.h"
#include "CacheFile.h"
#include "XercesString.h"



namespace xbrlcapi
{
	struct EntityResolver::Impl 
	{
		Cache cache;

		Impl() 
			: cache(Cache())
		{}

		Impl(Cache& cache) : cache(cache)
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
				cache == rhs.cache
				);
		}


		void setGrammarPool(const std::shared_ptr<xercesc::XMLGrammarPoolImpl>& pool)
		{
			cache.setGrammarPool(pool);
		}

		xercesc::InputSource* resolveEntity(const XMLCh *const publicId, const XMLCh *const systemId) 
		{
			return new xercesc::URLInputSource(systemId);

			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("SAX: Resolving the entity for " + toNative(systemId));
			Poco::URI uri(toNative(systemId));
			try {
				if (hasCache()) 
				{ 
					//						uri = cache.getCacheURI(uri);
				}
			} 
			catch (const XBRLException& e) 
			{
				logger.warn("Cache handling for " + toNative(systemId) + "failed.");
				//	return new InputSource(systemId);
			} 
			catch (Poco::SyntaxException e) 
			{
				logger.warn(toNative(systemId) + " is a malformed URI.");
				//	return new InputSource(systemId);
			}
			auto wc_uri = XercesString(uri);
			return new xercesc::URLInputSource(xercesc::XMLURL(wc_uri));
		}

		bool hasCache() 
		{
			return (cache);
		}

		xercesc::InputSource* resolveEntity(const xercesc::XMLResourceIdentifier& resource)
		{
			//try {
			//	logger.debug("SCHEMA: Resolving the entity for " + resource.getExpandedSystemId());
			//xercesc::XMLPlatformUtils::Initialize();
			std::string id = toNative(resource.getSystemId());
			Poco::URI uri(id);
			if (hasCache()) 
			{
				//	uri = cache.getCacheURI(uri);
			}
			//			logger.debug("... so resolving the entity for URI " + uri);
			auto wc_uri = XercesString(uri);
			return new xercesc::URLInputSource(xercesc::XMLURL(wc_uri));
			//} catch (XBRLException e) {
			//	logger.warn("Cache handling for " + resource.getExpandedSystemId() + "failed.");
			//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
			//} catch (URISyntaxException e) {
			//	logger.warn(resource.getExpandedSystemId() + " is a malformed URI.");
			//	return new xercesc::XMLInputSource(resource.getPublicId(),resource.getExpandedSystemId(), resource.getBaseSystemId());
			//}
		}

		std::shared_ptr<xercesc::InputSource> resolveSchemaURI(const Poco::URI& originalURI) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			auto xmlUrl = xercesc::XMLURL(XercesString(originalURI.toString()));
			try 
			{
				boost::filesystem::path fullPath = cache.getCachePath(originalURI);
				if (hasCache() && exists(fullPath) && boost::filesystem::file_size(fullPath) != 0) 
				{
					return std::make_shared<xercesc::LocalFileInputSource>(fullPath.c_str());
				}
				else
				{
					return std::make_shared<xercesc::URLInputSource>(xmlUrl);
				}
			} 
			catch (const boost::filesystem::filesystem_error& e) 
			{
				logger.warn("Cache handling for " + originalURI.toString() + "failed.");
				return std::make_shared<xercesc::URLInputSource>(xmlUrl);
			}
		}

		XercesString copyToCache(const Poco::URI& uri)
		{
				return cache.copyToCache(uri);
		}

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

	std::shared_ptr<xercesc::InputSource> EntityResolver::resolveSchemaURI(const Poco::URI& uri) 
	{
		return pImpl->resolveSchemaURI(uri);
	}

	bool EntityResolver::hasCache() 
	{
		return pImpl->hasCache();
	}

	void EntityResolver::setGrammarPool(const std::shared_ptr<xercesc::XMLGrammarPoolImpl>& pool)
	{
		pImpl->setGrammarPool(pool);
	}

	XercesString EntityResolver::copyToCache(const Poco::URI& uri)
	{
		return pImpl->copyToCache(uri);
	}
}
