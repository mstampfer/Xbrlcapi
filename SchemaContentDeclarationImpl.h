
#pragma once

#include "SchemaContentDeclaration.h"
#include "SchemaDeclarationImpl.h"
//#include "TypeDeclaration.h"

//**
/* Base interface for XML Schema element and attribute declaration fragments.
/
*/

namespace xbrlcapi
{
	class SchemaContentDeclarationImpl : public SchemaDeclarationImpl, public SchemaContentDeclaration 
	{

		/**
		* 
		*/
	private:

		/**
		* @see SchemaContentDeclaration#isGlobal()
		*/
		bool isGlobal();

		/**
		* @see org.xbrlapi.SchemaContentDeclaration#getForm()
		*/
		std::string getForm(); 

		/**
		* @see SchemaContentDeclaration#getDefault()
		*/
		std::string getDefault();

		/**
		* @see SchemaContentDeclaration#getFixed()
		*/
		std::string getFixed();

		/**
		* @see SchemaContentDeclaration#isFixed()
		*/
		bool isFixed() ; 

		/**
		* @see SchemaContentDeclaration#hasTypeReference()
		*/
		bool hasTypeReference();

		/**
		* @see SchemaContentDeclaration#getTypeNamespace()
		*/
		std::string getTypeNamespace();

		/**
		* @see SchemaContentDeclaration#getTypeNamespaceAlias()
		*/
		std::string getTypeNamespaceAlias();

		/**
		* @see SchemaContentDeclaration#getTypeQName()
		*/
		std::string getTypeQName();

		/**
		* @see SchemaContentDeclaration#getTypeLocalname()
		*/  
		std::string getTypeLocalname();

		/**
		* @see org.xbrlapi.SchemaContentDeclaration#getTypeDeclaration()
		*/  
		//TypeDeclaration getTypeDeclaration();

		/**
		* @return The XQuery that will retrieve the local type fragments for this fragment.
		*/
	private:
		std::string localTypeQuery();

		/**
		* @see SchemaContentDeclaration#hasLocalType()
		*/
		bool hasLocalType();

		/**
		* @see org.xbrlapi.SchemaContentDeclaration#getLocalType()
		*/
		//		TypeDeclaration getLocalType();

	};
}