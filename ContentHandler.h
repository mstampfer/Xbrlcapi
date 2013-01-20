#pragma once
#include "PimplImpl.h"
#include "BaseContentHandler.h"
#include <xercesc/sax/Locator.hpp>

/**
* SAX content handler used to parse a document into an XBRL API data store.
*
* The content handler is responsible for identifying
* XML fragments to be loaded into the data store,
* as they are parsed and then passing them over to
* the data loader for creation and storage.
*
* The content handler needs to be supplied with a variety
* of helpers to assist with data storage and XLink processing.
* These are supplied by the loader.
*
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class BaseURISAXResolver;
	class Loader;
	class ContentHandler : public BaseContentHandler, public std::enable_shared_from_this<ContentHandler>
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* Creates the content handler, starting out by
		* identifying the DTS structure that the content
		* handler is discovering.
		* @param loader The DTS loader that is using this content handler.
		* @param uri The URI of the document being parsed.
		* @throws XBRLException if any of the parameters
		* are null.
		*/
		ContentHandler::ContentHandler( std::shared_ptr<Loader>& loader, const Poco::URI& uri);

		/**
		* Creates the content handler, starting out by
		* identifying the data structure that the content
		* handler is discovering.
		* @param loader The data loader that is using this content handler.
		* @param uri The URI of the document being parsed.
		* @param xml The string representation of the XML document being parsed.
		* @throws XBRLException if any of the parameters
		* are null.
		*/
		//	ContentHandler(const Loader& loader, const Poco::URI& uri, const XMLCh* const xml);

		ContentHandler();
		~ContentHandler(); 
		ContentHandler(const ContentHandler& rhs);
		ContentHandler& operator=(const ContentHandler& rhs);
		ContentHandler(ContentHandler&& rhs);
		ContentHandler& operator=(ContentHandler&& rhs);
		bool operator==(const ContentHandler& rhs);
		bool operator!=(const ContentHandler& rhs);

		std::weak_ptr<ContentHandler> getPtr();

		/**
		* On starting to parse a document the Base URI resolver is
		* set up with the documents absolute URI.  The fragment identifiers
		* are also instantiated and initialised.
		*/
		void startDocument() override;

		/**
		* Sets the element state.
		* Increment the fragment children via the loader ????
		* Stash xsi:schemaLocation attribute URIs for discovery if required.
		* Identifies any new fragment.
		* Adds the fragment, if one is found, to the stack of fragments being built by the loader.
		* Update the map of defined namespaces.
		* Add the element to the current fragment.
		*
		* @see org.xml.sax.ContentHandler#startElement(std::string, std::string, std::string, Attributes)
		*/
		void startElement(
			const   XMLCh* const    namespaceURI,
			const   XMLCh* const    lName,
			const   XMLCh* const    qName,
			const	xercesc::Attributes&	attrs) override;

		/**
		* The end of an element triggers processing of an extended link
		* if we have reached the end of an extended link.
		* Otherwise, we step up to the parent element
		* unless the element that is ending did not ever become the current element.
		*/
		void endElement(
			const XMLCh* const namespaceURI,
			const XMLCh* const lName,
			const XMLCh* const qName) override;

		/**
		* Ignore ignorable whitespace
		*/
		void ignorableWhitespace(const XMLCh* const, const XMLSize_t) override;

		/**
		* Copy across processing instructions to the DTSImpl
		*/
		void processingInstruction(const XMLCh* const target, const XMLCh* const data) override;

		/**
		* Copy characters (trimming white space as required) to the DTSImpl.
		*/
		void characters(const XMLCh* const, const XMLSize_t) override;

		/**
		* The locator for a document is stored to facilitate resolution
		* of CacheURIImpl's relative to that location.
		*/
		void setDocumentLocator(const xercesc::Locator* const locator) override;

		std::shared_ptr<Loader> getLoader();

		void initialize();

	protected:

		/**
		* @return the base URI resolver for SAX parsing.
		*/
		BaseURISAXResolver getBaseURISAXResolver();

		/**
		* @param identifier The identifier to add to the list of
		* fragment identifiers used by the content handler.
		*/
		void addIdentifier(const std::shared_ptr<Identifier>& identifier);

		/**
		* @param index The index of the position at which
		* the new identifier is to be inserted in the list of
		* fragment identifiers.
		* @param identifier The identifier to add to the list of
		* fragment identifiers used by the content handler.
		*/
		//		void addIdentifier(int index, const Identifier& identifier);

		/**
		* @param index The index of the identifier to remove from the list of
		* fragment identifiers used by the content handler.
		*/
		void removeIdentifier(int index);
	};
}
