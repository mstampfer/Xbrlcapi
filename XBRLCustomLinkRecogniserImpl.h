

#pragma once
#include "Logger.h"
#include <string>
#include <xercesc/sax2/Attributes.hpp>
#include "Constants.h"

/**
* This class provides an example custom link
* recogniser tailored to the needs of the non-xlink
* links used by XBRL.

*/
namespace xbrlcapi
{
	class XBRLCustomLinkRecogniserImpl
	{
	private:

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
	private:
		Logger logger;
	};
}

