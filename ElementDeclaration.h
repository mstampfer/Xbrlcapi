

#pragma once
#include "Logger.h"


#include <string>
#include "SchemaContentDeclaration.h"

namespace xbrlcapi
{

	class ComplexTypeDeclaration;

	/**
	* Used for top level element declarations (where the elements are
	* given a name and occur as children of XML Schema schema elements.
	* Other element declarations are not used as roots for fragments.
	
	*/

	struct ElementDeclaration : public SchemaContentDeclaration {

		/**
		* @return true if the element is abstract and false otherwise.
		* @throws XBRLException
		*/
		virtual bool isAbstract();

		/**
		* @return true iff the element is final for extension.
		* @throws XBRLException
		*/
		virtual bool isFinalForExtension();    

		/**
		* @return true iff the element is final for restriction.
		* @throws XBRLException
		*/
		virtual bool isFinalForRestriction();

		/**
		* @return true iff the element is blocking substitution.
		* @throws XBRLException
		*/
		virtual bool isBlockingSubstitution();

		/**
		* @return true iff the element is blocking extension.
		* @throws XBRLException
		*/
		virtual bool isBlockingExtension();    

		/**
		* @return true iff the element is blocking restriction.
		* @throws XBRLException
		*/
		virtual bool isBlockingRestriction();    

		/**
		* Determine if a concept is nillable
		*
		* @return true if the concept is nillable and false otherwise.
		* @throws XBRLException
		*/
		virtual bool isNillable();

		/**
		* @return true if the content declaration has a named substitution group and false otherwise.
		* @throws XBRLException
		*/
		virtual bool hasSubstitutionGroup();

		/**
		* @return The fragment that is the declaration of the substitution group element.
		* @throws XBRLException if there is no such declaration in the data store or if the
		* fragment is not an XML Schema element declaration.
		*/
		virtual ElementDeclaration getSubstitutionGroupDeclaration();

		/**
		* Retrieve the substitution group namespace.
		* @return the namespace for the element substitution group.
		* @throws XBRLException if the substitution group is not declared by a substitution group attribute.
		*/
		virtual std::string getSubstitutionGroupNamespace();

		/**
		* Retrieve the substitution group namespace alias (also known as a namespace prefix).
		* @return the namespace alias for the element substitution group or the empty string if the default namespace prefix
		* is used.
		* @throws XBRLException if the substitution group is not declared by a substitution group attribute.
		*/ 
		virtual std::string getSubstitutionGroupNamespaceAlias();

		/**
		* Retrieve the substitution group QName.
		* @return the QName used to specify the substitution group or null
		* if the element has no substitutionGroup attribute.
		* @throws XBRLException if the data root element is not available.
		*/  
		virtual std::string getSubstitutionGroupQName();

		/**
		* Retrieve the substitution group local name.
		* @return the local name for the substitution group.
		* @throws XBRLException if the substitution group is not declared.
		*/
		virtual std::string getSubstitutionGroupLocalname();

		/**
		* @return true if the element declaration is for an element 
		* in the substitution group for the XBRL item element and
		* false otherwise.
		* @throws XBRLException
		*/
		virtual bool isItem();

		/**
		* @return true if the element declaration is for an element 
		* in the substitution group for the XBRL tuple element and
		* false otherwise.
		* @throws XBRLException
		*/
		virtual bool isTuple();

		/**
		* @return true iff the element declaration has a single local complex type.
		* @throws XBRLException
		*/
		virtual bool hasLocalComplexType();

		/**
		* @return the local complex type definition.
		* @throws XBRLException if there is no local complex type declaration or
		* if there is more than one local complex type declaration (an XML Schema error).
		*/
		virtual ComplexTypeDeclaration getLocalComplexType();     

		/**
		* @return the maximum number of times that the element can occur within a complex type definition.
		* @throws XBRLException if the element declaration is global.
		*/
		virtual std::string getMaxOccurs();

		/**
		* @return the minimum number of times that the element can occur within a complex type definition.
		* @throws XBRLException if the element declaration is global.
		*/
		virtual std::string getMinOccurs();    

		/**
		* @param candidate The candidate element declaration. 
		* @return true if this element substitutes for the candidate element declaration
		* and false otherwise.
		* @throws XBRLException
		*/
		virtual bool substitutesFor(ElementDeclaration candidate);     
		private:
Logger logger;
};
}
