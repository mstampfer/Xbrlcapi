#pragma once
#include "Storer.h"
#include <Poco/URI.h>
#include <vector>
//#include "Arc.h"
//#include "Fragment.h"
//#include "Relationship.h"
#include "Networks.h"
#include "Store.h"


namespace xbrlcapi
{
	class Networks;
	class Network;
	class Arcs;
	class Arc;
	class Relationship;
	struct Fragment;
	struct Storer::Impl
	{
		Store store;
		Impl() {}
		Impl(const Store& store) : 
			store(store)
		{}

		//void storeRelationships(const Networks& networks);

		void storeRelationships(const std::vector<Poco::URI>& documents)
		{
			//for (URI document: documents) {
			//	storeRelationships(document);
			//	this.getStore().sync();
			//}
		}

		//void storeRelationships(const Poco::URI& document);    

		void storeRelationships(const Networks& networks)
		{
			//for (const Network& network : networks) 
			//{
			//	storeRelationships(network);
			//}
		}

		//void storeRelationship(const Relationship& relationship);

		//void storeRelationship(const Arc& arc, const Fragment& source, const Fragment& target);


		//void storeAllRelationships();

		//void deleteRelationships(const Poco::URI& linkRole, const Poco::URI& arcrole);

		//void deleteRelationships(const Poco::URI& document);    

		//void deleteRelationships();

		//void deleteInactiveRelationships(const std::string& linkRole, const std::string& arcrole);

		//void deleteInactiveRelationships();
	};

	Storer::Storer() {}
	Storer::~Storer() {} 

	Storer::Storer(const Storer& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Storer& Storer::operator=(const Storer& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Storer::Storer(const Store& store) : pImpl(store)
	{}

	Storer::Storer(Storer&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Storer& Storer::operator=(Storer&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Storer::operator==(const Storer& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Storer::operator!=(const Storer& rhs)
	{
		return !this->operator==(rhs);
	}

	void Storer::storeRelationships(const Networks& networks)
	{
		pImpl->storeRelationships(networks);
	}

	void Storer::storeRelationships(const std::vector<Poco::URI>& documents)
	{
		pImpl->storeRelationships(documents);
	}

	//void storeRelationships(const Poco::URI& document);    

	//void storeRelationships(const Networks& network)
	//{

	//}

	//void storeRelationship(const Relationship& relationship);

	//void storeRelationship(const Arc& arc, const Fragment& source, const Fragment& target);

	//void storeAllRelationships();

	//void deleteRelationships(const Poco::URI& linkRole, const Poco::URI& arcrole);

	//void deleteRelationships(const Poco::URI& document);    

	//void deleteRelationships();

	//void deleteInactiveRelationships(const std::string& linkRole, const std::string& arcrole);

	//void deleteInactiveRelationships();
}
