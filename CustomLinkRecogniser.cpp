#include "CustomLinkRecogniser.h"
#include "Constants.h"
#include "XercesString.h"

namespace xbrlcapi {

	struct CustomLinkRecogniser::Impl 
	{
		Impl() {}

		bool isLink( const XMLCh* namespaceURI,  
			const XMLCh* lName,  
			const XMLCh* qName, 
			const xercesc::Attributes& attrs) 
		{
			bool result = false;
			if (namespaceURI == XS(XMLConstants::XMLSchemaNamespace) &&
				((lName == L"import") || (lName == L"include")))
				result = true;
			return result;
		}

		const XMLCh* getHref( const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs) 
		{
			return attrs.getValue(L"schemaLocation");
		}

	};

	CustomLinkRecogniser::CustomLinkRecogniser() {}
	CustomLinkRecogniser::~CustomLinkRecogniser() {} 

	CustomLinkRecogniser::CustomLinkRecogniser(const CustomLinkRecogniser& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	CustomLinkRecogniser& CustomLinkRecogniser::operator=(const CustomLinkRecogniser& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	CustomLinkRecogniser::CustomLinkRecogniser(CustomLinkRecogniser&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	CustomLinkRecogniser& CustomLinkRecogniser::operator=(CustomLinkRecogniser&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool CustomLinkRecogniser::operator==(const CustomLinkRecogniser& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool CustomLinkRecogniser::operator!=(const CustomLinkRecogniser& rhs)
	{
		return !this->operator==(rhs);
	}

	bool CustomLinkRecogniser::isLink(const XMLCh* namespaceURI,  
		const XMLCh* lName,  
		const XMLCh* qName, 
		const xercesc::Attributes& attrs) 
	{
		return pImpl->isLink(namespaceURI, lName, qName, attrs);
	}

	const XMLCh* CustomLinkRecogniser::getHref(const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs) 
	{
		return pImpl->getHref(namespaceURI, lName, qName, attrs);
	}	

	const XMLCh* CustomLinkRecogniser::getRole(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs) 
	{
		return L"";
	}

	const XMLCh* CustomLinkRecogniser::getArcrole(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs) 
	{

		return L"";
	}

	const XMLCh* CustomLinkRecogniser::getTitle(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs) 
	{

		return L"";
	}

	const XMLCh* CustomLinkRecogniser::getShow(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs) 
	{

		return L"";
	}

	const XMLCh* CustomLinkRecogniser::getActuate(const XMLCh* namespaceURI, const XMLCh* lName, const XMLCh* qName, const xercesc::Attributes& attrs) 
	{

		return L"";
	}

}