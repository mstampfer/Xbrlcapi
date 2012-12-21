
#include "Stdafx.h"
#pragma once
#include "Logger.h"

#include "SchemaContent.h"
#include <string>
#include <memory>
/**
* Base interface for all kinds of XML Schema declarations
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{
	class SchemaDeclarationImpl;
	class SchemaDeclaration : public  SchemaContent 
	{
		//std::unique_ptr<SchemaDeclarationImpl> pimpl;
	public:
		/**
		* @return the name of the structure being declared or null of the 
		* structure has no name.
		* @throws XBRLException
		*/
		virtual std::string getName(); 

		/**
		* @return true if the content declaration uses a reference to another XML Schema declaration
		* and false otherwise.
		* @throws XBRLException
		*/
		virtual bool hasReference();

		/**
		* @return the namespace for the referenced XML Schema declaration.
		* @throws XBRLException if the datatype is not declared by a type attribute.
		*/
		virtual std::string getReferenceNamespace();

		/**
		* @return the namespace alias (prefix)  for the referenced XML Schema declaration 
		* or the empty string if there is no namespace prefix used in the QName.
		*/
		virtual std::string getReferenceNamespaceAlias();

		/**
		* @return the QName used to specify the identity of the referenced XML Schema
		* declaration.
		* @throws XBRLException if the content declaration does not reference another 
		* XML Schema content declaration using a ref attribute.
		*/
		virtual std::string getReferenceQName();

		/**
		* Retrieve the type local name.
		* @return the local name for the datatype.
		* @throws XBRLException if the datatype is not declared.
		*/    
		virtual std::string getReferenceLocalname();

		/**
		* @return The fragment that is the XML Schema declaration referred to by the 
		* schema content declaration.
		* @throws XBRLException if the fragment cannot be found in the data store.
		*/
		// virtual <F extends SchemaDeclaration> F getReferencedSchemaDeclaration();

	
private:
Logger logger;
};
}
