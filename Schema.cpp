#include "Schema.h"
#include "ExtendedLink.h"
#include "Concept.h"
//#include "ReferencePartDeclaration.h"
//#include "RoleType.h"
//#include "ArcroleType.h"
#include "SimpleTypeDeclaration.h"
#include "SimpleLink.h"
#include "ComplexTypeDeclaration.h"
#include "SimpleTypeDeclaration.h"

namespace xbrlcapi
{

	struct Schema::Impl
	{
		Impl() {}
		bool isElementFormQualified()
		{
			//if (! getDataRootElement().getAttribute("elementFormDefault").equals("qualified")) return false;
			//return true;
			return false;
		}

		std::list<SimpleLink> getImports()
		{
			//String query = "#roots#[@parentIndex='" + this.getIndex() + "' and @type='org.xbrlapi.impl.SimpleLinkImpl' and */xsd:import]";
			//return getStore().<SimpleLink>queryForXMLResources(query);
			return std::list<SimpleLink>();
		}

		std::list<Schema> getImporters()
		{
			//String query = "for $root in #roots#[@type='"+SimpleLinkImpl.class.getName()+"'] where $root/xbrlapi:data/xsd:import/@namespace='" + getSchema().getTargetNamespace() + "' order by $root/xbrlapi:data/xsd:import/@namespace ascending return $root";
			//List<Schema> result = new Vector<Schema>();
			//List<SimpleLink> links = this.getStore().queryForXMLResources(query);
			//for (SimpleLink link: links) {
			//	try {
			//		result.add((Schema) link.getTarget());
			//	} catch (ClassCastException e) {
			//		throw new XBRLException("The schema import points illegally to a non-schema fragment.", e);
			//	}
			//}
			//return result;
			return std::list<Schema>();
		}    


		std::list<SimpleLink> getIncludes()
		{
			//String query = "#roots#[@parentIndex='" + this.getIndex() + "' and @type='org.xbrlapi.impl.SimpleLinkImpl' and */xsd:include]";
			//return getStore().<SimpleLink>queryForXMLResources(query);
			return std::list<SimpleLink>();
		}

		std::list<ExtendedLink> getExtendedLinks()
		{
			//List<Linkbase> linkbases = getStore().<Linkbase>getChildFragments(LinkbaseImpl.class,getIndex());
			//logger.debug("The schema contains " + linkbases.size() + " linkbases.");
			//List<ExtendedLink> links = new Vector<ExtendedLink>();
			//for (Linkbase linkbase: linkbases) {
			//	links.addAll(getStore().<ExtendedLink>getChildFragments(ExtendedLinkImpl.class,linkbase.getIndex()));
			//}
			//return links;
			return std::list<ExtendedLink>();
		}

		std::list<Concept> getOtherElementDeclarations()
		{
			//return this.<Concept>getChildren("org.xbrlapi.impl.ElementDeclarationImpl");
			return std::list<Concept>();
		}
		std::list<Concept> getConcepts()
		{
			//return this.<Concept>getChildren("Concept");
			return std::list<Concept>();
		}

		long getConceptCount()
		{
			//String query = "for $root in #roots#[@parentIndex='" + this.getIndex() + "' and @type='"+ ConceptImpl.class.getName() +"'] return $root";
			//return this.getStore().queryCount(query);
			return long();
		}

		Concept getConceptByName(const std::string& name)
		{
			//String query = "#roots#[@type='org.xbrlapi.impl.ConceptImpl' and @parentIndex='" + getIndex() + "' and "+ Constants.XBRLAPIPrefix+ ":" + "data/*/@name='" + name + "']";
			//List<Concept> concepts = getStore().<Concept>queryForXMLResources(query);
			//if (concepts.size() == 0) return null;
			//if (concepts.size() > 1) throw new XBRLException("The concept name is not unique to the schema.");
			//return concepts.get(0);
			return Concept();
		}
		std::list<Concept> getConceptsByType(const std::string& Namespace, const std::string& localName)
		{
			//List<Concept> matches = new Vector<Concept>();
			//List<Concept> concepts = getConcepts();
			//for (Concept concept: concepts) {
			//	if (concept.getTypeNamespace().equals(namespace) && 
			//		concept.getTypeLocalname().equals(localName)) {
			//			matches.add(concept);
			//	}
			//}
			//return matches;
			return std::list<Concept>();
		}

		std::list<Concept> getConceptsBySubstitutionGroup(const std::string& Namespace, const std::string& localname)
		{
			//Vector<Concept> matches = new Vector<Concept>();
			//List<Concept> concepts = getConcepts();
			//for (Concept concept: concepts) {
			//	if (concept.getSubstitutionGroupNamespace().equals(namespace) && 
			//		concept.getSubstitutionGroupLocalname().equals(localname)) {
			//			matches.add(concept);
			//	}
			//}
			//return matches;
			return std::list<Concept>();
		}

