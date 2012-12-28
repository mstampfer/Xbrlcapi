#include "BaseContentHandler.h"
#include "Loader.h"
#include <list>
#include <Poco/URI.h>
#include "ElementState.h"
#include "Identifier.h"



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
* 

*/
namespace xbrlcapi
{

	struct BaseContentHandler::Impl : public xercesc::DefaultHandler
	{
		Impl() {}
		Impl(const Loader& loader, const Poco::URI& uri) : xercesc::DefaultHandler()
		{
			setURI(uri);
			setLoader(loader);		
		}
		/**
		* The DTS loader that uses this content handler 
		* to process discovered XML
		*/
		Loader loader;

		/**
		* Data required to track the element scheme XPointer 
		* expressions that can be used to identify XBRL fragments.
		*/
		ElementState state;

		/**
		* List of the fragment identifiers to use in parsing the document.
		* Load these in order of frequency of fragment occurrence for optimum performance.
		*/
		std::list<Identifier> identifiers;// = new LinkedList<Identifier>();

		/**
		* The URI of the document being parsed.  This is used to
		* recover the XML Schema model for the document if required.
		*/
		Poco::URI uri;


		/**
		* @see org.xbrlapi.sax.ContentHandler#getLoader()
		*/
		Loader getLoader() {
			return loader;
		}


		void setLoader(Loader loader) 
		{
			this->loader = loader;
		}
		//
		//    /**
		//     * The URI of the document being parsed.  This is used to
		//     * recover the XML Schema model for the document if required.
		//     */
		//    private URI uri = null;
		//
		Poco::URI getURI() 
		{
			return uri;
		}

		void setURI(const Poco::URI& uri)
		{
			this->uri = uri;
		}
		//    
		//    /**
		//     * Data required to track the element scheme XPointer 
		//     * expressions that can be used to identify XBRL fragments.
		//     */
		//    private ElementState state = null;

		void setElementState(const ElementState& state)
		{
			this->state = state;
		}

/*		ElementState getElementState() 
		{
			return state;
		}  */  
		//    
		//    /**
		//     * List of the fragment identifiers to use in parsing the document.
		//     * Load these in order of frequency of fragment occurrence for optimum performance.
		//     */
		//    private List<Identifier> identifiers = new LinkedList<Identifier>();
		//    
		std::list<Identifier> getIdentifiers() 
		{
			return identifiers;
		}    

		//    
		//	/**
		//	 * @see org.xbrlapi.sax.ContentHandler#error(SAXParseException)
		//	 */
		//	@Override
		//    public void error(SAXParseException exception) throws SAXException {
		///*        if (exception.getMessage().contains("Cannot find the declaration of element"))
		//            if (exception.getMessage().contains("'schema'") || exception.getMessage().contains(":schema'"))
		//                return;*/
		//        logger.error(":" + exception.getMessage() + ": on line number " + exception.getLineNumber());
		//	}
		//
		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#fatalError(SAXParseException)
		//     */
		//   @Override
		//	public void fatalError(SAXParseException exception) throws SAXException {
		//        logger.error(exception.getMessage() + ": on line number " + exception.getLineNumber());
		//	}
		//
		//    /**
		//     * @see org.xbrlapi.sax.ContentHandler#warning(SAXParseException)
		//     */
		//   @Override
		//	public void warning(SAXParseException exception) throws SAXException {
		//		logger.warn(exception + "  Carrying on with parsing without doing validation.");
		//	}
		//   
	};

	BaseContentHandler::BaseContentHandler() {}
	BaseContentHandler::~BaseContentHandler() {} 

	BaseContentHandler::BaseContentHandler(const BaseContentHandler& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	BaseContentHandler& BaseContentHandler::operator=(const BaseContentHandler& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	BaseContentHandler::BaseContentHandler(BaseContentHandler&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	BaseContentHandler& BaseContentHandler::operator=(BaseContentHandler&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool BaseContentHandler::operator==(const BaseContentHandler& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool BaseContentHandler::operator!=(const BaseContentHandler& rhs)
	{
		return !this->operator==(rhs);
	}

}
