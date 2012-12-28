#include "Signer.h"

namespace xbrlcapi
{
	struct Signer::Impl 
	{
		Impl() {}
		std::string getSignature(std::vector<std::string> lines);
		Impl& operator=(const Impl& rhs) // = default;
		{
			return *this;
		}
	};
	Signer::Signer() {}
	Signer::~Signer() {} 
	Signer::Signer(const Signer& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Signer& Signer::operator=(const Signer& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}
	Signer::Signer(Signer&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Signer& Signer::operator=(Signer&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Signer::operator==(const Signer& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Signer::operator!=(const Signer& rhs)
	{
		return !this->operator==(rhs);
	}

}	
