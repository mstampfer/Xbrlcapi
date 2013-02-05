#pragma once
#include "PimplImpl.h"
#include <string>
#include "Item.h"

namespace xbrlcapi
{
	class NonNumericItem : public Item
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		NonNumericItem();
		~NonNumericItem();
		NonNumericItem(const NonNumericItem& rhs);
		NonNumericItem& operator=(const NonNumericItem& rhs);
		NonNumericItem(NonNumericItem&& rhs);
		NonNumericItem& operator=(NonNumericItem&& rhs);
		bool operator==(const NonNumericItem& rhs);
		bool operator!=(const NonNumericItem& rhs);

		/** 
		* @see org.xbrlapi.NonNumericItem#getValue()
		*/
		std::string getValue(); 

		/** 
		* @see org.xbrlapi.NonNumericItem#getXmlValue()
		*/
		std::string getXmlValue();

	};
}
