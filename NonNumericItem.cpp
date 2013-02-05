#include "NonNumericItem.h"
namespace xbrlcapi
{
	struct NonNumericItem::Impl 
	{
		Impl() {}

		std::string getValue() 
		{
			//if (this.isNil()) return null;
			//return getDataRootElement().getTextContent().trim();
			return std::string();
		}

		std::string getXmlValue()
		{
			//String value = this.getValue();
			//if (value == null) return value;
			//value.replaceAll("&nbsp;","&#160;");
			//value.replaceAll("&ndash;","&#8211;");
			//value.replaceAll("&lt;(.+)&gt;","<$1>");
			//return value;
			return std::string();
		}
	};

	NonNumericItem::NonNumericItem() {}
	NonNumericItem::~NonNumericItem() {} 

	NonNumericItem::NonNumericItem(const NonNumericItem& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	NonNumericItem& NonNumericItem::operator=(const NonNumericItem& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	NonNumericItem::NonNumericItem(NonNumericItem&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	NonNumericItem& NonNumericItem::operator=(NonNumericItem&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool NonNumericItem::operator==(const NonNumericItem& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool NonNumericItem::operator!=(const NonNumericItem& rhs)
	{
		return !this->operator==(rhs);
	}

	std::string NonNumericItem::getValue() 
	{
		return pImpl->getValue();

	}

	std::string NonNumericItem::getXmlValue()
	{
		return pImpl->getXmlValue();
	}

}
