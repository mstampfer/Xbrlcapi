#include "stdafx.h"
#pragma once
#include "Matcher.h"

namespace xbrlcapi

{
	class DefaultMatcherImpl : public Matcher //, Serializable 

	{

		/**
		* The serial version UID.
		* @see 
		* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
		* for information about what changes will require the serial version UID to be
		* modified.
		*/
	private:
		static const long long serialVersionUID = -2009126809674227559L;

	public:
		DefaultMatcherImpl();

		DefaultMatcherImpl(const DefaultMatcherImpl& rhs);

		virtual ~DefaultMatcherImpl(){};
		
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

		/**
		* @see java.lang.Object#equals(java.lang.Object)  override;
		*/

	};
}