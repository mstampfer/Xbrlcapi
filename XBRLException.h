#pragma once
#include <exception>
#include <string>
#include "log4cpp/Category.hh"

namespace xbrlcapi
{
	class XBRLException : public std::exception 
	{
	private:
		std::string reason;
		log4cpp::Category &logger;

	public:
		XBRLException() : std::exception(), logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{}

		XBRLException(const XBRLException& rhs) : std::exception(), logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{}

		XBRLException(const std::string& reason) : std::exception(), reason(reason), logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			logger.error("XBRLAPI Exception: " + reason);
		}

		XBRLException(const std::string& reason, const std::string& cause) : std::exception(), reason(reason), logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			logger.error("XBRLAPI Exception: " + reason);
			logger.error("cause: " + cause);
		}

		XBRLException(const std::string& reason, const std::exception& cause) : std::exception(), reason(reason), logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			logger.error("XBRLAPI Exception: " + reason);
			throw cause;
		}

		std::string getMessage() const
		{
			return reason;
		}
	};

}