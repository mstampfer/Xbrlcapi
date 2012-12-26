

#pragma once
#include "XLinkHandler.h"

/**
* Default XLinkHandler implementation, does nothing for any of the events.
* Extend this class to create your own XLinkHandler.

*/

namespace xbrlcapi
{
	class XLinkHandlerDefaultImpl : public XLinkHandler//, Serializable 
	{

		///**
		//* 
		//*/

		/**
		* Default XLink handler constructor
		*/
	public:
		XLinkHandlerDefaultImpl() 
		{
			XLinkHandler();
		}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startSimpleLink(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void startSimpleLink( std::string namespaceURI,  std::string lName,
		//	 std::string qName, Attributes attrs,  std::string href,  std::string role,
		//	 std::string arcrole,  std::string title,  std::string show,  std::string actuate)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endSimpleLink(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endSimpleLink( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startTitle(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes)
		//*/
		//public void startTitle( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs) throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endTitle(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endTitle( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#titleCharacters(char[], int, int)
		//*/
		//public void titleCharacters(char[] buf, int offset, int len)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startExtendedLink(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String)
		//*/
		//public void startExtendedLink( std::string namespaceURI,  std::string lName,
		//	 std::string qName, Attributes attrs,  std::string role,  std::string title)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endExtendedLink(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endExtendedLink( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startResource(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void startResource( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs,  std::string role,  std::string title,  std::string label)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endResource(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endResource( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startLocator(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void startLocator( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs,  std::string href,  std::string role,  std::string title,
		//	 std::string label) throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endLocator(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endLocator( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#startArc(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void startArc( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs,  std::string from,  std::string to,  std::string arcrole,
		//	 std::string title,  std::string show,  std::string actuate) throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#endArc(java.lang.String, java.lang.String, java.lang.String)
		//*/
		//public void endArc( std::string namespaceURI,  std::string sName,  std::string qName)
		//	throws XLinkException {
		//		;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#xmlBaseStart(java.lang.String)
		//*/
		//public void xmlBaseStart( std::string value) throws XLinkException {
		//	;
		//}

		///**
		//* @see org.xbrlapi.xlink.XLinkHandler#xmlBaseEnd()
		//*/
		//public void xmlBaseEnd() throws XLinkException {
		//	;
		//}

		///**
		//* Default error behaviour is to throw an XLink Exception
		//* @see org.xbrlapi.xlink.XLinkHandler#error(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		//*/
		//public void error( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string message) throws XLinkException {
		//		throw new XLinkException(message);
		//}

		///**
		//* Default warning behaviour is to ignore the warning
		//* @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		//*/
		//public void warning( std::string namespaceURI,  std::string lName,  std::string qName,
		//	Attributes attrs, std::string message) throws XLinkException {
		//		;
		//}

		///**
		//* @see java.lang.Object#hashCode()
		//*/
		//@Override
		//	public int hashCode() {
		//		return 1;
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
		//		return true;
		//}
	};
}

