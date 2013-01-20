#include "ContentHandler.h"
#include "BaseURISAXResolver.h"
#include "BaseContentHandler.h"
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
#include "XercesString.h"

#include <iostream>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/dom/DOMElement.hpp>

namespace xbrlcapi
{
	struct ContentHandler::Impl
	{

		std::weak_ptr<ContentHandler> outer;
		std::shared_ptr<Loader> loader;
		std::shared_ptr<xercesc::Locator> locator;
		std::string xml;

		/**
		* The list of fragment identifiers
		*/
		std::list<std::shared_ptr<Identifier>> identifiers;

		Impl() 
		{
		}

		Impl(std::shared_ptr<Loader>& loader) : 
			outer(outer),
			loader(loader)
		{
			//			identifiers = getIdentifiers();
		}

		Impl(std::shared_ptr<Loader>& loader, 
			const std::string& xml) : 
		outer(outer),
			loader(loader)
		{
			//			identifiers = getIdentifiers();
			setXML(xml);
		}

		void startDocument()
		{
			// Set up the base URI resolver for the content handler and the XLink handler.
			if (outer.lock()->getURI().empty()) 
			{
				throw xercesc::SAXException("The document URI must not be null when setting up the base URI resolver.");
			}
			setBaseURISAXResolver(BaseURISAXResolver(outer.lock()->getURI()));
			getXLinkHandler().setBaseURISAXResolver(baseURISAXResolver);

			std::shared_ptr<XBRLXLinkIdentifier> xbrlLinkIdentifier(new XBRLXLinkIdentifier(outer.lock()));
			std::shared_ptr<SchemaIdentifier> schemaIdentifier(new SchemaIdentifier(outer.lock()));
			std::shared_ptr<XBRLIdentifier> xbrlIdentifier(new XBRLIdentifier(outer.lock()));
			std::shared_ptr<LanguageIdentifier> languageIdentifier(new LanguageIdentifier(outer.lock()));
			std::shared_ptr<ReferencePartIdentifier> referencePartIdentifier(new ReferencePartIdentifier(outer.lock()));
			std::shared_ptr<GenericDocumentRootIdentifier> genericDocumentRootIdentifier(new GenericDocumentRootIdentifier(outer.lock()));
			xbrlLinkIdentifier->initialize();
			schemaIdentifier->initialize();
			xbrlIdentifier->initialize();
			languageIdentifier->initialize();
			referencePartIdentifier->initialize();
			genericDocumentRootIdentifier->initialize();

			// Instantiate the fragment identifiers
			try 
			{
				addIdentifier(xbrlLinkIdentifier);
				addIdentifier(schemaIdentifier);
				addIdentifier(xbrlIdentifier);
				addIdentifier(languageIdentifier);
				addIdentifier(referencePartIdentifier);
				addIdentifier(genericDocumentRootIdentifier);
			}
			catch (const XBRLException& e) 
			{
				throw xercesc::SAXException(("One of the fragment identifiers could not be instantiated." 
					+ e.getMessage() ).c_str());
			}

		}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName, 
			const xercesc::Attributes& attrs)
		{

			// Update the information about the state of the current element (tracks ancestor attributes)
			outer.lock()->setElementState( ElementState(outer.lock()->getElementState(), attrs ));

			// Stash new URIs in xsi:schemaLocation attributes if desired
			if (loader->useSchemaLocationAttributes()) 
			{
				std::string schemaLocations = to_string(attrs.getValue(XS(XMLConstants::XMLSchemaInstanceNamespace),XS("schemaLocation")));
				if (!schemaLocations.empty()) 
				{
					//logger.debug("Processing schema locations: " + schemaLocations);
					//std::string[] fields = schemaLocations.trim().split("\\s+");
					//for (int i=1; i<fields.length; i=i+2) 
					{
						//try 
						//{
						//	Poco::URI uri = getBaseURISAXResolver().getBaseURI().resolve(Poco::URI(fields[i]));
						//	logger.debug("Working on: " + uri);
						//	loader.stashURI(uri);
						//}
						//catch (URISyntaxException e) 
						//{
						//	logger.warn("Ignoring malformed XSI schemaLocation URI in: " + schemaLocations);
						//}
						//catch (XBRLException e) 
						//{
						//	logger.warn("A problem occurred when stashing the schemaLocation URI: " + fields[i]);
						//}
						//catch (XMLBaseException e) 
						//{
						//	logger.warn("A problem occurred when getting the base URI so schemaLocation URIs were not stashed from: " + schemaLocations);
						//}
					}
				}
			}

			// Identify the fragments
			for (const std::shared_ptr<Identifier>& identifier : identifiers) 
			{
				try 
				{
					identifier->startElement(namespaceURI, lName, qName, attrs);
					if (loader->isBuildingAFragment()) 
					{
						if (loader->getFragment().isNewFragment()) 
						{
							break;
						}
					}
				}
				catch (XBRLException e) 
				{
					//	logger.error(this->getURI() + " : " + e.getMessage());
					throw xercesc::SAXException(strcat("Fragment identification failed. ", + e.getMessage().c_str()));
				}
			}

			if (! loader->isBuildingAFragment()) 
			{
				throw xercesc::SAXException("Some element has not been placed in a fragment.");
			}

			// Insert the current element into the fragment being built
			try 
			{
				Fragment fragment = loader->getFragment();
				//if (fragment == NULL) throw xercesc::SAXException("A fragment should be being built.");
				Builder builder = fragment.getBuilder();
				//if (builder == null) throw xercesc::SAXException("A fragment that is being built needs a builder.");
				builder.appendElement(namespaceURI, lName, qName, attrs);

				// Hardwire XLink resource language code inheritance to
				// improve query performance based on language selections.
				if (attrs.getIndex(XS(XMLConstants::XLinkNamespace),XS("type")) > -1) 
				{
					//try 
					//{
					std::shared_ptr<DOMElement> element = fragment.getDataRootElement();
					if (!element->hasAttributeNS(XS(XMLConstants::XMLNamespace),XS("lang"))) 
					{
						std::string code = outer.lock()->getElementState().getLanguageCode();
						//if (code != null) 
						//{
						element->setAttribute(XS("xml:lang"),XS(code));
						//}
					}
					//}
					//catch (Throwable t) 
					//{
					//	logger.info("bugger");
					//}
				}

			}
			catch (XBRLException e) 
			{
				//	logger.error(this->getURI() + " : " + e.getMessage());
				throw xercesc::SAXException(strcat("The element could not be appended to the fragment.",e.getMessage().c_str()));
			}

		}

