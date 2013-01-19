#pragma once
#include "PimplImpl.h"
#include "NonFragmentXML.h"
#include <string>
#include <Poco/URI.h>

namespace xbrlcapi
{
	class Stub : public NonFragmentXML
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Stub();
		Stub(const std::string& id, const Poco::URI& uri, const std::string& reason); 
		~Stub();
		Stub(const Stub& rhs);
		Stub& operator=(const Stub& rhs);
		Stub(Stub&& rhs);
		Stub& operator=(Stub&& rhs);
		bool operator==(const Stub& rhs);
		bool operator!=(const Stub& rhs);

		/**
		* @return the reason that the stub was stored.
		* @throws XBRLException
		*/
		std::string getReason();

		/**
		* @return the :URI of the affected document.
		* @throws XBRLException if the URI syntax is incorrect.
		*/
		virtual Poco::URI getResourceURI();		

		/**
		* @param uri the URI of the document described by the stub.
		* @throws XBRLException if the URI is null
		*/
		virtual void setResourceURI(const Poco::URI& uri);

		/**
		* @param reason The reason for the stub to exist.
		* @throws XBRLException if the reason is null
		*/
		virtual void setReason(std::string reason);		

	};
}