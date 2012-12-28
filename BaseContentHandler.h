#pragma once
#include "PimplImpl.h"
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
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
	class BaseContentHandler : public xercesc::DefaultHandler
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		BaseContentHandler();
		~BaseContentHandler();
		BaseContentHandler(const BaseContentHandler& rhs);
		BaseContentHandler& operator=(const BaseContentHandler& rhs);
		BaseContentHandler(BaseContentHandler&& rhs);
		BaseContentHandler& operator=(BaseContentHandler&& rhs);
		bool operator==(const BaseContentHandler& rhs);
		bool operator!=(const BaseContentHandler& rhs);

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#getLoader()
		//     */
		//    public Loader getLoader();

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#setLoader(Loader)
		//     */
		//    public void setLoader(Loader loader) throws XBRLException;

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#getURI()
		//     */
		//    public URI getURI();

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#setURI(URI)
		//     */
		//    public void setURI(URI uri) throws XBRLException;


		//    /**
		//     * @param state The element state
		//     */
		//    public void setElementState(ElementState state);

		//    /**
		//     * @return the state for the element currently being parsed.
		//     */
		//    public ElementState getElementState();

		//    
		//    /**
		//     * @see ContentHandler#getIdentifiers()
		//     */
		//    public List<Identifier> getIdentifiers();

		//    /**
		//     * @param loader The DTS loader that is using this content handler.
		//     * @param uri The URI of the document being parsed.
		//     * @throws XBRLException if any of the parameters are null.
		//     */
		//	public BaseContentHandlerImpl(Loader loader, URI uri) throws XBRLException;

		//	/**
		//	 * @see org.xbrlapi.sax.ContentHandler#error(SAXParseException)
		//	 */
		//    public void error(SAXParseException exception) override;

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#fatalError(SAXParseException)
		//     */
		//	public void fatalError(SAXParseException exception) override;

		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#warning(SAXParseException)
		//     */
		//	public void warning(SAXParseException exception) override;
	};
}