		/**
		* The end of an element triggers processing of an extended link
		* if we have reached the end of an extended link.
		* Otherwise, we step up to the parent element
		* unless the element that is ending did not ever become the current element.
		*/
		void endElement(
			const   XMLCh* const    namespaceURI,
			const   XMLCh* const    lName,
			const   XMLCh* const    qName)
		{

			// Get the attributes of the element being ended.
			std::shared_ptr<const xercesc::Attributes> attrs = outer.lock()->getElementState().getAttributes();

			// Handle the ending of an element in the fragment builder
			//try 
			//{
			//	getLoader().getFragment().getBuilder().endElement(namespaceURI, lName, qName);
			//}
			//catch (XBRLException e) 
			//{
			//	throw xercesc::SAXException(("The XBRLAPI fragment endElement failed. " + 
			//		e.getMessage()).c_str());			
			//}

			//// Handle the ending of an element in the XLink processor
			//try 
			//{
			//	getLoader().getXlinkProcessor().endElement(namespaceURI, 
			//		lName, 
			//		qName, 
			//		*attrs);
			//}
			//catch (XLinkException e) 
			//{
			//	throw xercesc::SAXException(("The XLink processor endElement failed. " + 
			//		e.getMessage()).c_str());
			//}

			//// Update the states of the fragment identifiers
			//for (std::shared_ptr<Identifier>& id : getIdentifiers()) 
			//{
			//	try 
			//	{
			//		id->endElement(namespaceURI,lName,qName,*attrs);
			//	}
			//	catch (XBRLException e) 
			//	{
			//		throw xercesc::SAXException(("Fragment identifier state update failed at the end of an element failed." + 
			//			e.getMessage()).c_str());
			//	}
			//}

			//// Update the state of the loader.
			//try 
			//{
			//	getLoader().updateState(getElementState());
			//}
			//catch (XBRLException e) 
			//{
			//	throw xercesc::SAXException(("The state of the loader could not be updated at the end of element " + 
			//		namespaceURI + 
			//		":" + 
			//		lName + 
			//		"." + 
			//		e.getMessage()).c_str());
			//}

			//// Update the information about the state of the current element
			//setElementState(*getElementState().getParent());

		}

