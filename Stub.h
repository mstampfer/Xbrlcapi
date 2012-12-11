#include "stdafx.h"
#pragma once
#include <string>
#include "Poco/URI.h"

namespace xbrlcapi
{
	struct Stub 
	{
		/**
		* @return the reason that the stub was stored.
		* @throws XBRLException
		*/
		virtual std::string getReason()= 0;

		/**
		* @return the :URI of the affected document.
		* @throws XBRLException if the URI syntax is incorrect.
		*/
		virtual Poco::URI getResourceURI()= 0;

		/**
		* @param uri the URI of the document described by the stub.
		* @throws XBRLException if the URI is null
		*/
		virtual void setResourceURI(const Poco::URI& uri)= 0;    

		/**
		* @param reason The reason for the stub to exist.
		* @throws XBRLException if the reason is null
		*/
		virtual void setReason(std::string reason)= 0;        
	};
}