#pragma once
#include "PimplImpl.h"
#include <string>
#include <xercesc/sax2/Attributes.hpp>

/**
* The XLink processor is responsible for taking the input from a 
* SAX event and recognising any XLink events resulting from that
* SAX event and then passing the XLink event through to the 
* chosen XLinkHandler.  This makes the job of the XLink handler
* simplify down to one of Syntax recognition and XLink state tracking
* to ensure that only actual XLink are triggering XLink events.
* Note that the XLink specification is pretty persnicketty regarding
* nested XLink structures.
* 

*/
namespace xbrlcapi
{
	class XLinkHandler;
	class CustomLinkRecogniser;
	class XLinkProcessor //extends Serializable 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		XLinkProcessor();
		~XLinkProcessor();
		XLinkProcessor(const std::shared_ptr<XLinkHandler>& xlh, CustomLinkRecogniser& clr);
		XLinkProcessor(const XLinkProcessor& rhs);
		XLinkProcessor& operator=(const XLinkProcessor& rhs);
		XLinkProcessor(XLinkProcessor&& rhs);
		XLinkProcessor& operator=(XLinkProcessor&& rhs);
		bool operator==(const XLinkProcessor& rhs);
		bool operator!=(const XLinkProcessor& rhs);


		//
		//   /**
		//    * Set the custom link recogniser
		//    * @param customLinkRecogniser The class that indicates if a custom link
		//    * has been recognised.
		//    */
		//   public void setCustomLinkRecogniser(CustomLinkRecogniser customLinkRecogniser);

		/**
		* Respond to the start of an element, 
		* examining the element for XLink features
		* 
		* @param namespaceURI
		* @param lName
		* @param qName
		* @param attrs
		* @throws XLinkException
		*/
		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);

		/**
		* Respond to the end of an element, examining the element 
		* for XLink features.
		* 
		* The SAX content handler that uses this XLink processor 
		* will need to keep track of the attributes of the element being ended
		* and will need to access these attributes from within the endElement
		* method in the content handler that then calls the end element
		* method in this XLink processor.
		* 
		* @see org.xbrlapi.xlink.ElementState#ElementState(ElementState, Attributes)
		* 
		* @param namespaceURI The namespace of the element being ended.
		* @param lName The local name of the element being ended.
		* @param qName The QName of the element being ended.
		* @param attrs The attributes of the element being ended.
		* @throws XLinkException
		*/
		void endElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);

		///**
		// * Handles the character content for a title element 
		// * @param buf
		// * @param offset
		// * @param len
		// * @throws XLinkException
		// */
		//public void titleCharacters(char buf[], int offset, int len) throws XLinkException;

		/**
		* Provides access to the XLink handler being used by the XLink processor.
		* @return the XLink handler being used by the XLink processor.
		*/
		std::shared_ptr<XLinkHandler> getXLinkHandler();
	};
}
