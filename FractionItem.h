#pragma once
#include "PimplImpl.h"
#include "ContextComponent.h"
#include <string>
#include "NumericItem.h"

namespace xbrlcapi
{
	class EntityResource;
	class Segment;

	class FractionItem : public NumericItem
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		FractionItem();
		~FractionItem();
		FractionItem(const FractionItem& rhs);
		FractionItem& operator=(const FractionItem& rhs);
		FractionItem(FractionItem&& rhs);
		FractionItem& operator=(FractionItem&& rhs);
		bool operator==(const FractionItem& rhs);
		bool operator!=(const FractionItem& rhs);

		double getNumerator();

		double getDenominator();

	};
}
