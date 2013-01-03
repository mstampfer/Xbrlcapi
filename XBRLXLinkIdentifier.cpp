#pragma once
#include "XBRLXLinkIdentifier.h"
#include <xercesc/sax/AttributeList.hpp>
#include "XLinkException.h"
#include "XBRLException.h"
#include "XBRLXLinkHandler.h"
#include <xercesc/sax/AttributeList.hpp>
#include "ContentHandler.h"
#include "XLinkProcessor.h"

namespace xbrlcapi
{
	struct XBRLXLinkIdentifier::Impl : public BaseIdentifier
	{

		Impl() {}

		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler)
		{}

		XLinkProcessor getXLinkProcessor()
		{
			return getLoader().getXlinkProcessor();
		}

		std::shared_ptr<XLinkHandler> getXLinkHandler()
		{
			return getLoader().getXlinkProcessor().getXLinkHandler();
		}

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{

			// Set the Element state information in the XBRL XLink handler.
			//try
			{
				std::shared_ptr<XLinkHandler> xlinkHandler = getXLinkHandler();
				std::shared_ptr<XBRLXLinkHandler> handler(dynamic_cast<XBRLXLinkHandler*>(xlinkHandler.get()));
				handler->setElementState(getElementState());
				/*			} catch (ClassCastException e)
				{
				throw XBRLException("The XBRLXLinkIdentifier MUST use an XBRLXLinkHandler when parsing " + getContentHandler().getURI(),e);
				}*/

				// Pass control through to the XLink processor to detect XLink structures
				try
				{
					getXLinkProcessor().startElement(namespaceURI,lName,qName,attrs);
				} 
				catch (XLinkException e)
				{
					throw XBRLException("XLink processing of the start of an element failed when parsing " + 
						getContentHandler().getURI().toString(),e.getMessage());
				}

			}
		}
	};

	XBRLXLinkIdentifier::XBRLXLinkIdentifier() {}
	XBRLXLinkIdentifier::XBRLXLinkIdentifier(const ContentHandler& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	XBRLXLinkIdentifier::~XBRLXLinkIdentifier() {} 

	XBRLXLinkIdentifier::XBRLXLinkIdentifier(const XBRLXLinkIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XBRLXLinkIdentifier& XBRLXLinkIdentifier::operator=(const XBRLXLinkIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XBRLXLinkIdentifier::XBRLXLinkIdentifier(XBRLXLinkIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XBRLXLinkIdentifier& XBRLXLinkIdentifier::operator=(XBRLXLinkIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XBRLXLinkIdentifier::operator==(const XBRLXLinkIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XBRLXLinkIdentifier::operator!=(const XBRLXLinkIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	void XBRLXLinkIdentifier::startElement(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}
}