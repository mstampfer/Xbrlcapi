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
	struct XBRLXLinkIdentifier::Impl 
	{
		std::weak_ptr<XBRLXLinkIdentifier> outer;
		std::shared_ptr<ContentHandler> contentHandler;

		Impl() {}

		Impl(const std::shared_ptr<ContentHandler>& contentHandler) : contentHandler(contentHandler)
		{
		}

		XLinkProcessor getXLinkProcessor()
		{
			return contentHandler->getLoader()->getXlinkProcessor();
		}

		XLinkHandler getXLinkHandler()
		{
			return contentHandler->getLoader()->getXlinkProcessor().getXLinkHandler();
		}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{

			// Set the Element state information in the XBRL XLink handler.
			//try
			{
				XLinkHandler xlinkHandler = getXLinkHandler();
				xlinkHandler.setElementState(contentHandler->getElementState());
				/*			} catch (ClassCastException e)
				{
				throw XBRLException("The XBRLXLinkIdentifier MUST use an XLinkHandler when parsing " + getContentHandler().getURI(),e);
				}*/

				// Pass control through to the XLink processor to detect XLink structures
				try
				{
					getXLinkProcessor().startElement(namespaceURI,lName,qName,attrs);
				} 
				catch (XLinkException e)
				{
					throw XBRLException("XLink processing of the start of an element failed when parsing " + 
						contentHandler->getURI().toString(),e.getMessage());
				}

			}
		}
		void setOuter(const std::weak_ptr<XBRLXLinkIdentifier>& xbrlXLinkIdentifier)
		{
			outer = std::weak_ptr<XBRLXLinkIdentifier>(xbrlXLinkIdentifier);
		}
	};

	XBRLXLinkIdentifier::XBRLXLinkIdentifier() {}
	XBRLXLinkIdentifier::XBRLXLinkIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
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
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}

	std::weak_ptr<XBRLXLinkIdentifier> XBRLXLinkIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void XBRLXLinkIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}

}