
#include "Stdafx.h"
#pragma once
#include "Logger.h"

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

#include "Fragment.h"
namespace xbrlcapi
{
	class Schema;
	class Element;
	class Node;

	struct SchemaContent : public Fragment {

		/**
		* @return the schema fragment that is the schema containing this element declaration.
		* @throws XBRLException if the schema content is not inside a schema.
		*/
		virtual Schema getSchema();

		/**
		* @return the target Namespace of the schema that contains this fragment
		* or null if no targetNamespace attribute is defined for the containing
		* schema fragment.
		* @throws XBRLException
		*/
		virtual std::string getTargetNamespace();

		/**
		* @return a list of other (non XML Schema defined ) attributes
		* on the root element of the Schema declaration.  The list is 
		* empty if there are no other attributes.
		* @throws XBRLException
		*/
		virtual std::vector<Node> getOtherAttributes();

		/**
		* Mirrors the hasAttributeNS method of the org.w3c.dom.Element class.
		* @param Namespace The Namespace of the attribute being tested for
		* @param localname The local name of the attribute being tested for
		* @return true if the root element of the fragment has the specified
		* attribute and false otherwise.
		* @throws XBRLException
		*/
		virtual bool hasOtherAttribute(const std::string& Namespace, const std::string& localname);    

		/**
		* Mirrors the getAttributeNS method of the org.w3c.dom.Element class.
		* @param Namespace The Namespace of the attribute being tested for
		* @param localname The local name of the attribute being tested for
		* @return the value of the attribute if it occurs on 
		* the root element of the fragment and null otherwise.
		*/
		virtual std::string getOtherAttribute(const std::string& Namespace, const std::string& localname);  

		/**
		* @return a list of annotation child elements for the given fragment 
		* or the empty list if there are no child annotations.
		* @throws XBRLException
		*/
		virtual std::vector<Element> getAnnotations();    

		/**
		* @return the the XML Schema ID attribute value or null if the 
		* schema content root element has no XML Schema ID attribute.
		* @throws XBRLException
		*/
		virtual std::string getSchemaId();

	
private:
Logger logger;
};
}

