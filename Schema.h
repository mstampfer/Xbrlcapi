#pragma once
#include "PimplImpl.h"
#include "SchemaContent.h"


#include <list>

namespace xbrlcapi
{
	struct ExtendedLink;
	struct Concept;
	struct ReferencePartDeclaration;
	struct RoleType;
	struct ArcroleType;
	struct ComplexTypeDeclaration;
	struct SimpleTypeDeclaration;
	struct Schema : public SchemaContent 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Schema();
		~Schema();
		Schema(const Schema& rhs);
		Schema& operator=(const Schema& rhs);
		Schema(Schema&& rhs);
		Schema& operator=(Schema&& rhs);
		bool operator==(const Schema& rhs);
		bool operator!=(const Schema& rhs);

		/**
		* Checks if the element form is qualified.
		* @return true if the element form is qualified and false otherwise.
		* @throws XBRLException
		*/
		bool isElementFormQualified();

		/**
		* @return a std::list of SimpleLink fragments, one per XML Schema 
		* import used by this schema.
		* @throws XBRLException
		*/
		std::list<SimpleLink> getImports();

		/**
		* @return the std::list of schemas that import this schema.
		* @throws XBRLException
		*/
		std::list<Schema> getImporters();


		/**
		* @return a std::list of SimpleLink fragments, one per XML Schema 
		* include used by this schema.
		* @throws XBRLException
		*/
		std::list<SimpleLink> getIncludes();

		/**
		* @return a std::list of the extended links contained by the schema.
		* @throws XBRLException
		*/
		std::list<ExtendedLink> getExtendedLinks();

		/**
		* Get the fragment std::list of element declarations (that are not concepts) in the schema.
		* @return the std::list of element declarations in the schema.
		* @throws XBRLException.
		*/
		std::list<Concept> getOtherElementDeclarations();

		/**
		* Get the fragment std::list of concepts in the schema.
		* @return the std::list of concepts in the schema.
		* @throws XBRLException.
		*/
		std::list<Concept> getConcepts();

		/**
		* Get the number of concepts defined in the schema.
		* @return the number of XBRL concepts defined in the 
		* schema.  Note that concepts that are overloaded with 
		* and XBRL Dimensions interpretation are excluded from this
		* count if the XBRL Dimensions loader is being used.
		* @throws XBRLException.
		*/
		long getConceptCount();



		/**
		* Get a specific concept by its name.
		* return the chosen concept or null if the concept does not exist.
		* @param name The name of the concept
		* @throws XBRLException
		*/
		Concept getConceptByName(const std::string& name);

		/**
		* Get a std::list of concepts based on their type.
		* Returns null if no concepts match the selection criteria.
		*
		* @param namespace The namespaceURI of the concept type
		* @param localName The local name of the concept type
		* @return A std::list of concept fragments in the containing schema that
		* match the specified element type.
		* 
		* @throws XBRLException
		*/
		std::list<Concept> getConceptsByType(const std::string& Namespace, const std::string& localName);

		/**
		* Get a std::list concepts based on their substitution group.
		* Returns null if no concepts match the selection criteria.
		*
		* @param namespace The namespaceURI of the concept type
		* @param localname The local name of the concept type
		* 
		* @return a std::list of concepts in the schema that match the specified
		* substitution group
		* 
		* @throws XBRLException
		*/
		std::list<Concept> getConceptsBySubstitutionGroup(const std::string& Namespace, const std::string& localname);

		/**
		* Get a reference part declaration in a schema.
		* Returns null if the reference part does not exist in the schema.
		*
		* @param name The name attribute value of the reference part to be retrieved.
		* @throws XBRLException
		*/
		ReferencePartDeclaration getReferencePartDeclaration(const std::string& name);

		/**
		* Get a std::list of the reference part declarations in a schema.
		* @return a std::list of reference part declarations in the schema.
		* @throws XBRLException
		*/
		std::list<ReferencePartDeclaration> getReferencePartDeclarations();

		/**
		* @return the std::list of role type definitions in the schema
		* @throws XBRLException
		*/
		std::list<RoleType> getRoleTypes();

		/**
		* @return the std::list of arcrole type definitions in the schema
		* @throws XBRLException
		*/
		std::list<ArcroleType> getArcroleTypes();

		/**
		* @return the std::list of global complex type declarations in this schema.
		* @throws XBRLException
		*/
		std::list<ComplexTypeDeclaration> getGlobalComplexTypes();

		/**
		* @return the std::list of global simple type declarations in this schema.
		* @throws XBRLException
		*/
		std::list<SimpleTypeDeclaration> getGlobalSimpleTypes();

		/**
		* 
		* @param <D> The type of the declaration being retrieved.
		* @param name The name of the declaration being retrieved.
		* @return the fragment representing the global schema declaration or null
		* if none exists.
		* @throws XBRLException if the name is null or if the specified type of the global
		* declaration is not consistent with the actual type of the declaration.
		*/
		template<typename T> T getGlobalDeclaration(const std::string& name);
	};   
}