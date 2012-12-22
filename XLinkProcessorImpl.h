

#pragma once
#include "Logger.h"
#include <stack>
#include <unordered_map>


/**
* XLink 1.1 processor for use with SAX parsers.

* @author Henry S. Thompson (ht@w3.org)
*/

#include "CustomLinkRecogniser.h"
#include "XLinkHandler.h"

namespace xbrlcapi
{

	class XLinkProcessorImpl  //, Serializable 
	{

		///**
		//* 
		//*/


		///**
		//* The XLink handler to use for responding to XLink events
		//* in the SAX parsing process.
		//*/
	private:
		XLinkHandler xlinkHandler;

		/**
		* The Custom Link Recogniser, to be used for simple link
		* syntaxes that are not specified by the XLink specification
		* but need to be processed by the XLink processor.
		* Set to null by default for cases where no non-XLink 
		* syntax needs to be treated as a link.
		*/
		CustomLinkRecogniser customLinkRecogniser;

		///**
		//* Track the type of XLink element or other element that
		//* is the parent of the element being currently handled.
		//* This is important for the implementation of the
		//* elementStart functionality. 
		//*/
		//transient 
		std::stack<int> ancestorTypes;

		///**
		//* bool to track whether we are inside an extended
		//* link.  Note that it is not possible to have nested
		//* extended links so this does not need to be a stack.
		//*/
		//transient private bool insideAnExtendedLink = false;

		///**
		//* Hash map to store information about 
		//* the kinds of elements on which XLink attributes
		//* can be expected to occur. (Documentation by Geoff Shuetrim)
		//* Property added by Henry S Thompson.
		//*/
		//transient 
		std::unordered_map<std::string,int> xlinkAttrs;

