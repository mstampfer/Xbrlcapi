#pragma once
#include "PimplImpl.h"
#include "Link.h"

namespace xbrlcapi
{
	class SimpleLink : public Link
	{
		struct Impl;
		Pimpl<Impl> pImpl;	
	public:
		SimpleLink();
		~SimpleLink();
		SimpleLink(const SimpleLink& rhs);
		SimpleLink& operator=(const SimpleLink& rhs);
		SimpleLink(SimpleLink&& rhs);
		SimpleLink& operator=(SimpleLink&& rhs);
		bool operator==(const SimpleLink& rhs);
		bool operator!=(const SimpleLink& rhs);

		/**
		* @see org.xbrlapi.SimpleLink#setTarget(URI)
		*/
		void setTarget(const Poco::URI& uri);

		/**
		* Get the link HREF attribute value, before any resolution.
		* @return the CacheURIImpl value of the XLink href attribute
		* @throws XBRLException
		* @see org.xbrlapi.SimpleLink#getHref()
		*/
		std::string getHref();

		/**
		* @see org.xbrlapi.SimpleLink#getAbsoluteHref()
		*/
		Poco::URI getAbsoluteHref();

		/**
		* @see org.xbrlapi.SimpleLink#getTargetDocumentURI()
		*/
		Poco::URI getTargetDocumentURI();;

		/**
		* Get the link arcrole attribute value, before any resolution.
		* @throws XBRLException
		* @see org.xbrlapi.SimpleLink#getArcrole()
		*/
		std::string getArcrole();

		/**
		* @return the single fragment referenced by the simple link.
		* @throws XBRLException if the simple link does not reference exactly one fragment.
		* @see org.xbrlapi.SimpleLink#getTarget()
		*/
		Fragment getTarget();
	};
}
