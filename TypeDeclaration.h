#pragma once
#include "SchemaDeclaration.h"
#include <xercesc/dom/DOMElement.hpp>

namespace xbrlcapi
{
	class TypeDeclaration : public SchemaDeclaration
	{

		/**
		* @return the type derivation element specifying the QName of the type that is being extended or restricted.
		* @
		*/
	private:
		std::shared_ptr<xercesc::DOMElement>  getDerivation();

	public:
		/**
		* @see org.xbrlapi.TypeDeclaration#getFinal()
		*/
		std::string getFinal(); 

		/**
		* @see org.xbrlapi.TypeDeclaration#isFinal()
		*/
		bool isFinal(); 

		/**
		* @see org.xbrlapi.TypeDeclaration#isFinalForExtension()
		*/
		bool isFinalForExtension();

		/**
		* @see org.xbrlapi.TypeDeclaration#isFinalForRestriction()
		*/
		bool isFinalForRestriction(); 

		/**
		* @see org.xbrlapi.TypeDeclaration#isDerivedFrom(org.xbrlapi.TypeDeclaration)
		*/
		bool isDerivedFrom(TypeDeclaration candidate);

		/**
		* @see org.xbrlapi.TypeDeclaration#isDerivedFrom(std::string, java.lang.std::string)
		*/
		bool isDerivedFrom(const std::string& Namespace, const std::string& name);

		/**
		* @see org.xbrlapi.TypeDeclaration#getParentType()
		*/
		TypeDeclaration getParentType(); 

		/**
		* @see org.xbrlapi.TypeDeclaration#getParentTypeLocalname()
		*/
		std::string getParentTypeLocalname(); 

		/**
		* @see org.xbrlapi.TypeDeclaration#getParentTypeNamespace()
		*/
		std::string getParentTypeNamespace(); 

		/**
		* @see TypeDeclaration#isNumericItemType()
		*/
		bool isNumericItemType(); 
	};
}