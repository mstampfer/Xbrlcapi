#include "ElementDeclaration.h"
#include "TypeDeclaration.h"

namespace xbrlcapi 
{
	struct ElementDeclaration::Impl 
	{
		Impl() {}
		bool isAbstract()
		{
			//		if (getDataRootElement().getAttribute("abstract").equals("true")) {
			//			return true;
			//		}
			return false;
		}
		//
		bool isNillable()
		{
			//		if (getDataRootElement().getAttribute("nillable").equals("true")) {
			//			return true;
			//		}
			return false;
		}
		//
		bool isItem()
		{
			//		std::string sgName = this.getSubstitutionGroupLocalname();
			//		logger.debug(sgName);
			//		if (sgName == null) return false;
			//		std::string sgNamespace = this.getSubstitutionGroupNamespace();
			//		logger.debug(sgNamespace);
			//		std::string query = "#roots#[*/xsd:element/@name='" + sgName + "']";
			//		logger.debug(query);
			//		List<ElementDeclaration> declarations = getStore().<ElementDeclaration>queryForXMLResources(query);
			//		for (ElementDeclaration declaration: declarations) {
			//			if (declaration.getTargetNamespace().equals(sgNamespace)) {
			//				if (declaration.getName().equals("item") && declaration.getTargetNamespace().equals(Constants.XBRL21Namespace)) {
			//					return true;
			//				}
			//				try {
			//					return declaration.isItem();
			//				} catch (XBRLException e) {
			//					return false;
			//				}
			//			}
			//		}
			//		throw XBRLException("The substitution group is invalid.");
			return false;

		}

		bool isTuple()
		{
			//		if (this.getName().equals("tuple") && this.getTargetNamespace().equals(Constants.XBRL21Namespace)) return true;
			//		if (! this.hasSubstitutionGroup()) return false;
			//		return this.getSubstitutionGroupDeclaration().isTuple();
			return false;

		}

		bool substitutesFor(ElementDeclaration candidate)
		{
			//		if (! this.hasSubstitutionGroup() ) return false;
			//		ElementDeclaration parent = this.getSubstitutionGroupDeclaration();
			//		if (parent.equals(candidate)) return true;
			//		return parent.substitutesFor(candidate);
			return false;

		}

		bool hasSubstitutionGroup()
		{
			//		return getDataRootElement().hasAttribute("substitutionGroup");
			return false;

		}      

		std::string getSubstitutionGroupNamespace()
		{
			//		std::string qname = getSubstitutionGroupQName();
			//		if (qname.equals("") || (qname == null)) throw XBRLException("The element declaration does not declare its XML Schema substitution group via a substitutionGroup attribute.");   	
			//		return getNamespaceFromQName(qname, getDataRootElement());
			return std::string();
		}

		std::string getSubstitutionGroupNamespaceAlias()
		{
			//		std::string sg = getSubstitutionGroupQName();
			//		if (sg.equals("") || (sg == null))
			//			throw XBRLException("The element declaration does not declare its substitution group via a substitutionGroup attribute.");    	
			//		return getPrefixFromQName(sg);
			return std::string();
		}

		std::string getSubstitutionGroupQName()
		{
			//		if (getDataRootElement().hasAttribute("substitutionGroup"))
			//			return getDataRootElement().getAttribute("substitutionGroup");
			//		return null;
			return std::string();
		}

		ElementDeclaration getSubstitutionGroupDeclaration()
		{
			//
			//		ElementDeclaration result = null;
			//		if (this.hasSubstitutionGroup()) {
			//			try {
			//				result = (ElementDeclaration) getStore().getSchemaContent(this.getSubstitutionGroupNamespace(),this.getSubstitutionGroupLocalname());
			//				if (result == null) throw XBRLException("The substitution group element declaration is not declared in a schema contained in the data store.");
			//			} catch (ClassCastException cce) {
			//				throw XBRLException("The Substitution Group XML Schema element declaration is  of the wrong fragment type.",cce);
			//			}
			//		}
			//		return result;
			return ElementDeclaration();
		}

		std::string getSubstitutionGroupLocalname()
		{
			//		std::string sg = getSubstitutionGroupQName();
			//		if (sg == null) return null;
			//		if (sg.equals(""))
			//			throw XBRLException("The element declaration must not have an empty substitution group attribute.");    	
			//		return getLocalnameFromQName(sg);
			return std::string();
		}

		bool hasLocalComplexType()
		{
			//		return (getStore().queryCount("#roots#[@parentIndex='"+getIndex()+"' and @type='org.xbrlapi.impl.ComplexTypeDeclarationImpl']") == 1);
			return false;
		}    

		TypeDeclaration getLocalComplexType()
		{
			//	//		List<ComplexTypeDeclaration> ctds = this.getChildren("ComplexTypeDeclaration");
			//	//		if (ctds.size() > 1) throw XBRLException("The element has too many local complex types.");
			//	//		if (ctds.size() == 0) throw XBRLException("The element does not have a local complex type.");
			//	//		return ctds.get(0);
			return TypeDeclaration();
		}

