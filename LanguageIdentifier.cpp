#include "LanguageIdentifier.h"

namespace xbrlcapi 
{


	struct LanguageIdentifier::Impl : public BaseIdentifier
	{
		Impl() {}
		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler)
		{}

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{
			//		Fragment languageFragment = null;
			//		if (namespaceURI.equals(Constants.XBRLAPILanguagesNamespace.toString())) {
			//			if (lName.equals("language")) {
			//				languageFragment = new LanguageImpl();
			//			}
			//		}

			//		if (languageFragment != null) {
			//			this.processFragment(languageFragment,attrs);
			//		}

		}  
	};

	LanguageIdentifier::LanguageIdentifier() {}
	LanguageIdentifier::~LanguageIdentifier() {} 

	LanguageIdentifier::LanguageIdentifier(const ContentHandler& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	LanguageIdentifier::LanguageIdentifier(const LanguageIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	LanguageIdentifier& LanguageIdentifier::operator=(const LanguageIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	LanguageIdentifier::LanguageIdentifier(LanguageIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	LanguageIdentifier& LanguageIdentifier::operator=(LanguageIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool LanguageIdentifier::operator==(const LanguageIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool LanguageIdentifier::operator!=(const LanguageIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	void LanguageIdentifier::startElement(
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




