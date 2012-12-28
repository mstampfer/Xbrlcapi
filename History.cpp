#include "History.h"

namespace xbrlcapi
{
	struct History::Impl 
	{
		Impl() {}

		void addRecord(const Poco::URI& uri, const std::string& identifier)
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug(uri.toString() + " has identifier: " + identifier);
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

	History::History(const History& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	History& History::operator=(const History& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	History::History(History&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	History& History::operator=(History&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool History::operator==(const History& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool History::operator!=(const History& rhs)
	{
		return !this->operator==(rhs);
	}

	void History::addRecord(const Poco::URI& uri, const std::string& identifier)
	{
		pImpl->addRecord(uri, identifier);
	}

	std::string History::getIdentifier(const Poco::URI& uri)
	{
		return pImpl->getIdentifier(uri);
	}

	std::unordered_set<Poco::URI> History::getURIs()
	{
		return pImpl->getURIs();
	}
}