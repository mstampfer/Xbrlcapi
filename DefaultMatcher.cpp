
#include "DefaultMatcher.h"

namespace xbrlcapi
{
	struct DefaultMatcher::Impl
	{
		Impl() {}

		Impl(const Impl& rhs)
		{
		}

		Impl& operator=(const Impl& rhs)
		{
			return *this;
		}

		void setSigner(const Signer& signer) 
		{
			return;
		}

		Poco::URI getMatch(const Poco::URI& uri) 
		{
			return uri;
		}

		std::string getSignature(const Poco::URI& uri) 
		{
			return uri.toString();
		}

		Poco::URI del(const Poco::URI& uri) 
		{
			return Poco::URI();
		}

		std::vector<Poco::URI> getAllMatchingURIs(const Poco::URI& uri) 
		{
			std::vector<Poco::URI> result;
			result.push_back(uri);
			return result;
		}

		bool hasURI(const Poco::URI& uri) 
		{
			return true;
		}


		int hashCode() 
		{
			return 1;
		}

		//bool equals(Object obj) 
		//{
		//	if (this == obj)
		//		return true;
		//	if (obj == null)
		//		return false;
		//	if (getClass() != obj.getClass())
		//		return false;
		//	return true;
		//}
	};

	DefaultMatcher::DefaultMatcher() {}
	DefaultMatcher::~DefaultMatcher() {} 

	DefaultMatcher::DefaultMatcher(const DefaultMatcher& rhs) : pImpl(rhs.pImpl)
	{ }

	DefaultMatcher& DefaultMatcher::operator=(const DefaultMatcher& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	DefaultMatcher::DefaultMatcher(DefaultMatcher&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	DefaultMatcher& DefaultMatcher::operator=(DefaultMatcher&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool DefaultMatcher::operator==(const DefaultMatcher& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool DefaultMatcher::operator!=(const DefaultMatcher& rhs)
	{
		return !this->operator==(rhs);
	}

	void DefaultMatcher::setSigner(const Signer& signer) 
	{
		pImpl->setSigner(signer);
	}
	Poco::URI DefaultMatcher::getMatch(const Poco::URI& uri) 
	{
		return pImpl->getMatch(uri);
	}
	std::string DefaultMatcher::getSignature(const Poco::URI& uri) 
	{
		return pImpl->getSignature(uri);
	}
	Poco::URI DefaultMatcher::del(const Poco::URI& uri) 
	{
		return pImpl->del(uri);
	}
	std::vector<Poco::URI> DefaultMatcher::getAllMatchingURIs(const Poco::URI& uri) 
	{
		return pImpl->getAllMatchingURIs(uri);
	}
	bool DefaultMatcher::hasURI(const Poco::URI& uri) 
	{
		return pImpl->hasURI(uri);
	}
	int DefaultMatcher::hashCode()
	{
		return pImpl->hashCode();
	}
}