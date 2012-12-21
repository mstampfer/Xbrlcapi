#include "stdafx.h"
#include <string>
#include "MD5SignerImpl.h"

namespace xbrlcapi
{

	std::string MD5SignerImpl::MD5(const std::string& content) 
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


	std::string MD5SignerImpl::getSignature(const std::vector<std::string>& lines) 
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



	/**
	* @see java.lang.Object#hashCode()
	*/

	//int MD5SignerImpl::hashCode() 
	//{
	//	//return 1;
	//}

	/**
	* @see java.lang.Object#equals(java.lang.Object)
	*/

	/*		bool MD5SignerImpl::equals(Object obj) 
	{
	if (this == obj)
	return true;
	if (obj == null)
	return false;
	if (getClass() != obj.getClass())
	return false;
	return true;
	}  */  
}