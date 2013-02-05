#pragma once
#include "PimplImpl.h"
#include "XML.h"
#include "xercesc/dom/DOMElement.hpp"
#include <unordered_map>

namespace xbrlcapi
{
	class Store;
	class Builder;
	class XMLImpl : public XML
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		XMLImpl();
		~XMLImpl();
		XMLImpl(const XMLImpl& rhs);
		XMLImpl& operator=(const XMLImpl& rhs);
		XMLImpl(XMLImpl&& rhs);
		XMLImpl& operator=(XMLImpl&& rhs);
		bool operator==(const XMLImpl& rhs);
		bool operator!=(const XMLImpl& rhs);
		/**
		* Update this fragment in the data store by storing it again.
		* @throws XBRLException if this fragment cannot be updated in the data store.
		*/
		std::string XMLImpl::getIndex() override;
		Builder XMLImpl::getBuilder() override; 

	protected:
		void finalize();

	public:
		/**
		* @see org.xbrlapi.XML#setResource(Element)
		*/
		void setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement) override;

		/**
		* @see org.xbrlapi.XML#getDocumentNode()
		*/
		std::shared_ptr<xercesc::DOMDocument> XMLImpl::getDocumentNode() override;

		/**
		* @see org.xbrlapi.XML#setStore(Store)
		*/
		void setStore(const Store& store) override;

		/**
		* @see org.xbrlapi.XML#setBuilder(Builder)
		*/
		   void setBuilder(const Builder& builder) override;

		/**
		* @see org.xbrlapi.XML#getStore()
		*/
		Store getStore() override;
		
		void XMLImpl::setIndex(const std::string& index) override;

		std::string XMLImpl::getType() override;

		void XMLImpl::setMetaAttribute(const std::string& name, const std::string& value) override;

		void XMLImpl::removeMetaAttribute(const std::string& name) override;

		std::string XMLImpl::getMetaAttribute(const std::string& name) override;

		bool XMLImpl::hasMetaAttribute(const std::string& name) override;

		void XMLImpl::removeMetadataElement(const std::string& eName, std::unordered_map<std::string,std::string> attributes) override;

		//void serialize(File file)
		//{
		//	pImpl->serialize(file) override;
		//}

		//void serialize(OutputStream outputStream)
		//{
		//	pImpl->serialize(outputStream) override;
		//}

		std::string XMLImpl::serialize() override;

		void XMLImpl::updateInStore() override;
	
		std::shared_ptr<xercesc::DOMElement> XMLImpl::getMetadataRootElement() override;

		void XMLImpl::appendMetadataElement(const std::string& eName, 
			const std::unordered_map<std::string,std::string>& attributes) override;
	};
}
