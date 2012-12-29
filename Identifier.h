#pragma once
#include <xercesc/sax2/Attributes.hpp>
#include <string>
#include "Loader.h"
#include "ContentHandler.h"
#include "ElementState.h"
/**
* The fragment identifier interface is implemented by any class that
* is to be used by a SAX content handler to identify fragments.
* 
* Usage of fragment identifiers requires:
* 1. implementing the initialisation of the identifier - including 
* setting up any properties specific to the type of identifier being 
* configured.
* 
* 2. implementing the adjustment of the state of the fragment identifier 
* whenever the end of an element is encountered by the SAX parser.
* 
* 3. implementing the fragment recognition code.
* 
* Fragment identifiers are instantiated and initialised by the 
* documentStart event handler in the SAX content handler.
* 
* Fragment identification and state updating is triggered within the
* elementStart event handler.
* 
* Fragment state updating is triggered within the elementEnd event handler.
* 
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{
	class Identifier 
	{
	public:
		/**
		* Determines if the element starts a new fragment and if so:
		* 
		* <ul>
		* <li>creates the fragment</li>
		* <li>sets the fragment index</li>
		* <li>stores any ID attributes on the fragment root in the fragment metadata
		* and in the element state object</li>
		* <li>adds the fragment to the loader</li>
		* </ul>
		* 
		* @param namespaceURI the namespace of the element
		* @param lName the local name of the element 
		* @param qName the qname of the element
		* @param attrs the attributes of the element
		* @throws XBRLException
		*/
		virtual void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs) = 0;

		/**
		* Updates the state of the fragment identifier 
		* when the end of an element is parsed.
		* @param namespaceURI the namespace of the element
		* @param lName the local name of the element 
		* @param qName the qname of the element
		* @param attrs the attributes of the element
		* @throws XBRLException
		*/
		virtual void endElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs) = 0;

		/**
		* Set up the fragment index, handle ID metadata for the fragment and
		* add it to the loader.
		* @param fragment The fragment that has been identified.
		* @param attrs The attributes of the root element of the fragment.
		* @throws XBRLException
		*/
		virtual void processFragment(const Fragment& fragment, const xercesc::Attributes& attrs) = 0;

		/**
		* @return the SAX content handler using 
		* the fragment identifier.
		*/
		ContentHandler getContentHandler();    

		/**
		* @param contentHandler The content handler using the fragment identifier.
		* @throws XBRLException if the content handler is null.
		*/
		virtual void setContentHandler(const ContentHandler& contentHandler) = 0;

		/**
		* @return the loader that is using the content handler
		* that uses this fragment identifier.
		*/
		virtual Loader getLoader() = 0;

		/**
		* @return the element state for the element currently being parsed.
		*/
		virtual ElementState getElementState() = 0;

	};
}
