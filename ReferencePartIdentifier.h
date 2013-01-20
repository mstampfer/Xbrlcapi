#pragma once
#include "PimplImpl.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi
{
	/**
	* Identifies reference part fragments.
	*/

	class ReferencePartIdentifier : 
		public BaseIdentifier, 
		public std::enable_shared_from_this<ReferencePartIdentifier>   
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		ReferencePartIdentifier();
		~ReferencePartIdentifier();
		ReferencePartIdentifier(const ReferencePartIdentifier& rhs);
		ReferencePartIdentifier& operator=(const ReferencePartIdentifier& rhs);
		ReferencePartIdentifier(ReferencePartIdentifier&& rhs);
		ReferencePartIdentifier& operator=(ReferencePartIdentifier&& rhs);
		bool operator==(const ReferencePartIdentifier& rhs);
		bool operator!=(const ReferencePartIdentifier& rhs);

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		ReferencePartIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);
		std::weak_ptr<ReferencePartIdentifier> getPtr();
		void initialize();

		/**
        * Handle reference part fragments inside reference resources		
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(String,String,String,Attributes)
		*/

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs);
	};
}
