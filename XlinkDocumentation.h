#pragma once
#include "PimplImpl.h"
#include <string>
#include "Fragment.h"

namespace xbrlcapi
{

	class XlinkDocumentation : public Fragment 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		XlinkDocumentation();
		~XlinkDocumentation();
		XlinkDocumentation(const XlinkDocumentation& rhs);
		XlinkDocumentation& operator=(const XlinkDocumentation& rhs);
		XlinkDocumentation(XlinkDocumentation&& rhs);
		XlinkDocumentation& operator=(XlinkDocumentation&& rhs);
		bool operator==(const XlinkDocumentation& rhs);
		bool operator!=(const XlinkDocumentation& rhs);

		/**
		* TODO Provide a set value method for Xlink documentation fragments.
		* Get the value of the documentation fragment.
		* @return the text content of the documentation with leading and trailing spaces trimmed.
		* @throws XBRLException.
		* @see org.xbrlapi.XlinkDocumentation#getValue()
		*/
		std::string getValue();
	};
}