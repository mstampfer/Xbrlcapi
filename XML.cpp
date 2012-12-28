#include "XML.h"
#include <unordered_map>
#include "Store.h"
#include "XBRLException.h"
#include "xercesc/dom/DOMElement.hpp"

namespace xbrlcapi

{    
	struct XML::Impl
	{

		/**
		* The Fragment builder - used when building fragments during DTS discovery.
		*/
		Builder builder;

		/**
		* The data store that manages this fragment.
		*/
		std::unique_ptr<Store> store;

		/**
		* The DOM instantiation of the fragment's root DOMElement or null
		* if the fragment has not been built.
		*/

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

		/**
		* @see org.xbrlapi.XML#isa(Class)
		*/
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

		/**
		* @see java.lang.Object#hashCode()
		*/

		int hashCode() 
		{
			//final int prime = 31;
			int result = 1;
			//result = prime * result + ((rootElement == null) ? 0 : getIndex().hashCode());
			//result = prime * result + ((store == null) ? 0 : store.hashCode());
			return result;
		}

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/

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

		/**
		* Comparison is based upon the fragment index.
		* @see java.lang.Comparable#compareTo(Object o)
		*/
		//int compareTo(const XML& other) 
		//{
		//	//		return this->getIndex().compareTo(other.getIndex());
		//	return 0;
		//}

		//void setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement)
		//{
		//	if (rootElement == null) throw new XBRLException("The XML resource is null.");
		//	this->rootElement = rootElement;
		//	setBuilder(null);
		//}    

		/**
		* @see org.xbrlapi.XML#getDocumentNode()
		*/
		//Document getDocumentNode() 
		//{
		//	//if (builder != null) return getBuilder().getMetadata().getOwnerDocument();
		//	//return getResource().getOwnerDocument();
		//}   

		void setStore(Store store)
		{
			if (this->store != null) 
			{
				throw XBRLException("The data store has already been specified for this fragment.");
			}
			this->store = store;
		}

		void setBuilder(Builder builder) 
		{
			if (builder == null) 
			{
				this->builder = null;
				return;
			}
			builder.setMetaAttribute("type",getType());
			this->builder = builder;
		}

		std::unique_ptr<Store> getStore() 
		{
			return store;
		}



		Builder getBuilder() 
		{
			return builder;
		}

		//std::shared_ptr<xercesc::DOMElement> getMetadataRootElement() const
		//{
		//	if (builder != null) return builder.getMetadata();
		//	return getResource();
		//}

		/**
		* @see org.xbrlapi.XML#getIndex()
		*/
		std::string getIndex() 
		{
			return this->getMetaAttribute("index");
		}

		/**
		* @see org.xbrlapi.XML#setIndex(const std::string&)
		*/
		void setIndex(const std::string& index)
		{
			//if (index == null) throw new XBRLException("The index must not be null.");
			//if (index.equals("")) throw new XBRLException("A fragment index must not be an empty string.");
			//setMetaAttribute("index",index);
		}

		/**
		* @see org.xbrlapi.XML#getType()
		*/
		std::string getType() 
		{
			//	return this->getClass().getName();
			return std::string();
		}

		/**
		* @see org.xbrlapi.XML#setMetaAttribute(std::string, std::string)
		*/
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

		/**
		* @see org.xbrlapi.XML#removeMetaAttribute(std::string)
		*/
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

		/**
		* @see org.xbrlapi.XML#getMetaAttribute(std::string)
		*/
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

		/**
		* @see org.xbrlapi.XML#getMetaAttribute(std::string)
		*/
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

		/**
		* @see org.xbrlapi.XML#appendMetadataElement(std::string, Map)
		*/
		void appendMetadataElement(const std::string& eName, std::unordered_map<std::string,std::string> attributes)
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

		/**
		* @see org.xbrlapi.XML#removeMetadataElement(std::string, HashMap)
		*/
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



		/**
		* @see org.xbrlapi.XML#serialize(File)
		*/
		//void serialize(File file)
		//{
		//	//getStore().serialize(this->getMetadataRootElement(), file);
		//}

		/**
		* @see org.xbrlapi.XML#serialize(OutputStream)
		*/
		//void serialize(OutputStream outputStream)
		//{
		//	//getStore().serialize(this->getMetadataRootElement(), outputStream);
		//}

		/**
		* @see org.xbrlapi.XML#serialize()
		*/
		std::string serialize()
		{
			//return getStore().serialize(this->getMetadataRootElement());
			return std::string();
		}

		/**
		* @see org.xbrlapi.XML#updateInStore()
		*/
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


		/**
		* Handles object inflation.
		* @param in The input object stream used to access the object's serialization.
		* @throws IOException
		* @throws ClassNotFoundException
		*/
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

		/**
		* Handles serialization for XML resources that have been fully built.
		* @param out The input object stream used to store the serialization of the object.
		* @throws IOException if the object is still being built.
		*/
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

		/**
		* Get the XML resource that is the fragment from the data store.
		* @return the DOM root DOMElement of the fragment or null if the resource
		* has not been initialised to a DOM root DOMElement.
		*/
		//std::shared_ptr<xercesc::DOMElement> getResource() 
		//{
		//	return rootElement;
		//} 

		/**
		* Update this fragment in the data store by storing it again.
		* @throws XBRLException if this fragment cannot be updated in the data store.
		*/
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
}
