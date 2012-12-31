

#pragma once

#include <string>
#include "ArcEnd.h"

/**

*/
namespace xbrlcapi
{
	struct Resource : public ArcEnd {

		/**
		* Get the value of the resource role (xlink:role attribute) for the resource.
		* @return the value of the resource role (xlink:role attribute) for the resource or 
		* null if none is specified.
		* @throws XBRLException.
		*/
		//virtual std::string getResourceRole();
	};
}
