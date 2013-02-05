

#pragma once

#include "Xlink.h"

/**

*/
namespace xbrlcapi
{
	/**

	*/

	struct Link : public Xlink 
	{
		Link(){}
		/**
		* @return the link role (The xlink:role attribute value).
		* @throws XBRLException
		*/
		virtual std::string getLinkRole();
	};
}

