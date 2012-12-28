#ifndef LOGGER_H
#define LOGGER_H
#include <memory>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>

namespace xbrlcapi
{
	class Logger 
	{
	public:
		log4cpp::Category& root;
		log4cpp::Category& sub1; 
		log4cpp::Category& sub2;
		static std::shared_ptr<Logger> instance();
		Logger& Logger::operator=(const Logger& rhs);

	private:
		static std::shared_ptr<Logger> pInstance;
		Logger ();
	};
}
#endif
