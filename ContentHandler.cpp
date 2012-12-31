#include "BaseURISAXResolver.h"
#include "BaseURISAXResolver.h"
#include "Builder.h"
#include "Constants.h"
#include "ContentHandler.h"
#include "Fragment.h"
#include "GenericDocumentRootIdentifier.h"
#include "Identifier.h"
#include "LanguageIdentifier.h"
#include "ReferencePartIdentifier.h"
#include "SchemaIdentifier.h"
#include "XBRLException.h"
#include "XBRLIdentifier.h"
#include "XBRLXLinkIdentifier.h"
#include "XBRLXLinkHandler.h"
#include "XLinkException.h"
#include "XLinkProcessor.h"
#include "XercesStrings.h"
#include <iostream>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{

	struct ContentHandler::Impl :  public BaseContentHandler 
	{

		std::shared_ptr<xercesc::Locator> locator;
		std::string xml;
		/**
		* The list of fragment identifiers
		*/
		std::list<std::shared_ptr<Identifier>> identifiers;

		Impl() {}

		Impl(const Loader& loader, const Poco::URI& uri) : BaseContentHandler(loader, uri)
		{}

		Impl(const Loader& loader, const Poco::URI& uri, const std::string& xml) : Impl(loader, uri)
		{
			//identifiers = getIdentifiers();
			setXML(xml);
		}

		void startDocument(const xbrlcapi::ContentHandler& handler)
		{
			// Set up the base URI resolver for the content handler and the XLink handler.
			if (getURI().empty()) 
			{
				throw xercesc::SAXException("The document URI must not be null when setting up the base URI resolver.");
			}
			setBaseURISAXResolver(BaseURISAXResolver(getURI()));
			getXLinkHandler().setBaseURISAXResolver(baseURISAXResolver);

			// Instantiate the fragment identifiers
			try 
			{
				addIdentifier(std::shared_ptr<Identifier>(new XBRLXLinkIdentifier(handler)));
				addIdentifier(std::shared_ptr<Identifier>(new SchemaIdentifier(handler)));
				addIdentifier(std::shared_ptr<Identifier>(new XBRLIdentifier(handler)));
				addIdentifier(std::shared_ptr<Identifier>(new LanguageIdentifier(handler)));
				addIdentifier(std::shared_ptr<Identifier>(new ReferencePartIdentifier(handler)));
				addIdentifier(std::shared_ptr<Identifier>(new GenericDocumentRootIdentifier(handler)));
			}
			catch (const XBRLException& e) 
			{
				throw xercesc::SAXException(("One of the fragment identifiers could not be instantiated." 
					+ e.getMessage() ).c_str());
			}

		}

		void startElement(
			const std::string& namespaceURI,
			const std::string& lName,
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{

			//Loader loader = getLoader();

			//// Update the information about the state of the current element (tracks ancestor attributes)
			//setElementState(ElementState(getElementState(), xercesc::Attributes( attrs )));

			//// Stash new URIs in xsi:schemaLocation attributes if desired
			//if (loader.useSchemaLocationAttributes()) 
			//{
			//	std::string schemaLocations = attrs.getValue(XMLConstants::XMLSchemaInstanceNamespace,"schemaLocation");
			//	if (!schemaLocations.empty()) 
			//	{
			//		//logger.debug("Processing schema locations: " + schemaLocations);
			//		std::string[] fields = schemaLocations.trim().split("\\s+");
			//		for (int i=1; i<fields.length; i=i+2) 
			//		{
			//			try 
			//			{
			//				URI uri = getBaseURISAXResolver().getBaseURI().resolve(new URI(fields[i]));
			//				logger.debug("Working on: " + uri);
			//				loader.stashURI(uri);
			//			}
			//			catch (URISyntaxException e) 
			//			{
			//				logger.warn("Ignoring malformed XSI schemaLocation URI in: " + schemaLocations);
			//			}
			//			catch (XBRLException e) 
			//			{
			//				logger.warn("A problem occurred when stashing the schemaLocation URI: " + fields[i]);
			//			}
			//			catch (XMLBaseException e) 
			//			{
			//				logger.warn("A problem occurred when getting the base URI so schemaLocation URIs were not stashed from: " + schemaLocations);
			//			}
			//		}
			//	}
			//}

			//// Identify the fragments
			//for (Identifier identifier: getIdentifiers()) 
			//{
			//	try 
			//	{
			//		identifier.startElement(namespaceURI,lName,qName,attrs);
			//		if (loader.isBuildingAFragment()) 
			//		{
			//			if (loader.getFragment().isNewFragment()) 
			//			{
			//				break;
			//			}
			//		}
			//	}
			//	catch (XBRLException e) 
			//	{
			//		logger.error(this->getURI() + " : " + e.getMessage());
			//		throw xercesc::SAXException("Fragment identification failed.",e);
			//	}
			//}

			//if (! loader.isBuildingAFragment()) 
			//{
			//	throw xercesc::SAXException("Some element has not been placed in a fragment.");
			//}

			//// Insert the current element into the fragment being built
			//try 
			//{
			//	Fragment fragment = getLoader().getFragment();
			//	if (fragment == null) throw xercesc::SAXException("A fragment should be being built.");
			//	Builder builder = fragment.getBuilder();
			//	if (builder == null) throw xercesc::SAXException("A fragment that is being built needs a builder.");
			//	builder.appendElement(namespaceURI, lName, qName, attrs);

			//	// Hardwire XLink resource language code inheritance to
			//	// improve query performance based on language selections.
			//	if (attrs.getIndex(Constants.XLinkNamespace.toString(),"type") > -1) 
			//	{
			//		try 
			//		{
			//			Element element = fragment.getDataRootElement();
			//			if (!element.hasAttributeNS(Constants.XMLNamespace,"lang")) 
			//			{
			//				std::string code = getElementState().getLanguageCode();
			//				if (code != null) 
			//				{
			//					element.setAttribute("xml:lang",code);
			//				}
			//			}
			//		}
			//		catch (Throwable t) 
			//		{
			//			logger.info("bugger");
			//		}
			//	}

			//}
			//catch (XBRLException e) 
			//{
			//	logger.error(this->getURI() + " : " + e.getMessage());
			//	throw xercesc::SAXException("The element could not be appended to the fragment.",e);
			//}

		}

		/**
		* The end of an element triggers processing of an extended link
		* if we have reached the end of an extended link.
		* Otherwise, we step up to the parent element
		* unless the element that is ending did not ever become the current element.
		*/
		void endElement(
			const std::string& namespaceURI,
			const std::string& lName,
			const std::string& qName)
		{

			// Get the attributes of the element being ended.
			std::shared_ptr<xercesc::Attributes> attrs = getElementState().getAttributes();

			// Handle the ending of an element in the fragment builder
			try 
			{
				getLoader().getFragment().getBuilder().endElement(namespaceURI, lName, qName);
			}
			catch (XBRLException e) 
			{
				throw xercesc::SAXException(("The XBRLAPI fragment endElement failed. " + 
					e.getMessage()).c_str());			
			}

			// Handle the ending of an element in the XLink processor
			try 
			{
				getLoader().getXlinkProcessor().endElement(namespaceURI, 
														   lName, 
														   qName, 
														   *attrs);
			}
			catch (XLinkException e) 
			{
				throw xercesc::SAXException(("The XLink processor endElement failed. " + 
					e.getMessage()).c_str());
			}

			// Update the states of the fragment identifiers
			for (std::shared_ptr<Identifier>& id : getIdentifiers()) 
			{
				try 
				{
					id->endElement(namespaceURI,lName,qName,*attrs);
				}
				catch (XBRLException e) 
				{
					throw xercesc::SAXException(("Fragment identifier state update failed at the end of an element failed." + 
						e.getMessage()).c_str());
				}
			}

			// Update the state of the loader.
			try 
			{
				getLoader().updateState(getElementState());
			}
			catch (XBRLException e) 
			{
				throw xercesc::SAXException(("The state of the loader could not be updated at the end of element " + 
					namespaceURI + 
					":" + 
					lName + 
					"." + 
					e.getMessage()).c_str());
			}

			// Update the information about the state of the current element
			setElementState(*getElementState().getParent());

		}

		/**
		* Ignore ignorable whitespace
		*/
		void ignorableWhitespace(char buf[], int offset, int len)
		{
			/*		try 
			{
			std::string s(buf, offset, len);
			if (!s.trim().equals(""))
			getLoader().getFragment().getBuilder().appendText(s);
			}
			catch (XBRLException e) 
			{
			throw xercesc::SAXException(("Failed to handle ignorable white space." + 
			getInputErrorInformation() + 
			e.getMessage()).c_str());
			}*/
		}

		/**
		* Copy across processing instructions to the DTSImpl
		*/
		void processingInstruction(const std::string& target, const std::string& data)

		{
			try 
			{
				Fragment fragment = getLoader().getFragment();
				fragment.getBuilder().appendProcessingInstruction(target,data);
			}
			catch (XBRLException e) 
			{
				// Need to store processing instructions for incorporation into the fragment being created.
			}
		}

		/**
		* Copy characters (trimming white space as required) to the DTSImpl.
		*/
		void characters(char buf[], int offset, int len)
		{
			try 
			{
				std::string s(buf, offset, len);
				getLoader().getFragment().getBuilder().appendText(s);
			}
			catch (XBRLException e) 
			{
				throw xercesc::SAXException(("The characters could not be appended to the fragment." + 
					getInputErrorInformation() + 
					e.getMessage()).c_str());
			}
		}

		/**
		* The locator for a document is stored to facilitate resolution
		* of CacheURIImpl's relative to that location.
		*/
		void setDocumentLocator(const std::shared_ptr<xercesc::Locator>& locator) 
		{
			this->locator = locator;
		}

		/**
		* @return the base URI resolver for SAX parsing.
		*/
		BaseURISAXResolver getBaseURISAXResolver() 
		{
			return baseURISAXResolver;
		}

		/**
		* @param identifier The identifier to add to the list of
		* fragment identifiers used by the content handler.
		*/
		void addIdentifier(const std::shared_ptr<Identifier>& identifier) 
		{
			identifiers.push_back(identifier);
		}


		/**
		* @param index The index of the position at which
		* the new identifier is to be inserted in the list of
		* fragment identifiers.
		* @param identifier The identifier to add to the list of
		* fragment identifiers used by the content handler.
		*/
		//void addIdentifier(int index, const Identifier& identifier) 
		//{
		//	identifiers.push_back(std::make_shared<Identifier>(identifier));
		//}

		/**
		* @param index The index of the identifier to remove from the list of
		* fragment identifiers used by the content handler.
		*/
		void removeIdentifier(int index)
		{
			//if (index > identifiers.size()-1) throw XBRLException("The identifier index was too large.");
			//if (index < 0) throw XBRLException("The identifier index was too low.");
			//if (identifiers.size() == 0) throw XBRLException("There are no identifiers to remove.");
			//identifiers.remove(index);
		}

		std::shared_ptr<xercesc::Locator> getLocator()
		{
			return this->locator;
		}
		std::string getPublicId()
		{
			return xerces_util::toNative(locator->getPublicId());
		}

		std::string getSystemId()
		{
			return xerces_util::toNative(locator->getSystemId());
		}

		long long getLineNumber()
		{
			return locator->getLineNumber();
		}

		long long getColumnNumber()
		{
			return locator->getColumnNumber();
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
				return std::string();
		}

		XBRLXLinkHandler getXLinkHandler()
		{
			//try
			//{
			//	return (XBRLXLinkHandler) this->getLoader().getXlinkProcessor().getXLinkHandler();
			//}
			//catch (ClassCastException e)
			//{
			//	throw new xercesc::SAXException("The XBRL API is not using the XBRL XLink Handler implementation.");
			//}
			return *(new XBRLXLinkHandler);
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
			pImpl->~Impl();
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
		pImpl->startDocument(*this);
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
		pImpl->ignorableWhitespace(buf, offset, len);
	}

	void ContentHandler::processingInstruction(const std::string& target, const std::string& data)
	{
		pImpl->processingInstruction(target, data);
	}

	void ContentHandler::characters(char buf[], int offset, int len)
	{
		pImpl->characters(buf, offset, len);
	}


	void ContentHandler::setDocumentLocator(const std::shared_ptr<xercesc::Locator>& locator) 
	{
		pImpl->setDocumentLocator(locator) ;
	}

	BaseURISAXResolver ContentHandler::getBaseURISAXResolver() 
	{
		return pImpl->getBaseURISAXResolver();
	}

	void ContentHandler::addIdentifier(const std::shared_ptr<Identifier>& identifier) 
	{
		pImpl->addIdentifier(identifier) ;
	}

	//void ContentHandler::addIdentifier(int index, const Identifier& identifier) 
	//{
	//	pImpl->addIdentifier(index, identifier);
	//}

	void ContentHandler::removeIdentifier(int index)
	{
		pImpl->removeIdentifier(index);
	}
}
