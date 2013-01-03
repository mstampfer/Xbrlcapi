#include "CustomLinkRecogniser.h"
#include "Constants.h"

namespace xbrlcapi {

	struct CustomLinkRecogniser::Impl 
	{
		Impl() {}

		bool isLink( const std::string& namespaceURI,  
			const std::string& lName,  
			const std::string& qName, 
			const xercesc::Attributes& attrs) 
		{
			bool result = false;
			if (namespaceURI == XMLConstants::XMLSchemaNamespace &&
				((lName == "import") || (lName == "include")))
				result = true;
			return result;
		}

		//const std::string getHref( const std::string& namespaceURI, 
		//	const std::string& lName, 
		//	const std::string& qName,
		//	const xercesc::Attributes& attrs) 
		//{
		//	const XMLCh* const schemaLocation = L"schemaLocation";
		//	return attrs.getValue(schemaLocation);
		//}

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

	bool CustomLinkRecogniser::isLink( const std::string& namespaceURI,  
		const std::string& lName,  
		const std::string& qName, 
		const xercesc::Attributes& attrs) 
	{
		return pImpl->isLink(namespaceURI, lName, qName, attrs);
	}

	std::string CustomLinkRecogniser::getHref( const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs) 
	{
//		return pImpl->getHref(namespaceURI, lName, qName, attrs);
		return std::string();
	}	
}