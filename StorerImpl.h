#include "stdafx.h"
#pragma once
#include "Storer.h"
#include <Poco/URI.h>
#include <set>
#include "Store.h"

/**
* @author Geoff Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class Networks;
	class Network;
	class Arcs;
	class Relationship;

	class StorerImpl : public Storer {

		/*protected:
		static Logger logger = Logger.getLogger(StorerImpl.class);  */ 

	private:
		Store store;
		/**
		* @return The data store in which the relationships are
		* to be persisted.
		* @throws XBRLException if the data store is null.
		*/
		Store getStore();

		/**
		* @param store The data store in which the relationships are
		* to be persisted.
		* @throws XBRLException if the data store is null.
		*/
		void StorerImpl::setStore(Store& store);

		/**
		* @param arc The arc to store relationships for.
		* @throws XBRLException
		*/
		void storeRelationships(const Arc& arc);

		void markActiveRelationships(std::string linkRole, const std::string& arcrole);


		/**
		* @param linkRole The network link role
		* @param arcrole The network arcrole
		* @return a map of sorted sets of equivalent relationships in the network.
		* @throws XBRLException
		*/
		std::unordered_map<std::string, std::set<Relationship>> getEquivalentRelationships(std::string linkRole, const std::string& arcrole, const std::string& sourceIndex, const std::string& targetIndex);;

	public:
		StorerImpl(Store& store);

		/**
		* @see org.xbrlapi.networks.Storer#storeRelationship(Relationship)
		*/

		void storeRelationship(const Relationship& relationship);


		/**
		* @see org.xbrlapi.networks.Storer#storeRelationship(Arc, Fragment, Fragment)
		*/

		void storeRelationship(const Arc& arc, const Fragment& source, const Fragment& target);


		/**
		* @see org.xbrlapi.networks.Storer#storeRelationships(org.xbrlapi.networks.Network)
		*/

		void storeRelationships(const Network& network);

		/**
		* @see org.xbrlapi.networks.Storer#storeRelationships(org.xbrlapi.networks.Networks)
		*/

		void storeRelationships(const Networks& networks);


		/**+++
		* @see org.xbrlapi.networks.Storer#storeAllRelationships()
		*/

		void storeAllRelationships();


		/**
		* @see Storer#deleteRelationships(Poco::URI, Poco::URI)
		*/

		void deleteRelationships(const Poco::URI& linkRole, const Poco::URI& arcrole);

		/**
		* @see Storer#deleteRelationships(Poco::URI)
		*/

		void deleteRelationships(const Poco::URI& document);


		/**
		* @see org.xbrlapi.networks.Storer#deleteRelationships()
		*/

		void deleteRelationships();


		/**
		* @see org.xbrlapi.networks.Storer#storeRelationships(Collection)
		*/

		void storeRelationships(const std::set<Poco::URI>& documents);


		/**
		* This implementation uses just 3 database queries for the document.
		* @see org.xbrlapi.networks.Storer#storeRelationships(URI)
		*/

		void storeRelationships(const Poco::URI& document);

		/**
		* @see Storer#deleteInactiveRelationships()
		*/

		void deleteInactiveRelationships();


		/**
		* @see Storer#deleteInactiveRelationships(const std::string&, const std::string&)
		*/

		void deleteInactiveRelationships(std::string linkRole, const std::string& arcrole);

		/**
		* @param linkRole The link role of the relationships to mark.
		* @param arcrole the arcrole  of the relationships to mark.
		* @throws XBRLException
		*/


	};
}