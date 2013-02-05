#include "XlinkDocumentation.h"

namespace xbrlcapi
{
	struct XlinkDocumentation::Impl 
	{
		Impl() {}
		std::string getValue()
		{

			//return this.getDataRootElement().getTextContent().trim();
			return std::string();
		}

	};

	XlinkDocumentation::XlinkDocumentation() {}
	XlinkDocumentation::~XlinkDocumentation() {} 

	XlinkDocumentation::XlinkDocumentation(const XlinkDocumentation& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XlinkDocumentation& XlinkDocumentation::operator=(const XlinkDocumentation& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XlinkDocumentation::XlinkDocumentation(XlinkDocumentation&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XlinkDocumentation& XlinkDocumentation::operator=(XlinkDocumentation&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XlinkDocumentation::operator==(const XlinkDocumentation& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XlinkDocumentation::operator!=(const XlinkDocumentation& rhs)
	{
		return !this->operator==(rhs);
	}

		std::string XlinkDocumentation::getValue()
		{
			return pImpl->getValue();
		}

}