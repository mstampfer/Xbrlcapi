#include "Stdafx.h"
#pragma once
#include "Logger.h"

//#include "Schema.h"
#include "SchemaContent.h"
#include "FragmentImpl.h"
#include <string>

namespace xbrlcapi
{

	/**
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/

	class SchemaContentImpl : public FragmentImpl, public SchemaContent 
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
		std::vector<Element> getAnnotations();

		/**
		* @see SchemaContent#hasOtherAttribute(String,String)
		* @see Element#hasAttributeNS(String, String)
		*/
		bool hasOtherAttribute(const std::string& Namespace, const std::string& localname);

		/**
		* @see org.xbrlapi.SchemaContent#getOtherAttributes()
		*/
		std::vector<Node> getOtherAttributes();

		/**
		* @see org.w3c.dom.Element#getAttributeNS(String, String)
		* @see SchemaContent#getOtherAttribute(String,String)
		*/
		std::string getOtherAttribute(const std::string& Namespace, const std::string& localname);

		/**
		*  @see org.xbrlapi.SchemaDeclaration#getSchemaId()
		*/
		std::string getSchemaId();

	private:
Logger logger;
};
}