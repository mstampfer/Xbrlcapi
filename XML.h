#pragma once
#include "PimplImpl.h"
#include <unordered_map>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>

namespace xbrlcapi
{
	class Builder;
	class Store;

	class XML 
	{
	public:
		XML() {}
		~XML() {}
		XML(const XML& rhs);
		XML& operator=(const XML& rhs);
		XML(XML&& rhs);
		XML& operator=(XML&& rhs);
		bool operator==(const XML& rhs);
		bool operator!=(const XML& rhs);

		/**
		* @param superType The specified fragment type to test against.
		* @return true if the fragment is an extension of the specified fragment type.
		* @throws XBRLException
		* @see XML#isa(Class)
		*/
		//virtual bool isa(const std::string& superType) = 0;

		/**
		* Closes down the fragment builder and sets the data and metadata
		* resources for the fragment.  This should only be used by Store implementations
		* at the point where a newly built fragment is stored.
		* @param rootElement The fragment data.
		* @throws XBRLException If the builder cannot be shut down or if the 
		* resource cannot be set or is null.
		*/
		virtual void setResource(const std::shared_ptr<xercesc::DOMElement>& rootElement) = 0;

		/**
		* Get the XML DOM Document for the fragment data.
		* @return an XML DOM document for the fragment or null if none exists.
		*/
		virtual std::shared_ptr<xercesc::DOMDocument> getDocumentNode() = 0;

		/**
		* Get the root element of the fragment metadata.
		* @return an XML Element that is the root of the fragment metadata.
		*/
		virtual std::shared_ptr<xercesc::DOMElement> getMetadataRootElement() = 0;

		/**
		* Set the data store that manages this fragment.
		* @param store The data store.
		* @throws XBRLException if the data store has already been set.
		*/
		virtual void setStore(const Store& store) = 0;

		/**
		* Set the builder that constructs the fragment XML during parsing.
		* @param builder The builder object used to construct the fragment XML.
		* @throws XBRLException if the builder cannot be set or is null.
		*/
		virtual void setBuilder(const Builder& builder) = 0;  

		/**
		* Get the data store that manages this fragment.
		* @return the data store that manages this fragment or 
		* null if the fragment has not been stored.
		*/
		virtual Store getStore() = 0;

		/**
		* Get the fragment builder.  Note that the builder is null
		* if the fragment has already been stored in a data store.
		* TODO Should fragments hide the builder property?
		* @return the fragment builder or null if one is not available.
		*/
		virtual Builder getBuilder() = 0;

		/**
		* Get the Fragment type.  The fragment type is immutable. 
		* No virtual method is available to set the fragment type.
		* @return The full class name of the fragment.
		*/
		virtual std::string getType() = 0;

		/**
		* Get the index of the XML resource.  This is the 
		* name used for the XML resource in the data store.
		*/
		virtual std::string getIndex() = 0;

		/**
		* Set the fragment index.  Note that no checks are
		* performed to ensure that the fragment index is
		* unique within the data store.
		* This method instantiates a fragment builder for fragments that do
		* not have a resource property.
		* @throws an XBRLException if the index is null or an empty string.
		*/
		virtual void setIndex(const std::string& index) = 0;

		/**
		* Set a fragment metadata attribute.
		* @param name the name of the attribute
		* @param value the value to give to the metadata attribute
		* @throws XBRLException
		*/
		virtual void setMetaAttribute(const std::string& name, const std::string& value) = 0;

		/**
		* Get a fragment metadata attribute.
		* @param name the name of the attribute.
		* @return The value of the metadata attribute or null if none exists.
		*/
		virtual std::string getMetaAttribute(const std::string& name) = 0;

		/**
		* @param name the name of the attribute.
		* @return true if the XML resource has a metadata attribute with the specfied name.
		*/
		virtual bool hasMetaAttribute(const std::string& name) = 0;

		/**
		* Removes a metadata attribute
		* @param name The name of the attribute to remove
		* @throws XBRLException
		*/
		virtual void removeMetaAttribute(const std::string& name) = 0;

		/**
		* Appends a child element to the root metadata element.
		* @param eName Name of the element to be added (no namespaces are used).
		* @param attributes A map from attribute name keys to attribute values.
		* @throws XBRLException.
		*/
		virtual void appendMetadataElement(const std::string& eName, const std::unordered_map<std::string,std::string>& attributes) = 0;

		/**
		* removes a child element from the metadata root element by specifying the name of the child and
		* the value of the element's text content and/or the value of a named attribute.  All specified information
		* must match for the deletion to succeed.
		* @param eName Name of the element to be added (no namespaces are used).
		* @param attributes A hashmap from attribute name keys to attribute values.
		* @throws XBRLException If no deletion happens.
		*/
		virtual void removeMetadataElement(const std::string& eName, std::unordered_map<std::string,std::string> attributes) = 0;



		/**
		* Serializes the XML to the specified file.
		* @param file The specified output file.
		*/
		//virtual void serialize(File file) = 0;

		/**
		* Serializes the XML to the specified output stream.
		* @param outputStream The specified output stream.
		*/
		//virtual void serialize(OutputStream) = 0;

		/**
		* @return the XML as a string.
		*/
		virtual std::string serialize() = 0;

		/**
		* Updates the data store to reflect the current state of
		* this XML object.  If the XML object has not yet been
		* stored then no action is taken.  If there is a XML resource
		* in the store with the same index, then that earlier version
		* is first deleted from the data store.
		* @throws XBRLException
		*/
		virtual void updateInStore() = 0;
	};
}
