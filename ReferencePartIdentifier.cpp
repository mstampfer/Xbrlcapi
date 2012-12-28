#include "ReferencePartIdentifier.h"

namespace xbrlcapi 
{


	struct ReferencePartIdentifier::Impl : public BaseIdentifier
	{
		Impl() {}
		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler)
		{}

		//void startElement(
		//String namespaceURI, 
		//	String lName, 
		//	String qName,
		//	Attributes attrs) throws XBRLException {

        //if (! getLoader().isBuildingAFragment()) {
        //    return;
        //}
        //
        //// Handle reference part fragments inside reference resources
        //Fragment fragment = getLoader().getFragment();
        //if (fragment.getType().equals("org.xbrlapi.impl.ReferenceResourceImpl")) {
        //    Fragment referencePartFragment = new ReferencePartImpl();
        //    processFragment(referencePartFragment,attrs);
        //}
	};

	ReferencePartIdentifier::ReferencePartIdentifier() {}
	ReferencePartIdentifier::~ReferencePartIdentifier() {} 

	ReferencePartIdentifier::ReferencePartIdentifier(const ReferencePartIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ReferencePartIdentifier& ReferencePartIdentifier::operator=(const ReferencePartIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
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

	ReferencePartIdentifier::ReferencePartIdentifier(const ContentHandler& contentHandler) : Impl(contentHandler)
	{}

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
}    




