#pragma once
#include "PimplImpl.h"
#include <string>
#include "Item.h"


namespace xbrlcapi
{
	class Unit;

	class NumericItem : public Item
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		NumericItem();
		~NumericItem();
		NumericItem(const NumericItem& rhs);
		NumericItem& operator=(const NumericItem& rhs);
		NumericItem(NumericItem&& rhs);
		NumericItem& operator=(NumericItem&& rhs);
		bool operator==(const NumericItem& rhs);
		bool operator!=(const NumericItem& rhs);

		Unit getUnit();

		std::string getUnitId();

		/** 
		* Get the decimals attribute for this item.
		* @return the value of the decimals attribute
		* @throws XBRLException
		* @see org.xbrlapi.NumericItem#getDecimals()
		*/
		std::string getDecimals();

		/** 
		* Get the precision attribute for this item.
		* @return the value of the precision attribute
		* @throws XBRLException
		* @see org.xbrlapi.NumericItem#getPrecision()
		*/
		std::string getPrecision();

		/** 
		* Returns true if the fact has a precision attribute.
		* @return true if the fact has a precision attribute and false otherwise.
		* @throws XBRLException
		* @see org.xbrlapi.NumericItem#hasPrecision()
		*/
		bool hasPrecision();

		/** 
		* Returns true if the fact has a decimals attribute.
		* @return true if the fact has a decimals attribute and false otherwise.
		* @throws XBRLException
		* @see org.xbrlapi.NumericItem#hasDecimals()
		*/
		bool hasDecimals();
	};
}