		void initialize(const XLinkHandler& xlinkHandler) 
		{
			//this->xlinkHandler = xlinkHandler; //TODO
			ancestorTypes.push(NOT_XLINK);
			if ( xlinkAttrs.empty() ) 
			{
				xlinkAttrs.insert(std::make_pair("type",-1));
				xlinkAttrs.insert(std::make_pair("href",	SIMPLE_LINK + LOCATOR));
				xlinkAttrs.insert(std::make_pair("role",	SIMPLE_LINK + EXTENDED_LINK + LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair("arcrole",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair("title",	SIMPLE_LINK + EXTENDED_LINK + ARC + LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair("show",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair("actuate",	SIMPLE_LINK + ARC));
				xlinkAttrs.insert(std::make_pair("label",	LOCATOR + RESOURCE));
				xlinkAttrs.insert(std::make_pair("from",	ARC));
				xlinkAttrs.insert(std::make_pair("to",		ARC));
			}

		}
	public:
		/**
		* constructor
		* @param xlinkHandler The XLink Handler
		*/
		XLinkProcessorImpl(XLinkHandler& xlinkHandler)
		{
			initialize(xlinkHandler);
		}

		/**
		* copy constructor
		* ToDo: implement
		*/
		//		XLinkProcessorImpl(XLinkProcessorImpl&& rhs) = default;

		//		XLinkProcessorImpl& operator=(XLinkProcessorImpl& rhs) = default

		/**
		* constructor
		* @param xlinkHandler The XLink Handler.
		* @param recogniser The Custom link recogniser.
		*/
		XLinkProcessorImpl(XLinkHandler& xlinkHandler, CustomLinkRecogniser& recogniser) 
		{
			initialize(xlinkHandler);
			setCustomLinkRecogniser(recogniser);
		}

		/**
		* assignment operator
		* Todo: implement later
		*/
		XLinkProcessorImpl& operator=(const XLinkProcessorImpl& rhs)
		{
			return *this;
		}
		/**
		* Set the custom link recogniser
		* @param customLinkRecogniser The class that indicates if a custom link
		* has been recognised.
		*/
		void setCustomLinkRecogniser(CustomLinkRecogniser& clr) 
		{
			customLinkRecogniser = std::move(clr);
		}
		const static int SIMPLE_LINK = 1;
		const static int EXTENDED_LINK = 2;
		const static int CUSTOM_LINK = 4;
		const static int RESOURCE = 8;
		const static int LOCATOR = 16;
		const static int ARC = 32;
		const static int TITLE = 64;
		const static int NOT_XLINK=  0;


		///**
		//* @see org.xbrlapi.xlink.XLinkProcessor#startElement(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes)
		//*/
		//public void startElement( std::string namespaceURI,  std::string lName,  std::string qName, Attributes attrs) throws XLinkException {

		//	// Handle the XML Base attribute on the element (even when it does not exist or has "" value)
		//	xlinkHandler.xmlBaseStart(attrs.getValue(Constants.XMLNamespace.toString(),"base"));

		//	// Complain about any unexpected attributes in the XLink namespace.
		//	// Added by Henry S Thompson
		//	bool hasSomeXLinkAttributes = false;
		//	for (int i=0; i<attrs.getLength(); i++) {
		//		if (attrs.getURI(i).equals(Constants.XLinkNamespace.toString())) {
		//			 std::string attributeName = attrs.getLocalName(i);
		//			if (! XLINKATTRS.containsKey(attributeName)) {
		//				xlinkHandler.error(namespaceURI, lName, qName, attrs, attributeName + " is not defined in the XLink namespace.");
		//			} else {
		//				hasSomeXLinkAttributes = true;
		//			}
		//		}
		//	}

		//	// Handle any custom links
		//	if (! (customLinkRecogniser == null))
		//		if (customLinkRecogniser.isLink(namespaceURI, lName, qName, attrs)) {

		//			logger.debug("Found a custom link: " + lName);

		//			 std::string href = customLinkRecogniser.getHref(namespaceURI, lName, qName, attrs);
		//			 std::string role = customLinkRecogniser.getRole(namespaceURI, lName, qName, attrs);
		//			 std::string arcrole = customLinkRecogniser.getArcrole(namespaceURI, lName, qName, attrs);
		//			 std::string title = customLinkRecogniser.getTitle(namespaceURI, lName, qName, attrs);
		//			 std::string show = customLinkRecogniser.getShow(namespaceURI, lName, qName, attrs);
		//			 std::string actuate = customLinkRecogniser.getActuate(namespaceURI, lName, qName, attrs);

		//			validateHref(namespaceURI,lName,qName,attrs,href);
		//			validateRole(namespaceURI,lName,qName,attrs,role);
		//			validateArcrole(namespaceURI,lName,qName,attrs,arcrole);
		//			validateShow(namespaceURI,lName,qName,attrs,show);
		//			validateActuate(namespaceURI,lName,qName,attrs,actuate);

		//			xlinkHandler.startSimpleLink(namespaceURI, lName, qName, attrs,href,role,arcrole,title,show,actuate);
		//			ancestorTypes.push(NOT_XLINK);
		//			return;
		//		}

		//		// Try to get XLink attribute values directly from the set of attributes on the element
		//		 std::string href = attrs.getValue(Constants.XLinkNamespace.toString(), "href");
		//		 std::string role = attrs.getValue(Constants.XLinkNamespace.toString(), "role");
		//		 std::string arcrole = attrs.getValue(Constants.XLinkNamespace.toString(), "arcrole");
		//		 std::string from = attrs.getValue(Constants.XLinkNamespace.toString(), "from");
		//		 std::string to = attrs.getValue(Constants.XLinkNamespace.toString(), "to");
		//		 std::string title = attrs.getValue(Constants.XLinkNamespace.toString(), "title");
		//		 std::string show = attrs.getValue(Constants.XLinkNamespace.toString(), "show");
		//		 std::string actuate = attrs.getValue(Constants.XLinkNamespace.toString(), "actuate");
		//		 std::string label = attrs.getValue(Constants.XLinkNamespace.toString(), "label");
		//		 std::string type = attrs.getValue(Constants.XLinkNamespace.toString(), "type");        

		//		// Handle elements that are explicitly not XLink elements
		//		if (type != null) {
		//			if (type.equals("none")) {
		//				ancestorTypes.push(NOT_XLINK);
		//				return; // We definitely do not have any XLink meaning for this element.
		//			}
		//		}

		//		// If not an XLink element, handle accordingly.
		//		// Improved by Henry S Thompson
		//		if (type == null) {
		//			if (href == null) {
		//				ancestorTypes.push(NOT_XLINK);
		//				// Throw an error if real XLink attributes are used but 
		//				// the xlink:type or xlink:href attributes are missing.
		//				if (hasSomeXLinkAttributes) {
		//					xlinkHandler.error(namespaceURI,lName,qName,attrs,"Attributes in the XLink namespace must be accompanied by xlink:type and/or xlink:href attributes");
		//				}
		//				return;
		//			} 
		//			// XLink 1.1 says we default to 'simple' if xlink:type is missing but xlink:href is present
		//			type = "simple";
		//		}

		//		// We have a potential XLink element
		//		// Improved by Henry S Thompson
		//		if (type.equals("simple")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,SIMPLE_LINK) &&
		//				validateHref(namespaceURI,lName,qName,attrs,href) &&
		//				validateRole(namespaceURI,lName,qName,attrs,role) &&
		//				validateArcrole(namespaceURI,lName,qName,attrs,arcrole) &&
		//				validateShow(namespaceURI,lName,qName,attrs,show) &&
		//				validateActuate(namespaceURI,lName,qName,attrs,actuate)) {

		//					ancestorTypes.push(SIMPLE_LINK);
		//					xlinkHandler.startSimpleLink(namespaceURI, lName, qName, attrs,
		//						href,role,arcrole,title,show,actuate
		//						);
		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}           

		//		} else if (type.equals("extended")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,EXTENDED_LINK) &&
		//				validateRole(namespaceURI,lName,qName,attrs,role)) {

		//					insideAnExtendedLink = true;
		//					ancestorTypes.push(EXTENDED_LINK);
		//					xlinkHandler.startExtendedLink(namespaceURI, lName, qName, attrs,
		//						role,title
		//						);              
		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}

		//		} else if (type.equals("locator")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,LOCATOR) &&
		//				validateHref(namespaceURI,lName,qName,attrs,href) &&
		//				validateRole(namespaceURI,lName,qName,attrs,role) &&
		//				validateLabel(namespaceURI,lName,qName,attrs,label)) {

		//					ancestorTypes.push(LOCATOR);
		//					xlinkHandler.startLocator(namespaceURI, lName, qName, attrs,href,role,title,label);
		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}

		//		} else if (type.equals("arc")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,ARC) &&
		//				validateLabel(namespaceURI,lName,qName,attrs,from) &&
		//				validateLabel(namespaceURI,lName,qName,attrs,to) &&
		//				validateArcrole(namespaceURI,lName,qName,attrs,arcrole) &&
		//				validateShow(namespaceURI,lName,qName,attrs,show) &&
		//				validateActuate(namespaceURI,lName,qName,attrs,actuate)) {

		//					ancestorTypes.push(ARC);
		//					xlinkHandler.startArc(namespaceURI, lName, qName, attrs,from,to,arcrole,title,show,actuate);              

		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}

