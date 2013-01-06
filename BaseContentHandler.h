#pragma once
#include "PimplImpl.h"
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <list>
#include <Poco/URI.h>

/**
* SAX content handler used in construction of an XBRL 
* Discoverable Taxonomy Set (DTS).
* The content handler is responsible for building up the XBRL
* XML fragments as they are parsed and then passing them over
* to the underlying data representation for storage.
* 
* The content handler needs to be supplied with a variety of helpers
* to assist with data storage and XLink processing. These are 
* supplied by the loader.
*/
namespace xbrlcapi
{
	class Identifier;
	class ElementState;
	class Loader;
	class BaseContentHandler : public xercesc::DefaultHandler
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		BaseContentHandler();
		/**
		* @param loader The DTS loader that is using this content handler.
		* @param uri The URI of the document being parsed.
		* @throws XBRLException if any of the parameters are null.
		*/
		BaseContentHandler(const Loader& loader, const Poco::URI& uri);
		~BaseContentHandler();
		BaseContentHandler(const BaseContentHandler& rhs);
		BaseContentHandler& operator=(const BaseContentHandler& rhs);
		BaseContentHandler(BaseContentHandler&& rhs);
		BaseContentHandler& operator=(BaseContentHandler&& rhs);
		bool operator==(const BaseContentHandler& rhs);
		bool operator!=(const BaseContentHandler& rhs);

		/**
		* @see org.xbrlapi.sax.ContentHandler#getLoader()
		*/
		Loader getLoader();

		/**
		* @see org.xbrlapi.sax.ContentHandler#setLoader(Loader)
		*/
		void setLoader(const Loader& loader);

		/**
		* @see org.xbrlapi.sax.ContentHandler#getURI()
		*/
		Poco::URI getURI();

		/**
		* @see org.xbrlapi.sax.ContentHandler#setURI(URI)
		*/
		void setURI(const Poco::URI& uri);


		/**
		* @param state The element state
		*/
		void setElementState(const ElementState& state);

		/**
		* @return the state for the element currently being parsed.
		*/
		ElementState getElementState();


		/**
		* @see ContentHandler#getIdentifiers()
		*/
		std::list<std::shared_ptr<Identifier>> getIdentifiers();

		/**
		* @see org.xbrlapi.sax.ContentHandler#error(SAXParseException)
		*/
		void error(const xercesc::SAXParseException& exception) override;

		/**
		* @see org.xbrlapi.sax.ContentHandler#fatalError(SAXParseException)
		*/
		void fatalError(const xercesc::SAXParseException& exception) override;

		/**
		* @see org.xbrlapi.sax.ContentHandler#warning(SAXParseException)
		*/
		void warning(const xercesc::SAXParseException& exception) override;
	};
}
