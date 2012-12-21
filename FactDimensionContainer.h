
#include "Stdafx.h"
#pragma once
#include "Logger.h"


#include "Fragment.h"
#include <string>
#include <vector>

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	struct FactDimensionContainer : public Fragment {

		/**
		* Get the id attribute value of the container
		* @return the value of the id attribute for the unit or context.
		* @throws XBRLException if the id attribute is missing.
		*/
		virtual std::string getId();

		/**
		* @return the list of items in the instance that reference this context.
		* The list is empty if no facts in the instance reference this context.
		* @throws XBRLException
		*/
		template <typename I>
		std::vector<I> getReferencingItems();
		private:
Logger logger;
};
}

