#pragma once
#include "Matcher.h"
#include "PimplImpl.h"

namespace xbrlcapi

{

	class DefaultMatcher : public Matcher //, Serializable 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		DefaultMatcher();
		~DefaultMatcher();
		DefaultMatcher(const DefaultMatcher& rhs);
		DefaultMatcher& operator=(const DefaultMatcher& rhs);
		DefaultMatcher(DefaultMatcher&& rhs);
		DefaultMatcher& operator=(DefaultMatcher&& rhs);
		bool operator==(const DefaultMatcher& rhs);
		bool operator!=(const DefaultMatcher& rhs);

		//		DefaultMatcher(const DefaultMatcher& rhs);

		//		DefaultMatcher& operator=(const DefaultMatcher& rhs);

		/**
		* @see Matcher#setSigner(Signer)
		*/
		void setSigner(const Signer& signer) override;

		/**
		* @see Matcher#getMatch(URI)
		*/
		//synchronized
		Poco::URI getMatch(const Poco::URI& uri) override;

		/**
		* @see Matcher#getSignature(URI)
		*/
		std::string getSignature(const Poco::URI& uri) override;

		/**
		* @see Matcher#delete(URI)
		*/
		Poco::URI del(const Poco::URI& uri) override;

		/**
		* @see org.xbrlapi.data.resource.Matcher#getAllMatchingURIs(java.net.URI)
		*/
		std::vector<Poco::URI> getAllMatchingURIs(const Poco::URI& uri) override;

		/**
		* @see org.xbrlapi.data.resource.Matcher#hasURI(java.net.URI)
		*/
		bool hasURI(const Poco::URI& uri) override;

		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();

	};
}