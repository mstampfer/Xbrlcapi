#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"

namespace xbrlcapi
{
	class ContentHandler;
	class XBRLXLinkIdentifier : public BaseIdentifier
	{
	private:
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		XBRLXLinkIdentifier(const ContentHandler& contentHandler);
		XBRLXLinkIdentifier();
		~XBRLXLinkIdentifier();
		XBRLXLinkIdentifier(const XBRLXLinkIdentifier& rhs);
		XBRLXLinkIdentifier& operator=(const XBRLXLinkIdentifier& rhs);
		XBRLXLinkIdentifier(XBRLXLinkIdentifier&& rhs);
		XBRLXLinkIdentifier& operator=(XBRLXLinkIdentifier&& rhs);
		bool operator==(const XBRLXLinkIdentifier& rhs);
		bool operator!=(const XBRLXLinkIdentifier& rhs);

		/**
		* Passes responsibility along to the XLink handler via the XLink Processor.
		* 
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(String,String,String,Attributes)
		*/
		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);
	};
}