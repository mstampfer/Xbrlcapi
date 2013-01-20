#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{
	/* Identifies fragments in the XBRL 2.1 namespace.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/

	class XBRLIdentifier : public BaseIdentifier, public std::enable_shared_from_this<XBRLIdentifier> 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		XBRLIdentifier();
		~XBRLIdentifier();
		XBRLIdentifier(const XBRLIdentifier& rhs);
		XBRLIdentifier& operator=(const XBRLIdentifier& rhs);
		XBRLIdentifier(XBRLIdentifier&& rhs);
		XBRLIdentifier& operator=(XBRLIdentifier&& rhs);
		bool operator==(const XBRLIdentifier& rhs);
		bool operator!=(const XBRLIdentifier& rhs);
		std::weak_ptr<XBRLIdentifier> getPtr();
		void initialize();

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		XBRLIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);

		/**
		* Finds fragments in the XBRL 2.1 namespace and keeps
		* track of boolean state variables tracking whether the
		* parser is inside and XBRL instance and whether the current
		* element can be a tuple in an XBRL instance.
		* 
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(const std::string&,const std::string&,const std::string&,const xercesc::Attributes&)
		*/
		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs);

		/**
		* Set the boolean state variables based upon whether the next 
		* element can be a tuple in an XBRL instance and whether the
		* parser is within an XBRL instance and whether the parser is
		* within a reference resource.
		* 
		* @see Identifier#endElement(const XMLCh*, const XMLCh*, const XMLCh*, const xercesc::Attributes&)
		*/
		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs);    
	};
}
