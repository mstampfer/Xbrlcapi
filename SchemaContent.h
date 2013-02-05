#pragma once
#include "PimplImpl.h"
#include "Fragment.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>

namespace xbrlcapi
{
	class Schema;

	class SchemaContent : public Fragment  
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		SchemaContent();
		~SchemaContent();
		SchemaContent(const SchemaContent& rhs);
		SchemaContent& operator=(const SchemaContent& rhs);
		SchemaContent(SchemaContent&& rhs);
		SchemaContent& operator=(SchemaContent&& rhs);
		bool operator==(const SchemaContent& rhs);
		bool operator!=(const SchemaContent& rhs);

		/**
		* @return the schema fragment that is the schema containing this element declaration.
		* @throws XBRLException if the schema content is not inside a schema.
		*/
		virtual SchemaContent getSchema();

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
		virtual std::vector<std::shared_ptr<xercesc::DOMNode>> getOtherAttributes();

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
		virtual std::vector<std::shared_ptr<xercesc::DOMElement>> getAnnotations();    

		/**
		* @return the the XML Schema ID attribute value or null if the 
		* schema content root element has no XML Schema ID attribute.
		* @throws XBRLException
		*/
		virtual std::string getSchemaId();
	};
}

