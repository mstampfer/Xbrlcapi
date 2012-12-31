#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{
	/* Identifies fragments in the XBRL 2.1 namespace.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/

	class XBRLIdentifier : public BaseIdentifier 
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

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		XBRLIdentifier(const ContentHandler& contentHandler);

		/**
		* Finds fragments in the XBRL 2.1 namespace and keeps
		* track of boolean state variables tracking whether the
		* parser is inside and XBRL instance and whether the current
		* element can be a tuple in an XBRL instance.
		* 
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(const std::string&,const std::string&,const std::string&,const xercesc::Attributes&)
		*/
		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);

		/**
		* Set the boolean state variables based upon whether the next 
		* element can be a tuple in an XBRL instance and whether the
		* parser is within an XBRL instance and whether the parser is
		* within a reference resource.
		* 
		* @see Identifier#endElement(const std::string&, const std::string&, const std::string&, const xercesc::Attributes&)
		*/
		void endElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);    
	};
}
