#pragma once
#include <string>
#include <unordered_set>
#include <Poco/URI.h>
#include "HashFunctions.h"
#include "PimplImpl.h"

/**
* The interface defining the contract for 
* recording the history of documents being loaded
* into a data store by a loader.
* @author Geoff Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class History // extends Serializable 
	{
		struct Impl;
		Pimpl<Impl> p;
	public:
		int get_it(); 
		History();
		~History();
		History(History&& rhs);
		History& operator=(History&& rhs);
		bool operator==(const History& rhs);
		bool operator!=(const History& rhs);
		virtual void addRecord(const Poco::URI& uri, const std::string& identifier);
		virtual std::string getIdentifier(const Poco::URI& uri);
		virtual std::unordered_set<Poco::URI> getURIs();
	};
}