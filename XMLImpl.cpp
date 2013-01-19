#include "XMLImpl.h"
#include <unordered_map>
#include "Store.h"
#include "XBRLException.h"
#include "Builder.h"

namespace xbrlcapi
{    
	struct XMLImpl::Impl
	{

		Builder builder;
		Store store;
		std::shared_ptr<xercesc::DOMElement> rootElement;

		Impl() {}

		Impl(const Impl& rhs) :
			builder(rhs.builder),
			store(rhs.store),
			rootElement(rhs.rootElement)
		{

		}

		Impl(const Impl&& rhs) :
			builder(std::move(rhs.builder)),
			store(std::move(rhs.store)),
			rootElement(std::move(rhs.rootElement))
		{

		}

		Impl& operator=(Impl& rhs)
		{
			if (this != &rhs)
			{
				builder = rhs.builder;
				store = rhs.store;
				rootElement = rhs.rootElement;
			}
			return *this;
		}

		Impl& operator=(Impl&& rhs)
		{
			if (this != &rhs)
			{
				builder = std::move(rhs.builder);
				store = std::move(rhs.store);
				rootElement = std::move(rhs.rootElement);
			}
			return *this;
		}

		bool operator==(const Impl& rhs)
		{
			return ( 
				builder == rhs.builder &&
				store == rhs.store &&
				rootElement == rhs.rootElement
				);
		}

		void setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement)
		{
			//if (rootElement == null) throw new XBRLException("The XML resource is null.");
			//this->rootElement = rootElement;
			//setBuilder(null);
		}    

		//Document getDocumentNode() 
		//{
		//	//if (builder != null) return getBuilder().getMetadata().getOwnerDocument();
		//	//return getResource().getOwnerDocument();
		//}   

		void setStore(const Store& store)
		{
			//if (this->store != null) 
			//{
			//	throw XBRLException("The data store has already been specified for this fragment.");
			//}
			this->store = store;
		}

		void setBuilder(Builder builder) 
		{
			//if (builder == null) 
			//{
			//	this->builder = null;
			//	return;
			//}
			//builder.setMetaAttribute("type",getType());
			//this->builder = builder;
		}

		Store getStore() 
		{
			return store;
		}

		Builder getBuilder() 
		{
			return builder;
		}

		std::shared_ptr<xercesc::DOMElement> getMetadataRootElement()
		{
			if (builder.getMetadata().get() != nullptr) return builder.getMetadata();
			return getResource();
		}

		void appendMetadataElement(const std::string& eName, const std::unordered_map<std::string,std::string>& attributes)
		{
			//if (eName == null) throw new XBRLException("An DOMElement name must be specified.");

			//if (getBuilder() != null) 
			//{
			//	getBuilder().appendMetadataElement(eName, attributes);
			//	return;
			//}

			//std::shared_ptr<xercesc::DOMElement> root = getMetadataRootElement();
			//Document document = root.getOwnerDocument();
			//std::shared_ptr<xercesc::DOMElement> child = document.createElementNS(Constants.XBRLAPINamespace.toString(),Constants.XBRLAPIPrefix + ":" + eName);

			//for (std::string& aName: attributes.keySet()) 
			//{
			//	std::string aValue = attributes.get(aName);
			//	if (aName != null) 
			//	{
			//		if (aValue == null) throw new XBRLException("A metadata DOMElement is being added but attribute, " + aName + ", has a null value.");
			//		child.setAttribute(aName,aValue); 
			//	} else throw new XBRLException("A metadata DOMElement is being added with an attribute with a null name.");
			//}
			//root.appendChild(child);
			//updateStore();
		}

		void finalize()
		{
			//super.finalize(); 
		}    

		std::shared_ptr<xercesc::DOMElement> getResource() 
		{
			return rootElement;
		} 

		void updateStore()
		{
			//		getStore().persist(this);
		}

		//    Builder getBuilder();

		//   Element getMetadataRootElement();

		std::string getIndex()
		{
			return this->getMetaAttribute("index");
		}

		void setIndex(const std::string& index)
		{
			//if (index == null) throw new XBRLException("The index must not be null.");
			//if (index.equals("")) throw new XBRLException("A fragment index must not be an empty string.");
			//setMetaAttribute("index",index);
		}

		std::string getType() 
		{
			//	return this->getClass().getName();
			return std::string();
		}

		void setMetaAttribute(const std::string& name, const std::string& value)
		{
			//if (getBuilder() != null) 
			//{
			//	getBuilder().setMetaAttribute(name,value);
			//	return;
			//}

			//std::shared_ptr<xercesc::DOMElement> DOMElement = this->getMetadataRootElement();
			//DOMElement.setAttribute(name,value);
			//updateStore();
		}

		void removeMetaAttribute(const std::string& name)
		{
			//if (getBuilder() != null) 
			//{
			//	getBuilder().removeMetaAttribute(name);
			//	return;
			//}

			//std::shared_ptr<xercesc::DOMElement> DOMElement = this->getMetadataRootElement();
			//if (DOMElement == null) throw new XBRLException("The metadata does not contain a root DOMElement.");      
			//DOMElement.removeAttribute(name);
			//updateStore();
		}

		std::string getMetaAttribute(const std::string& name) 
		{
			//if (getBuilder() != null) 
			//{
			//	return getBuilder().getMetaAttribute(name);
			//}

			//std::shared_ptr<xercesc::DOMElement> root = getMetadataRootElement();
			//if (! root.hasAttribute(name)) return null;
			//return root.getAttribute(name);
			return std::string();
		}

