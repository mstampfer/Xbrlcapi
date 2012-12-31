#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{

	class LanguageIdentifier : public BaseIdentifier 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		LanguageIdentifier();
		~LanguageIdentifier();
		LanguageIdentifier(const LanguageIdentifier& rhs);
		LanguageIdentifier& operator=(const LanguageIdentifier& rhs);
		LanguageIdentifier(LanguageIdentifier&& rhs);
		LanguageIdentifier& operator=(LanguageIdentifier&& rhs);
		bool operator==(const LanguageIdentifier& rhs);
		bool operator!=(const LanguageIdentifier& rhs);

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/

		LanguageIdentifier(const ContentHandler& contentHandler);


		/**
		* Find fragments defining and labelling XML language codes.
		* 
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(String,String,String,Attributes)
		*/

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);
	};
}
