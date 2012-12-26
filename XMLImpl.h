
#pragma once

#include <string>
#include "XML.h"
#include <memory>
namespace xbrlcapi
{
	class Store;
	class XMLImpl : public XML 
	{

	private:
		XMLImpl();

	protected:
		void finalize();

		/**
		* The Fragment builder - used when building fragments during DTS discovery.
		*/
	private:
		//	Builder builder;

		/**
		* The data store that manages this fragment.
		*/
	private:
		//std::unique_ptr<Store> store;

		/**
		* The DOM instantiation of the fragment's root element or null
		* if the fragment has not been built.
		*/
	private:
		//	Element rootElement = null;

		/**
		* @see org.xbrlapi.XML#isa(const std::string& )
		*/
		bool isa(const std::string& type);

		/**
		* @see org.xbrlapi.XML#isa(Class)
		*/
		template <typename T>
		bool isa(T targetClass); 

		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
		//    bool equals(Object obj);

		/**
		* Comparison is based upon the fragment index.
		* @see java.lang.Comparable#compareTo(Object o)
		*/
		int compareTo(const XML& other);

		/**
		* @see org.xbrlapi.XML#setResource(Element)
		*/
		//    void setResource(Element rootElement);

		/**
		* @see org.xbrlapi.XML#getDocumentNode()
		*/
		//   Document getDocumentNode();

		/**
		* Get the XML resource that is the fragment from the data store.
		* @return the DOM root element of the fragment or null if the resource
		* has not been initialised to a DOM root element.
		*/
		//    private Element getResource();

		/**
		* @see org.xbrlapi.XML#setStore(Store)
		*/
		void setStore(Store store);

		/**
		* @see org.xbrlapi.XML#setBuilder(Builder)
		*/
		//    void setBuilder(Builder builder);

		/**
		* @see org.xbrlapi.XML#getStore()
		*/
		std::unique_ptr<Store> getStore();

		/**
		* Update this fragment in the data store by storing it again.
		* @throws XBRLException if this fragment cannot be updated in the data store.
		*/
	private:
		void updateStore();

		/**
		* @see org.xbrlapi.XML#getBuilder()
		*/
		//    Builder getBuilder();

		/**
		* @see org.xbrlapi.XML#getMetadataRootElement()
		*/
		//   Element getMetadataRootElement();

		/**
		* @see org.xbrlapi.XML#getIndex()
		*/
		std::string getIndex();

		/**
		* @see org.xbrlapi.XML#setIndex(const std::string& )
		*/
		void setIndex(const std::string& index);

		/**
		* @see org.xbrlapi.XML#getType()
		*/
		std::string getType();

		/**
		* @see org.xbrlapi.XML#setMetaAttribute(const std::string& , const std::string& )
		*/
		void setMetaAttribute(const std::string& name, const std::string& value);

		/**
		* @see org.xbrlapi.XML#removeMetaAttribute(const std::string& )
		*/
		void removeMetaAttribute(const std::string& name);

		/**
		* @see org.xbrlapi.XML#getMetaAttribute(const std::string& )
		*/
		std::string getMetaAttribute(const std::string& name);

		/**
		* @see org.xbrlapi.XML#getMetaAttribute(const std::string& )
		*/
		bool hasMetaAttribute(const std::string& name);

		/**
		* @see org.xbrlapi.XML#appendMetadataElement(const std::string& , Map)
		*/
		void appendMetadataElement(const std::string& eName,  std::unordered_map<std::string ,std::string > attributes);

		/**
		* @see org.xbrlapi.XML#removeMetadataElement(const std::string& , HashMap)
		*/
		void removeMetadataElement(const std::string& eName, std::unordered_map<std::string ,std::string > attributes);



		/**
		* @see org.xbrlapi.XML#serialize(File)
		*/
		//    void serialize(File file);

		/**
		* @see org.xbrlapi.XML#serialize(OutputStream)
		*/
		//    void serialize(OutputStream outputStream);

		/**
		* @see org.xbrlapi.XML#serialize()
		*/
		std::string serialize();

		/**
		* @see org.xbrlapi.XML#updateInStore()
		*/
		void updateInStore();

		/**
		* Handles serialization for XML resources that have been fully built.
		* @param out The input object stream used to store the serialization of the object.
		* @throws IOException if the object is still being built.
		*/
	private:
		//		void writeObject(java.io.ObjectOutputStream out);

		/**
		* Handles object inflation.
		* @param in The input object stream used to access the object's serialization.
		* @throws IOException
		* @throws ClassNotFoundException
		*/
	private:
		//		void readObject(ObjectInputStream in);
	};
}