		//ReferencePartDeclaration getReferencePartDeclaration(const std::string& name)
		//{
		//	//for (int i=0; i<getReferencePartDeclarations().size(); i++) {
		//	//	if (getReferencePartDeclarations().get(i).getLocalname().equals(name))
		//	//		return getReferencePartDeclarations().get(i);
		//	//}
		//	//return null;
		//	return ReferencePartDeclaration();
		//}

		//std::list<ReferencePartDeclaration> getReferencePartDeclarations()
		//{
		//	//return this.getChildren("ReferencePartDeclaration");
		//	return std::list<ReferencePartDeclaration>();
		//}
		//std::list<RoleType> getRoleTypes()
		//{
		//	//return this.<RoleType>getChildren("RoleType");
		//	return std::list<RoleType>();
		//}
		//std::list<ArcroleType> getArcroleTypes()
		//{
		//	//return this.<ArcroleType>getChildren("ArcroleType");
		//	return std::list<ArcroleType>();
		//}
		std::list<ComplexTypeDeclaration> getGlobalComplexTypes()
		{
			//return getStore().<ComplexTypeDeclaration>getChildFragments(ComplexTypeDeclarationImpl.class,getIndex());
			return std::list<ComplexTypeDeclaration>();
		}
		std::list<SimpleTypeDeclaration> getGlobalSimpleTypes()
		{
			//return getStore().<SimpleTypeDeclaration>getChildFragments(SimpleTypeDeclarationImpl.class,getIndex());
			return std::list<SimpleTypeDeclaration>();
		}

		template<typename T> T getGlobalDeclaration(const std::string& name)
		{
			//return getStore().<SimpleTypeDeclaration>getChildFragments(SimpleTypeDeclarationImpl.class,getIndex());
			return T();
		}

	};

	Schema::Schema() {}
	Schema::~Schema() {} 

	Schema::Schema(const Schema& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Schema& Schema::operator=(const Schema& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Schema::Schema(Schema&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Schema& Schema::operator=(Schema&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Schema::operator==(const Schema& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Schema::operator!=(const Schema& rhs)
	{
		return !this->operator==(rhs);
	}
	bool Schema::isElementFormQualified()
	{
		return pImpl->isElementFormQualified();
	}

	std::list<SimpleLink>  Schema::getImports()
	{
		return pImpl->getImports();
	}

	std::list<Schema>  Schema::getImporters()
	{
		return pImpl->getImporters();
	}

	std::list<SimpleLink>  Schema::getIncludes()
	{
		return pImpl->getIncludes();
	}

	std::list<ExtendedLink>  Schema::getExtendedLinks()
	{
		return pImpl->getExtendedLinks();
	}

	std::list<Concept>  Schema::getOtherElementDeclarations()
	{
		return pImpl->getOtherElementDeclarations();
	}

	std::list<Concept>  Schema::getConcepts()
	{
		return pImpl->getConcepts();
	}

	long Schema::getConceptCount()
	{
		return pImpl->getConceptCount();
	}

	Concept Schema::getConceptByName(const std::string& name)
	{
		return pImpl->getConceptByName(name);
	}

	std::list<Concept>  Schema::getConceptsByType(const std::string& Namespace, const std::string& localName)
	{
		return pImpl->getConceptsByType(Namespace, localName);
	}

	std::list<Concept>  Schema::getConceptsBySubstitutionGroup(const std::string& Namespace, const std::string& localname)
	{
		return pImpl->getConceptsBySubstitutionGroup(Namespace, localname);
	}

	//ReferencePartDeclaration Schema::getReferencePartDeclaration(const std::string& name)
	//{
	//return pImpl->
	//}

	//std::list<ReferencePartDeclaration>  Schema::getReferencePartDeclarations()
	//{
	//	return pImpl->getReferencePartDeclarations();
	//}

	//std::list<RoleType>  Schema::getRoleTypes()
	//{
	//	return pImpl->getRoleTypes();
	//}

	//std::list<ArcroleType>  Schema::getArcroleTypes()
	//{
	//	return pImpl->getArcroleTypes();
	//}

	std::list<ComplexTypeDeclaration>  Schema::getGlobalComplexTypes()
	{
		return pImpl->getGlobalComplexTypes();
	}

	std::list<SimpleTypeDeclaration>  Schema::getGlobalSimpleTypes()
	{
		return pImpl->getGlobalSimpleTypes();
	}

	template<typename T>  T Schema::getGlobalDeclaration(const std::string& name)
	{
		return pImpl->getGlobalDeclaration(name);
	}
}