#include "Analyser.h"

namespace xbrlcapi
{

	struct Analyser::Impl 
	{
		Impl() {}

		operator bool() const
		{
			//if (exists(uriPath) && exists(path) && os) 
			//	return true;
			//else 
				return false;
		}
		//boolean hasAllRelationships(URI document);

		//Set<String> getLinkRoles();

		//Set<String> getArcroles();

		//Set<String> getLinkRoles(String arcrole);        

		//Set<String> getArcroles(String linkRole);    

		//List<Relationship> getRelationships(String linkRole, Set<String> arcroles);

		//List<Relationship> getRelationships(Set<String> arcroles);

		//List<Relationship> getAllRelationships();

		//List<Relationship> getRelationships(String arcrole);

		//List<Relationship> getRelationships(String linkRole, String arcrole);

		//SortedSet<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, String arcrole);

		//SortedSet<Relationship> getRelationshipsTo(String targetIndex, String linkRole, String arcrole);

		//List<Relationship> getRelationshipsFrom(String sourceIndex, String arcrole);

		//List<Relationship> getRelationshipsTo(String targetIndex, String arcrole);

		//List<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, Set<String> arcroles);

		//List<Relationship> getRelationshipsTo(String targetIndex, String linkRole, Set<String> arcroles);

		//List<Relationship> getRelationshipsFrom(String sourceIndex, Set<String> arcroles);

		//List<Relationship> getRelationshipsTo(String targetIndex, Set<String> arcroles);

		//List<Relationship> getRootRelationships(String linkRole, String arcrole);

		//<F extends Fragment> Set<F> getRoots(String linkRole, String arcrole);    

		//Set<String> getRootIndices(String linkRole, String arcrole);

		//List<Relationship> getLabelRelationships(String sourceIndex);

		//List<Relationship> getLabelRelationshipsByLanguage(String sourceIndex, String language);

		//List<Relationship> getLabelRelationshipsByLanguages(String sourceIndex, List<String> languages);

		//List<Relationship> getLabelRelationshipsByRole(String sourceIndex, String role);

		//List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> roles);    

		//List<Relationship> getLabelRelationshipsByLanguageAndRole(String sourceIndex, String language, String role);

		//List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles);

		//List<Relationship> getReferenceRelationships(String sourceIndex);

		//List<Relationship> getReferenceRelationshipsByLanguage(String sourceIndex, String language);

		//List<Relationship> getReferenceRelationshipsByLanguages(String sourceIndex, List<String> languages);

		//List<Relationship> getReferenceRelationshipsByRole(String sourceIndex, String role);

		//List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> roles);    

		//List<Relationship> getReferenceRelationshipsByLanguageAndRole(String sourceIndex, String language, String role);

		//List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles);    

		//List<Relationship> getRelationships(String sourceIndex, String targetIndex, String linkRole, String arcrole);

	};
	Analyser::Analyser() {}
	Analyser::~Analyser() {} 

	Analyser::Analyser(const Analyser& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Analyser& Analyser::operator=(const Analyser& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Analyser::Analyser(Analyser&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Analyser& Analyser::operator=(Analyser&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Analyser::operator==(const Analyser& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Analyser::operator!=(const Analyser& rhs)
	{
		return !this->operator==(rhs);
	}

	Analyser::operator bool()
	{
		return pImpl->operator bool();
	}
	//boolean hasAllRelationships(URI document)
	//{
	//return pImpl->();
	//}

	//Set<String> getLinkRoles()
	//{
	//return pImpl->();
	//}

	//Set<String> getArcroles()
	//{
	//return pImpl->();
	//}

	//Set<String> getLinkRoles(String arcrole)
	//{
	//return pImpl->();
	//}        

	//Set<String> getArcroles(String linkRole)
	//{
	//return pImpl->();
	//}    

	//List<Relationship> getRelationships(String linkRole, Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationships(Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getAllRelationships()
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationships(String arcrole)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationships(String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

	//SortedSet<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

	//SortedSet<Relationship> getRelationshipsTo(String targetIndex, String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsFrom(String sourceIndex, String arcrole)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsTo(String targetIndex, String arcrole)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsTo(String targetIndex, String linkRole, Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsFrom(String sourceIndex, Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRelationshipsTo(String targetIndex, Set<String> arcroles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getRootRelationships(String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

	//<F extends Fragment> Set<F> getRoots(String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}    

	//Set<String> getRootIndices(String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationships(String sourceIndex)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationshipsByLanguage(String sourceIndex, String language)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationshipsByLanguages(String sourceIndex, List<String> languages)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationshipsByRole(String sourceIndex, String role)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> roles)
	//{
	//return pImpl->();
	//}    

	//List<Relationship> getLabelRelationshipsByLanguageAndRole(String sourceIndex, String language, String role)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationships(String sourceIndex)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationshipsByLanguage(String sourceIndex, String language)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationshipsByLanguages(String sourceIndex, List<String> languages)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationshipsByRole(String sourceIndex, String role)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> roles)
	//{
	//return pImpl->();
	//}    

	//List<Relationship> getReferenceRelationshipsByLanguageAndRole(String sourceIndex, String language, String role)
	//{
	//return pImpl->();
	//}

	//List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles)
	//{
	//return pImpl->();
	//}    

	//List<Relationship> getRelationships(String sourceIndex, String targetIndex, String linkRole, String arcrole)
	//{
	//return pImpl->();
	//}

}