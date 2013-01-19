#pragma once
#include "PimplImpl.h"
#include "XercesString.h"
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/util/XMLEntityResolver.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <Poco/URI.h>
#include <unordered_map>

/**
* General entity resolver interface that enforces serializability.
*/
namespace xbrlcapi
{
	class Cache;
	class CacheFile;
	class EntityResolver 
		: public xercesc::EntityResolver, public xercesc::XMLEntityResolver //, Serializable 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		EntityResolver();
		//		EntityResolver(const EntityResolver&);
		~EntityResolver();
		EntityResolver(const EntityResolver& rhs);
		EntityResolver& operator=(const EntityResolver& rhs);
		EntityResolver(EntityResolver&& );
		EntityResolver(CacheFile&, std::unordered_map<Poco::URI,Poco::URI>&);
		EntityResolver(Cache& cache);
		EntityResolver(Cache& cache, std::unordered_map<Poco::URI, Poco::URI> uriMap);
		EntityResolver& operator=(EntityResolver&& rhs);
		bool operator==(const EntityResolver& rhs);
		bool operator!=(const EntityResolver& rhs);
//		xercesc::InputSource* resolveEntity(const wchar_t *const publicId, const wchar_t *const systemId) override;
		virtual xercesc::InputSource* resolveEntity(const XMLCh *const publicId, const XMLCh *const systemId) override;
		virtual xercesc::InputSource* resolveEntity(xercesc::XMLResourceIdentifier* resourceIdentifier) override;
		std::shared_ptr<xercesc::InputSource> resolveSchemaURI(const Poco::URI& uri);
		void setGrammarPool(const std::shared_ptr<xercesc::XMLGrammarPoolImpl>&pool);
		XercesString  copyToCache(const Poco::URI& uri);
		bool hasCache();
	};
}
