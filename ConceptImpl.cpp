
#include "ConceptImpl.h"

namespace xbrlcapi
{
	/**
		
	*/


	//	/**
	//	* The serial version UID.
	//	* @see 
	//	* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
	//	* for information about what changes will require the serial version UID to be
	//	* modified.
	//	*/
	//private:

	//public: 
	//	/**
	//	* @see org.xbrlapi.Concept#getPeriodType()
	//	*/
	//	std::string getPeriodType() {
	//		Element root = getDataRootElement();
	//		if (root.hasAttributeNS(Constants.XBRL21Namespace,"periodType"))
	//			return root.getAttributeNS(Constants.XBRL21Namespace,"periodType");
	//		if (! this->isTuple()) throw XBRLException("The period attribute is mandatory on XBRL concepts in the item substitution group.");
	//		return nullptr;
	//	}

	//	/**
	//	* @see org.xbrlapi.Concept#getBalance()
	//	*/
	//	std::string getBalance() {
	//		Element root = getDataRootElement();
	//		if (root.hasAttributeNS(Constants.XBRL21Namespace,"balance"))
	//			return root.getAttributeNS(Constants.XBRL21Namespace,"balance");
	//		return nullptr;
	//	}

	//	/**
	//	* Retrieves the fragment that is the schema for this concept.
	//	* @return a Schema fragment for the parent schema of this concept.
	//	* @throws XBRLException
	//	* @see org.xbrlapi.Concept#getSchema()
	//	*/
	//	Schema getSchema() {
	//		return (Schema) this->getAncestorOrSelf("org.xbrlapi.impl.SchemaImpl");
	//	}

	//	/**
	//	* @see org.xbrlapi.Concept#getFacts()
	//	*/
	//	std::vector<Fact&> getFacts() {
	//		getStore().setNamespaceBinding(this->getTargetNamespace(),"xbrlapi_concept");
	//		return getStore().queryForXMLResources("#roots#[xbrlapi:data/xbrlapi_concept:"+ this->getName() + "]"); 
	//	}

	//	/**
	//	* @see org.xbrlapi.Concept#getRootFacts()
	//	*/
	//	std::vector<Fact&> getRootFacts() {
	//		getStore().setNamespaceBinding(this->getTargetNamespace(),"xbrlapi_concept");
	//		std::string query = "for $instance in #roots#[@type='"+InstanceImpl.class.getName()+"'], $root in #roots#[xbrlapi:data/xbrlapi_concept:"+ this->getName() + "] where ($instance/@index = $root/@parentIndex) return $root";
	//		return getStore().queryForXMLResources(query); 
	//	}    

	//	/**
	//	* @see org.xbrlapi.Concept#getFactCount()
	//	*/
	//	long getFactCount() {
	//		getStore().setNamespaceBinding(getTargetNamespace(),"xbrlapi_concept");
	//		std::string query = "for $root in #roots# where $root/xbrlapi:data/xbrlapi_concept:"+ this->getName() + " return $root";
	//		return getStore().queryCount(query);
	//	}

	//	/**
	//	* @see org.xbrlapi.Concept#getFactIndices()
	//	*/
	//	std::unordered_set<std::string> getFactIndices() {
	//		getStore().setNamespaceBinding(getTargetNamespace(),"xbrlapi_concept");
	//		return getStore().queryForIndices("#roots#[*/xbrlapi_concept:"+ this->getName() + "]");
	//	}        

	//	/**
	//	* @see org.xbrlapi.Concept#getPresentationNetworkLinkroles()
	//	*/
	//	std::vector<std::string> getPresentationNetworkLinkroles() {
	//		std::vector<std::string> roles = new Vector<std::string>();
	//		for (const Network& network: getStore().getMinimalNetworksWithArcrole(this,Constants.PresentationArcrole)) {
	//			roles.add(network.getLinkRole());
	//		}
	//		return roles;
	//	}

	//	/**
	//	* @see Concept#isNumeric()
	//	*/
	//	bool isNumeric() {
	//		if (this->isTuple()) return false;
	//		TypeDeclaration typeDeclaration = this->getTypeDeclaration();
	//		return typeDeclaration.isNumericItemType();
		//}
}