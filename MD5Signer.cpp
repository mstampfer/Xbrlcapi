#include "MD5Signer.h"

namespace xbrlcapi
{
	struct MD5Signer::Impl 
	{
		Impl() {}
		Impl& operator=(const Impl& rhs) // = default;
		{
			return *this;
		}
		std::string MD5(const std::string& content) 
		{
			//try 
			//{
			//	MessageDigest algorithm = MessageDigest.getInstance("MD5");
			//	algorithm.reset();
			//	algorithm.update(content.getBytes());
			//	byte messageDigest[] = algorithm.digest();
			//	StringBuffer hexString = new StringBuffer();

			//	for (int i=0;i<messageDigest.length;i++) 
			//	{
			//		std::string hex = Integer.toHexString(0xFF & messageDigest[i]);
			//		if (hex.length() == 1) 
			//		{
			//			hexString.append('0');
			//		}
			//		hexString.append(Integer.toHexString(0xFF & messageDigest[i]));
			//	}
			//	return hexString.toString();

			//}
			//catch (NoSuchAlgorithmException e) 
			//{
			//	logger.error("Your system is missing an MD5 algorithm.");
			//	return "corruptedSignature";
			//}
			return std::string("Not Implemented");
		}


		std::string getSignature(const std::vector<std::string>& lines) 
		{
			//std::string document = "";
			//double divisor = Math.ceil(lines.size() / 21);
			//for (int i=0; i<lines.size(); i++) 
			//{
			//	if (i < 40) 
			//	{
			//		document = document + lines.get(i);
			//	} else if (i > (lines.size()-10)) 
			//	{
			//		document = document + lines.get(i);
			//	} else 
			//	{
			//		double result = i/divisor;
			//		if ( result == Math.floor(result)) 
			//		{
			//			document = document + lines.get(i);
			//		}
			//	}
			//}
			//return (new Integer(lines.size())).toString() + MD5(document);
			return std::string("Not Implemented");
		}

	};
	MD5Signer::MD5Signer() {}
	MD5Signer::~MD5Signer() {} 

	MD5Signer::MD5Signer(MD5Signer& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	MD5Signer& MD5Signer::operator=(MD5Signer& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	MD5Signer::MD5Signer(MD5Signer&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}
	MD5Signer& MD5Signer::operator=(MD5Signer&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool MD5Signer::operator==(const MD5Signer& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool MD5Signer::operator!=(const MD5Signer& rhs)
	{
		return !this->operator==(rhs);
	}

}	

