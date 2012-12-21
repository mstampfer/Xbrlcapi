
#include "Stdafx.h"
#pragma once
#include "Logger.h"

#include <string>
#include "ArcEnd.h"

/**
 * @author Geoffrey Shuetrim (geoff@galexy.net)
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
	virtual std::string getResourceRole();
    
    

private:
Logger logger;
};
}
