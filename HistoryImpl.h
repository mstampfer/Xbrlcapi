#include "History.h"
#include "Logger.h"
#include <string>
#include <unordered_set>
#include <Poco/URI.h>
#include "History.h"

namespace xbrlcapi
{
	struct History::Impl 
	{
		Logger logger;
		Impl() {}
		void addRecord(const Poco::URI& uri, const std::string& identifier)
		{
			logger.root.debug(uri.toString() + " has identifier: " + identifier);
		}
		std::string getIdentifier(const Poco::URI& uri)
		{
			return "";
		}    

		std::unordered_set<Poco::URI> getURIs()
		{
			return std::unordered_set<Poco::URI>();
		}
	};
	History::History() {}
	History::~History() {} 
	History::History(History&& rhs) 
	{ 
		p = std::move(rhs.p); 
	}

	History& History::operator=(History&& rhs)
	{
		if (p != rhs.p)
			p = std::move(rhs.p);
		return *this;
	}

	bool History::operator==(const History& rhs)
	{
		return (p == rhs.p);
	}

	bool History::operator!=(const History& rhs)
	{
		return !this->operator==(rhs);
	}

}
