#include "Concept.h"
#include "Schema.h"
#include "Fact.h"
#include <string>
#include <vector>

namespace xbrlcapi
{
	struct Concept::Impl 
	{
		Impl() {}
		std::string getPeriodType() 
		{
			//Element root = getDataRootElement();
			//if (root.hasAttributeNS(Constants.XBRL21Namespace,"periodType"))
			//	return root.getAttributeNS(Constants.XBRL21Namespace,"periodType");
			//if (! this->isTuple()) throw XBRLException("The period attribute is mandatory on XBRL concepts in the item substitution group.");
			//return nullptr;
			return std::string();
		}

		std::string getBalance() 
		{
			//Element root = getDataRootElement();
			//if (root.hasAttributeNS(Constants.XBRL21Namespace,"balance"))
			//	return root.getAttributeNS(Constants.XBRL21Namespace,"balance");
			//return nullptr;
			return std::string();
		}

		Schema getSchema() 
		{
			//return (Schema) this->getAncestorOrSelf("org.xbrlapi.impl.SchemaImpl");
			return Schema();
		}

		std::vector<Fact> getFacts() 
		{
			//getStore().setNamespaceBinding(this->getTargetNamespace(),"xbrlapi_concept");
			//return getStore().queryForXMLResources("#roots#[xbrlapi:data/xbrlapi_concept:"+ this->getName() + "]"); 
			return std::vector<Fact>();
		}

		std::vector<Fact> getRootFacts() 
		{
			//getStore().setNamespaceBinding(this->getTargetNamespace(),"xbrlapi_concept");
			//std::string query = "for $instance in #roots#[@type='"+InstanceImpl.class.getName()+"'], $root in #roots#[xbrlapi:data/xbrlapi_concept:"+ this->getName() + "] where ($instance/@index = $root/@parentIndex) return $root";
			//return getStore().queryForXMLResources(query); 
			return std::vector<Fact>();
		}    

		long getFactCount() 
		{
			//getStore().setNamespaceBinding(getTargetNamespace(),"xbrlapi_concept");
			//std::string query = "for $root in #roots# where $root/xbrlapi:data/xbrlapi_concept:"+ this->getName() + " return $root";
			//return getStore().queryCount(query);
			return long();
		}

		std::unordered_set<std::string> getFactIndices() 
		{
			//getStore().setNamespaceBinding(getTargetNamespace(),"xbrlapi_concept");
			//return getStore().queryForIndices("#roots#[*/xbrlapi_concept:"+ this->getName() + "]");
			return std::unordered_set<std::string>();
		}        

		std::vector<std::string> getPresentationNetworkLinkroles() 
		{
			//std::vector<std::string> roles = new Vector<std::string>();
			//for (const Network& network: getStore().getMinimalNetworksWithArcrole(this,Constants.PresentationArcrole)) 
			//{

			//	roles.add(network.getLinkRole());
			//}
			//return roles;
			return std::vector<std::string>();
		}

		bool isNumeric() 
		{
			//if (this->isTuple()) return false;
			//TypeDeclaration typeDeclaration = this->getTypeDeclaration();
			//return typeDeclaration.isNumericItemType();
			return false;
		}
	};

	Concept::Concept() {}
	Concept::~Concept() {} 

	Concept::Concept(const Concept& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Concept& Concept::operator=(const Concept& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Concept::Concept(Concept&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Concept& Concept::operator=(Concept&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Concept::operator==(const Concept& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Concept::operator!=(const Concept& rhs)
	{
		return !this->operator==(rhs);
	}

	std::string Concept::getPeriodType()
	{
		return pImpl->getPeriodType();
	}


	std::string Concept::getBalance()
	{
		return pImpl->getBalance();
	}


	bool Concept::isNumeric()
	{
		return pImpl->isNumeric();
	}


	std::vector<Fact> Concept::getFacts()
	{
		return pImpl->getFacts();
	}


	std::vector<Fact> Concept::getRootFacts()
	{
		return pImpl->getRootFacts();
	}


	long Concept::getFactCount()
	{
		return pImpl->getFactCount();
	}


	std::unordered_set<std::string> Concept::getFactIndices()
	{
		return pImpl->getFactIndices();
	}


	std::vector<std::string> Concept::getPresentationNetworkLinkroles()
	{
		return pImpl->getPresentationNetworkLinkroles();
	}


}