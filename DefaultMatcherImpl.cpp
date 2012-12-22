
#include "DefaultMatcherImpl.h"

namespace xbrlcapi
{
	DefaultMatcherImpl::DefaultMatcherImpl()
{}

	DefaultMatcherImpl::DefaultMatcherImpl(const DefaultMatcherImpl& rhs)
	{
	}

	DefaultMatcherImpl& DefaultMatcherImpl::operator=(const DefaultMatcherImpl& rhs)
	{
		return *this;
	}

	/**
	* @see Matcher#setSigner(Signer)
	*/
	void DefaultMatcherImpl::setSigner(const Signer& signer) 
	{
		return;
	}

	/**
	* @see Matcher#getMatch(URI)
	*/
	//synchronized
	Poco::URI DefaultMatcherImpl::getMatch(const Poco::URI& uri) 
	{
		return uri;
	}



	/**
	* @see Matcher#getSignature(URI)
	*/
	std::string DefaultMatcherImpl::getSignature(const Poco::URI& uri) 
	{
		return uri.toString();
	}

	/**
	* @see Matcher#delete(URI)
	*/
	Poco::URI DefaultMatcherImpl::del(const Poco::URI& uri) 
	{
		return Poco::URI();
	}

	/**
	* @see org.xbrlapi.data.resource.Matcher#getAllMatchingURIs(java.net.URI)
	*/
	std::vector<Poco::URI> DefaultMatcherImpl::getAllMatchingURIs(const Poco::URI& uri) 
	{
		std::vector<Poco::URI> result;
		result.push_back(uri);
		return result;
	}

	/**
	* @see org.xbrlapi.data.resource.Matcher#hasURI(java.net.URI)
	*/
	bool DefaultMatcherImpl::hasURI(const Poco::URI& uri) 
	{
		return true;
	}

	/**
	* @see java.lang.Object#hashCode()
	*/

	int DefaultMatcherImpl::hashCode() 
	{
		return 1;
	}

	/**
	* @see java.lang.Object#equals(java.lang.Object)
	*/

	//bool DefaultMatcherImpl::equals(Object obj) 
	//{
	//	if (this == obj)
	//		return true;
	//	if (obj == null)
	//		return false;
	//	if (getClass() != obj.getClass())
	//		return false;
	//	return true;
	//}
}