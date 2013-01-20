#include "GenericDocumentRootIdentifier.h"

namespace xbrlcapi 
{


	struct GenericDocumentRootIdentifier::Impl 
	{
		std::weak_ptr<GenericDocumentRootIdentifier> outer;
		std::shared_ptr<ContentHandler> contentHandler;
		Impl() {}
		Impl(const std::shared_ptr<ContentHandler>& contentHandler) : contentHandler(contentHandler)
		{}

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{

			////if (! getLoader().get().isNewFragment()) {
			//    if (! getElementState().hasParent()) {
			//        Fragment root = new FragmentImpl();
			//        processFragment(root,attrs);
			//    }
		}
		void setOuter(const std::weak_ptr<GenericDocumentRootIdentifier>& genericDocumentRootIdentifier)
		{
			outer = std::weak_ptr<GenericDocumentRootIdentifier>(genericDocumentRootIdentifier);
		}
	};

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier() {}
	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	GenericDocumentRootIdentifier::~GenericDocumentRootIdentifier() {} 

	GenericDocumentRootIdentifier::GenericDocumentRootIdentifier(const GenericDocumentRootIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	GenericDocumentRootIdentifier& GenericDocumentRootIdentifier::operator=(const GenericDocumentRootIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
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

	std::weak_ptr<GenericDocumentRootIdentifier> GenericDocumentRootIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void GenericDocumentRootIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}
}    