		//		} else if (type.equals("resource")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,RESOURCE) &&
		//				validateLabel(namespaceURI,lName,qName,attrs,label) &&
		//				validateRole(namespaceURI,lName,qName,attrs,role)) {

		//					ancestorTypes.push(RESOURCE);
		//					xlinkHandler.startResource(namespaceURI, lName, qName, attrs,role,title,label);
		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}

		//		} else if (type.equals("title")) {

		//			if (isXLink(namespaceURI, lName, qName, attrs,TITLE)) {
		//				ancestorTypes.push(TITLE);              
		//				xlinkHandler.startTitle(namespaceURI, lName, qName, attrs);
		//			} else {
		//				ancestorTypes.push(NOT_XLINK);
		//			}

		//			// XLink type attributes with a value of none should generate a warning
		//			// because they are not doing anything, even though they are valid.
		//		} else if (type.equals("none")) {
		//			ancestorTypes.push(NOT_XLINK);

		//			// Any other value of the xlink type attribute is an error
		//		} else {
		//			xlinkHandler.error(namespaceURI, lName, qName, attrs,"The XLink type attribute must take one of the following values: extended, simple, locator, arc, resource or title or none.");
		//			ancestorTypes.push(NOT_XLINK);
		//		}

		//}

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
		//private bool isXLink( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs,Integer type) throws XLinkException {

		//		Integer parentType = ancestorTypes.peek();

		//		bool OK = true;
		//		// Complain about any inappropriate attributes in the xlink namespace
		//		// Contributed by Henry S Thompson
		//		for (int i=0; i<attrs.getLength(); i++) {
		//			if (attrs.getURI(i).equals(Constants.XLinkNamespace.toString())) {
		//				 std::string attributeName = attrs.getLocalName(i);
		//				Integer allowed = XLINKATTRS.get(attributeName);
		//				// if the attribute is allowed for this XLink element type
		//				if ( allowed!=null && ((allowed.intValue()&type.intValue())==0) ) {
		//					xlinkHandler.error(namespaceURI,lName,qName,attrs,attributeName + " attribute not allowed for this type of XLink.");
		//					OK = false;
		//				}
		//			}
		//		}


		//		// Extended links cannot contain simple links or extended links
		//		if (insideAnExtendedLink)
		//			if (type.equals(SIMPLE_LINK) || type.equals(EXTENDED_LINK)) {
		//				xlinkHandler.warning(namespaceURI,lName,qName,attrs,"Simple and extended links have no XLink meaning when nexted in an extended link.");
		//				return false;
		//			}

