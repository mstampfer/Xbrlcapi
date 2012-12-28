#include "ContentHandler.h"
#include "Locator.h"
#include "Loader.h"
#include "XBRLXLinkHandlerImpl.h"
#include <xercesc/sax/SAXException.hpp>
#include "XBRLXLinkIdentifier.h"
#include "XBRLIdentifier.h"
#include "SchemaIdentifier.h"
#include "LanguageIdentifier.h"
#include "ReferencePartIdentifier.h"
#include "GenericDocumentRootIdentifier.h"

namespace xbrlcapi
{

	class ContentHandler::Impl :  BaseContentHandler 
	{
		Impl() {}

		Impl(const Loader& loader, const Poco::URI& uri) : BaseContentHandler(loader, uri)
		{}

		Impl(const Loader& loader, const Poco::URI& uri, const std::string& xml) : Impl(loader, uri)
		{
			setXML(xml);
		}

		void startDocument()
		{
			// Set up the base URI resolver for the content handler and the XLink handler.
			if (getURI() == null) 
			{
				throw xercesc::SAXException("The document URI must not be null when setting up the base URI resolver.");
			}
			setBaseURISAXResolver(new BaseURISAXResolverImpl(this->getURI()));
			getXLinkHandler().setBaseURISAXResolver(this->getBaseURISAXResolver());

			// Instantiate the fragment identifiers
			try 
			{
				addIdentifier(new XBRLXLinkIdentifier(this));
				addIdentifier(new SchemaIdentifier(this));
				addIdentifier(new XBRLIdentifier(this));
				addIdentifier(new LanguageIdentifier(this));
				addIdentifier(new ReferencePartIdentifier(this));
				addIdentifier(new GenericDocumentRootIdentifier(this));
			}
			catch (XBRLException e) 
			{
				throw new xercesc::SAXException("One of the fragment identifiers could not be instantiated.",e);
			}


		void startElement(
			const std::string& namespaceURI,
			const std::string& lName,
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{

		//	Loader loader = getLoader();

		//	// Update the information about the state of the current element (tracks ancestor attributes)
		//	setElementState(new ElementState(getElementState(),new AttributesImpl( attrs )));

		//	// Stash new URIs in xsi:schemaLocation attributes if desired
		//	if (loader.useSchemaLocationAttributes()) 
		//	{
		//		std::string schemaLocations = attrs.getValue(Constants.XMLSchemaInstanceNamespace.toString(),"schemaLocation");
		//		if (schemaLocations != null) 
		//		{
		//			logger.debug("Processing schema locations: " + schemaLocations);
		//			std::string[] fields = schemaLocations.trim().split("\\s+");
		//			for (int i=1; i<fields.length; i=i+2) 
		//			{
		//				try 
		//				{
		//					URI uri = getBaseURISAXResolver().getBaseURI().resolve(new URI(fields[i]));
		//					logger.debug("Working on: " + uri);
		//					loader.stashURI(uri);
		//				}
		//				catch (URISyntaxException e) 
		//				{
		//					logger.warn("Ignoring malformed XSI schemaLocation URI in: " + schemaLocations);
		//				}
		//				catch (XBRLException e) 
		//				{
		//					logger.warn("A problem occurred when stashing the schemaLocation URI: " + fields[i]);
		//				}
		//				catch (XMLBaseException e) 
		//				{
		//					logger.warn("A problem occurred when getting the base URI so schemaLocation URIs were not stashed from: " + schemaLocations);
		//				}
		//			}
		//		}
		//	}

		//	// Identify the fragments
		//	for (Identifier identifier: getIdentifiers()) 
		//	{
		//		try 
		//		{
		//			identifier.startElement(namespaceURI,lName,qName,attrs);
		//			if (loader.isBuildingAFragment()) 
		//			{
		//				if (loader.getFragment().isNewFragment()) 
		//				{
		//					break;
		//				}
		//			}
		//		}
		//		catch (XBRLException e) 
		//		{
		//			logger.error(this->getURI() + " : " + e.getMessage());
		//			throw new xercesc::SAXException("Fragment identification failed.",e);
		//		}
		//	}

		//	if (! loader.isBuildingAFragment()) 
		//	{
		//		throw new xercesc::SAXException("Some element has not been placed in a fragment.");
		//	}

		//	// Insert the current element into the fragment being built
		//	try 
		//	{
		//		Fragment fragment = getLoader().getFragment();
		//		if (fragment == null) throw new xercesc::SAXException("A fragment should be being built.");
		//		Builder builder = fragment.getBuilder();
		//		if (builder == null) throw new xercesc::SAXException("A fragment that is being built needs a builder.");
		//		builder.appendElement(namespaceURI, lName, qName, attrs);

		//		// Hardwire XLink resource language code inheritance to
		//		// improve query performance based on language selections.
		//		if (attrs.getIndex(Constants.XLinkNamespace.toString(),"type") > -1) 
		//		{
		//			try 
		//			{
		//				Element element = fragment.getDataRootElement();
		//				if (!element.hasAttributeNS(Constants.XMLNamespace,"lang")) 
		//				{
		//					std::string code = getElementState().getLanguageCode();
		//					if (code != null) 
		//					{
		//						element.setAttribute("xml:lang",code);
		//					}
		//				}
		//			}
		//			catch (Throwable t) 
		//			{
		//				logger.info("bugger");
		//			}
		//		}

		//	}
		//	catch (XBRLException e) 
		//	{
		//		logger.error(this->getURI() + " : " + e.getMessage());
		//		throw new xercesc::SAXException("The element could not be appended to the fragment.",e);
		//	}

		}

		void endElement(
			const std::string& namespaceURI,
			const std::string& lName,
			const std::string& qName)
		{

			// Get the attributes of the element being ended.
			Attributes attrs = getElementState().getAttributes();

			// Handle the ending of an element in the fragment builder
			try 
			{
				getLoader().getFragment().getBuilder().endElement(namespaceURI, lName, qName);
			}
			catch (XBRLException e) 
			{
				throw new xercesc::SAXException("The XBRLAPI fragment endElement failed.",e);
			}

			// Handle the ending of an element in the XLink processor
			try 
			{
				getLoader().getXlinkProcessor().endElement(namespaceURI, lName, qName, attrs);
			}
			catch (XLinkException e) 
			{
				throw new xercesc::SAXException("The XLink processor endElement failed.",e);
			}

			// Update the states of the fragment identifiers
			for (Identifier identifier: this->getIdentifiers()) 
			{
				try 
				{
					identifier.endElement(namespaceURI,lName,qName,attrs);
				}
				catch (XBRLException e) 
				{
					throw new xercesc::SAXException("Fragment identifier state update failed at the end of an element failed.",e);
				}
			}

			// Update the state of the loader.
			try 
			{
				getLoader().updateState(getElementState());
			}
			catch (XBRLException e) 
			{
				throw new xercesc::SAXException("The state of the loader could not be updated at the end of element " + namespaceURI + ":" + lName + "." + e.getMessage(),e);
			}

			// Update the information about the state of the current element
			setElementState(getElementState().getParent());

		}

		void ignorableWhitespace(char buf[], int offset, int len)
		{
		//	try 
		//	{
		//		std::string s(buf, offset, len);
		//		if (!s.trim().equals(""))
		//			getLoader().getFragment().getBuilder().appendText(s);
		//	}
		//	catch (XBRLException e) 
		//	{
		//		throw new xercesc::SAXException("Failed to handle ignorable white space." + getInputErrorInformation());
		//	}
		}

		void processingInstruction(const std::string& target, const std::string& data)
		{
		//	try 
		//	{
		//		Fragment fragment = getLoader().getFragment();
		//		if (fragment != null) 
		//		{
		//			fragment.getBuilder().appendProcessingInstruction(target,data);
		//		}
		//	}
		//	catch (XBRLException e) 
		//	{
		//		// Need to store processing instructions for incorporation into the fragment being created.
		//	}
		}

		void characters(char buf[], int offset, int len)
		{
		//	try 
		//	{
		//		std::string s(buf, offset, len);
		//		getLoader().getFragment().getBuilder().appendText(s);
		//	}
		//	catch (XBRLException e) 
		//	{
		//		throw new xercesc::SAXException("The characters could not be appended to the fragment." + getInputErrorInformation());
		//	}
		}

		void setDocumentLocator(const Locator& locator) 
		{
		//	this->locator = locator;
		}


		BaseURISAXResolver getBaseURISAXResolver() 
		{
			return baseURISAXResolver;
		}

		std::list<Identifier> identifiers = getIdentifiers();

		void addIdentifier(const Identifier& identifier) 
		{
			identifiers.add(identifier);
		}
		void addIdentifier(int index, const Identifier& identifier) 
		{
		//	identifiers.add(index,identifier);
		}

		void removeIdentifier(int index)
		{
		//	if (index > identifiers.size()-1) throw new XBRLException("The identifier index was too large.");
		//	if (index < 0) throw new XBRLException("The identifier index was too low.");
		//	if (identifiers.size() == 0) throw new XBRLException("There are no identifiers to remove.");
		//	identifiers.remove(index);
		}

		Locator locator;

		std::string xml;

		Locator getLocator()
		{
		//	return this->locator;
		}
		std::string getPublicId()
		{
		//	return getLocator().getPublicId();
		}

		std::string getSystemId()
		{
		//	return getLocator().getSystemId();
		}

		int getLineNumber()
		{
		//	return getLocator().getLineNumber();
		}

		int getColumnNumber()
		{
		//	return getLocator().getColumnNumber();
		}

		std::string getInputErrorInformation()
		{
		//	//StringBuffer s = new StringBuffer("  The problem occurred in ");
		//	//if (!(getSystemId() == null))
		//	//	s.append(getSystemId() + ".  ");
		//	//else
		//	//	s.append("a document without a URI.  All DTS documents must have a URI but one being parsed into the DTS does not.");
		//	//s.append("The problem seems to be on line" + getLineNumber() + " at column " + getColumnNumber() + ".");
		//	//return s.toString();
		//	return std::string();
		}

		XBRLXLinkHandler getXLinkHandler()
		{
			try
			{
				return (XBRLXLinkHandlerImpl) this->getLoader().getXlinkProcessor().getXLinkHandler();
			}
			catch (ClassCastException e)
			{
				throw new xercesc::SAXException("The XBRL API is not using the XBRL XLink Handler implementation.");
			}
		}

		BaseURISAXResolver baseURISAXResolver;

		void setBaseURISAXResolver(const BaseURISAXResolver& resolver)
		{
			this->baseURISAXResolver = resolver;
		}

		void setXML(const std::string& xml)
		{
		//	this->xml = xml;
		}

	};

	ContentHandler::ContentHandler() {}
	ContentHandler::~ContentHandler() {} 

	ContentHandler::ContentHandler(const ContentHandler& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ContentHandler& ContentHandler::operator=(const ContentHandler& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ContentHandler::ContentHandler(ContentHandler&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ContentHandler& ContentHandler::operator=(ContentHandler&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ContentHandler::operator==(const ContentHandler& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ContentHandler::operator!=(const ContentHandler& rhs)
	{
		return !this->operator==(rhs);
	}

	void ContentHandler::startDocument()
	{
		pImpl->startDocument();
	}

	void ContentHandler::startElement(
		const std::string& namespaceURI,
		const std::string& lName,
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(
		namespaceURI,
		lName,
		qName,
		attrs);
	}

	void ContentHandler::endElement(
		const std::string& namespaceURI,
		const std::string& lName,
		const std::string& qName)
	{
		pImpl->endElement(
		namespaceURI,
		lName,
		qName);
	}

	void ContentHandler::ignorableWhitespace(char buf[], int offset, int len)
	{
		pImpl->ignorableWhitespace(buf[], offset, len);
	}

	void ContentHandler::processingInstruction(const std::string& target, const std::string& data)
	{
		pImpl->processingInstruction(target, data);
	}

	void ContentHandler::characters(char buf[], int offset, int len)
	{
		pImpl->characters(buf[], offset, len);
	}


	void ContentHandler::setDocumentLocator(const Locator& locator) 
	{
		pImpl->setDocumentLocator(locator) ;
	}

	BaseURISAXResolver ContentHandler::getBaseURISAXResolver() 
	{
		pImpl->getBaseURISAXResolver();
	}

	void ContentHandler::addIdentifier(const Identifier& identifier) 
	{
		pImpl->addIdentifier(identifier) ;
	}

	void ContentHandler::addIdentifier(int index, const Identifier& identifier) 
	{
		pImpl->addIdentifier(index, identifier);
	}

	void ContentHandler::removeIdentifier(int index)
	{
		pImpl->removeIdentifier(index);
	}
}
