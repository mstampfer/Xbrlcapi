#pragma once
#include "XLinkHandler.h"
#include <string>
#include <xercesc/sax2/Attributes.hpp>

/**
* Default XLinkHandler implementation, does nothing for any of the events.
* Extend this class to create your own XLinkHandler.
*/

namespace xbrlcapi

{
	class XLinkHandlerDefault : public XLinkHandler

	{
		/**
		* Default XLink handler constructor
		*/
	public:
		XLinkHandlerDefault() 
		{}

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startSimpleLink(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void startSimpleLink( const std::string& namespaceURI, 
			const std::string& lName,
			const std::string& qName, 
			const xercesc::Attributes&attrs, 
			const std::string& href, 
			const std::string& role,
			const std::string& arcrole, 
			const std::string& title, 
			const std::string& show, 
			const std::string& actuate) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endSimpleLink(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endSimpleLink( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startTitle(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes)
		*/

		virtual void startTitle( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endTitle(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endTitle( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#titleCharacters(char[], int, int)
		*/
		virtual void titleCharacters(char* buf, int offset, int len) = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startExtendedLink(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String)
		*/
		virtual void startExtendedLink( const std::string& namespaceURI, 
			const std::string& lName,
			const std::string& qName, 
			const xercesc::Attributes&attrs, 
			const std::string& role, 
			const std::string& title) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endExtendedLink(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endExtendedLink( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startResource(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void startResource( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&attrs, 
			const std::string& role, 
			const std::string& title, 
			const std::string& label) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endResource(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endResource( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startLocator(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void startLocator( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&attrs, 
			const std::string& href, 
			const std::string& role, 
			const std::string& title,
			const std::string& label) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endLocator(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endLocator( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#startArc(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void startArc( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&attrs, 
			const std::string& from, 
			const std::string& to, 
			const std::string& arcrole,
			const std::string& title, 
			const std::string& show, 
			const std::string& actuate) = 0;
		/**
		* @see org.xbrlapi.xlink.XLinkHandler#endArc(java.lang.String, java.lang.String, java.lang.String)
		*/
		virtual void endArc( const std::string& namespaceURI, 
			const std::string& sName, 
			const std::string& qName) = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#xmlBaseStart(java.lang.String)
		*/
		virtual void xmlBaseStart( const std::string& value)  = 0;

		/**
		* @see org.xbrlapi.xlink.XLinkHandler#xmlBaseEnd()
		*/
		virtual void xmlBaseEnd()  = 0;

		/**
		* Default error behaviour is to throw an XLink Exception
		* @see org.xbrlapi.xlink.XLinkHandler#error(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		*/
		virtual void error( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&attrs,	
			const std::string& message) = 0;
		/**
		* Default warning behaviour is to ignore the warning
		* @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		*/
		virtual void warning( const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&attrs, 
			const std::string& message) = 0;
	};
}

