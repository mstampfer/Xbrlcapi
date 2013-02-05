#pragma once
#include "PimplImpl.h"
#include <string>
#include <list>
#include "Item.h"
#include "CustomType.h"

namespace xbrlcapi
{
	class ExtendedLink;
	class SimpleLink;
	class Resource;

	class RoleType : public CustomType
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		RoleType();
		~RoleType();
		RoleType(const RoleType& rhs);
		RoleType& operator=(const RoleType& rhs);
		RoleType(RoleType&& rhs);
		RoleType& operator=(RoleType&& rhs);
		bool operator==(const RoleType& rhs);
		bool operator!=(const RoleType& rhs);

		std::list<ExtendedLink> getUsingExtendedLinks();

		std::list<SimpleLink> getUsingSimpleLinks();

		std::list<Resource> getUsingResources();

	};
}
