#pragma once
#include "Signer.h"
#include <string>
#include <vector>


namespace xbrlcapi
{
	class MD5Signer : public Signer 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		MD5Signer();
		~MD5Signer();
		MD5Signer(MD5Signer& rhs);
		MD5Signer& operator=(MD5Signer& rhs);
		MD5Signer(MD5Signer&& rhs);
		MD5Signer& operator=(MD5Signer&& rhs);
		bool operator==(const MD5Signer& rhs);
		bool operator!=(const MD5Signer& rhs);

		std::string MD5(const std::string& content);
		std::string getSignature(const std::vector<std::string>& lines);
	};
}
