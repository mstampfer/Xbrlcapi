
#pragma once

//#include "ComplexTypeDeclaration.h"
#include "ElementDeclaration.h"
#include "Constants.h"
#include "SchemaContentDeclarationImpl.h"
#include <string>
/**

*/
namespace xbrlcapi 
{

	class ElementDeclarationImpl : public SchemaContentDeclarationImpl, public ElementDeclaration 
	{

		/**
		* The serial version UID.
		* @see 
		* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
		* for information about what changes will require the serial version UID to be
		* modified.
		*/
	private:

		/**
		* @see org.xbrlapi.ElementDeclaration#isAbstract()
		*/
		bool isAbstract();

		/**
		* @see org.xbrlapi.ElementDeclaration#isNillable()
		*/
		bool isNillable();

		/**
		* @see org.xbrlapi.ElementDeclaration#isItem()
		*/
		bool isItem();

		/**
		* @see org.xbrlapi.ElementDeclaration#isTuple()
		*/
		bool isTuple();

		/**
		* @see ElementDeclaration#substitutesFor(ElementDeclaration)
		*/
		bool substitutesFor(const ElementDeclaration& candidate);

		/**
		* @see org.xbrlapi.ElementDeclaration#hasSubstitutionGroup()
		*/
		bool hasSubstitutionGroup();

		/**
		* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupNamespace()
		*/
		std::string getSubstitutionGroupNamespace();

		/**
		* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupNamespaceAlias()
		*/    
		std::string getSubstitutionGroupNamespaceAlias();

		/**
		* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupQName()
		*/  
		std::string getSubstitutionGroupQName();

		/**
		* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupDeclaration()
		*/
		ElementDeclaration getSubstitutionGroupDeclaration();

		/**
		* @see org.xbrlapi.ElementDeclaration#getSubstitutionGroupLocalname()
		*/  
		std::string getSubstitutionGroupLocalname();

		/**
		* @see ElementDeclaration#hasLocalComplexType()
		*/
		bool hasLocalComplexType();

		/**
		* @see org.xbrlapi.ElementDeclaration#getLocalComplexType()
		*/
		ComplexTypeDeclaration getLocalComplexType();

		/**
		* @see org.xbrlapi.ElementDeclaration#isFinalForRestriction()
		*/
		bool isFinalForRestriction();

		/**
		* @see org.xbrlapi.ElementDeclaration#isFinalForRestriction()
		*/
		bool isFinalForExtension();

		/**
		* @see org.xbrlapi.ElementDeclaration#isBlockingSubstitution()
		*/
		bool isBlockingSubstitution();

		/**
		* @see org.xbrlapi.ElementDeclaration#isBlockingRestriction()
		*/
		bool isBlockingRestriction();

		/**
		* @see org.xbrlapi.ElementDeclaration#isBlockingRestriction()
		*/
		bool isBlockingExtension();

		/**
		* @see ElementDeclaration#getMaxOccurs()
		*/
		std::string getMaxOccurs();

		/**
		* @see ElementDeclaration#getMinOccurs()
		*/
		std::string getMinOccurs();
	};
}