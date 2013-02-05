#pragma once
#include "PimplImpl.h"
#include <string>
#include "Fragment.h"

namespace xbrlcapi
{
	struct Context;
	struct UsedOn : public Fragment 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		UsedOn();
		~UsedOn();
		UsedOn(const UsedOn& rhs);
		UsedOn& operator=(const UsedOn& rhs);
		UsedOn(UsedOn&& rhs);
		UsedOn& operator=(UsedOn&& rhs);
		bool operator==(const UsedOn& rhs);
		bool operator!=(const UsedOn& rhs);

		std::string getUsedOnNamespace(); 

		std::string getUsedOnLocalname();

		bool isUsedOn(const std::string& namespaceURI, const std::string& localname);

	};
}