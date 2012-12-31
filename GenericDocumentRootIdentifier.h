#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include "ContentHandler.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{
	/**
	* Identifies XML Schema fragments.
	*/

	class GenericDocumentRootIdentifier : public BaseIdentifier 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		GenericDocumentRootIdentifier();
		~GenericDocumentRootIdentifier();
		GenericDocumentRootIdentifier(const GenericDocumentRootIdentifier& rhs);
		GenericDocumentRootIdentifier& operator=(const GenericDocumentRootIdentifier& rhs);
		GenericDocumentRootIdentifier(GenericDocumentRootIdentifier&& rhs);
		GenericDocumentRootIdentifier& operator=(GenericDocumentRootIdentifier&& rhs);
		bool operator==(const GenericDocumentRootIdentifier& rhs);
		bool operator!=(const GenericDocumentRootIdentifier& rhs);

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		GenericDocumentRootIdentifier(const ContentHandler& contentHandler);

		/**
		* Add a generic fragment for a document root element if we 
		* have not already done so.
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(String,String,String,Attributes)
		*/
		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);
	};
}
