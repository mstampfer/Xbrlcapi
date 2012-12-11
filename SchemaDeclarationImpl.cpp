#include "stdafx.h"
#include "SchemaDeclarationImpl.h"

namespace xbrlcapi
{
	/**
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/


	///**
	// * Get the name of structure being declared.
	// * @return the name of the structure being declared.
	// * @throws XBRLException
	// * @see org.xbrlapi.SchemaDeclaration#getName()
	// */
	//std::string getName() {
	//    Element element = getDataRootElement();
	//    if (element.hasAttribute("name")) return element.getAttribute("name");
	//    return null;
	//}

	///**
	// * @see org.xbrlapi.SchemaDeclaration#hasReference()
	// */
	//bool hasReference() {
	//    return getDataRootElement().hasAttribute("ref");
	//}

	///**
	// * @see org.xbrlapi.SchemaDeclaration#getReferenceNamespace()
	// */
	//std::string getReferenceNamespace() {
	//    return getNamespaceFromQName(getReferenceQName(), getDataRootElement());
	//}
	//
	///**
	// * @see org.xbrlapi.SchemaDeclaration#getReferenceNamespaceAlias()
	// */
	//std::string getReferenceNamespaceAlias() {
	//    return getPrefixFromQName(getReferenceQName());
	//}

	///**
	// * @see org.xbrlapi.SchemaDeclaration#getReferenceQName()
	// */
	//std::string getReferenceQName() {
	//    if (! hasReference()) throw new XBRLException("The content declaration does not use a reference to another XML Schema declaration.");
	//    std::string qname = getDataRootElement().getAttribute("ref");
	//    if (qname.equals("") || (qname == null)) throw new XBRLException("The element declaration does not use a reference to another XML Schema declaration.");
	//    return qname;
	//}

	///**
	// * @see org.xbrlapi.SchemaDeclaration#getReferenceLocalname()
	// */  
	//std::string getReferenceLocalname() {
	//    return getLocalnameFromQName(getReferenceQName());
	//}

	///**
	// * @see org.xbrlapi.SchemaDeclaration#getReferencedSchemaDeclaration()
	// */  
	//@SuppressWarnings("unchecked")
	//<F extends SchemaDeclaration> F getReferencedSchemaDeclaration() {
	//    try {
	//        F sd = (F) getStore().getSchemaContent(this.getReferenceNamespace(),this.getReferenceLocalname());
	//        if (sd == null) throw new XBRLException("The schema declaration is not in a schema contained in the data store.");
	//        return sd;
	//    } catch (ClassCastException e) {
	//        throw new XBRLException("The XML Schema declaration is  of the wrong fragment type.",e);
	//    }

}