		//			// Locators, resources and arcs must be children of extended links
		//			if (!parentType.equals(EXTENDED_LINK))
		//				if (type.equals(LOCATOR) || type.equals(ARC) || type.equals(RESOURCE)) {
		//					xlinkHandler.warning(namespaceURI,lName,qName,attrs,"Arcs, locators and resources only have XLink semantics when they are children of extended link elements.");
		//					return false;
		//				}

		//				// Title types only imply XLink title elements when children of extended links, locators or arcs.
		//				if (parentType.equals(NOT_XLINK) || parentType.equals(RESOURCE) || parentType.equals(SIMPLE_LINK) || parentType.equals(TITLE))
		//					if (type.equals(TITLE)) {
		//						xlinkHandler.warning(namespaceURI,lName,qName,attrs,"Titles only have XLink semantics when they are children of extended links, locators or arcs.");
		//						return false;
		//					}

		//					return OK;

		//}

		///**
		//* Checks that the href attribute has a value.
		//* Note that checking that the value is a valid URI reference
		//* after escaping of disallowed characters, is not required by
		//* the XLink specification.  
		//* TODO figure out how to test URI reference validity of XLink hrefs.
		//* @param value
		//* @return true if the parameter is valid.
		//* @throws XLinkException if the href does not specify a value.
		//*/
		//private bool validateHref( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string value) throws XLinkException {
		//		if (value == "") {
		//			xlinkHandler.error(namespaceURI,lName,qName,attrs,"The XLink href attribute must not be empty.");
		//			return false;
		//		}
		//		if (value == null) {
		//			xlinkHandler.error(namespaceURI,lName,qName,attrs,"The XLink href attribute must be provided on a locator.");
		//			return false;
		//		}
		//		return true;
		//}

		///**
		//* The role attribute, if supplied, must be an absolute URI
		//* @param value
		//* @return true if the parameter is valid.
		//* @throws XLinkException if the role is not an absolute URI
		//*/
		//private bool validateRole(
		//	 std::string namespaceURI, 
		//	 std::string lName, 
		//	 std::string qName,
		//	Attributes attrs,
		//	 std::string value) throws XLinkException {
		//		if (value == null) return true;
		//		try {
		//			URI uri = new URI(value);
		//			if (! uri.isAbsolute()) {
		//				xlinkHandler.error(namespaceURI,lName,qName,attrs,"The XLink role must be an absolute URI");
		//				return false;
		//			}
		//			return true;
		//		} catch (URISyntaxException e) {
		//			xlinkHandler.error(namespaceURI,lName,qName,attrs,"The XLink role must have valid URI syntax");
		//			return false;
		//		}
		//}

		///**
		//* The arcrole attribute, if supplied, must be an absolute URI
		//* @param value
		//* @return true if the parameter is valid.
		//* @throws XLinkException if the arcrole is not an absolute URI
		//*/
		//private bool validateArcrole( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string value) throws XLinkException {
		//		if (value == null) return true;
		//		try {           
		//			URI uri = new URI(value);
		//			if (! uri.isAbsolute()) {
		//				xlinkHandler.error(namespaceURI,lName,qName,attrs,"The arcrole must be an absolute URI");
		//				return false;
		//			}
		//			return true;
		//		} catch (URISyntaxException e) {
		//			xlinkHandler.error(namespaceURI,lName,qName,attrs,"The arcrole must be an absolute URI");
		//			return false;
		//		}
		//}

		///**
		//* Labels must be NCNames if provided.
		//* Uses the Apache XML11Chars to test validity.
		//* @param value The value of the label attribute
		//* @return true if the parameter is valid.
		//* @throws XLinkException
		//*/
		//private bool validateLabel( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string value) throws XLinkException {
		//		if (value == null) return true;
		//		if (! XML11Char.isXML11ValidNCName(value)) {
		//			xlinkHandler.error(namespaceURI,lName,qName,attrs,"The XLink label must be an NCName.");
		//			return false;
		//		}
		//		return true;
		//}

		///**
		//* Show attributes must take one of a the values, new
		//* replace, embed, other or none if supplied.
		//* @param value
		//* @return true if the parameter is valid.
		//* @throws XLinkException
		//*/
		//private bool validateShow( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string value) throws XLinkException {
		//		if (value == null) return true;
		//		if (
		//			(!value.equals("new")) && 
		//			(!value.equals("replace")) && 
		//			(!value.equals("embed")) && 
		//			(!value.equals("other")) && 
		//			(!value.equals("none"))
		//			){
		//				xlinkHandler.error(namespaceURI,lName,qName,attrs,"If supplied, the XLink show attribute must be one of new, replace, embed, other or none. Instead it was " + value);
		//				return false;
		//		}
		//		return true;
		//}

