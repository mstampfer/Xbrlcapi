#include "ReferencePartIdentifier.h"

namespace xbrlcapi 
{


	struct ReferencePartIdentifier::Impl 
	{
		std::weak_ptr<ReferencePartIdentifier> outer;
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

			//if (! getLoader().isBuildingAFragment()) {
			//    return;
			//}
			//
			//// Handle reference part fragments inside reference resources
			//Fragment fragment = getLoader().getFragment();
			//if (fragment.getType().equals("org.xbrlapi.impl.ReferenceResourceImpl")) {
			//    Fragment referencePartFragment = new ReferencePartImpl();
			//    processFragment(referencePartFragment,attrs);
		}
		void setOuter(const std::weak_ptr<ReferencePartIdentifier>& referencePartIdentifier)
		{
			outer = std::weak_ptr<ReferencePartIdentifier>(referencePartIdentifier);
		}
	};

	ReferencePartIdentifier::ReferencePartIdentifier() {}
	ReferencePartIdentifier::~ReferencePartIdentifier() {} 
	ReferencePartIdentifier::ReferencePartIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	ReferencePartIdentifier::ReferencePartIdentifier(const ReferencePartIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ReferencePartIdentifier& ReferencePartIdentifier::operator=(const ReferencePartIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ReferencePartIdentifier::ReferencePartIdentifier(ReferencePartIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ReferencePartIdentifier& ReferencePartIdentifier::operator=(ReferencePartIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ReferencePartIdentifier::operator==(const ReferencePartIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ReferencePartIdentifier::operator!=(const ReferencePartIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	void ReferencePartIdentifier::startElement(
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
	std::weak_ptr<ReferencePartIdentifier> ReferencePartIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void ReferencePartIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}
}    




