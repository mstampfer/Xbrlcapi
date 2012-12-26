#pragma once
#include "PimplImpl.h"
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/util/XMLEntityResolver.hpp>
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
		Pimpl<Impl> p;
	public:
		EntityResolver();
//		EntityResolver(const EntityResolver&);
		~EntityResolver();
		EntityResolver(CacheFile&);
		EntityResolver(Cache&);
		EntityResolver(EntityResolver&& );
		EntityResolver(CacheFile&, std::unordered_map<Poco::URI,Poco::URI>&);
		EntityResolver& operator=(EntityResolver&& rhs);
		bool operator==(const EntityResolver& rhs);
		bool operator!=(const EntityResolver& rhs);

		xercesc::InputSource* resolveEntity(const wchar_t *const publicId, const wchar_t *const systemId)  override;
		xercesc::InputSource* resolveEntity(xercesc::XMLResourceIdentifier* resourceIdentifier) override;
		//xercesc::InputSource* resolveSchemaURI(const Poco::URI& uri);
	};
}
