
#include "stdafx.h"
//#include "ComplexTypeDeclaration.h"
#include "ElementDeclarationImpl.h"
/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi 
{

	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isAbstract()
	//	*/
	//	bool ElementDeclarationImpl::isAbstract()
	//	{
	//		if (getDataRootElement().getAttribute("abstract").equals("true")) {
	//			return true;
	//		}
	//		return false;
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isNillable()
	//	*/
	//	bool ElementDeclarationImpl::isNillable()
	//	{
	//		if (getDataRootElement().getAttribute("nillable").equals("true")) {
	//			return true;
	//		}
	//		return false;
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isItem()
	//	*/
	//	bool ElementDeclarationImpl::isItem()
	//	{
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
	//		throw new XBRLException("The substitution group is invalid.");
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isTuple()
	//	*/
	//	bool ElementDeclarationImpl::isTuple()
	//	{
	//		if (this.getName().equals("tuple") && this.getTargetNamespace().equals(Constants.XBRL21Namespace)) return true;
	//		if (! this.hasSubstitutionGroup()) return false;
	//		return this.getSubstitutionGroupDeclaration().isTuple();
	//	}
	//
	//	/**
	//	* @see ElementDeclaration#substitutesFor(ElementDeclaration)
	//	*/
	//	bool ElementDeclarationImpl::substitutesFor(ElementDeclaration candidate)
	//	{
	//		if (! this.hasSubstitutionGroup() ) return false;
	//		ElementDeclaration parent = this.getSubstitutionGroupDeclaration();
	//		if (parent.equals(candidate)) return true;
	//		return parent.substitutesFor(candidate);
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#hasSubstitutionGroup()
	//	*/
	//	bool ElementDeclarationImpl::hasSubstitutionGroup()
	//	{
	//		return getDataRootElement().hasAttribute("substitutionGroup");
	//	}      
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupNamespace()
	//	*/
	//	std::string ElementDeclarationImpl::getSubstitutionGroupNamespace()
	//	{
	//		std::string qname = getSubstitutionGroupQName();
	//		if (qname.equals("") || (qname == null)) throw new XBRLException("The element declaration does not declare its XML Schema substitution group via a substitutionGroup attribute.");   	
	//		return getNamespaceFromQName(qname, getDataRootElement());
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupNamespaceAlias()
	//	*/    
	//	std::string ElementDeclarationImpl::getSubstitutionGroupNamespaceAlias()
	//	{
	//		std::string sg = getSubstitutionGroupQName();
	//		if (sg.equals("") || (sg == null))
	//			throw new XBRLException("The element declaration does not declare its substitution group via a substitutionGroup attribute.");    	
	//		return getPrefixFromQName(sg);
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupQName()
	//	*/  
	//	std::string ElementDeclarationImpl::getSubstitutionGroupQName()
	//	{
	//		if (getDataRootElement().hasAttribute("substitutionGroup"))
	//			return getDataRootElement().getAttribute("substitutionGroup");
	//		return null;
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupDeclaration()
	//	*/
	//	ElementDeclaration ElementDeclarationImpl::getSubstitutionGroupDeclaration()
	//	{
	//
	//		ElementDeclaration result = null;
	//		if (this.hasSubstitutionGroup()) {
	//			try {
	//				result = (ElementDeclaration) getStore().getSchemaContent(this.getSubstitutionGroupNamespace(),this.getSubstitutionGroupLocalname());
	//				if (result == null) throw new XBRLException("The substitution group element declaration is not declared in a schema contained in the data store.");
	//			} catch (ClassCastException cce) {
	//				throw new XBRLException("The Substitution Group XML Schema element declaration is  of the wrong fragment type.",cce);
	//			}
	//		}
	//		return result;
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupLocalname()
	//	*/  
	//	std::string ElementDeclarationImpl::getSubstitutionGroupLocalname()
	//	{
	//		std::string sg = getSubstitutionGroupQName();
	//		if (sg == null) return null;
	//		if (sg.equals(""))
	//			throw new XBRLException("The element declaration must not have an empty substitution group attribute.");    	
	//		return getLocalnameFromQName(sg);
	//	}
	//
	//	/**
	//	* @see ElementDeclaration#hasLocalComplexType()
	//	*/
	//	bool ElementDeclarationImpl::hasLocalComplexType()
	//	{
	//		return (getStore().queryCount("#roots#[@parentIndex='"+getIndex()+"' and @type='org.xbrlapi.impl.ComplexTypeDeclarationImpl']") == 1);
	//	}    
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#getLocalComplexType()
	//	*/
	//	ComplexTypeDeclaration getLocalComplexType()
	//	{
	//		List<ComplexTypeDeclaration> ctds = this.getChildren("ComplexTypeDeclaration");
	//		if (ctds.size() > 1) throw new XBRLException("The element has too many local complex types.");
	//		if (ctds.size() == 0) throw new XBRLException("The element does not have a local complex type.");
	//		return ctds.get(0);
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isFinalForRestriction()
	//	*/
	//	bool ElementDeclarationImpl::isFinalForRestriction()
	//	{
	//		std::string value = getDataRootElement().getAttribute("final");
	//		if (value.matches("restriction")) return true;
	//		return value.equals("#all");
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isFinalForRestriction()
	//	*/
	//	bool ElementDeclarationImpl::isFinalForExtension()
	//	{
	//		std::string value = getDataRootElement().getAttribute("final");
	//		if (value.matches("extension")) return true;
	//		return value.equals("#all");
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isBlockingSubstitution()
	//	*/
	//	bool ElementDeclarationImpl::isBlockingSubstitution()
	//	{
	//		std::string value = getDataRootElement().getAttribute("block");
	//		if (value.matches("substitution")) return true;
	//		return value.equals("#all");
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isBlockingRestriction()
	//	*/
	//	bool ElementDeclarationImpl::isBlockingRestriction()
	//	{
	//		std::string value = getDataRootElement().getAttribute("block");
	//		if (value.matches("restriction")) return true;
	//		return value.equals("#all");
	//	}
	//
	//	/**
	//	* @see org.xbrlapi.ElementDeclaration#isBlockingRestriction()
	//	*/
	//	bool ElementDeclarationImpl::isBlockingExtension()
	//	{
	//		std::string value = getDataRootElement().getAttribute("block");
	//		if (value.matches("extension")) return true;
	//		return value.equals("#all");
	//	}
	//
	//
	//
	//	/**
	//	* @see ElementDeclaration#getMaxOccurs()
	//	*/
	//	std::string ElementDeclarationImpl::getMaxOccurs()
	//	{
	//		if (this.isGlobal()) throw new XBRLException("The element is global.");
	//		if (getDataRootElement().hasAttribute("maxOccurs")) return getDataRootElement().getAttribute("maxOccurs");
	//		return "1";
	//	}
	//
	//	/**
	//	* @see ElementDeclaration#getMinOccurs()
	//	*/
	//	std::string ElementDeclarationImpl::getMinOccurs()
	//	{
	//		if (this.isGlobal()) throw new XBRLException("The element is global.");
	//		if (getDataRootElement().hasAttribute("minOccurs")) return getDataRootElement().getAttribute("minOccurs");
	//		return "1";
	//	}
}