		bool hasMetaAttribute(const std::string& name) 
		{
			//Builder builder = getBuilder();
			//if (builder != null) 
			//{
			//	return builder.hasMetaAttribute(name);
			//}
			//return getMetadataRootElement().hasAttribute(name);
			return false;
		}

		void removeMetadataElement(const std::string& eName, std::unordered_map<std::string,std::string> attributes)
		{

			//if (eName == null) throw new XBRLException("A DOMElement name must be specified.");

			//if (getBuilder() != null) 
			//{
			//	getBuilder().removeMetadataElement(eName, attributes);
			//	return;
			//}

			//// If the fragment has been stored update the data store
			//std::shared_ptr<xercesc::DOMElement> DOMElement = this->getMetadataRootElement();
			//if (DOMElement == null) throw new XBRLException("The metadata does not contain a root DOMElement.");
			//NodeList children = DOMElement.getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),eName);
			//for (int i=0; i<children.getLength(); i++) 
			//{
			//	bool match = true;
			//	std::shared_ptr<xercesc::DOMElement> child = (std::shared_ptr<xercesc::DOMElement>) children.item(i);
			//	Iterator<std::string> attributeNames = attributes.keySet().iterator();
			//	while (attributeNames.hasNext()) 
			//	{
			//		std::string aName = attributeNames.next();
			//		std::string aValue = attributes.get(aName);
			//		if (aName != null) 
			//		{
			//			if (aValue == null) throw new XBRLException("A metadata DOMElement is being checked but attribute, " + aName + ", has a null value.");
			//			if (! child.getAttribute(aName).equals(aValue)) 
			//			{
			//				match = false;
			//			}
			//		} else throw new XBRLException("A metadata DOMElement is being checked against an attribute with a null name.");
			//	}

			//	if (match) 
			//	{
			//		DOMElement.removeChild(child);
			//		break;
			//	}
			//}
			//updateStore();

		}

		//void serialize(File file)
		//{
		//	//getStore().serialize(this->getMetadataRootElement(), file);
		//}

		//void serialize(OutputStream outputStream)
		//{
		//	//getStore().serialize(this->getMetadataRootElement(), outputStream);
		//}

		std::string serialize()
		{
			//return getStore().serialize(this->getMetadataRootElement());
			return std::string();
		}

		void updateInStore()
		{
			//Store store = this->getStore();
			//if (store == null) return;
			//if (store.hasXMLResource(this->getIndex())) 
			//{
			//	store.remove(this->getIndex());
			//}
			//store.persist(this);
		}

		std::shared_ptr<xercesc::DOMDocument> getDocumentNode()
		{
			//if (builder != null) return getBuilder().getMetadata().getOwnerDocument();
			//return getResource().getOwnerDocument();
			return std::shared_ptr<xercesc::DOMDocument>();
		}   


	};

	XMLImpl::XMLImpl() {}
	XMLImpl::~XMLImpl() {} 

	XMLImpl::XMLImpl(const XMLImpl& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XMLImpl& XMLImpl::operator=(const XMLImpl& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XMLImpl::XMLImpl(XMLImpl&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XMLImpl& XMLImpl::operator=(XMLImpl&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XMLImpl::operator==(const XMLImpl& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XMLImpl::operator!=(const XMLImpl& rhs)
	{
		return !this->operator==(rhs);
	}

	void XMLImpl::setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement)
	{
		pImpl->setResource(rootElement);
	}    

	std::shared_ptr<xercesc::DOMDocument> XMLImpl::getDocumentNode()
	{
		return pImpl->getDocumentNode();
	}   

	void XMLImpl::setStore(const Store& store)
	{
		pImpl->setStore(store);
	}

	void XMLImpl::setBuilder(const Builder& builder) 
	{
		pImpl->setBuilder(builder);
	}

	Store XMLImpl::getStore() 
	{
		return pImpl->getStore();
	}

	Builder XMLImpl::getBuilder() 
	{
		return pImpl->getBuilder();
	}

	std::shared_ptr<xercesc::DOMElement> XMLImpl::getMetadataRootElement()
	{
		return getMetadataRootElement();
	}

	void XMLImpl::appendMetadataElement(const std::string& eName, const std::unordered_map<std::string,std::string>& attributes)
	{
		pImpl->appendMetadataElement(eName,attributes);
	}

	std::string XMLImpl::getIndex()
	{
		return pImpl->getIndex();
	}

	void XMLImpl::setIndex(const std::string& index)
	{
		pImpl->setIndex(index);
	}

	std::string XMLImpl::getType() 
	{
		return pImpl->getType();
	}

	void XMLImpl::setMetaAttribute(const std::string& name, const std::string& value)
	{
		pImpl->setMetaAttribute(name, value);
	}

	void XMLImpl::removeMetaAttribute(const std::string& name)
	{
		pImpl->removeMetaAttribute(name);
	}

	std::string XMLImpl::getMetaAttribute(const std::string& name) 
	{
		return pImpl->getMetaAttribute(name);
	}

	bool XMLImpl::hasMetaAttribute(const std::string& name) 
	{
		return pImpl->hasMetaAttribute(name);
	}

	void XMLImpl::removeMetadataElement(const std::string& eName, std::unordered_map<std::string,std::string> attributes)
	{
		pImpl->removeMetadataElement(eName, attributes);
	}

	//void serialize(File file)
	//{
	//	pImpl->serialize(file);
	//}

	//void serialize(OutputStream outputStream)
	//{
	//	pImpl->serialize(outputStream);
	//}

	std::string XMLImpl::serialize()
	{
		return pImpl->serialize();
	}

	void XMLImpl::updateInStore()
	{
		pImpl->updateInStore();
	}
}
