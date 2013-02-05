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
		bool isLink( const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName, 
			const xercesc::Attributes& attrs); 

		/**
		* Get the href from the custom link
		*/
		const XMLCh* getHref(const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs); 

		/**
		* Get the simple link role equivalent if it exists
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @return the role or null if it does not exist
		* @throws XLinkException
		*/
		const XMLCh* getRole(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs); 

		/**
		* Get the simple link arcrole equivalent if it exists
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @return the arcrole or null if it does not exist
		* @throws XLinkException
		*/
		const XMLCh* getArcrole(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs); 

		/**
		* Get the simple link title attribute equivalent if it exists
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @return the title or null if it does not exist
		* @throws XLinkException
		*/
		const XMLCh* getTitle(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs); 

		/**
		* Get the simple link show equivalent if it exists
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @return the show or null if it does not exist
		* @throws XLinkException
		*/
		const XMLCh* getShow(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs); 

		/**
		* Get the simple link actuate equivalent if it exists
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @return the actuate or null if it does not exist
		* @throws XLinkException
		*/
		const XMLCh* getActuate(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs); 
	};
}

