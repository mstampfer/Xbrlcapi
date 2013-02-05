#pragma once
#include "PimplImpl.h"
#include <string>
#include "Fact.h"

namespace xbrlcapi
{
	struct Context;
	struct Item : public Fact 
	{

		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Item();
		~Item();
		Item(const Item& rhs);
		Item& operator=(const Item& rhs);
		Item(Item&& rhs);
		Item& operator=(Item&& rhs);
		bool operator==(const Item& rhs);
		bool operator!=(const Item& rhs);
		/** 
		* Get the context for this item.
		* Presumes that there is at most one XBRL instance in each document in the data store.
		* @return the context fragment associated with this item
		* @throws XBRLException if the context reference is missing or the context is unavailable.
		*/
		Context getContext();

		/** 
		* @return the ID of the context referenced by this item.
		* @throws XBRLException if the context reference is missing.
		*/
		std::string getContextId();	
	};
}