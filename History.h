#include "stdafx.h"
#pragma once
#include <string>
#include <unordered_set>
#include <Poco/URI.h>
#include "HashFunctions.h"

/**
* The interface defining the contract for 
* recording the history of documents being loaded
* into a data store by a loader.
* @author Geoff Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	struct History // extends Serializable 
	{

		virtual void addRecord(const Poco::URI& uri, const std::string& identifier) = 0;

		virtual std::string getIdentifier(const Poco::URI& uri) = 0;

		virtual std::unordered_set<Poco::URI> getURIs() = 0;

	};
}