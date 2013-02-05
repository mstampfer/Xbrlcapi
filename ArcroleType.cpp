#include "ArcroleType.h"


namespace xbrlcapi
{
	struct ArcroleType::Impl 
	{
		Impl() {}

		std::string getCyclesAllowed()
		{
			//Element root = getDataRootElement();
			//if (root.hasAttribute("cyclesAllowed")) {
			//	return root.getAttribute("cyclesAllowed");
			//}
			//throw new XBRLException("A cyclesAllowed attribute must be specified.");
			return std::string();
		}

		Networks getNetworks()
		{
			//			return getStore().getNetworks(this.getCustomURI());
			return Networks();
		}
	};
	ArcroleType::ArcroleType() {}
	ArcroleType::~ArcroleType() {} 

	ArcroleType::ArcroleType(const ArcroleType& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ArcroleType& ArcroleType::operator=(const ArcroleType& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ArcroleType::ArcroleType(ArcroleType&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ArcroleType& ArcroleType::operator=(ArcroleType&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ArcroleType::operator==(const ArcroleType& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ArcroleType::operator!=(const ArcroleType& rhs)
	{
		return !this->operator==(rhs);
	}

	Networks ArcroleType::getNetworks()
	{
		return pImpl->getNetworks();
	}
}