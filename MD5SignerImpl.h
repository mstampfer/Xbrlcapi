#include "stdafx.h"
#include "Signer.h"
#include <string>

namespace xbrlcapi
{
	class MD5SignerImpl : public Signer 
	{

	private:


	public:
		std::string MD5(const std::string& content);

		std::string getSignature(const std::vector<std::string>& lines);




		/**
		* @see java.lang.Object#hashCode()
		*/

		int hashCode();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/

		//		bool equals(Object obj);
	private:
Logger logger;
};
}
