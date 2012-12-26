
#pragma once
#include "Loader.h"
#include "xercesc/sax2/ContentHandler.hpp"
#include "ContentHandlerImpl.h"
#include <memory>

namespace xbrlcapi
{
	class ContentHandler : public xercesc::ErrorHandler, public xercesc::ContentHandler 
	{

	private:
		std::unique_ptr<ContentHandlerImpl> pimpl;

	public:
		ContentHandler() : pimpl(new ContentHandlerImpl()) {}

		ContentHandler(const Poco::URI& uri, const Loader& loader) : pimpl(new ContentHandlerImpl()) 
		{

		}
		/**
		* @return the loader using this content handler.
		*/
		//Loader getLoader()
		//{
		//	return pimpl->getLoader();
		//}

		///**
		//* @param loader The loader that will use the content handler.
		//* @throws XBRLException if the loader is null
		//*/
		//void setLoader(const Loader& loader)
		//{
		//	pimpl->setLoader();
		//}

		///**
		//* @return the URI of the document being parsed.
		//*/
		//Poco::URI getURI()
		//{
		//	return pimpl->getURI();
		//}

		///**
		//* @param uri The URI of the document being parsed.
		//* @throws XBRLException if the URI is null.
		//*/
		//void setURI(const Poco::URI& uri)
		//{
		//	pimpl->setURI(const Poco::URI& uri);
		//}

		/**
		* @param state The element state
		*/
		//    void setElementState(const ElementState& state);

		/**
		* @return the state for the element currently being parsed.
		*/
		//    ElementState getElementState();

		/**
		* @return the list of fragment identifiers used by the content handler.
		*/
		//std::list<Identifier> getIdentifiers();

		/**
		* Handles SAX parsing exceptions.
		* @param exception The SAX parsing exception
		* @throws SAXException
		*/
		//    void error(SAXParseException exception);

		/**
		* Handles fatal SAX parsing exceptions.
		* @param exception The fatal SAX parsing exception.
		* @throws SAXException
		*/
		//   void fatalError(SAXParseException exception);

		/**
		* Handles warnings based on SAX parsing exceptions.
		* @param exception the SAX parsing exception triggering the warning.
		* @throws SAXException
		*/
		//   void warning(SAXParseException exception);

		void characters(const XMLCh *const ,const XMLSize_t)
		{
		}
		void endDocument(void)
		{
		}
		void endElement(const XMLCh *const ,const XMLCh *const ,const XMLCh *const )
		{
		}
		void ignorableWhitespace(const XMLCh *const ,const XMLSize_t)
		{
		}
		void processingInstruction(const XMLCh *const ,const XMLCh *const )
		{
		}
		void setDocumentLocator(const xercesc_3_1::Locator *const )
		{
		}
		void startDocument(void)
		{
		}
		void startElement(const XMLCh *const ,const XMLCh *const ,const XMLCh *const ,const xercesc_3_1::Attributes &)
		{
		}
		void startPrefixMapping(const XMLCh *const ,const XMLCh *const )
		{
		}
		void endPrefixMapping(const XMLCh *const )
		{
		}
		void skippedEntity(const XMLCh *const )
		{
		}
		void error(const xercesc::SAXParseException &exc)
		{
			pimpl->error(exc);
		}
		void fatalError(const xercesc::SAXParseException &exc)
		{
			pimpl->fatalError(exc);
		}
		void resetErrors()
		{
			pimpl->resetErrors();
		}
		void warning(const xercesc::SAXParseException &exc)
		{
			pimpl->warning(exc);
		}
	};
}