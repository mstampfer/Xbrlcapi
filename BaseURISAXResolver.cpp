#include "BaseURISAXResolver.h"
#include <stack>

namespace xbrlcapi
{
	struct BaseURISAXResolver::Impl : public BaseURIResolver
	{
		std::stack<Poco::URI> baseURIs;

		Impl(const Poco::URI& documentURI) 
		{
			baseURIs.push(documentURI);
		}

		Impl() 
		{
			baseURIs.push(Poco::URI());
		}

		Impl(const Impl& rhs) 
		{
			baseURIs = rhs.baseURIs;
		}

		Poco::URI getBaseURI() 
		{
			return baseURIs.top();
		}

		void addBaseURI(const std::string& xmlBase) 
		{

			//// If no xmlBase information then just use the current one
			//if ((xmlBase == "") || (xmlBase == null))
			//{
			//	baseURIs.push(getBaseURI());
			//	return;
			//}

			//Poco::URI base = null;
			//if (getBaseURI() == null)
			//{
			//	try
			//	{
			//		base = new URI(xmlBase);
			//	} catch (URISyntaxException e)
			//	{
			//		throw new XMLBaseException("Base URI attribute contains a Malformed URI: " + xmlBase,e);
			//	}
			//} else
			//{
			//	try
			//	{
			//		base = getBaseURI().resolve(new URI(xmlBase));
			//	} catch (URISyntaxException e)
			//	{
			//		throw new XMLBaseException("Base URI resolution of attribute value " + xmlBase + " against " + getBaseURI() + "involved a Malformed URI.",e);
			//	}
			//}
			//baseURIs.push(base);
		}

		void removeBaseURI() 
		{
			//baseURIs.pop();
		}
	};

	BaseURISAXResolver::BaseURISAXResolver() {}

	BaseURISAXResolver::~BaseURISAXResolver() {} 

	BaseURISAXResolver::BaseURISAXResolver(const Poco::URI& documentURI) 
	{
		pImpl->baseURIs.push(documentURI);
	}

	BaseURISAXResolver::BaseURISAXResolver(const BaseURISAXResolver& rhs) 
	{
		pImpl = rhs.pImpl;
	}

	BaseURISAXResolver::BaseURISAXResolver(BaseURISAXResolver&& rhs) : pImpl(std::move(rhs.pImpl))
	{}

	BaseURISAXResolver& BaseURISAXResolver::operator=(const BaseURISAXResolver& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	BaseURISAXResolver& BaseURISAXResolver::operator=(BaseURISAXResolver&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool BaseURISAXResolver::operator==(const BaseURISAXResolver& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool BaseURISAXResolver::operator!=(const BaseURISAXResolver& rhs)
	{
		return !this->operator==(rhs);
	}

	Poco::URI BaseURISAXResolver::getBaseURI()
	{
		return pImpl->getBaseURI();
	}

	void BaseURISAXResolver::addBaseURI(const std::string& xmlBase)
	{
		pImpl->addBaseURI(xmlBase);
	}

	void BaseURISAXResolver::removeBaseURI()
	{
		pImpl->removeBaseURI();
	}
}