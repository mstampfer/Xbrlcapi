#include "CustomType.h"

namespace xbrlcapi
{
	struct CustomType::Impl 
	{
		Impl() {}

		std::string getCustomTypeId()
		{
			//Element root = getDataRootElement();
			//if (root.hasAttribute("id"))
			//	return root.getAttribute("id");
			//return null;
			return std::string();
		}

		std::string getCustomURI()
		{
			//if (getDataRootElement().hasAttribute("roleURI")) {
			//	return getDataRootElement().getAttribute("roleURI");
			//}
			//if (getDataRootElement().hasAttribute("arcroleURI")) {
			//	return getDataRootElement().getAttribute("arcroleURI");
			//}
			//throw new XBRLException("The value of the custom URI is not provided.");
			return std::string();
		}

		std::string  getDefinition()
		{
			//Element data = this.getDataRootElement();
			//NodeList definitions = data.getElementsByTagNameNS(Constants.XBRL21LinkNamespace.toString(),"definition");
			//if (definitions.getLength() == 0) return null;
			//Element definition = (Element) definitions.item(0);
			//return definition.getTextContent().trim();		 	
			return std::string();
		}

		bool isUsedCorrectly(Fragment fragment)
		{
			//List<UsedOn> usedOns = getUsedOns();
			//for (UsedOn usedOn: usedOns) {
			//	if (usedOn.isUsedOn(fragment.getNamespace(),fragment.getLocalname())) {
			//		return true;
			//	}
			//}
			//return false;
			return false;
		}

		bool isUsedOn(const std::string& Namespace, const std::string& localname)
		{
			//List<UsedOn> fragments = this.getUsedOns();
			//for(int i=0; i<fragments.size(); i++) {
			//	UsedOn usedOn = fragments.get(i);
			//	if (usedOn.isUsedOn(namespace,localname)) return true;
			//}
			//return false;
			return false;
		}

		std::list<UsedOn> getUsedOns()
		{
			//return this.<UsedOn>getChildren("org.xbrlapi.impl.UsedOnImpl");
			return std::list<UsedOn>();
		}  
	};

	CustomType::CustomType() {}
	CustomType::~CustomType() {} 

	CustomType::CustomType(const CustomType& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	CustomType& CustomType::operator=(const CustomType& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	CustomType::CustomType(CustomType&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	CustomType& CustomType::operator=(CustomType&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool CustomType::operator==(const CustomType& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool CustomType::operator!=(const CustomType& rhs)
	{
		return !this->operator==(rhs);
	}

	std::string CustomType::getCustomTypeId()
	{
		return pImpl->getCustomTypeId();
	}

	std::string CustomType::getCustomURI()
	{
		return pImpl->getCustomURI();
	}

	std::string  CustomType::getDefinition()
	{
		return pImpl->getDefinition();
	}

	bool CustomType::isUsedCorrectly(const Fragment& fragment)
	{
		return pImpl->isUsedCorrectly(fragment);
	}

	bool CustomType::isUsedOn(const std::string& Namespace, const std::string& localname)
	{
		return pImpl->isUsedOn(Namespace, localname);
	}

	std::list<UsedOn> CustomType::getUsedOns()
	{
		return pImpl->getUsedOns();
	}
}