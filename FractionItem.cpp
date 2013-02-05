#include "FractionItem.h"


namespace xbrlcapi
{
	struct FractionItem::Impl 
	{
		Impl() {}

		double getNumerator()
		{
			//Element data = getDataRootElement();
			//Node child = data.getFirstChild();
			//while (child.getNodeType() != Node.ELEMENT_NODE) {
			//	child = child.getNextSibling();
			//	if (child == null) throw new XBRLException("The fraction numerator is missing.");
			//}
			//return new Double(child.getTextContent().trim()).doubleValue();
			return 0.;
		}


		double getDenominator()
		{
			//Element data = getDataRootElement();
			//Node child = data.getFirstChild();
			//while (child.getNodeType() != Node.ELEMENT_NODE) {
			//	child = child.getNextSibling();
			//	if (child == null) throw new XBRLException("The fraction numerator is missing.");
			//}
			//child = child.getNextSibling();
			//if (child == null) throw new XBRLException("The fraction denominator is missing.");
			//while (child.getNodeType() != Node.ELEMENT_NODE) {
			//	child = child.getNextSibling();
			//	if (child == null) throw new XBRLException("The fraction denominator is missing.");
			//}
			//return new Double(child.getTextContent().trim()).doubleValue();
			return 0.;
		}
	};
	FractionItem::FractionItem() {}
	FractionItem::~FractionItem() {} 

	FractionItem::FractionItem(const FractionItem& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	FractionItem& FractionItem::operator=(const FractionItem& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	FractionItem::FractionItem(FractionItem&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	FractionItem& FractionItem::operator=(FractionItem&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool FractionItem::operator==(const FractionItem& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool FractionItem::operator!=(const FractionItem& rhs)
	{
		return !this->operator==(rhs);
	}

	double FractionItem::getNumerator()
	{
		return pImpl->getNumerator();
	}

	double FractionItem::getDenominator()
	{
		return pImpl->getDenominator();
	}

}