		///**
		//* Actuate attributes must take one of the values: onLoad, onRequest
		//* other or none if supplied.
		//* @param value
		//* @return true if the parameter is valid.
		//* @throws XLinkException
		//*/
		//private bool validateActuate( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string value) throws XLinkException {
		//		if (value == null) return true;
		//		if (
		//			(!value.equals("onLoad")) && 
		//			(!value.equals("onRequest")) && 
		//			(!value.equals("other")) && 
		//			(!value.equals("none"))
		//			){
		//				xlinkHandler.error(namespaceURI,lName,qName,attrs,"If supplied, the XLink actuate attribute must be one of onLoad, onRequest, other or none.  Instead it was " + value);
		//				return false;
		//		}
		//		return true;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkProcessor#endElement(String, String, String, Attributes)
		//*/
		//public void endElement( std::string namespaceURI,  std::string lName,  std::string qName, Attributes attrs) throws XLinkException {

		//	xlinkHandler.xmlBaseEnd();
		//	Integer parentType = ancestorTypes.pop();

		//	// Handle any custom links
		//	if (! (customLinkRecogniser == null))
		//		if (customLinkRecogniser.isLink(namespaceURI, lName, qName, attrs)) {
		//			xlinkHandler.endSimpleLink(namespaceURI, lName, qName);
		//			return;
		//		}

		//		// If not an XLink Type element then we are done.
		//		if (parentType.equals(NOT_XLINK))
		//			return;

		//		// We have an XLink element so find which one
		//		if (parentType.equals(SIMPLE_LINK)) {
		//			xlinkHandler.endSimpleLink(namespaceURI, lName, qName);
		//		} else if (parentType.equals(EXTENDED_LINK)) {
		//			xlinkHandler.endExtendedLink(namespaceURI, lName, qName);
		//			insideAnExtendedLink = false;
		//		} else if (parentType.equals(RESOURCE)) {
		//			xlinkHandler.endResource(namespaceURI, lName, qName);
		//		} else if (parentType.equals(LOCATOR)) {
		//			xlinkHandler.endLocator(namespaceURI, lName, qName);
		//		} else if (parentType.equals(ARC)) {
		//			xlinkHandler.endArc(namespaceURI, lName, qName);
		//		} else if (parentType.equals(TITLE)) {
		//			xlinkHandler.endTitle(namespaceURI, lName, qName);
		//		}       
		//}   

		///**
		//* @see org.xbrlapi.xlink.XLinkProcessor#titleCharacters(char[], int, int)
		//*/
		//public void titleCharacters(char[] buf, int offset, int len)
		//	throws XLinkException {
		//		if ((ancestorTypes.peek()).equals(TITLE)) {
		//			xlinkHandler.titleCharacters(buf, offset, len);
		//		}
		//}

		///**
		//* Provides access to the XLink handler being used by the XLink processor.
		//* @return the XLink handler being used by the XLink processor.
		//*/
		//public XLinkHandler getXLinkHandler() {
		//	return xlinkHandler;
		//}



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

		///**
		//* @see java.lang.Object#hashCode()
		//*/
		//@Override
		//	public int hashCode() {
		//		final int prime = 31;
		//		int result = 1;
		//		result = prime
		//			* result
		//			+ ((customLinkRecogniser == null) ? 0 : customLinkRecogniser.hashCode());
		//		result = prime * result
		//			+ ((xlinkHandler == null) ? 0 : xlinkHandler.hashCode());
		//		return result;
		//}

		///**
		//* @see java.lang.Object#equals(java.lang.Object)
		//*/
		//@Override
		//	public bool equals(Object obj) {
		//		if (this == obj)
		//			return true;
		//		if (obj == null)
		//			return false;
		//		if (getClass() != obj.getClass())
		//			return false;
		//		XLinkProcessorImpl other = (XLinkProcessorImpl) obj;
		//		if (customLinkRecogniser == null) {
		//			if (other.customLinkRecogniser != null)
		//				return false;
		//		} else if (!customLinkRecogniser.equals(other.customLinkRecogniser))
		//			return false;
		//		if (xlinkHandler == null) {
		//			if (other.xlinkHandler != null)
		//				return false;
		//		} else if (!xlinkHandler.equals(other.xlinkHandler))
		//			return false;
		//		return true;
		//}

	private:
		Logger logger;
	};
}
