#pragma once
#include "XMLImpl.h"

namespace xbrlcapi
{
	class NonFragmentXML : public XMLImpl  
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		NonFragmentXML();
		~NonFragmentXML();
		NonFragmentXML(const NonFragmentXML& rhs);
		NonFragmentXML& operator=(const NonFragmentXML& rhs);
		NonFragmentXML(NonFragmentXML&& rhs);
		NonFragmentXML& operator=(NonFragmentXML&& rhs);
		bool operator==(const NonFragmentXML& rhs);
		bool operator!=(const NonFragmentXML& rhs);
	};
}