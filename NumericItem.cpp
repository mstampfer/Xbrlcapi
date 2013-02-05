#include "NumericItem.h"
#include "Unit.h"


namespace xbrlcapi
{
	struct NumericItem::Impl 
	{
		Impl() {}

		Unit getUnit()
		{
			//std::string query = "for $root in #roots#[@uri='"+this.getURI()+"' and @type='"+UnitImpl.class.getName()+"' and xbrlapi:data/xbrli:unit/@id='"+this.getUnitId()+"'] return $root";
			//List<Unit> units = getStore().<Unit>queryForXMLResources(query);
			//if (units.size() == 1) return units.get(0);
			//throw new XBRLException("There is not a unique matching context with ID "+this.getUnitId()+" for this fact in instance " + this.getURI());
			return Unit();
		}

		std::string getUnitId()
		{
			//Element root = getDataRootElement();
			//if (root.hasAttribute("unitRef")) {
			//	return root.getAttribute("unitRef");
			//}
			//throw new XBRLException("The unit reference is missing on numeric item " + this.getIndex());
			return std::string();
		}

		std::string getDecimals()
		{
			//if (getType().equals("org.xbrlapi.impl.FractionItemImpl")) return "INF";
			//if (hasDecimals()) return getDataRootElement().getAttribute("decimals").trim();
			//throw new XBRLException("The numeric item does not explicitly specify decimals");
			return std::string();
		}

		std::string getPrecision()
		{
			//if (getType().equals("org.xbrlapi.impl.FractionItemImpl")) return "INF";		
			//if (hasPrecision()) return getDataRootElement().getAttribute("precision").trim();
			//throw new XBRLException("The precision attribute is not explicitly specified.");
			return std::string();
		}

		bool hasPrecision()
		{
			//if (getType().equals("org.xbrlapi.impl.FractionItemImpl")) return true;		
			//if (getDataRootElement().hasAttribute("precision")) {
			//	return true;
			//}
			//return false;
			return false;
		}

		bool hasDecimals()
		{
			//if (getType().equals("org.xbrlapi.impl.FractionItemImpl")) return true;		
			//if (getDataRootElement().hasAttribute("decimals")) {
			//	return true;
			//}
			//return false;
			return false;
		}	
	};

	NumericItem::NumericItem() {}
	NumericItem::~NumericItem() {} 

	NumericItem::NumericItem(const NumericItem& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	NumericItem& NumericItem::operator=(const NumericItem& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	NumericItem::NumericItem(NumericItem&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	NumericItem& NumericItem::operator=(NumericItem&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool NumericItem::operator==(const NumericItem& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool NumericItem::operator!=(const NumericItem& rhs)
	{
		return !this->operator==(rhs);
	}

	Unit NumericItem::getUnit()
	{
		return pImpl->getUnit();
	}

	std::string NumericItem::getUnitId()
	{
		return pImpl->getUnitId();
	}

	std::string NumericItem::getDecimals()
	{
		return pImpl->getDecimals();
	}

	std::string NumericItem::getPrecision()
	{
		return pImpl->getPrecision();
	}

	bool NumericItem::hasPrecision()
	{
		return pImpl->hasPrecision();
	}

	bool NumericItem::hasDecimals()
	{
		return pImpl->hasDecimals();
	}	

}