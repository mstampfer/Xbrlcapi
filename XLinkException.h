#include <exception>
#include <log4cpp/Category.hh>

namespace xbrlcapi
{
	class XLinkException : public std::exception 
	{
	private:
		std::string reason;
		log4cpp::Category &logger;
		std::exception cause;

	public:
		XLinkException() : exception(),
			logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{}

		XLinkException(const std::exception e) : exception(), 
			logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			reason = e.what();
			throw XLinkException(reason);
		}

		XLinkException(const std::string& reason) : 
			std::exception(), 
			reason(reason), 
			logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			logger.error("XBRLAPI Exception: " + reason);
		}

		XLinkException(const std::string& reason, const exception& cause) : 
			std::exception(reason.c_str()), 
			reason(reason), 
			logger(log4cpp::Category::getInstance( std::string("log_sub1") ))
		{
			logger.error("XBRLAPI Exception: " + reason);
			throw cause;
		}

		//void printStackTrace()
		//{
		//	printStackTrace(System.err);
		//	if (getCause() != null)
		//	{
		//		System.err.print("Caused by: ");
		//		this.cause.printStackTrace(System.err);
		//	}
		//}

		//void printStackTrace(const PrintStream& s)
		//{
		//	super.printStackTrace(s);
		//	if (getCause() != null)
		//	{
		//		s.print("Caused by: ");
		//		this.cause.printStackTrace(s);
		//	}
		//}

		//void printStackTrace(const PrintWriter& s)
		//{
		//	super.printStackTrace(s);
		//	if (getCause() != null)
		//	{
		//		s.print("Caused by: ");
		//		this.cause.printStackTrace(s);
		//	}
		//}

		std::string getMessage()
		{
			std::string s("\nCaused by: ");
			return s = + cause.what();
		}
	};
}

