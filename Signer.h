#pragma once
#include <string>
#include <vector>
#include "PimplImpl.h"

namespace xbrlcapi
{
	class Signer // extends Serializable 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Signer();
		~Signer();
		Signer(const Signer& rhs);
		Signer& operator=(const Signer& rhs);
		Signer(Signer&& rhs);
		Signer& operator=(Signer&& rhs);
		bool operator==(const Signer& rhs);
		bool operator!=(const Signer& rhs);
		/**
		* @param lines The list of all lines in the resource.
		* @return the signature given the resource content.
		*/
		std::string getSignature(std::vector<std::string> lines);
	};
}
