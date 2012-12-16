
#include "Stdafx.h"
#pragma once
#include "Logger.h"
#include <memory>
#include "XLinkProcessorImpl.h"
#include "XBRLXLinkHandlerImpl.h"

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
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class XLinkProcessor //extends Serializable 
	{
		std::unique_ptr<XLinkProcessorImpl> pimpl;
		XLinkProcessor& operator=(const XLinkProcessor& rhs);
		XLinkProcessor(XLinkProcessor& rhs);

	public:
		XLinkProcessor(){}
		XLinkProcessor(XBRLXLinkHandlerImpl& xlinkHandler) : 
							pimpl(new XLinkProcessorImpl(xlinkHandler)) {}
		XLinkProcessor(XBRLXLinkHandlerImpl& xlinkHandler, CustomLinkRecogniser& recogniser) : 
							pimpl(new XLinkProcessorImpl(xlinkHandler, recogniser)) {}
		XLinkProcessor& operator=(XLinkProcessor&& rhs)
		{
			if (pimpl != rhs.pimpl)
			{
				pimpl = std::move(rhs.pimpl);
			}
			return *this;
		}

		XLinkProcessor(XLinkProcessor&& rhs)
		{
				pimpl = std::move(rhs.pimpl);
		}

		//public final static Integer SIMPLE_LINK = new Integer(1);
		//public final static Integer EXTENDED_LINK = new Integer(2);
		//public final static Integer CUSTOM_LINK = new Integer(4);
		//public final static Integer RESOURCE = new Integer(8);
		//public final static Integer LOCATOR = new Integer(16);
		//public final static Integer ARC = new Integer(32);
		//public final static Integer TITLE = new Integer(64);
		//public final static Integer NOT_XLINK = new Integer(0);
		//
		//   /**
		//    * Set the custom link recogniser
		//    * @param customLinkRecogniser The class that indicates if a custom link
		//    * has been recognised.
		//    */
		//   public void setCustomLinkRecogniser(CustomLinkRecogniser customLinkRecogniser);

		//   /**
		//    * Respond to the start of an element, 
		//    * examining the element for XLink features
		//    * 
		//    * @param namespaceURI
		//    * @param lName
		//    * @param qName
		//    * @param attrs
		//    * @throws XLinkException
		//    */
		//public void startElement(
		//		 std::string namespaceURI, 
		//		 std::string lName, 
		//		 std::string qName, 
		//		Attributes attrs) throws XLinkException;
		//
		//   /**
		//    * Respond to the end of an element, examining the element 
		//    * for XLink features.
		//    * 
		//    * The SAX content handler that uses this XLink processor 
		//    * will need to keep track of the attributes of the element being ended
		//    * and will need to access these attributes from within the endElement
		//    * method in the content handler that then calls the end element
		//    * method in this XLink processor.
		//    * 
		//    * @see org.xbrlapi.xlink.ElementState#ElementState(ElementState, Attributes)
		//    * 
		//    * @param namespaceURI The namespace of the element being ended.
		//    * @param lName The local name of the element being ended.
		//    * @param qName The QName of the element being ended.
		//    * @param attrs The attributes of the element being ended.
		//    * @throws XLinkException
		//    */
		//public void endElement(
		//		 std::string namespaceURI, 
		//		 std::string lName, 
		//		 std::string qName,
		//		Attributes attrs) throws XLinkException;


		///**
		// * Handles the character content for a title element 
		// * @param buf
		// * @param offset
		// * @param len
		// * @throws XLinkException
		// */
		//public void titleCharacters(char buf[], int offset, int len) throws XLinkException;
		//  
		///**
		// * Provides access to the XLink handler being used by the XLink processor.
		// * @return the XLink handler being used by the XLink processor.
		// */
		//public XLinkHandler getXLinkHandler();

	private:
Logger logger;
};
}
