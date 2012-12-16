#include "stdafx.h"
#pragma once
#include "Logger.h"

#include <string>
#include <vector>

namespace xbrlcapi
{
	struct Signer // extends Serializable 
	{

		/**
		* @param lines The list of all lines in the resource.
		* @return the signature given the resource content.
		*/
		std::string getSignature(std::vector<std::string> lines);
		Signer& operator=(const Signer& rhs) // = default;
		{
			return *this;
		}


	private:
		Logger logger;
	};
}
