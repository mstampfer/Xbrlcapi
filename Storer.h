#pragma once
#include "PimplImpl.h"
#include <Poco/URI.h>
#include <set>

namespace xbrlcapi
{
	class Store;
	class Relationship;
	class Arc;
	class Fragment;
	class Network;
	class Networks;

	class Storer
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Storer();
		~Storer();
		Storer(const Storer& rhs);
		Storer& operator=(const Storer& rhs);
		Storer(Storer&& rhs);
		Storer& operator=(Storer&& rhs);
		bool operator==(const Storer& rhs);
		bool operator!=(const Storer& rhs);
		Storer(const Store& store);

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

		void storeRelationships(const std::vector<Poco::URI>& documents);


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