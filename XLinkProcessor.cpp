#pragma once
#include "XLinkProcessor.h"
#include "CustomLinkRecogniser.h"
#include "XBRLXLinkHandler.h"
#include <stack>
#include <unordered_map>
#include "Constants.h"
#include "XercesString.h"
#include <xercesc/util/XMLChar.hpp>


/**
* XLink 1.1 processor for use with SAX parsers.

* @author Henry S. Thompson (ht@w3.org)
*/


namespace xbrlcapi
{

	struct XLinkProcessor::Impl  //, Serializable 
	{
		XLinkHandler xlinkHandler;
		CustomLinkRecogniser customLinkRecogniser;
		std::stack<int> ancestorTypes;
		bool insideAnExtendedLink;
		std::unordered_map<const XMLCh*,int> xlinkAttrs;
		const static int SIMPLE_LINK = 1;
		const static int EXTENDED_LINK = 2;
		const static int CUSTOM_LINK = 4;
		const static int RESOURCE = 8;
		const static int LOCATOR = 16;
		const static int ARC = 32;
		const static int TITLE = 64;
		const static int NOT_XLINK=  0;

		Impl() {}

		Impl(const XLinkHandler& xlinkHandler)
		{
			initialize(xlinkHandler);
		}

		Impl(const XLinkHandler& xlinkHandler, CustomLinkRecogniser& recogniser) 
		{
			initialize(xlinkHandler);
			setCustomLinkRecogniser(recogniser);
		}

		void setCustomLinkRecogniser(CustomLinkRecogniser& clr) 
		{
			customLinkRecogniser = clr;
		}

