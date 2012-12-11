
#include "Stdafx.h"
#pragma once
#include <string>
#include <xercesc/sax2/Attributes.hpp>
#include "Constants.h"

/**
* This class provides an example custom link
* recogniser tailored to the needs of the non-xlink
* links used by XBRL.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class XBRLCustomLinkRecogniserImpl
	{
	private:
		static const long long serialVersionUID = 5149996620311673778L;
		//		private static const Logger logger = Logger.getLogger(XBRLCustomLinkRecogniserImpl.class);

		/**
		* Constructor for the XBRL custom link recogniser
		*/
	public:

		/**
		* @see org.xbrlapi.xlink.CustomLinkRecogniser#isLink(String, String, String, Attributes)
		*/
		bool isLink( const std::string& namespaceURI,  
			const std::string& lName,  
			const std::string& qName, 
			const xercesc::Attributes& attrs) 
		{
			bool result = false;
			if (namespaceURI == XMLConstants::XMLSchemaNamespace &&
				((lName == "import") || (lName == "include")))
				result = true;
			return result;
		}

		/**
		* Get the href from the custom link
		*/
		//const std::string getHref( const std::string& namespaceURI, 
		//	const std::string& lName, 
		//	const std::string& qName,
		//	const xercesc::Attributes& attrs) 
		//{
		//	const XMLCh* const schemaLocation = L"schemaLocation";
		//	return attrs.getValue(schemaLocation);
		//}

	};
}

