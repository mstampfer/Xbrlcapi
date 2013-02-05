#pragma once
#include "PimplImpl.h"
#include <string>
#include "NumericItem.h"

namespace xbrlcapi
{
	class SimpleNumericItem : public NumericItem
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		SimpleNumericItem();
		~SimpleNumericItem();
		SimpleNumericItem(const SimpleNumericItem& rhs);
		SimpleNumericItem& operator=(const SimpleNumericItem& rhs);
		SimpleNumericItem(SimpleNumericItem&& rhs);
		SimpleNumericItem& operator=(SimpleNumericItem&& rhs);
		bool operator==(const SimpleNumericItem& rhs);
		bool operator!=(const SimpleNumericItem& rhs);

		std::string getValue(); 

		std::string getPrecisionAdjustedValue();

		std::string getInferredPrecision();

	};
}


