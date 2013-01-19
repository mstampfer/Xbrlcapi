#pragma once
#include "PimplImpl.h"
/**
* Classes implementing this interface support analysis of
* persisted relationship information in a data store.  This 
* can be much more efficient than direct analysis of the 
* network information based upon the original data.
* @author Geoff Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{

	class Analyser
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Analyser();
		~Analyser();
		Analyser(const Analyser& rhs);
		Analyser& operator=(const Analyser& rhs);
		Analyser(Analyser&& rhs);
		Analyser& operator=(Analyser&& rhs);
		bool operator==(const Analyser& rhs);
		bool operator!=(const Analyser& rhs);
		operator bool();


		///**
		//* @param document The document URI.
		//* @return true if all of the relationships expressed by
		//* the arcs in the document have been persisted in the data store
		//* and false otherwise.
		//* @throws XBRLException
		//*/
		//virtual boolean hasAllRelationships(URI document);

		///**
		//* @return a list of all extended link roles for persisted relationships.
		//* @throws XBRLException
		//*/
		//virtual Set<String> getLinkRoles();

		///**
		//* @return a list of all arcroles for persisted relationships.
		//* @throws XBRLException
		//*/
		//virtual Set<String> getArcroles();

		///**
		//* @param arcrole the constraining arcrole value.
		//* @return a list of all link roles for extended links that 
		//* contain arcs defining persisted relationships with the
		//* given arcrole.
		//* @throws XBRLException
		//*/
		//virtual Set<String> getLinkRoles(String arcrole);        

		///**
		//* @param linkRole the constraining link role value.
		//* @return a list of all arcroles for persisted relationships defined
		//* in extended links with the given link role.
		//* @throws XBRLException
		//*/
		//virtual Set<String> getArcroles(String linkRole);    

		///**
		//* @param linkRole The link role for the extended links that
		//* are allowed to contain the arcs defining the active relationships
		//* to be returned.
		//* @param arcroles The list of arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any one of the specified arcroles and that are in networks
		//* with the given link role.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationships(String linkRole, Set<String> arcroles);

		///**
		//* @param arcroles The list of arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any one of the specified arcroles.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationships(Set<String> arcroles);

		///**
		//* @return A list of all relationships in the data store that are
		//* accepted by the analyser's relationship filtration rules.  Note that
		//* this can tend to overwhelm available physical resources when the data
		//* store is of significant size.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getAllRelationships();

		///**
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* the specified arcrole.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationships(String arcrole);

		///**
		//* @param linkRole The link role constraining the set of
		//* returned active relationships.
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* the specified arcrole and that have the specified link role.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationships(String linkRole, String arcrole);

		///**
		//* @param sourceIndex The index of the fragment to get relationships from.
		//* @param linkRole The link role constraining the set of
		//* returned active relationships.
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A sorted set of all active relationships that involve 
		//* the specified arcrole and that have the specified link role
		//* and that run from the specified source fragment, ordered by the arc order
		//* attribute value.  The arcrole and link role is ignored if it is null.
		//* @throws XBRLException
		//*/
		//virtual SortedSet<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, String arcrole);

		///**
		//* @param targetIndex The index of the fragment to get relationships to.
		//* @param linkRole The link role constraining the set of
		//* returned active relationships.
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A sorted set of all active relationships that involve 
		//* the specified arcrole and that have the specified link role
		//* and that run to the specified target fragment.  The relationships
		//* are sorted by the order attributes on the arcs expressing them.
		//* The arcrole and link role is ignored if it is null.
		//* @throws XBRLException
		//*/
		//virtual SortedSet<Relationship> getRelationshipsTo(String targetIndex, String linkRole, String arcrole);


		///**
		//* @param sourceIndex The index of the fragment to get relationships from.
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* the specified arcrole and that run from the specified source fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsFrom(String sourceIndex, String arcrole);

		///**
		//* @param targetIndex The index of the fragment to get relationships to.
		//* @param arcrole The arcrole used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* the specified arcrole and that run to the specified target fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsTo(String targetIndex, String arcrole);

		///**
		//* @param sourceIndex The index of the fragment to get relationships from.
		//* @param linkRole The link role constraining the set of
		//* returned active relationships.
		//* @param arcroles The arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any of the specified arcroles and that have the specified link role
		//* and that run from the specified source fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsFrom(String sourceIndex, String linkRole, Set<String> arcroles);

		///**
		//* @param targetIndex The index of the fragment to get relationships to.
		//* @param linkRole The link role constraining the set of
		//* returned active relationships.
		//* @param arcroles The arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any of the specified arcroles and that have the specified link role
		//* and that run to the specified target fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsTo(String targetIndex, String linkRole, Set<String> arcroles);


		///**
		//* @param sourceIndex The index of the fragment to get relationships from.
		//* @param arcroles The arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any of the specified arcroles and that run from the specified source fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsFrom(String sourceIndex, Set<String> arcroles);

		///**
		//* @param targetIndex The index of the fragment to get relationships to.
		//* @param arcroles The arcroles used to select the
		//* returned list of active relationships that have been
		//* persisted in the data store.
		//* @return A list of all active relationships that involve 
		//* any of the specified arcroles and that run to the specified target fragment.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationshipsTo(String targetIndex, Set<String> arcroles);

		///**
		//* @param linkRole The link role of the network.
		//* @param arcrole The arcrole of the network.
		//* @return the relationships that run from root fragments in the 
		//* network with the specified link role and arcrole.  If the arcrole or
		//* link role is null it is ignored.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRootRelationships(String linkRole, String arcrole);

		///**
		//* @param <F> The fragment type
		//* @param linkRole The link role URI
		//* @param arcrole The arcrole URI
		//* @return the list of fragments that are roots of networks with the given
		//* link role and arcrole.
		//* @throws XBRLException
		//*/
		//virtual <F extends Fragment> Set<F> getRoots(String linkRole, String arcrole);    

		///**
		//* @param linkRole The link role defining the network
		//* @param arcrole The arcrole defining the network
		//* @return the set of indices of the root fragments in the network.
		//* If the arcrole or link role is null it is ignored.
		//* @throws XBRLException
		//*/
		//virtual Set<String> getRootIndices(String linkRole, String arcrole);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @return a list of active relationships to labels from the 
		//* fragment identified by the specified index.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationships(String sourceIndex);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param language The XML language code identifying the language of the label.
		//* @return a list of active relationships to labels from the 
		//* fragment identified by the specified index and with the specified language.
		//* The list is empty if no relationships match the specified selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByLanguage(String sourceIndex, String language);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param languages The list of XML language code identifying the language of the label,
		//* in order of preference with the first value being the most preferred.
		//* A null value in the list implies that the full set of labels that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to labels that match the selection criteria.
		//* The list is empty if no relationships match the specified selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByLanguages(String sourceIndex, List<String> languages);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param role A required resource role for the labels.
		//* @return a list of active relationships to labels that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByRole(String sourceIndex, String role);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param roles A list of resource roles for the labels in order of preference with the 
		//* first role in the list being the most preferred XLink role attribute value.
		//* A null value in the list implies that the full set of labels that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to labels that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> roles);    

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param language The XML language code identifying the language of the label.
		//* @param role A required resource role for the labels.
		//* @return a list of active relationships to labels that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByLanguageAndRole(String sourceIndex, String language, String role);

		///**
		//* @param sourceIndex The index of the fragment to get the labels for.
		//* @param languages The list of XML language code identifying the language of the label,
		//* in order of preference with the first value being the most preferred.
		//* A null value in the list implies that the full set of labels that match the 
		//* other criteria will be selected.
		//* @param roles A list of resource roles for the labels in order of preference with the 
		//* first role in the list being the most preferred XLink role attribute value.
		//* A null value in the list implies that the full set of labels that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to labels that match the selection criteria.  Note that
		//* label language preferences get precedence over label role preferences.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getLabelRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @return a list of active relationships to references from the 
		//* fragment identified by the specified index.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationships(String sourceIndex);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param language The XML language code identifying the language of the reference.
		//* @return a list of active relationships to references from the 
		//* fragment identified by the specified index and with the specified language.
		//* The list is empty if no relationships match the specified selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByLanguage(String sourceIndex, String language);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param languages The list of XML language code identifying the language of the reference,
		//* in order of preference with the first value being the most preferred.
		//* A null value in the list implies that the full set of references that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to references that match the selection criteria.
		//* The list is empty if no relationships match the specified selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByLanguages(String sourceIndex, List<String> languages);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param role A required resource role for the references.
		//* @return a list of active relationships to references that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByRole(String sourceIndex, String role);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param roles A list of resource roles for the references in order of preference with the 
		//* first role in the list being the most preferred XLink role attribute value.
		//* A null value in the list implies that the full set of references that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to references that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> roles);    

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param language The XML language code identifying the language of the reference.
		//* @param role A required resource role for the references.
		//* @return a list of active relationships to references that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByLanguageAndRole(String sourceIndex, String language, String role);

		///**
		//* @param sourceIndex The index of the fragment to get the references for.
		//* @param languages The list of XML language code identifying the language of the reference,
		//* in order of preference with the first value being the most preferred.
		//* A null value in the list implies that the full set of references that match the 
		//* other criteria will be selected.
		//* @param roles A list of resource roles for the references in order of preference with the 
		//* first role in the list being the most preferred XLink role attribute value.
		//* A null value in the list implies that the full set of references that match the 
		//* other criteria will be selected.
		//* @return a list of active relationships to references that match the selection criteria.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getReferenceRelationshipsByRoles(String sourceIndex, List<String> languages, List<String> roles);    

		///**
		//* @param sourceIndex The source index to match.
		//* @param targetIndex The target index to match.
		//* @param linkRole The link role to match.
		//* @param arcrole The arcrole to match.
		//* @return a list of persisted relationships matching the specified
		//* criteria.  The arcrole and linkrole are ignored if they are equal to null.
		//* @throws XBRLException
		//*/
		//virtual List<Relationship> getRelationships(String sourceIndex, String targetIndex, String linkRole, String arcrole);

	};
}