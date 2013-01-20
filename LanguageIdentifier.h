#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{

	class LanguageIdentifier : 
		public BaseIdentifier, 
		public std::enable_shared_from_this<LanguageIdentifier>  
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
		LanguageIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);
		std::weak_ptr<LanguageIdentifier> getPtr();
		void initialize();

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
