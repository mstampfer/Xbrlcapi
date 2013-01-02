#pragma once
#include "PimplImpl.h"
#include <xercesc/sax2/Attributes.hpp>
#include <string>


/**
* This class provides an example custom link
* recogniser tailored to the needs of the non-xlink
* links used by XBRL.

*/
namespace xbrlcapi
{
	class CustomLinkRecogniser
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		int get_it(); 
		CustomLinkRecogniser();
		~CustomLinkRecogniser();
		CustomLinkRecogniser(const CustomLinkRecogniser& rhs);
		CustomLinkRecogniser& operator=(const CustomLinkRecogniser& rhs);
		CustomLinkRecogniser(CustomLinkRecogniser&& rhs);
		CustomLinkRecogniser& operator=(CustomLinkRecogniser&& rhs);
		bool operator==(const CustomLinkRecogniser& rhs);
		bool operator!=(const CustomLinkRecogniser& rhs);

		/**
		* @see org.xbrlapi.xlink.CustomLinkRecogniser#isLink(String, String, String, Attributes)
		*/
		bool isLink( const std::string& namespaceURI,  
			const std::string& lName,  
			const std::string& qName, 
			const xercesc::Attributes& attrs); 

		/**
		* Get the href from the custom link
		*/
		std::string getHref( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs); 
	};
}

