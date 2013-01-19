#include "NonFragmentXML.h"

namespace xbrlcapi
{
	struct NonFragmentXML::Impl 
	{
		Impl() {}

		//void finalizeBuilder()
		//{
		//	setResource(getBuilder().getMetadata());
		//	setBuilder(NULL);
		//}
	};
	NonFragmentXML::NonFragmentXML() {}
	NonFragmentXML::~NonFragmentXML() {} 

	NonFragmentXML::NonFragmentXML(const NonFragmentXML& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	NonFragmentXML& NonFragmentXML::operator=(const NonFragmentXML& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	NonFragmentXML::NonFragmentXML(NonFragmentXML&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	NonFragmentXML& NonFragmentXML::operator=(NonFragmentXML&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool NonFragmentXML::operator==(const NonFragmentXML& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool NonFragmentXML::operator!=(const NonFragmentXML& rhs)
	{
		return !this->operator==(rhs);
	}

	//void NonFragmentXML::finalizeBuilder()
	// {
	// }

}