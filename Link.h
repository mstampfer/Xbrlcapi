
#include "Stdafx.h"
#pragma once

#include "Xlink.h"

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	/**
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/

	struct Link : public Xlink {

		/**
		* @return the link role (The xlink:role attribute value).
		* @throws XBRLException
		*/
		virtual std::string getLinkRole();

	};
}

