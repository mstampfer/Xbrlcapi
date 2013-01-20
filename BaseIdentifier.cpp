#include "BaseIdentifier.h"
#include "ContentHandler.h"
#include "Fragment.h"
namespace xbrlcapi
{
	struct BaseIdentifier::Impl 
	{
		/**
		* The content handler that is using this fragment identifier
		*/
		std::shared_ptr<ContentHandler> contentHandler;

		Impl() 
		{
		}

		Impl(const std::shared_ptr<ContentHandler>& contentHandler) 
		{
			setContentHandler(contentHandler);
		}

		std::shared_ptr<ContentHandler> getContentHandler()
		{
			return contentHandler;
		}

		void setContentHandler(const std::shared_ptr<ContentHandler>& contentHandler)
		{
			//if (contentHandler == null) throw new XBRLException("The content handler must not be null.");
			this->contentHandler = contentHandler;
		}

		std::shared_ptr<Loader> getLoader()
		{
			return contentHandler->getLoader();
		}

		ElementState getElementState()
		{
			return contentHandler->getElementState();
		}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes&  attrs)
		{}		

		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes&  attrs)
		{}		

		void processFragment(const std::shared_ptr<Fragment>& fragment, const xercesc::Attributes& attrs)
		{
			//	Loader loader = getLoader();
			//	fragment.setBuilder(new Builder(loader.getBuilderDOM()));
			//	fragment.setIndex(loader.getNextFragmentId());
			//	if (attrs.getValue("id") != null)
			//	{
			//		fragment.appendID(attrs.getValue("id"));
			//		getElementState().setId(attrs.getValue("id"));
			//	}
			//	loader.add(fragment,getElementState());
			//}
		};

	};

	BaseIdentifier::BaseIdentifier() {}
	BaseIdentifier::~BaseIdentifier() {} 

	BaseIdentifier::BaseIdentifier(const BaseIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	BaseIdentifier& BaseIdentifier::operator=(const BaseIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	BaseIdentifier::BaseIdentifier(BaseIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	BaseIdentifier& BaseIdentifier::operator=(BaseIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool BaseIdentifier::operator==(const BaseIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool BaseIdentifier::operator!=(const BaseIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	BaseIdentifier::BaseIdentifier(const std::shared_ptr<ContentHandler>& contentHandler)
	{
		pImpl->contentHandler = contentHandler;
	}

	std::shared_ptr<ContentHandler> BaseIdentifier::getContentHandler()
	{
		return pImpl->getContentHandler();
	}
	/**
	* @see Identifier#setContentHandler(ContentHandler)
	*/
	void BaseIdentifier::setContentHandler(const std::shared_ptr<ContentHandler>& contentHandler)
	{
		pImpl->setContentHandler(contentHandler);
	}

	/**
	* @see Identifier#getLoader()
	*/
	std::shared_ptr<Loader> BaseIdentifier::getLoader()
	{
		return pImpl->getLoader();
	}

	/**
	* @see Identifier#getElementState()
	*/
	ElementState BaseIdentifier::getElementState()
	{
		return pImpl->getElementState();
	}


	/**
	* @see Identifier#startElement(String, String, String, Attributes)
	*/
	void BaseIdentifier::startElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes&  attrs)
	{
		pImpl->startElement(namespaceURI,
			lName,
			qName,
			attrs);
	}

	/**
	* @see Identifier#endElement(String, String, String, Attributes)
	*/
	void BaseIdentifier::endElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(namespaceURI,
			lName,
			qName,
			attrs);
	}

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
		const xercesc::Attributes& attrs)
	{
		pImpl->processFragment(fragment, attrs);
	}
}