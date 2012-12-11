
#include "stdafx.h"
#include "SchemaContentDeclarationImpl.h"
#include "SchemaContentDeclaration.h"
#include "SchemaDeclarationImpl.h"
//#include "TypeDeclaration.h"

/**
* Base interface for XML Schema element and attribute declaration fragments.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{

		///**
		//* @see SchemaContentDeclaration#isGlobal()
		//*/
		//bool isGlobal() {
		//	return getSchema().getIndex().equals(this.getParentIndex());
		//}

		///**
		//* @see org.xbrlapi.SchemaContentDeclaration#getForm()
		//*/
		//std::string getForm() {
		//	if (! getDataRootElement().hasAttribute("form")) return null;
		//	return getDataRootElement().getAttribute("form");
		//}    

		///**
		//* @see SchemaContentDeclaration#getDefault()
		//*/
		//std::string getDefault() {
		//	Element root = getDataRootElement(); 
		//	if (! root.hasAttribute("default")) return null;
		//	return root.getAttribute("default");
		//}

		///**
		//* @see SchemaContentDeclaration#getFixed()
		//*/
		//std::string getFixed() {
		//	Element root = getDataRootElement(); 
		//	if (! root.hasAttribute("fixed")) return null;
		//	return root.getAttribute("fixed");      
		//}

		///**
		//* @see SchemaContentDeclaration#isFixed()
		//*/
		//bool isFixed() {
		//	return getDataRootElement().hasAttribute("fixed");
		//}    

		///**
		//* @see SchemaContentDeclaration#hasTypeReference()
		//*/
		//bool hasTypeReference() {
		//	return getDataRootElement().hasAttribute("type");
		//}

		///**
		//* @see SchemaContentDeclaration#getTypeNamespace()
		//*/
		//std::string getTypeNamespace() {
		//	return getNamespaceFromQName(getTypeQName(), getDataRootElement());
		//}

		///**
		//* @see SchemaContentDeclaration#getTypeNamespaceAlias()
		//*/
		//std::string getTypeNamespaceAlias() {
		//	return getPrefixFromQName(getTypeQName());
		//}

		///**
		//* @see SchemaContentDeclaration#getTypeQName()
		//*/
		//std::string getTypeQName() {
		//	if (! hasTypeReference()) throw new XBRLException(this.getIndex() + ": The schema content declaration does not have a named data type.");
		//	std::string qname = getDataRootElement().getAttribute("type");
		//	if (qname.equals("") || (qname == null)) throw new XBRLException("The element declaration does not declare its XML Schema data type via a type attribute.");
		//	return qname;
		//}

		///**
		//* @see SchemaContentDeclaration#getTypeLocalname()
		//*/  
		//std::string getTypeLocalname() {
		//	return getLocalnameFromQName(getTypeQName());
		//}

		///**
		//* @see org.xbrlapi.SchemaContentDeclaration#getTypeDeclaration()
		//*/  
		//TypeDeclaration getTypeDeclaration() {
		//	TypeDeclaration result = this.getLocalType();
		//	if (result != null) return result;
		//	if (this.hasTypeReference()) {
		//		try {
		//			result = (TypeDeclaration) getStore().getSchemaContent(this.getTypeNamespace(),this.getTypeLocalname());
		//			if (result == null) throw new XBRLException("The type " + this.getTypeQName() + " is not declared in a schema contained in the data store.");
		//		} catch (ClassCastException cce) {
		//			throw new XBRLException("The XML Schema type declaration is  of the wrong fragment type.",cce);
		//		}
		//	}
		//	return result;
		//}

		///**
		//* @return The XQuery that will retrieve the local type fragments for this fragment.
		//*/
		//private std::string localTypeQuery() {
		//	return "for $root in #roots#[@parentIndex='"+getIndex()+"'] where $root/@type='org.xbrlapi.impl.SimpleTypeDeclarationImpl' or $root/@type='org.xbrlapi.impl.ComplexTypeDeclarationImpl' return $root";
		//}

		///**
		//* @see SchemaContentDeclaration#hasLocalType()
		//*/
		//bool hasLocalType() {
		//	long localTypes = getStore().queryCount(localTypeQuery());
		//	if (localTypes > 1) throw new XBRLException("The Schema content declaration has too many local types.");
		//	return (localTypes == 1);
		//}

		///**
		//* @see org.xbrlapi.SchemaContentDeclaration#getLocalType()
		//*/
		//TypeDeclaration getLocalType() {

		//	List<TypeDeclaration> types = getStore().<TypeDeclaration>queryForXMLResources(localTypeQuery());
		//	if (types.size() == 1) return types.get(0);
		//	if (types.size() > 1) throw new XBRLException("There are too many local type declarations for this content declaration.");
		//	return null;
		//}    

}