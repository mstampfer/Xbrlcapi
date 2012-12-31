#include "XML.h"
#include <unordered_map>
#include "Store.h"
#include "XBRLException.h"
#include "Builder.h"
#include "xercesc/dom/DOMElement.hpp"

namespace xbrlcapi
{    
	struct XML::Impl
	{
		Builder builder;
		Store store;
		std::shared_ptr<xercesc::DOMElement> rootElement;
		Impl() {}

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

		bool isa(const std::string& type)
		{

			//Class<?> targetClass = FragmentFactory.getClass(type);
			//Class<?> candidateClass = this->getClass();
			//while (candidateClass != null) 
			//{
			//	if (candidateClass.equals(targetClass)) return true;
			//	candidateClass = candidateClass.getSuperclass();
			//}

			return false;
		}

		//bool isa(Class<?> targetClass) 
		//{
		//	//Class<?> candidateClass = this->getClass();
		//	//while (candidateClass != null) 
		//	//{
		//	//	if (candidateClass.equals(targetClass)) return true;
		//	//	candidateClass = candidateClass.getSuperclass();
		//	//}
		//	return false;
		//}    

		int hashCode() 
		{
			//final int prime = 31;
			int result = 1;
			return result;
		}

		//bool xmlimpl::equals(object obj) 
		//{
		//	//if (this == obj) 
		//	//{
		//	//	return true;
		//	//}
		//	//if (obj == null)
		//	//	return false;
		//	//if (getclass() != obj.getclass())
		//	//	return false;
		//	//xmlimpl other = (xmlimpl) obj;

		//	//if (store == null) 
		//	//{
		//	//	if (other.store != null)
		//	//		return false;
		//	//} else if (!store.equals(other.store))
		//	//	return false;

		//	//std::string index = this->getindex();
		//	//if (index == null) return false;
		//	//if (!index.equals(other.getindex())) return false;

		//	return true;
		//}

		//int compareTo(const XML& other) 
		//{
		//	//		return this->getIndex().compareTo(other.getIndex());
		//	return 0;
		//}

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

		void finalize()
		{
			//super.finalize(); 
		}    

		//void readObject(ObjectInputStream in)
		//{

		//in.defaultReadObject();
		//try 
		//{
		//	XMLDOMBuilder builder = new XMLDOMBuilder();
		//	Document dom = builder.newDocument((std::string) in.readObject());
		//	rootElement = dom.getDocumentElement();
		//} catch (XBRLException e) 
		//{
		//	throw new IOException("The XML Resource could not be de-serialized.",e);
		//}
		//}

		//void writeObject(java.io.ObjectOutputStream out) throws IOException 
		//{
		//if (this->getBuilder() != null) 
		//{
		//	logger.error(this->getIndex() + " still has a builder.");
		//	throw new IOException("The XML Resource could not be serialized because it is still being built.");
		//}
		//out.defaultWriteObject( );
		//try 
		//{
		//	std::string xml = store.serialize(rootElement);
		//	out.writeObject(xml);
		//} catch (XBRLException e) 
		//{
		//	throw new IOException("Could not convert the store content to a string representation of the XML.",e);
		//}
		//}

		std::shared_ptr<xercesc::DOMElement> getResource() 
		{
			return rootElement;
		} 

		void updateStore()
		{
			//		getStore().persist(this);
		}
	};

	XML::XML() {}

	XML::~XML() {} 

	XML::XML(const XML& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XML& XML::operator=(const XML& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XML::XML(XML&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XML& XML::operator=(XML&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XML::operator==(const XML& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XML::operator!=(const XML& rhs)
	{
		return !this->operator==(rhs);
	}

	void XML::setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement)
	{
		pImpl->setResource(rootElement);
	}

	std::shared_ptr<xercesc::DOMElement> XML::getMetadataRootElement()
	{
		return pImpl->getMetadataRootElement();
	}

	void XML::setStore(const Store& store)
	{
		pImpl->setStore(store);
	}

	Store XML::getStore()
	{
		return pImpl->getStore();
	}

	Builder XML::getBuilder()
	{
		return pImpl->getBuilder();
	}

	std::string XML::getIndex()
	{
		return pImpl->getIndex();
	}

	void XML::setMetaAttribute(const std::string& name, const std::string& value)
	{
		pImpl->setMetaAttribute(name, value);
	}

	void XML::appendMetadataElement(const std::string& eName, const std::unordered_map<std::string,std::string>& attributes)
	{
		pImpl->appendMetadataElement(eName, attributes);
	}

	std::string XML::getMetaAttribute(const std::string& name)
	{
		return pImpl->getMetaAttribute(name);
	}

}
