#include "stdafx.h"
#pragma once
#include "Logger.h"
#include <string>
#include <Poco/URI.h>
#include "StubImpl.h"

namespace xbrlcapi
{
	class Stub 
	{
	private:
		std::unique_ptr<StubImpl> pimpl;

	public:

		Stub() : pimpl(new StubImpl()){}

		Stub(const std::string& id, const Poco::URI& uri, const std::string& reason) : 
			pimpl(new StubImpl(id, uri, reason)){}

		/**
		* @return the reason that the stub was stored.
		* @throws XBRLException
		*/
		std::string getReason()
		{
			return pimpl->getReason();
		}

		/**
		* @return the :URI of the affected document.
		* @throws XBRLException if the URI syntax is incorrect.
		*/
		virtual Poco::URI getResourceURI()		
		{
			return pimpl->getResourceURI();
		}

		/**
		* @param uri the URI of the document described by the stub.
		* @throws XBRLException if the URI is null
		*/
		virtual void setResourceURI(const Poco::URI& uri)		
		{
			return pimpl->setResourceURI(uri);
		}

		/**
		* @param reason The reason for the stub to exist.
		* @throws XBRLException if the reason is null
		*/
		virtual void setReason(std::string reason)		
		{
			return pimpl->setReason(reason);
		}

private:
Logger logger;
};
}