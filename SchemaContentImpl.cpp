
//#include "Schema.h"
#include "SchemaContentImpl.h"

namespace xbrlcapi
{
	///**
	//* @see org.xbrlapi.SchemaContent#getSchema()
	//*/
	//Schema getSchema()
	//{
	//	return (Schema) getAncestorOrSelf("org.xbrlapi.impl.SchemaImpl");
	//}

	///**
	//* @see org.xbrlapi.SchemaContent#getTargetNamespace()
	//*/
	//std::string getTargetNamespace()
	//{
	//	Schema s = getSchema();
	//	Element e = s.getDataRootElement();
	//	if (e.hasAttribute("targetNamespace")) return e.getAttribute("targetNamespace");
	//	return null;
	//}

	///**
	//* @see org.xbrlapi.SchemaContent#getAnnotations()
	//*/
	//List<Element> getAnnotations()
	//{
	//	List<Element> result = new Vector<Element>();
	//	NodeList nodes = this.getDataRootElement().getElementsByTagNameNS(Constants.XMLSchemaNamespace.toString(),"annotation");
	//	for (int i=0; i<nodes.getLength(); i++)
	//{
	//		result.add((Element) nodes.item(i));
	//	}
	//	return result;
	//}    

	///**
	//* @see SchemaContent#hasOtherAttribute(String,String)
	//* @see Element#hasAttributeNS(String, String)
	//*/
	//boolean hasOtherAttribute(const std::string& namespace, const std::string& localname)
	//{
	//	return getDataRootElement().hasAttributeNS(namespace.toString(), localname);
	//}

	///**
	//* @see org.xbrlapi.SchemaContent#getOtherAttributes()
	//*/
	//LinkedList<Node> getOtherAttributes()
	//{
	//	NamedNodeMap attributes = getDataRootElement().getAttributes();
	//	LinkedList<Node> otherAttributes = new LinkedList<Node>();
	//	for (int i=0; i<attributes.getLength(); i++)
	//{
	//		std::string ns = attributes.item(i).getNamespaceURI();
	//		if (! ns.equals(Constants.XMLSchemaNamespace.toString()) && ! ns.equals(Constants.XBRL21Namespace.toString()))
	//{
	//			otherAttributes.add(attributes.item(i));
	//		}
	//	}
	//	return otherAttributes;
	//}    

	///**
	//* @see org.w3c.dom.Element#getAttributeNS(String, String)
	//* @see SchemaContent#getOtherAttribute(String,String)
	//*/
	//std::string getOtherAttribute(const std::string& namespace, const std::string& localname)
	//{
	//	if (this.hasOtherAttribute(namespace, localname)) 
	//		return getDataRootElement().getAttributeNS(namespace.toString(), localname);
	//	return null;
	//}

	///**
	//*  @see org.xbrlapi.SchemaDeclaration#getSchemaId()
	//*/
	//std::string getSchemaId()
	//{
	//	if (! getDataRootElement().hasAttributeNS(Constants.XMLSchemaNamespace.toString(),"id")) return null;
	//	return getDataRootElement().getAttributeNS(Constants.XMLSchemaNamespace.toString(),"id");
	//}    
}