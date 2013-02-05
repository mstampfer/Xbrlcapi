#include "Tuple.h"
namespace xbrlcapi
{
	struct Tuple::Impl 
	{
		Impl() {}

		std::list<Fact> getChildFacts()
		{
			//return getStore().queryForXMLResources("#roots#[@parentIndex='" + this.getIndex() + "' and (@type='org.xbrlapi.impl.SimpleNumericItemImpl' or @type='org.xbrlapi.impl.FractionItemImpl' or @type='org.xbrlapi.impl.NonNumericItemImpl'  or @type='org.xbrlapi.impl.TupleImpl')]");
			return std::list<Fact>();
		}


		std::list<Fact> getChildFacts(const std::string& Naamespace, const std::string& name) 
		{
			//this.getStore().setNamespaceBinding(namespace,"xbrlapi_concept");
			//String query = "for $root in #roots#[@parentIndex='" + this.getIndex() + "'] where $root/xbrlapi:data/xbrlapi_concept:" + name + " return $root";
			//return getStore().queryForXMLResources(query); 
			return std::list<Fact>();
		}

		std::list<Fact> getChildFacts(const std::string& Namespace, const std::string& name, const std::string& contextRef) 
		{
			//getStore().setNamespaceBinding(namespace,"xbrlapi_tupleNamespacePrefix");
			//String query = "#roots#[@parentIndex='" + this.getIndex() + "' and " + Constants.XBRLAPIPrefix + ":" +  "data/xbrlapi_tupleNamespacePrefix:" +  name + "[@contextRef='" + contextRef + "']]";
			//return getStore().queryForXMLResources(query);
			return std::list<Fact>();
		}
	};

	Tuple::Tuple() {}
	Tuple::~Tuple() {} 

	Tuple::Tuple(const Tuple& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Tuple& Tuple::operator=(const Tuple& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Tuple::Tuple(Tuple&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Tuple& Tuple::operator=(Tuple&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Tuple::operator==(const Tuple& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Tuple::operator!=(const Tuple& rhs)
	{
		return !this->operator==(rhs);
	}

	std::list<Fact> Tuple::getChildFacts()
	{
		return pImpl->getChildFacts();
	}


	std::list<Fact> Tuple::getChildFacts(const std::string& Naamespace, const std::string& name) 
	{
		return pImpl->getChildFacts();
	}

	std::list<Fact> Tuple::getChildFacts(const std::string& Namespace, const std::string& name, const std::string& contextRef) 
	{
		return pImpl->getChildFacts(Namespace, name, contextRef);
	}
}