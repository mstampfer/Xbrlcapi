#pragma once

#include <memory>

#include "Loader.h"
#include "XBRLXLinkHandler.h"
#include "BaseURISAXResolver.h"
#include "ElementState.h"
#include "XLinkException.h"
#include "XBRLException.h"
//#include "XMLBaseException.h"

namespace xbrlcapi
{

	struct XLinkHandler::Impl 
	{
		//Loader loader;

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

		//void setLoader(const Loader& loader) 
		//{
		//	this->loader = loader;
		//}

		void setBaseURISAXResolver(const BaseURISAXResolver& resolver)
		{
			baseURIResolver = resolver;
		}

		void xmlBaseStart(const XMLCh* value)
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


		void startTitle(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
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
			const XMLCh* namespaceURI, 
			const XMLCh* lName,
			const XMLCh* qName, 
			const xercesc::Attributes& attrs, 
			const XMLCh* role, 
			const XMLCh* title)
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

		void endExtendedLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
		{}

		void startResource(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* role, 
			const XMLCh* title, 
			const XMLCh* label)
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

		void endResource(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
		{}

		void startLocator(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* href, 
			const XMLCh* role, 
			const XMLCh* title,
			const XMLCh* label) 
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

		void endLocator(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
		{}

		void startArc(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* from, 
			const XMLCh* to, 
			const XMLCh* arcrole,
			const XMLCh* title, 
			const XMLCh* show, 
			const XMLCh* actuate)
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

		void endArc(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
		{}

		void startSimpleLink(
			const XMLCh* namespaceURI, 
			const XMLCh* lName,
			const XMLCh* qName, 
			const xercesc::Attributes& attrs, 
			const XMLCh* href, 
			const XMLCh* role,
			const XMLCh* arcrole, 
			const XMLCh* title, 
			const XMLCh* show, 
			const XMLCh* actuate)
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

		void endSimpleLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
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

		void error(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
			const xercesc::Attributes& attrs,const XMLCh* message)
		{

			//if (message.endsWith(" is not defined in the XLink namespace.")) 
			//{
			//	this->warning(namespaceURI, lName, qName, attrs, message);
			//	return;
			//}

			//throw XLinkException(message);
		}


		void warning(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
			const xercesc::Attributes& attrs,const XMLCh* message)
		{
			//logger.warn(message);
		}

		void titleCharacters(char* buf, int offset, int len)
		{
			// not implemented

		}

		void endTitle( const XMLCh* namespaceURI, 
			const XMLCh* sName, 
			const XMLCh* qName)
		{
			//not Implemeted
		}

	};

	XLinkHandler::XLinkHandler() {}
	XLinkHandler::~XLinkHandler() {} 

	XLinkHandler::XLinkHandler(const XLinkHandler& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XLinkHandler& XLinkHandler::operator=(const XLinkHandler& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XLinkHandler::XLinkHandler(XLinkHandler&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XLinkHandler& XLinkHandler::operator=(XLinkHandler&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XLinkHandler::operator==(const XLinkHandler& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XLinkHandler::operator!=(const XLinkHandler& rhs)
	{
		return !this->operator==(rhs);
	}

	//void XLinkHandler::setLoader(const Loader& loader) 
	//{
	//	pImpl-> setLoader(loader);
	//}

	void XLinkHandler::setBaseURISAXResolver(const BaseURISAXResolver& resolver)
	{
		pImpl->setBaseURISAXResolver(resolver);
	}

	void XLinkHandler::xmlBaseStart(const XMLCh* value)
	{
		pImpl->xmlBaseStart(value);
	}


	void XLinkHandler::startTitle(const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl-> startTitle(namespaceURI,
			lName,
			qName,
			attrs);
	}


	void XLinkHandler::xmlBaseEnd()
	{
		pImpl->xmlBaseEnd();
	}


	void XLinkHandler::startExtendedLink(
		const XMLCh* namespaceURI, 
		const XMLCh* lName,
		const XMLCh* qName, 
		const xercesc::Attributes& attrs, 
		const XMLCh* role, 
		const XMLCh* title)
	{
		pImpl-> startExtendedLink(namespaceURI,
			lName,
			qName,
			attrs,
			role, 
			title);
	}

	void XLinkHandler::endExtendedLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
	{
		pImpl->endExtendedLink(namespaceURI, 
			sName,
			qName);
	}

	void XLinkHandler::startResource(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs, 
		const XMLCh* role, 
		const XMLCh* title, 
		const XMLCh* label)
	{
		pImpl->startResource(namespaceURI,
			lName,
			qName,
			attrs,
			role, 
			title,
			label);
	}

	void XLinkHandler::endResource(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
	{
		pImpl->endResource(namespaceURI, 
			sName, 
			qName);
	}

	void XLinkHandler::startLocator(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs, 
		const XMLCh* href, 
		const XMLCh* role, 
		const XMLCh* title,
		const XMLCh* label) 
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

	void XLinkHandler::endLocator(const XMLCh* namespaceURI, 
		const XMLCh* sName, 
		const XMLCh* qName)
	{
		pImpl-> endLocator(namespaceURI,
			sName,
			qName);
	}

	void XLinkHandler::startArc(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs, 
		const XMLCh* from, 
		const XMLCh* to, 
		const XMLCh* arcrole,
		const XMLCh* title, 
		const XMLCh* show, 
		const XMLCh* actuate)
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

	void XLinkHandler::endArc(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
	{
		pImpl->endArc(namespaceURI, 
			sName, 
			qName);
	}

	void XLinkHandler::startSimpleLink(
		const XMLCh* namespaceURI, 
		const XMLCh* lName,
		const XMLCh* qName, 
		const xercesc::Attributes& attrs, 
		const XMLCh* href, 
		const XMLCh* role,
		const XMLCh* arcrole, 
		const XMLCh* title, 
		const XMLCh* show, 
		const XMLCh* actuate)
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

	void XLinkHandler::endSimpleLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName)
	{
		pImpl->endSimpleLink(namespaceURI, 
			sName, 
			qName);
	}

	void XLinkHandler::setElementState(const ElementState& elementState) 
	{
		pImpl-> setElementState(elementState) ;
	}

	void XLinkHandler::error(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
		const xercesc::Attributes& attrs,const XMLCh* message)
	{
		pImpl->error(namespaceURI, 
			lName, 
			qName,
			attrs,
			message);
	}


	void XLinkHandler::warning(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
		const xercesc::Attributes& attrs,const XMLCh* message)
	{
		pImpl->warning(namespaceURI, 
			lName, 
			qName,
			attrs,
			message);
	}

	void XLinkHandler::titleCharacters(char* buf, int offset, int len)
	{
		pImpl->titleCharacters(buf, offset, len);
	}

	void XLinkHandler::endTitle( const XMLCh* namespaceURI, 
		const XMLCh* sName, 
		const XMLCh* qName)
	{
		pImpl->endTitle(namespaceURI, sName, qName);
	}
}

