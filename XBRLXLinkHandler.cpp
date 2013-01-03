#pragma once

#include <memory>
#include "XLinkHandlerDefault.h"
#include "Loader.h"
#include "XBRLXLinkHandler.h"
#include "BaseURISAXResolver.h"
#include "ElementState.h"
#include "XLinkException.h"
#include "XBRLException.h"
//#include "XMLBaseException.h"

namespace xbrlcapi
{

	struct XBRLXLinkHandler::Impl 
	{
		Loader loader;

		BaseURISAXResolver baseURIResolver;

		ElementState elementState;

		Impl() 
		{}

		/**
		* Set up the fragment and add it to the loader.
		* @param fragment The newly identified fragment.
		* @param attrs The attributes of the root element of the fragment.
		* @throws XBRLException
		*/
		void processFragment(const Fragment& fragment, const xercesc::Attributes& attrs)
		{
			/*		Loader loader = this->getLoader();
			fragment.setBuilder(new BuilderImpl(loader.getBuilderDOM()));
			std::string index = getLoader().getNextFragmentId();
			if (index == null) throw XBRLException(getLoader().getDocumentURI() + ": The fragment index MUST not be null.");
			if (index.equals("")) throw XBRLException(getLoader().getDocumentURI() + ": The fragment index MUST not be the empty string.");
			fragment.setIndex(index);
			if (attrs.getValue("id") != null) {
			fragment.appendID(attrs.getValue("id"));
			this->getElementState().setId(attrs.getValue("id"));
			}
			loader.add(fragment,getElementState());*/
		}

		void setLoader(const Loader& loader) 
		{
			this->loader = loader;
		}

		void setBaseURISAXResolver(const BaseURISAXResolver& resolver)
		{
			baseURIResolver = resolver;
		}

		void xmlBaseStart(const std::string& value)
		{
			//try 
			//{
			//	baseURIResolver.addBaseURI(value);
			//}
			//catch (const XMLBaseException& e) 
			//{
			//	throw XLinkException("The Base URI Resolver could not update the base URI",e);
			//}
		}


		void startTitle(const std::string& namespaceURI, const std::string& lName, const std::string& qName,
			const xercesc::Attributes& attrs) 
		{
			/*		try 
			{
			processFragment(new TitleImpl(),attrs);
			}
			catch (XBRLException e) 
			{
			throw XLinkException("The title could not be created and stored.",e);
			}*/
		}


		void xmlBaseEnd()
		{
			/*		try 
			{
			baseURIResolver.removeBaseURI();
			}
			catch (XMLBaseException e) 
			{
			throw XLinkException("The Base URI Resolver could not revert to the previous base URI",e);
			}*/
		}


		void startExtendedLink(
			const std::string& namespaceURI, 
			const std::string& lName,
			const std::string& qName, 
			const xercesc::Attributes& attrs, 
			const std::string& role, 
			const std::string& title)
		{

			//try 
			//{
			//	processFragment(new ExtendedLinkImpl(),attrs);
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The extended link could not be created.",e);
			//}
		}