		/**
		* Ignore ignorable whitespace
		*/
		void ignorableWhitespace(const   XMLCh* const buf, const XMLSize_t offset)
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
		void processingInstruction(const   XMLCh* const target, const XMLCh* const data)
		{
			//try 
			//{
			//	Fragment fragment = getLoader().getFragment();
			//	fragment.getBuilder().appendProcessingInstruction(target,data);
			//}
			//catch (XBRLException e) 
			//{
			//	// Need to store processing instructions for incorporation into the fragment being created.
			//}
		}

		/**
		* Copy characters (trimming white space as required) to the DTSImpl.
		*/
		void characters(const   XMLCh* const buf, const  XMLSize_t offset)
		{
			//try 
			//{
			//	std::string s(buf, offset, len);
			//	getLoader().getFragment().getBuilder().appendText(s);
			//}
			//catch (XBRLException e) 
			//{
			//	throw xercesc::SAXException(("The characters could not be appended to the fragment." + 
			//		getInputErrorInformation() + 
			//		e.getMessage()).c_str());
			//}
		}

		/**
		* The locator for a document is stored to facilitate resolution
		* of CacheURIImpl's relative to that location.
		*/
		void setDocumentLocator(const xercesc::Locator* locator) 
		{
			//this->locator = locator;
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
		//	identifiers.push_back(std::shared_ptr<Identifier>(identifier));
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
			return to_string(locator->getPublicId());
		}

		std::string getSystemId()
		{
			return to_string(locator->getSystemId());
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

		XLinkHandler getXLinkHandler()
		{
			return loader->getXlinkProcessor().getXLinkHandler();
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

		std::shared_ptr<Loader> getLoader()
		{
			return loader;
		}

		void setOuter(const std::weak_ptr<ContentHandler>& contentHandler)
		{
			outer = std::weak_ptr<ContentHandler>(contentHandler);
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

	ContentHandler::ContentHandler(std::shared_ptr<Loader>& loader, const Poco::URI& uri) : 
		BaseContentHandler(uri), 
		pImpl(loader)
	{
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
		const   XMLCh* const    namespaceURI,
		const   XMLCh* const    lName,
		const   XMLCh* const    qName,
		const	xercesc::Attributes&	attrs)
	{
		pImpl->startElement(
			namespaceURI,
			lName,
			qName,
			attrs);
	}

	void ContentHandler::endElement(
		const   XMLCh* const    namespaceURI,
		const   XMLCh* const    lName,
		const   XMLCh* const    qName)
	{
		pImpl->endElement(
			namespaceURI,
			lName,
			qName);
	}

	void ContentHandler::ignorableWhitespace(const   XMLCh* const buf, const XMLSize_t offset)
	{
		pImpl->ignorableWhitespace(buf, offset);
	}

	void ContentHandler::processingInstruction(const   XMLCh* const target, const XMLCh* const data)
	{
		pImpl->processingInstruction(target, data);
	}

	void ContentHandler::characters(const   XMLCh* const buf, const  XMLSize_t offset)
	{
		pImpl->characters(buf, offset);
	}


	void ContentHandler::setDocumentLocator(const xercesc::Locator* locator) 
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

	std::shared_ptr<Loader> ContentHandler::getLoader()
	{
		return pImpl->getLoader();
	}

	std::weak_ptr<ContentHandler> ContentHandler::getPtr()
	{
		return shared_from_this();
	}

	void ContentHandler::initialize()
	{
		pImpl->setOuter(getPtr());
	}

}
