#include "GenericDocumentRootIdentifier.h"

namespace xbrlcapi 
{


	struct GenericDocumentRootIdentifier::Impl : public BaseIdentifier
	{
		Impl() {}
		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler)
		{}

		//void startElement(
		//String namespaceURI, 
		//	String lName, 
		//	String qName,
		//	Attributes attrs) throws XBRLException {

        ////if (! getLoader().get().isNewFragment()) {
        //    if (! getElementState().hasParent()) {
        //        Fragment root = new FragmentImpl();
        //        processFragment(root,attrs);
        //    }
        ////}
	};

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier() {}
	GenericDocumentRootIdentifier::~GenericDocumentRootIdentifier() {} 

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier(const GenericDocumentRootIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	GenericDocumentRootIdentifier& GenericDocumentRootIdentifier::operator=(const GenericDocumentRootIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier(GenericDocumentRootIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	GenericDocumentRootIdentifier& GenericDocumentRootIdentifier::operator=(GenericDocumentRootIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool GenericDocumentRootIdentifier::operator==(const GenericDocumentRootIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool GenericDocumentRootIdentifier::operator!=(const GenericDocumentRootIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier(const ContentHandler& contentHandler) : Impl(contentHandler)
	{}

	void GenericDocumentRootIdentifier::startElement(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{      
		pImpl->startElement(
			namespaceURI, 
			lName, 
			qName,
			attrs);
	}        
}    




