#include "Logger.h"		

namespace xbrlcapi
{
	Logger::Logger () : 
		root(log4cpp::Category::getRoot()), 
		sub1(log4cpp::Category::getInstance(std::string("sub1"))),
		sub2(log4cpp::Category::getInstance(std::string("sub1.sub2")))
	{ 
		std::string initFileName = "log4cpp.properties";
		try
		{
			log4cpp::PropertyConfigurator::configure( initFileName );
		}
		catch( log4cpp::ConfigureFailure &e )
		{
			std::cout 
				<< e.what() 
				<< " [log4cpp::ConfigureFailure catched] while reading " 
				<< initFileName 
				<< std::endl;
			exit(1);
		}
	}
}