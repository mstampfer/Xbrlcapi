#pragma once
#include "PimplImpl.h"
#include "Identifier.h"
#include "ContentHandler.h"

/**
* The class implements the common methods for a fragment identifier.
* This fragment identifier will never identify a fragment.
* Customised fragment identifiers should extend this base
* class to inherit the implementations of the common methods.
* 
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/


namespace xbrlcapi
{
	class BaseIdentifier : public Identifier 
	{

		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		BaseIdentifier();
		virtual ~BaseIdentifier();
		BaseIdentifier(const BaseIdentifier& rhs);
		BaseIdentifier& operator=(const BaseIdentifier& rhs);
		BaseIdentifier(BaseIdentifier&& rhs);
		BaseIdentifier& operator=(BaseIdentifier&& rhs);
		bool operator==(const BaseIdentifier& rhs);
		bool operator!=(const BaseIdentifier& rhs);

		BaseIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);

		std::shared_ptr<ContentHandler> getContentHandler() override;

		/**
		* @see Identifier#setContentHandler(ContentHandler)
		*/
		void setContentHandler(const std::shared_ptr<ContentHandler>& contentHandler) override;

		/**
		* @see Identifier#getLoader()
		*/
		std::shared_ptr<Loader> getLoader();

		/**
		* @see Identifier#getElementState()
		*/
		ElementState getElementState() override;

		/**
		* @see Identifier#startElement(String, String, String, Attributes)
		*/
		virtual void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes&  attrs) override;

		/**
		* @see Identifier#endElement(String, String, String, Attributes)
		*/
		virtual void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs) override;

		/**
		* Performs the following operations on the fragment:
		* <ul>
		* <li>Sets its fragment index</li>
		* <li>Determines if the fragment as an ID attribute and if so, appends
		* an ID ( @see org.xbrlapi.Fragment#appendID(String) ) and 
		* sets the ID in the element state.</li>
		* <li>Adds the fragment ( @see org.xbrlapi.loader.Loader#add(org.xbrlapi.Fragment,org.xbrlapi.xlink.ElementState) )</li>
		* </ul>
		* Override this base implementation if an ID of the fragment root element can be
		* expressed by an attribute other than "id".
		* @see Identifier#processFragment(Fragment, Attributes)
		*/
		void BaseIdentifier::processFragment(
			const std::shared_ptr<Fragment>& fragment, 
			const xercesc::Attributes& attrs);
	};
}

