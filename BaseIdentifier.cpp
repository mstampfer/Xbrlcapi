#include "BaseIdentifier.h"
#include "ContentHandler.h"
#include "Fragment.h"
namespace xbrlcapi
{
	struct BaseIdentifier::Impl
	{
		Impl() {}

		BaseIdentifier(const ContentHandler& contentHandler)
		{
			setContentHandler(contentHandler);
		}

		/**
		* The content handler that is using this fragment identifier
		*/
		ContentHandler contentHandler;

		ContentHandler getContentHandler()
		{
			return contentHandler;
		}

		void setContentHandler(const ContentHandler& contentHandler)
		{
			//if (contentHandler == null) throw new XBRLException("The content handler must not be null.");
			this->contentHandler = contentHandler;
		}

		Loader getLoader()
		{
			return getContentHandler().getLoader();
		}

		ElementState getElementState()
		{
			return getContentHandler().getElementState();
		}



		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&  attrs)
		{
			;
		}

		void endElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes&  attrs)
		{
			;
		}

		void processFragment(const Fragment& fragment,const xercesc::Attributes& attrs)
		{
			Loader loader = this.getLoader();
			fragment.setBuilder(new BuilderImpl(loader.getBuilderDOM()));
			fragment.setIndex(getLoader().getNextFragmentId());
			if (attrs.getValue("id") != null)
			{
				fragment.appendID(attrs.getValue("id"));
				this.getElementState().setId(attrs.getValue("id"));
			}
			loader.add(fragment,getElementState());
		}
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
			pImpl->~Impl();
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

	BaseIdentifier::BaseIdentifier(const ContentHandler& contentHandler)
	{
		Impl(contentHandler);
	}

	ContentHandler BaseIdentifier::getContentHandler()
	{
		return pImpl->getContentHandler();
	}
	/**
	* @see Identifier#setContentHandler(ContentHandler)
	*/
	void BaseIdentifier::setContentHandler(ContentHandler contentHandler)
	{
		pImpl->setContentHandler();
	}

	/**
	* @see Identifier#getLoader()
	*/
	Loader BaseIdentifier::getLoader()
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
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
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
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
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
	void BaseIdentifier::processFragment(const Fragment& fragment, const xercesc::Attributes& attrs)
	{
		pImpl->processFragment(fragment, attrs);
	}
}