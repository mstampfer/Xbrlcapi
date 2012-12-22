

#pragma once
#include "Logger.h"

#include "Xlink.h"

/**

*/
namespace xbrlcapi
{
	/**
	
	*/

	struct Link : public Xlink {

		/**
		* @return the link role (The xlink:role attribute value).
		* @throws XBRLException
		*/
		virtual std::string getLinkRole();

	
private:
Logger logger;
};
}