		void endExtendedLink(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
		{}

		void startResource(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs, 
			const std::string& role, 
			const std::string& title, 
			const std::string& label)
		{
			//try 
			//{

			//	Resource fragment = null;

			//	if (namespaceURI.equals(Constants.XBRL21LinkNamespace.toString())) 
			//	{
			//		if (lName.equals("label")) 
			//		{
			//			fragment = LabelResourceImpl();
			//		} else if (lName.equals("reference")) 
			//		{
			//			fragment = ReferenceResourceImpl();
			//		} else if (lName.equals("footnote")) 
			//		{
			//			fragment = FootnoteResourceImpl();
			//		}
			//	} else if (namespaceURI.equals(Constants.GenericLabelNamespace.toString())) 
			//	{
			//		if (lName.equals("label")) 
			//		{
			//			fragment = LabelResourceImpl();			
			//		}
			//	} else if (namespaceURI.equals(Constants.GenericReferenceNamespace.toString())) 
			//	{
			//		if (lName.equals("reference")) 
			//		{
			//			fragment = ReferenceResourceImpl();				
			//		}
			//	} else if (namespaceURI.equals(Constants.XBRLAPIEntitiesNamespace.toString())) 
			//	{
			//		if (lName.equals("identifier")) 
			//		{
			//			fragment = EntityResourceImpl();             
			//		}
			//	} else if (namespaceURI.equals(Constants.XBRLAPIMeasuresNamespace.toString())) 
			//	{
			//		if (lName.equals("measure")) 
			//		{
			//			fragment = MeasureResourceImpl();    
			//		}
			//	}			
			//	if (fragment == null) 
			//	{
			//		fragment = ResourceImpl();
			//	}

			//	processFragment(fragment,attrs);

			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The resource could not be created.",e);
			//}
		}

		void endResource(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
		{}

		void startLocator(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs, 
			const std::string& href, 
			const std::string& role, 
			const std::string& title,
			const std::string& label) 
		{
			/*			try 
			{
			try 
			{
			xercesc::Locator fragment = LocatorImpl();
			processFragment(fragment,attrs);            

			Loader loader = getLoader();
			URI uri = baseURIResolver.getBaseURI().resolve(new URI(href));
			fragment.setTarget(uri);
			loader.stashURI(uri);

			}
			catch (URISyntaxException e) 
			{
			logger.error("Problem encountered starting a locator for " + loader.getDocumentURI());
			throw XLinkException("The locator href value," + href + ", is a malformed URI.",e);
			}
			catch (XMLBaseException e) 
			{
			logger.error("Problem encountered starting a locator for " + loader.getDocumentURI());
			throw XLinkException("Base URI problems prevented the locator href from being queued up for processing.",e);
			}
			}
			catch (XBRLException xbrlException) 
			{
			throw XLinkException("An XBRL Exception prevented the locator href from being queued up for processing.",xbrlException);
			}    */       
		}

		void endLocator(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
		{}

		void startArc(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs, 
			const std::string& from, 
			const std::string& to, 
			const std::string& arcrole,
			const std::string& title, 
			const std::string& show, 
			const std::string& actuate)
		{
			//try 
			//{
			//	if (from == null || to == null) 
			//	{
			//		throw XLinkException("The XBRL XLink arc must have a 'from' and a 'to' label.");
			//	}
			//	processFragment(new ArcImpl(),attrs);
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The arc could not be created.",e);
			//}
		}

		void endArc(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
		{}

		void startSimpleLink(
			const std::string& namespaceURI, 
			const std::string& lName,
			const std::string& qName, 
			const xercesc::Attributes& attrs, 
			const std::string& href, 
			const std::string& role,
			const std::string& arcrole, 
			const std::string& title, 
			const std::string& show, 
			const std::string& actuate)
		{
			//SimpleLink fragment = SimpleLinkImpl();
			//try 
			//{
			//	processFragment(fragment,attrs);
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The simple link fragment could not be processed.",e);
			//}

			//URI uri = null;
			//try 
			//{
			//	uri = URI(href);
			//}
			//catch (URISyntaxException e) 
			//{
			//	throw XLinkException("The simple link URI could not be queued up for exploration in DTS discovery.",e);
			//}

			//if (! uri.isAbsolute()) 
			//{
			//	URI baseUri = null;
			//	try 
			//	{
			//		baseUri = baseURIResolver.getBaseURI();
			//	} 
			//	catch (const xercesc::XMLBaseException& e) 
			//	{
			//		throw XLinkException("The base URI to use for URI resolution cannot be accessed.",e);
			//	}
			//	uri = baseUri.resolve(uri);
			//}

			////	logger.debug("Got a simple link to " + uri);

			//try 
			//{
			//	loader = getLoader();
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The loader could not be accessed so the simple link URI cannot be stashed for discovery.",e);
			//}

			//try 
			//{
			//	fragment.setTarget(uri);
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The simple link fragment target could not be set to " + uri,e);
			//}

			//try 
			//{
			//	loader.stashURI(uri);
			//}
			//catch (XBRLException e) 
			//{
			//	throw XLinkException("The simple link URI could not be stashed for future discovery: " + href,e);
			//}

		}

		void endSimpleLink(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
		{}

		Loader getLoader()
		{
			//if (loader == null) throw XBRLException("The XLink Handler has no XBRL DTS loader to work with.");
			//return loader;
		}

		void setElementState(ElementState elementState) 
		{
			this->elementState = elementState; 
		}

		ElementState getElementState() 
		{
			//return elementState; 
		}	

		void error(const std::string& namespaceURI, const std::string& lName, const std::string& qName,
			const xercesc::Attributes& attrs,const std::string& message)
		{

			//if (message.endsWith(" is not defined in the XLink namespace.")) 
			//{
			//	this->warning(namespaceURI, lName, qName, attrs, message);
			//	return;
			//}

			//throw XLinkException(message);
		}


		void warning(const std::string& namespaceURI, const std::string& lName, const std::string& qName,
			const xercesc::Attributes& attrs,const std::string& message)
		{
			//logger.warn(message);
		}

		void titleCharacters(char* buf, int offset, int len)
		{
			// not implemented

		}

		void endTitle( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName)
		{
			//not Implemeted
		}

	};

	XBRLXLinkHandler::XBRLXLinkHandler() {}
	XBRLXLinkHandler::~XBRLXLinkHandler() {} 

	XBRLXLinkHandler::XBRLXLinkHandler(const XBRLXLinkHandler& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XBRLXLinkHandler& XBRLXLinkHandler::operator=(const XBRLXLinkHandler& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XBRLXLinkHandler::XBRLXLinkHandler(XBRLXLinkHandler&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XBRLXLinkHandler& XBRLXLinkHandler::operator=(XBRLXLinkHandler&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XBRLXLinkHandler::operator==(const XBRLXLinkHandler& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XBRLXLinkHandler::operator!=(const XBRLXLinkHandler& rhs)
	{
		return !this->operator==(rhs);
	}

	void XBRLXLinkHandler::setLoader(const Loader& loader) 
	{
		pImpl-> setLoader(loader);
	}

	void XBRLXLinkHandler::setBaseURISAXResolver(const BaseURISAXResolver& resolver)
	{
		pImpl->setBaseURISAXResolver(resolver);
	}

	void XBRLXLinkHandler::xmlBaseStart(const std::string& value)
	{
		pImpl->xmlBaseStart(value);
	}


	void XBRLXLinkHandler::startTitle(const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl-> startTitle(namespaceURI,
			lName,
			qName,
			attrs);
	}


	void XBRLXLinkHandler::xmlBaseEnd()
	{
		pImpl->xmlBaseEnd();
	}


	void XBRLXLinkHandler::startExtendedLink(
		const std::string& namespaceURI, 
		const std::string& lName,
		const std::string& qName, 
		const xercesc::Attributes& attrs, 
		const std::string& role, 
		const std::string& title)
	{
		pImpl-> startExtendedLink(namespaceURI,
			lName,
			qName,
			attrs,
			role, 
			title);
	}

	void XBRLXLinkHandler::endExtendedLink(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
	{
		pImpl->endExtendedLink(namespaceURI, 
			sName,
			qName);
	}

	void XBRLXLinkHandler::startResource(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs, 
		const std::string& role, 
		const std::string& title, 
		const std::string& label)
	{
		pImpl->startResource(namespaceURI,
			lName,
			qName,
			attrs,
			role, 
			title,
			label);
	}

	void XBRLXLinkHandler::endResource(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
	{
		pImpl->endResource(namespaceURI, 
			sName, 
			qName);
	}

	void XBRLXLinkHandler::startLocator(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs, 
		const std::string& href, 
		const std::string& role, 
		const std::string& title,
		const std::string& label) 
	{
		pImpl->startLocator(namespaceURI,
			lName,
			qName,
			attrs,
			href,
			role, 
			title,
			label);
	}

	void XBRLXLinkHandler::endLocator(const std::string& namespaceURI, 
		const std::string& sName, 
		const std::string& qName)
	{
		pImpl-> endLocator(namespaceURI,
			sName,
			qName);
	}

	void XBRLXLinkHandler::startArc(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs, 
		const std::string& from, 
		const std::string& to, 
		const std::string& arcrole,
		const std::string& title, 
		const std::string& show, 
		const std::string& actuate)
	{
		pImpl->startArc(namespaceURI, 
			lName, 
			qName,
			attrs, 
			from, 
			to, 
			arcrole,
			title, 
			show, 
			actuate);
	}

	void XBRLXLinkHandler::endArc(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
	{
		pImpl->endArc(namespaceURI, 
			sName, 
			qName);
	}

	void XBRLXLinkHandler::startSimpleLink(
		const std::string& namespaceURI, 
		const std::string& lName,
		const std::string& qName, 
		const xercesc::Attributes& attrs, 
		const std::string& href, 
		const std::string& role,
		const std::string& arcrole, 
		const std::string& title, 
		const std::string& show, 
		const std::string& actuate)
	{
		pImpl->startSimpleLink(namespaceURI, 
			lName,
			qName, 
			attrs, 
			href, 
			role,
			arcrole, 
			title, 
			show, 
			actuate);
	}

	void XBRLXLinkHandler::endSimpleLink(const std::string& namespaceURI, const std::string& sName, const std::string& qName)
	{
		pImpl->endSimpleLink(namespaceURI, 
			sName, 
			qName);
	}

	void XBRLXLinkHandler::setElementState(const ElementState& elementState) 
	{
		pImpl-> setElementState(elementState) ;
	}

	void XBRLXLinkHandler::error(const std::string& namespaceURI, const std::string& lName, const std::string& qName,
		const xercesc::Attributes& attrs,const std::string& message)
	{
		pImpl->error(namespaceURI, 
			lName, 
			qName,
			attrs,
			message);
	}


	void XBRLXLinkHandler::warning(const std::string& namespaceURI, const std::string& lName, const std::string& qName,
		const xercesc::Attributes& attrs,const std::string& message)
	{
		pImpl->warning(namespaceURI, 
			lName, 
			qName,
			attrs,
			message);
	}

	void XBRLXLinkHandler::titleCharacters(char* buf, int offset, int len)
	{
		pImpl->titleCharacters(buf, offset, len);
	}

	void XBRLXLinkHandler::endTitle( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName)
	{
		pImpl->endTitle(namespaceURI, sName, qName);
	}
}