		void initialize(const XLinkHandler& xlinkHandler) 
		{
			this->xlinkHandler = xlinkHandler; 
			insideAnExtendedLink = false;
			ancestorTypes.push(NOT_XLINK);
			if ( xlinkAttrs.empty() ) 
			{
				xlinkAttrs.insert(std::make_pair(L"type",-1));
				xlinkAttrs.insert(std::make_pair(L"href",	SIMPLE_LINK + LOCATOR));
				xlinkAttrs.insert(std::make_pair(L"role",	SIMPLE_LINK + EXTENDED_LINK + LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair(L"arcrole",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair(L"title",	SIMPLE_LINK + EXTENDED_LINK + ARC + LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair(L"show",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair(L"actuate",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair(L"label",	LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair(L"from",	ARC));
				xlinkAttrs.insert(std::make_pair(L"to",		ARC));
			}
		}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{
			// Handle the XML Base attribute on the element (even when it does not exist or has "" value)
			xlinkHandler.xmlBaseStart(attrs.getValue(XS(XMLConstants::XMLNamespace),XS("base")));

			// Complain about any unexpected attributes in the XLink namespace.
			// Added by Henry S Thompson
			bool hasSomeXLinkAttributes = false;
			for (int i=0; i<attrs.getLength(); i++) {
				if (to_string(attrs.getURI(i)) == XMLConstants::XLinkNamespace) 
				{
					const XMLCh* attributeName = attrs.getLocalName(i);
					if ( xlinkAttrs.find(attributeName) != xlinkAttrs.end() ) 
					{
						XMLCh message = *attributeName;
						xlinkHandler.error(namespaceURI, 
							lName, 
							qName, 
							attrs, 
							wcscat(&message,L" is not defined in the XLink namespace."));
					} 
					else 
					{
						hasSomeXLinkAttributes = true;
					}
				}
			}


			// Handle any custom links
			//	if (! (customLinkRecogniser == null))
			if (customLinkRecogniser.isLink(namespaceURI, lName, qName, attrs)) 
			{

				//		logger.debug("Found a custom link: " + lName);

				const XMLCh* href = customLinkRecogniser.getHref(namespaceURI, lName, qName, attrs);
				const XMLCh* role = customLinkRecogniser.getRole(namespaceURI, lName, qName, attrs);
				const XMLCh* arcrole = customLinkRecogniser.getArcrole(namespaceURI, lName, qName, attrs);
				const XMLCh* title = customLinkRecogniser.getTitle(namespaceURI, lName, qName, attrs);
				const XMLCh* show = customLinkRecogniser.getShow(namespaceURI, lName, qName, attrs);
				const XMLCh* actuate = customLinkRecogniser.getActuate(namespaceURI, lName, qName, attrs);

				validateHref(namespaceURI,lName,qName,attrs,href);
				validateRole(namespaceURI,lName,qName,attrs,role);
				validateArcrole(namespaceURI,lName,qName,attrs,arcrole);
				validateShow(namespaceURI,lName,qName,attrs,show);
				validateActuate(namespaceURI,lName,qName,attrs,actuate);
				xlinkHandler.startSimpleLink(namespaceURI, lName, qName, attrs,href,role,arcrole,title,show,actuate);
				ancestorTypes.push(NOT_XLINK);
				return;
			}

			// Try to get XLink attribute values directly from the set of attributes on the element
			const XMLCh* href = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"href");
			const XMLCh* role = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"role");
			const XMLCh* arcrole = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"arcrole");
			const XMLCh* from = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"from");
			const XMLCh* to = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"to");
			const XMLCh* title = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"title");
			const XMLCh* show = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"show");
			const XMLCh* actuate = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"actuate");
			const XMLCh* label = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"label");
			const XMLCh* type = attrs.getValue(XS(XMLConstants::XLinkNamespace), L"type");        

			// Handle elements that are explicitly not XLink elements
			if (type != L"") 
			{
				if (type == L"none") 
				{
					ancestorTypes.push(NOT_XLINK);
					return; // We definitely do not have any XLink meaning for this element.
				}
			}

			// If not an XLink element, handle accordingly.
			// Improved by Henry S Thompson
			if (type != L"") 
			{
				if (href == L"none") 
				{
					ancestorTypes.push(NOT_XLINK);
					// Throw an error if real XLink attributes are used but 
					// the xlink:type or xlink:href attributes are missing.
					if (hasSomeXLinkAttributes) 
					{
						xlinkHandler.error(
							namespaceURI,
							lName,
							qName,
							attrs,
							L"Attributes in the XLink namespace must be accompanied by xlink:type and/or xlink:href attributes");
					}
					return;
				} 
				// XLink 1.1 says we default to 'simple' if xlink:type is missing but xlink:href is present
				type = L"simple";
			}

			// We have a potential XLink element
			// Improved by Henry S Thompson
			if (type == L"simple") 
			{

				if (isXLink(namespaceURI, lName, qName, attrs,SIMPLE_LINK) &&
					validateHref(namespaceURI,lName,qName,attrs,href) &&
					validateRole(namespaceURI,lName,qName,attrs,role) &&
					validateArcrole(namespaceURI,lName,qName,attrs,arcrole) &&
					validateShow(namespaceURI,lName,qName,attrs,show) &&
					validateActuate(namespaceURI,lName,qName,attrs,actuate)) 
				{

					ancestorTypes.push(SIMPLE_LINK);
					xlinkHandler.startSimpleLink(namespaceURI, lName, qName, attrs,
						href,role,arcrole,title,show,actuate
						);
				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}           

			} 
			else if (type == L"extended")
			{

				if (isXLink(namespaceURI, lName, qName, attrs,EXTENDED_LINK) &&
					validateRole(namespaceURI,lName,qName,attrs,role)) 
				{

					insideAnExtendedLink = true;
					ancestorTypes.push(EXTENDED_LINK);
					xlinkHandler.startExtendedLink(namespaceURI, lName, qName, attrs,
						role,title
						);              
				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}

			} 
			else if (type == L"locator")
			{

				if (isXLink(namespaceURI, lName, qName, attrs,LOCATOR) &&
					validateHref(namespaceURI,lName,qName,attrs,href) &&
					validateRole(namespaceURI,lName,qName,attrs,role) &&
					validateLabel(namespaceURI,lName,qName,attrs,label)) 
				{

					ancestorTypes.push(LOCATOR);
					xlinkHandler.startLocator(namespaceURI, lName, qName, attrs,href,role,title,label);
				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}

			} 
			else if (type == L"arc")
			{

				if (isXLink(namespaceURI, lName, qName, attrs,ARC) &&
					validateLabel(namespaceURI,lName,qName,attrs,from) &&
					validateLabel(namespaceURI,lName,qName,attrs,to) &&
					validateArcrole(namespaceURI,lName,qName,attrs,arcrole) &&
					validateShow(namespaceURI,lName,qName,attrs,show) &&
					validateActuate(namespaceURI,lName,qName,attrs,actuate)) {

						ancestorTypes.push(ARC);
						xlinkHandler.startArc(namespaceURI, lName, qName, attrs,from,to,arcrole,title,show,actuate);              

				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}

			} 
			else if (type == L"resource")
			{

				if (isXLink(namespaceURI, lName, qName, attrs,RESOURCE) &&
					validateLabel(namespaceURI,lName,qName,attrs,label) &&
					validateRole(namespaceURI,lName,qName,attrs,role)) {

						ancestorTypes.push(RESOURCE);
						xlinkHandler.startResource(namespaceURI, lName, qName, attrs,role,title,label);
				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}

			} 
			else if (type == L"title")
			{

				if (isXLink(namespaceURI, lName, qName, attrs,TITLE)) 
				{
					ancestorTypes.push(TITLE);              
					xlinkHandler.startTitle(namespaceURI, lName, qName, attrs);
				} 
				else 
				{
					ancestorTypes.push(NOT_XLINK);
				}

				// XLink type attributes with a value of none should generate a warning
				// because they are not doing anything, even though they are valid.
			} 
			else if (type == L"none")
			{
				ancestorTypes.push(NOT_XLINK);

				// Any other value of the xlink type attribute is an error
			} 
			else 
			{
				xlinkHandler.error(namespaceURI, 
					lName, 
					qName, 
					attrs,
					L"The XLink type attribute must take one of the following values: extended, simple, locator, arc, resource or title or none.");
				ancestorTypes.push(NOT_XLINK);
			}

		}

		///**
		//* Tests if an XLink type element is really appropriate to give XLink semantics.
		//* When this test is run, the element can be not an XLink element if it has
		//* the wrong kinds of XLink attributes or if it has the wrong ancestor elements.
		//* Also has side effects of tracking the XLink ancestors seen so far in the
		//* XML tree ancestor path and tracking the type of element (XLink or otherwise
		//* that is the parent of this element).
		//* @param namespaceURI The namespace of the element
		//* @param lName The local name of the element
		//* @param qName The QName of the element
		//* @param attrs The attributes of the element
		//* @param type The XLink type of the element
		//* @return true if the Element is an XLink element.
		//* @throws XLinkException
		//*/
		bool isXLink( const XMLCh* const namespaceURI,  const XMLCh* lName,  const XMLCh* qName,
			const xercesc::Attributes& attrs, int type) 
		{

			int parentType = ancestorTypes.top();

			bool OK = true;
			// Complain about any inappropriate attributes in the xlink namespace
			// Contributed by Henry S Thompson
			for (int i=0; i<attrs.getLength(); i++) 
			{

				if (attrs.getURI(i) == XS(XMLConstants::XLinkNamespace))
				{

					const XMLCh* attributeName = attrs.getLocalName(i);
					auto allowed = xlinkAttrs.find(attributeName);
					// if the attribute is allowed for this XLink element type
					if ( allowed != xlinkAttrs.end() ) 
					{
						XMLCh message = *attributeName;
						xlinkHandler.error(
							namespaceURI,
							lName,
							qName,
							attrs,
							wcscat(&message,L" attribute not allowed for this type of XLink."));
						OK = false;
					}
				}
			}


			// Extended links cannot contain simple links or extended links
			if (insideAnExtendedLink)
				if (type == SIMPLE_LINK || type == EXTENDED_LINK) 
				{

					xlinkHandler.warning(
						namespaceURI,
						lName,
						qName,
						attrs,
						L"Simple and extended links have no XLink meaning when nexted in an extended link.");
					return false;
				}

				// Locators, resources and arcs must be children of extended links
				if (parentType != EXTENDED_LINK)
					if (type == LOCATOR || type == ARC || type == RESOURCE) 
					{

						xlinkHandler.warning(
							namespaceURI,
							lName,
							qName,
							attrs,
							L"Arcs, locators and resources only have XLink semantics when they are children of extended link elements.");
						return false;
					}

					// Title types only imply XLink title elements when children of extended links, locators or arcs.
					if (parentType == NOT_XLINK || parentType == RESOURCE || parentType == SIMPLE_LINK || parentType == TITLE)
						if (type == TITLE) 
						{

							xlinkHandler.warning(
								namespaceURI,
								lName,
								qName,
								attrs,
								L"Titles only have XLink semantics when they are children of extended links, locators or arcs.");
							return false;
						}

						return OK;

		}

		/**
		* Checks that the href attribute has a value.
		* Note that checking that the value is a valid URI reference
		* after escaping of disallowed characters, is not required by
		* the XLink specification.  
		* TODO figure out how to test URI reference validity of XLink hrefs.
		* @param value
		* @return true if the parameter is valid.
		* @throws XLinkException if the href does not specify a value.
		*/
		bool validateHref( const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* value)
		{

			if (value == L"") 
			{

				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					L"The XLink href attribute must not be empty.");
				return false;
			}
			if (value = L"") 
			{
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					L"The XLink href attribute must be provided on a locator.");
				return false;
			}
			return true;
		}

		/**
		* The role attribute, if supplied, must be an absolute URI
		* @param value
		* @return true if the parameter is valid.
		* @throws XLinkException if the role is not an absolute URI
		*/
		bool validateRole(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const Attributes& attrs,
			const XMLCh* value)
		{

			if (value == L"") return true;
			//try 
			//{

			Poco::URI uri(to_string(value));
			if (uri.isRelative()) 
			{
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					L"The XLink role must be an absolute URI");
				return false;
			}
			return true;
			//} catch (URISyntaxException e) 
			//{
			//	xlinkHandler.error(namespaceURI,
			//		lName,
			//		qName,
			//		attrs,
			//		L"The XLink role must have valid URI syntax");
			//	return false;
			//}
		}

		/**
		* The arcrole attribute, if supplied, must be an absolute URI
		* @param value
		* @return true if the parameter is valid.
		* @throws XLinkException if the arcrole is not an absolute URI
		*/
		bool validateArcrole( 
			const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* value)
		{

			if (value == L"") return true;
			//try 
			//{

			Poco::URI uri(to_string(value));
			if (uri.isRelative()) 
			{
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					L"The XLink role must be an absolute URI");
				return false;
			}
			return true;
			//} catch (URISyntaxException e) 
			//{
			//	xlinkHandler.error(namespaceURI,
			//		lName,
			//		qName,
			//		attrs,
			//		L"The XLink role must be an absolute URI");
			//	return false;
			//}
		}

		/**
		* Labels must be NCNames if provided.
		* Uses the Apache XML11Chars to test validity.
		* @param value The value of the label attribute
		* @return true if the parameter is valid.
		* @throws XLinkException
		*/
		bool validateLabel( 
			const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* value)
		{

			if (value == L"") return true;
			if (! XMLChar1_1::isValidNCName(value, sizeof(value))) 
			{
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					L"The XLink label must be an NCName.");
				return false;
			}
			return true;
		}

		/**
		* Show attributes must take one of a the values, new
		* replace, embed, other or none if supplied.
		* @param value
		* @return true if the parameter is valid.
		* @throws XLinkException
		*/
		bool validateShow( 
			const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* value)
		{
			if (value == L"") return true;
			if (
				(value != L"new") && 
				(value != L"replace") && 
				(value != L"embed") && 
				(value != L"other") && 
				(value != L"none")
				)
			{
				XMLCh* message = L"If supplied, the XLink show attribute must be one of new, replace, embed, other or none. Instead it was ";
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					wcscat(message, value));
				return false;
			}
			return true;
		}

		/**
		* Actuate attributes must take one of the values: onLoad, onRequest
		* other or none if supplied.
		* @param value
		* @return true if the parameter is valid.
		* @throws XLinkException
		*/
		bool validateActuate(
			const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* value)
		{

			if (value == L"") return true;
			if (
				(value != L"onLoad") && 
				(value != L"onRequest") && 
				(value != L"other") && 
				(value != L"none")
				)
			{
				XMLCh* message = L"If supplied, the XLink actuate attribute must be one of onLoad, onRequest, other or none.  Instead it was ";
				xlinkHandler.error(namespaceURI,
					lName,
					qName,
					attrs,
					wcscat(message,value));
				return false;
			}
			return true;
		}

		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{
			//xlinkHandler.xmlBaseEnd();
			//Integer parentType = ancestorTypes.pop();

			//// Handle any custom links
			//if (! (customLinkRecogniser == null))
			//	if (customLinkRecogniser.isLink(namespaceURI, lName, qName, attrs)) {
			//		xlinkHandler.endSimpleLink(namespaceURI, lName, qName);
			//		return;
			//	}

			//	// If not an XLink Type element then we are done.
			//	if (parentType.equals(NOT_XLINK))
			//		return;

			//	// We have an XLink element so find which one
			//	if (parentType.equals(SIMPLE_LINK)) {
			//		xlinkHandler.endSimpleLink(namespaceURI, lName, qName);
			//	} else if (parentType.equals(EXTENDED_LINK)) {
			//		xlinkHandler.endExtendedLink(namespaceURI, lName, qName);
			//		insideAnExtendedLink = false;
			//	} else if (parentType.equals(RESOURCE)) {
			//		xlinkHandler.endResource(namespaceURI, lName, qName);
			//	} else if (parentType.equals(LOCATOR)) {
			//		xlinkHandler.endLocator(namespaceURI, lName, qName);
			//	} else if (parentType.equals(ARC)) {
			//		xlinkHandler.endArc(namespaceURI, lName, qName);
			//	} else if (parentType.equals(TITLE)) {
			//		xlinkHandler.endTitle(namespaceURI, lName, qName);
			//	}       
		}   

		///**
		//* @see org.xbrlapi.xlink.XLinkProcessor#titleCharacters(char[], int, int)
		//*/
		//public void titleCharacters(char[] buf, int offset, int len)
		//	throws XLinkException {
		//		if ((ancestorTypes.peek()).equals(TITLE)) {
		//			xlinkHandler.titleCharacters(buf, offset, len);
		//		}
		//}

		XLinkHandler getXLinkHandler() 
		{
			return xlinkHandler;
		}



		///**
		//* Handles object inflation.
		//* @param in The input object stream used to access the object's serialization.
		//* @throws IOException
		//* @throws ClassNotFoundException
		//*/
		//private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		//	in.defaultReadObject( );
		//	initialize(this.getXLinkHandler());
		//}

	};

	XLinkProcessor::XLinkProcessor() {}
	XLinkProcessor::~XLinkProcessor() {} 
	XLinkProcessor::XLinkProcessor(const XLinkProcessor& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XLinkProcessor& XLinkProcessor::operator=(const XLinkProcessor& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}
	XLinkProcessor::XLinkProcessor(XLinkProcessor&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XLinkProcessor::XLinkProcessor(const XLinkHandler& xlh, CustomLinkRecogniser& clr) : pImpl(xlh, clr)
	{}

	XLinkProcessor& XLinkProcessor::operator=(XLinkProcessor&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XLinkProcessor::operator==(const XLinkProcessor& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XLinkProcessor::operator!=(const XLinkProcessor& rhs)
	{
		return !this->operator==(rhs);
	}

	//   public void setCustomLinkRecogniser(CustomLinkRecogniser customLinkRecogniser);

	void XLinkProcessor::startElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(namespaceURI, lName, qName, attrs);
	}

	void XLinkProcessor::endElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(namespaceURI, lName, qName, attrs);
	}


	//public void titleCharacters(char buf[], int offset, int len) throws XLinkException;
	XLinkHandler XLinkProcessor::getXLinkHandler()
	{
		return pImpl->getXLinkHandler();
	}
}
