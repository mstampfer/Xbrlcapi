#pragma once

#include <xercesc/sax2/Attributes.hpp>
#include "BaseURISAXResolver.h"

namespace xbrlcapi
{
	class Loader;
	class ElementState;
	/**
	* XBRL XLink Handler
	* This class provides a real world example of an XLink handler for XBRL.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
	class XLinkHandler //: public XLinkHandlerDefault 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* XBRL XLink handler constructor
		*/
		XLinkHandler();
		~XLinkHandler();
		XLinkHandler(const XLinkHandler& rhs);
		XLinkHandler& operator=(const XLinkHandler& rhs);
		XLinkHandler(XLinkHandler&& rhs);
		XLinkHandler& operator=(XLinkHandler&& rhs);
		bool operator==(const XLinkHandler& rhs);
		bool operator!=(const XLinkHandler& rhs);


		/**
		* Set the XBRL DTS loader
		* @param loader The XBRL DTS loader
		*/
		//void setLoader(const Loader& loader);

		/**
		* Set the base URI resolver for the XBRL XLink handler.
		* @param resolver the base URI resolver used by the XLink handler.
		*/
		void setBaseURISAXResolver(const BaseURISAXResolver& resolver);

		/**
		* Handle the XML Base attribute discovery
		* @param value the Value of the XML Base attribute
		*/
		void xmlBaseStart(const XMLCh* value);

		/**
		* Creates and stores an XLink title fragment.
		*/
		void startTitle(const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs);

		/**
		* Handle the change of XML Base scope as you step back up the tree
		*/
		void xmlBaseEnd();

		/**
		* The extended link processing algorithm, central to this implementation, 
		* operates as follows:
		* <ul>
		* <li>Store all locators and resources that are found in the extended link 
		* in a map of lists where the map is indexed by XLink label attribute values
		* and each list is made up of the locators and resources that have been found
		* in the extended link that carry the same XLink label.
		* </li>
		* <li> 
		* Preprocess the XLink href attribute values on locators to determine those
		* locators linking to XML resources that have already been discovered and 
		* parsed and those linking to XML resources that are yet to be parsed.  For 
		* locators linking to parsed XML resources, add a relationship element to the
		* locator containing the DTS index of the resource and add a relationship
		* element to the resource containing the DTS index of the locator (The DTS
		* index is the index attribute value unique within the DTS that is given to 
		* various elements during the discovery process.)  For locators linked to 
		* unparsed XML resources, place them in map of unprocessed locators, indexed
		* by the href attribute value of the locator so that a resource can quickly 
		* find all locators that point to them using the map and knowing their location.
		* </li>
		* <li>
		* Store all arcs that are found in the extended link in a stack ready for 
		* processing once the end of the extended link has been found.
		* </li>
		* </ul>
		*/
		void startExtendedLink(
			const XMLCh* namespaceURI, 
			const XMLCh* lName,
			const XMLCh* qName, 
			const xercesc::Attributes& attrs, 
			const XMLCh* role, 
			const XMLCh* title);

		/**
		* Nothing needs to be done at the end of the extended link discovery.
		*/
		void endExtendedLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName);

		/**
		* @see XLinkHandler#startResource(std::string, std::string, std::string, Attributes, std::string, std::string, std::string)
		*/
		void startResource(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* role, 
			const XMLCh* title, 
			const XMLCh* label);

		/**
		* Handle the end of the resource.
		*/
		void endResource(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName);

		/**
		* Create the locator fragment and then add it to the map of arc anchors.
		* Finally queue up the locator href value in the exploration queue.
		*/
		void startLocator(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs, 
			const XMLCh* href, 
			const XMLCh* role, 
			const XMLCh* title,
			const XMLCh* label);


		/**
		* Handle the end of the locator.
		*/
		void endLocator(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName);

		/**
		* Create the arc fragment first. Then add the arc to the 
		* stack of arcs to be processed.
		*/
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
			const XMLCh* actuate);

		/**
		* Handle the end of the arc.
		*/
		void endArc(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName);

		/**
		* Add the href to the set of XML documents to be explored and 
		* create the fragment for the simple link.
		* TODO Should simple links generate relationship metadata?
		*/
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
			const XMLCh* actuate);

		/**
		* Handle the end of the simple link
		*/
		void endSimpleLink(const XMLCh* namespaceURI, const XMLCh* sName, const XMLCh* qName);


		/**
		* @param elementState The state for the current element.
		*/
		void setElementState(const ElementState& elementState);

		/**
		* Walter Hamscher has identified documents in the XBRL community that violate the constraint
		* that attributes not defined in the XLink specification must not be in the XLink namespace.
		* To accommodate this imperfection, we catch that kind of error and make it a warning.
		* 
		* @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.std::string,java.lang.std::string, java.lang.std::string, org.xml.sax.Attributes, java.lang.std::string)
		*/
		void XLinkHandler::error(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
			const xercesc::Attributes& attrs,const XMLCh* message);

		/**
		* Log a warning message
		* @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.std::string,java.lang.std::string, java.lang.std::string, org.xml.sax.Attributes, java.lang.std::string)
		*/
		void warning(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName,
			const xercesc::Attributes& attrs,const XMLCh* message);

		void titleCharacters(char* buf, int offset, int len);

		void endTitle( const XMLCh* namespaceURI, 
			const XMLCh* sName, 
			const XMLCh* qName);

	};
}
