#include "RoleType.h"
#include "SimpleLink.h"
#include "ExtendedLink.h"
#include "Resource.h"

namespace xbrlcapi
{
	struct RoleType::Impl 
	{
		Impl() {}

		std::list<ExtendedLink> getUsingExtendedLinks()
		{
			//std::string query = "for $root in #roots#[@type='"+ExtendedLinkImpl.class.getName()+"'] where $root/xbrlapi:data/*/@xlink:role='"+ this.getCustomURI() +"' return $root";
			//std::list<ExtendedLink> result = getStore().<ExtendedLink>queryForXMLResources(query);
			//return result;
			return std::list<ExtendedLink>();
		}

		std::list<SimpleLink> getUsingSimpleLinks()
		{
			//std::string query = "for $root in #roots#[@type='"+SimpleLinkImpl.class.getName()+"'] where $root/xbrlapi:data/*/@xlink:role='"+ this.getCustomURI() +"' return $root";
			//std::list<SimpleLink> result = getStore().<SimpleLink>queryForXMLResources(query);
			//return result;
			return std::list<SimpleLink>();
		}    

		std::list<Resource> getUsingResources()
		{
			//std::string query = "for $root in #roots# let $data := $root/xbrlapi:data/* where ($data/@xlink:type='resource' and $data/@xlink:role='"+ this.getCustomURI() +"') return $root";
			//std::list<Resource> result = getStore().<Resource>queryForXMLResources(query);
			//return result;
			return std::list<Resource>();
		}   
	};
	RoleType::RoleType() {}
	RoleType::~RoleType() {} 

	RoleType::RoleType(const RoleType& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	RoleType& RoleType::operator=(const RoleType& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	RoleType::RoleType(RoleType&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	RoleType& RoleType::operator=(RoleType&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool RoleType::operator==(const RoleType& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool RoleType::operator!=(const RoleType& rhs)
	{
		return !this->operator==(rhs);
	}
	std::list<ExtendedLink> RoleType::getUsingExtendedLinks()
	{
		return pImpl->getUsingExtendedLinks();
	}

	std::list<SimpleLink> RoleType::getUsingSimpleLinks()
	{
		return pImpl->getUsingSimpleLinks();
	}    

	std::list<Resource> RoleType::getUsingResources()
	{
		return pImpl->getUsingResources();
	}   

}