		bool isFinalForRestriction()
		{
			//		std::string value = getDataRootElement().getAttribute("final");
			//		if (value.matches("restriction")) return true;
			//		return value.equals("#all");
			return false;
		}

		bool isFinalForExtension()
		{
			//		std::string value = getDataRootElement().getAttribute("final");
			//		if (value.matches("extension")) return true;
			//		return value.equals("#all");
			return false;

		}

		bool isBlockingSubstitution()
		{
			//		std::string value = getDataRootElement().getAttribute("block");
			//		if (value.matches("substitution")) return true;
			//		return value.equals("#all");
			return false;
		}

		bool isBlockingRestriction()
		{
			//		std::string value = getDataRootElement().getAttribute("block");
			//		if (value.matches("restriction")) return true;
			//		return value.equals("#all");
			return false;

		}

		bool isBlockingExtension()
		{
			//		std::string value = getDataRootElement().getAttribute("block");
			//		if (value.matches("extension")) return true;
			//		return value.equals("#all");
			return false;

		}

		std::string getMaxOccurs()
		{
			//		if (this.isGlobal()) throw XBRLException("The element is global.");
			//		if (getDataRootElement().hasAttribute("maxOccurs")) return getDataRootElement().getAttribute("maxOccurs");
			//		return "1";
			return std::string();
		}

		std::string getMinOccurs()
		{
			//		if (this.isGlobal()) throw XBRLException("The element is global.");
			//		if (getDataRootElement().hasAttribute("minOccurs")) return getDataRootElement().getAttribute("minOccurs");
			//		return "1";
			return std::string();
		}
	};

	ElementDeclaration::ElementDeclaration() {}
	ElementDeclaration::~ElementDeclaration() {} 

	ElementDeclaration::ElementDeclaration(const ElementDeclaration& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ElementDeclaration& ElementDeclaration::operator=(const ElementDeclaration& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ElementDeclaration::ElementDeclaration(ElementDeclaration&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ElementDeclaration& ElementDeclaration::operator=(ElementDeclaration&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ElementDeclaration::operator==(const ElementDeclaration& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ElementDeclaration::operator!=(const ElementDeclaration& rhs)
	{
		return !this->operator==(rhs);
	}


	bool ElementDeclaration::isAbstract()
	{
		return pImpl->isAbstract();
	}
	bool ElementDeclaration::isNillable()
	{
		return pImpl->isNillable();
	}
	bool ElementDeclaration::isItem()
	{
		return pImpl->isItem();
	}

	bool ElementDeclaration::isTuple()
	{
		return pImpl->isTuple();
	}

	bool ElementDeclaration::substitutesFor(const ElementDeclaration& candidate)
	{
		return pImpl->substitutesFor(candidate);
	}

	bool ElementDeclaration::hasSubstitutionGroup()
	{
		return pImpl->hasSubstitutionGroup();
	}      

	std::string ElementDeclaration::getSubstitutionGroupNamespace()
	{
		return pImpl->getSubstitutionGroupNamespace();
	}

	std::string ElementDeclaration::getSubstitutionGroupNamespaceAlias()
	{
		return pImpl->getSubstitutionGroupNamespaceAlias();
	}

	std::string ElementDeclaration::getSubstitutionGroupQName()
	{
		return pImpl->getSubstitutionGroupQName();
	}

	ElementDeclaration ElementDeclaration::getSubstitutionGroupDeclaration()
	{
		return pImpl->getSubstitutionGroupDeclaration();
	}

	std::string ElementDeclaration::getSubstitutionGroupLocalname()
	{
		return pImpl->getSubstitutionGroupLocalname();
	}

	bool ElementDeclaration::hasLocalComplexType()
	{
		return pImpl->hasLocalComplexType();
	}    

	TypeDeclaration ElementDeclaration::getLocalComplexType()
	{
		return pImpl->getLocalComplexType();
	}

	bool ElementDeclaration::isFinalForRestriction()
	{
		return pImpl->isFinalForRestriction();
	}

	bool ElementDeclaration::isFinalForExtension()
	{
		return pImpl->isFinalForExtension();
	}

	bool ElementDeclaration::isBlockingSubstitution()
	{
		return pImpl->isBlockingSubstitution();
	}

	bool ElementDeclaration::isBlockingRestriction()
	{
		return pImpl->isBlockingRestriction();
	}

	bool ElementDeclaration::isBlockingExtension()
	{
		return pImpl->isBlockingExtension();
	}

	std::string ElementDeclaration::getMaxOccurs()
	{
		return pImpl->getMaxOccurs();
	}

	std::string ElementDeclaration::getMinOccurs()
	{
		return pImpl->getMinOccurs();
	}
}