#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"

namespace xbrlcapi
{
	class ContentHandler;
	class XBRLXLinkIdentifier : public BaseIdentifier, public std::enable_shared_from_this<XBRLXLinkIdentifier>
	{
	private:
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		XBRLXLinkIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);
		XBRLXLinkIdentifier();
		~XBRLXLinkIdentifier();
		XBRLXLinkIdentifier(const XBRLXLinkIdentifier& rhs);
		XBRLXLinkIdentifier& operator=(const XBRLXLinkIdentifier& rhs);
		XBRLXLinkIdentifier(XBRLXLinkIdentifier&& rhs);
		XBRLXLinkIdentifier& operator=(XBRLXLinkIdentifier&& rhs);
		bool operator==(const XBRLXLinkIdentifier& rhs);
		bool operator!=(const XBRLXLinkIdentifier& rhs);
		std::weak_ptr<XBRLXLinkIdentifier> getPtr();
		void initialize();


		/**
		* Passes responsibility along to the XLink handler via the XLink Processor.
		* 
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(String,String,String,Attributes)
		*/
		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes&  attrs) override;

	};
}