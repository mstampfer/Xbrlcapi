
#pragma once

//#include "Schema.h"
#include "SchemaContent.h"
#include "Fragment.h"
#include <string>

namespace xbrlcapi
{

	/**

	*/

	class SchemaContentImpl : public Fragment, public SchemaContent 
	{

		/**
		* 
		*/
	private:

		/**
		* @see org.xbrlapi.SchemaContent#getSchema()
		*/
		Schema getSchema();

		/**
		* @see org.xbrlapi.SchemaContent#getTargetNamespace()
		*/
		std::string getTargetNamespace();

		/**
		* @see org.xbrlapi.SchemaContent#getAnnotations()
		*/
		std::vector<std::shared_ptr<xercesc::DOMElement>> getAnnotations();

		/**
		* @see SchemaContent#hasOtherAttribute(String,String)
		* @see Element#hasAttributeNS(String, String)
		*/
		bool hasOtherAttribute(const std::string& Namespace, const std::string& localname);

		/**
		* @see org.xbrlapi.SchemaContent#getOtherAttributes()
		*/
		std::vector<std::shared_ptr<xercesc::DOMNode>> getOtherAttributes();

		/**
		* @see org.w3c.dom.Element#getAttributeNS(String, String)
		* @see SchemaContent#getOtherAttribute(String,String)
		*/
		std::string getOtherAttribute(const std::string& Namespace, const std::string& localname);

		/**
		*  @see org.xbrlapi.SchemaDeclaration#getSchemaId()
		*/
		std::string getSchemaId();
	};
}