#include "stdafx.h"
#pragma once
#include "Logger.h"
#include "Cache.h"
#include "Signer.h"
#include "Matcher.h"

//#include "Signer.h"

namespace xbrlcapi
{

	/**
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/


	class BaseMatcherImpl : public Matcher 
	{
		/**
		* The serial version UID.
		* @see 
		* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
		* for information about what changes will require the serial version UID to be
		* modified.
		*/
	private:
//		static const 		Logger logger;
		/**
		* The cache implementation to be used by the matcher when accessing
		* resources.  If this is null, then no cache is used.
		*/
		Cache cache;
		Signer signer;

	protected:
		Cache getCache();

		void setCache(Cache& cache);

		Signer getSigner();

	protected:
		std::vector<std::string> getResourceContent(std::ifstream& file);

		std::vector<std::string> getResourceContent(const Poco::URI& uri);

		//int hashCode();

//		bool equals(Object obj); 

	public:
		void setSigner(const Signer& signer);

		/**
		* @param cache The resource cache to be used by the matcher when accessing
		* resources to determine their signature.
		* @param signature The object used to generate resource signatures.
		* @throws XBRLException if either parameter is null.
		*/
		BaseMatcherImpl(Cache& cache, const Signer& signature);

		/**
		* @see org.xbrlapi.data.resource.Matcher#getSignature(URI)
		*/
		//std::string getSignature(const Poco::URI& uri);
	private:
Logger logger;
};
}
