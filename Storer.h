#include "stdafx.h"
#pragma once
#include <Poco/URI.h>
#include <vector>
//#include "Arc.h"
//#include "Fragment.h"
//#include "Relationship.h"
//#include "Network.h"

/**
* Classes implementing this interface support persistance
* of relationship information in a data store.  This kind
* of persistence can reduce the query burden associated with
* network analysis.
* @author Geoff Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
class Networks;
class Network;
class Arcs;
class Arc;
class Relationship;
struct Fragment;
	struct Storer {

		/**
		* @param networks The set of networks from 
		* which all active relationships
		* will be persisted in the data store.
		* @see org.xbrlapi.Relationship
		* @throws XBRLException
		*/
		void storeRelationships(const Networks& networks);

		/**
		* @param documents The collection of Poco::URIs of the documents to store the relationships for.
		* Relationships are sought among the XLink arcs in the documents.
		* This is used by the discover to updated persisted relationships
		* in the data store.
		* @throws XBRLException
		*/
		void storeRelationships(const std::vector<Poco::URI>& documents);

		/**
		* @param document The Poco::URI of the document to store the relationships for.
		* Relationships are sought among the XLink arcs in the documents.
		* This is used by the discover to updated persisted relationships
		* in the data store.
		* @throws XBRLException
		*/
		void storeRelationships(const Poco::URI& document);    

		/**
		* @param network The network from which all 
		* relationships (active and inactive) will be 
		* persisted in the data store.
		* @see org.xbrlapi.Relationship
		* @throws XBRLException
		*/
		void storeRelationships(const Network& network);

		/**
		* When the relationship is persisted in the data store, any equivalent
		* relationship will be removed from the data store.  Equivalence is 
		* assessed on the basis of the relationship semantic key.
		* @see org.xbrlapi.Relationship#getSignature()
		* @param relationship The relationship that will be be persisted in the data store.
		* @throws XBRLException
		*/
		void storeRelationship(const Relationship& relationship);

		/**
		* Persist the relationship defined by the given fragments.
		* @param arc The relationship arc
		* @param source The relationship source fragment
		* @param target The relationship target fragment
		* @throws XBRLException
		*/
		void storeRelationship(const Arc& arc, const Fragment& source, const Fragment& target);


		/**
		* Stores all active relationships in the entire data store.
		* @throws XBRLException
		*/
		void storeAllRelationships();

		/**
		* Deletes the persisted relationships with the given link and arc role from 
		* the data store.  Note that this has no impact on the document fragments
		* stored in the data store.
		* @param linkRole The linkrole for relationships to be deleted.
		* @param arcrole The arcrole for relationships to be deleted.
		* @throws XBRLException
		*/
		void deleteRelationships(const Poco::URI& linkRole, const Poco::URI& arcrole);

		/**
		* Deletes the persisted relationships that are related to arcs 
		* in the specified document.
		* @param document The Poco::URI of the document to delete the persisted
		* relationships for.
		* @throws XBRLException
		*/
		void deleteRelationships(const Poco::URI& document);    

		/**
		* Deletes all persisted relationships in the data store.
		* @throws XBRLException
		*/
		void deleteRelationships();

		/**
		* Removes persisted prohibited or overridden relationships from a network.
		* @param linkRole The linkRole of the network to purge.
		* @param arcrole The arcrole of the network to purge.
		* @throws XBRLException
		*/
		void deleteInactiveRelationships(const std::string& linkRole, const std::string& arcrole);

		/**
		* Removes all persisted prohibited or overridden relationships from a network.
		* @throws XBRLException
		*/
		void deleteInactiveRelationships();

	};
}
