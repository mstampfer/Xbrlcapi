#include "LanguageIdentifier.h"

namespace xbrlcapi 
{


	struct LanguageIdentifier::Impl 
	{
		std::weak_ptr<LanguageIdentifier> outer;
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

		void setOuter(const std::weak_ptr<LanguageIdentifier>& languageIdentifier)
		{
			outer = std::weak_ptr<LanguageIdentifier>(languageIdentifier);
		}
	};

	LanguageIdentifier::LanguageIdentifier() {}
	LanguageIdentifier::~LanguageIdentifier() {} 

	LanguageIdentifier::LanguageIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
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
	std::weak_ptr<LanguageIdentifier> LanguageIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void LanguageIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}
}    




