#include "Stdafx.h"
#pragma once
#include "Logger.h"


#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/util/XMLEntityResolver.hpp>
#include <xercesc/framework/URLInputSource.hpp>

#include "HashFunctions.h"
#include "EntityResolverImpl.h"

#include <memory>
#include <unordered_map>
/**
* General entity resolver interface that enforces serializability.
* 
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class EntityResolver 
		: public xercesc::EntityResolver, public xercesc::XMLEntityResolver //, Serializable 
	{
		std::shared_ptr<EntityResolverImpl> pimpl;
		EntityResolver& operator=(EntityResolver& rhs);
		EntityResolver(EntityResolver& rhs);

	public:

		EntityResolver& operator=(EntityResolver&& rhs)
		{
			pimpl = rhs.pimpl;
			return *this;
		}

		EntityResolver(EntityResolver&& rhs)
		{
			pimpl = std::move(rhs.pimpl);
		}


		EntityResolver() : pimpl(new EntityResolverImpl()) {}

		EntityResolver(CacheFile& cacheFile) : pimpl(new EntityResolverImpl(cacheFile)) {}

		EntityResolver(Cache& cache) 
		{
			pimpl->setCache(cache);
		}

		EntityResolver(CacheFile& cacheFile, std::unordered_map<Poco::URI,Poco::URI> uriMap) 
			: pimpl(new EntityResolverImpl(cacheFile, uriMap)) 
		{}

		xercesc::InputSource* resolveEntity(const wchar_t *const publicId, const wchar_t *const systemId)  override
		{
			return pimpl->resolveEntity(std::wstring(publicId), std::wstring(systemId));
		}

		xercesc::InputSource* resolveEntity(xercesc::XMLResourceIdentifier* resourceIdentifier) override
		{
			return pimpl->resolveEntity(std::ref(*resourceIdentifier));
		}

		/**
		* @param uri the URI to be resolved.
		* @return the XMLInputSource for the given URI.
		*/
		xercesc::InputSource* resolveSchemaURI(const Poco::URI& uri) 
		{
			return pimpl->resolveSchemaURI(uri);
		}


		private:
Logger logger;
};
}
