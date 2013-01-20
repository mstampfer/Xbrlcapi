#pragma once
#include "PimplImpl.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <string>
/**
* Class defining the SAX event handlers that
* enable a fragment to be built up during 
* DTS discovery.
* This should only be instantiated during
* the creation of a fragment subclass.
* The builder is responsible for construction of the XML
* constituting the fragment itself and the XML that contains
* the metadata about the fragment and its relationship to other 
* fragments.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class Builder 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Builder();
		~Builder();
		Builder(const Builder& rhs);
		Builder& operator=(const Builder& rhs);
		Builder(Builder&& rhs);
		Builder& operator=(Builder&& rhs);
		bool operator==(const Builder& rhs);
		bool operator!=(const Builder& rhs);

		//	/**
		//	 * Create the builder controlling which XML DOM is being used.
		//	 * @param dom The DOM to use in the builder.
		//	 * @throws XBRLException if the DOM is null.
		//	 */
		//	BuilderImpl(Document dom);
		//
		//	/**
		//	 * Create the builder making sure that the static DOM 
		//	 * is instantiated and creating the metadata root element.
		//	 * @throws XBRLException if the DOM Builder cannot be instantiated.
		//	 */
		//	BuilderImpl();
		//
		//	/**
		//	 * Restores the builder to its pre-use state.
		//	 */
		//	void close() ;
		//	
		//	/**
		//	 * @see Builder#getData()
		//	 */
		//	Element getData();
		//	
		/**
		* Get the metadata DOM document.
		* @return the metadata XML structure.
		*/
		std::shared_ptr<xercesc::DOMElement>  Builder::getMetadata();
		
			/**
			 * @return true iff the builder has not yet added an element to the fragment.
			 */
			bool isNewFragment();
		//
		//    /**
		//     * Get the insertion point for new data content.
		//     * @return the insertion point for new data nodes.
		//     */
		//    Element getInsertionPoint() ;
		//    
			/**
			 * Append a text node.
			 * @param text The node to be appended.
			 * @throws XBRLException if the node cannot be appended.
			 */
			void appendText(const std::string& text);
			
			/**
			 * Append a processing instruction node
			 * @param target The processing target application identifier.
			 * @param data The data defining what is to be done.
			 * @throws XBRLException if the node cannot be appended.
			 */
			void appendProcessingInstruction(const std::string& target, const std::string& data);		//	
		//	/**
		//	 * Append a comment node.
		//	 * @param text The data constituting the content of the comment.
		//	 * @throws XBRLException if the node cannot be appended.
		//	 */
		//	void appendComment(const std::string& text)		//;
		
			/**
			 * Append an element node.
			 * @param namespaceURI The namespace of the element found by the SAX parser.
			 * @param lName The local name of the element found by the SAX parser.
			 * @param qName The QName of the element found by the SAX parser.
			 * @param attrs The set of attributes found by the SAX parser.
			 * @throws XBRLException if the node cannot be appended.
			 */
			void appendElement(
					const XMLCh* namespaceURI, 
					const XMLCh* lName, 
					const XMLCh* qName, 
					const xercesc::Attributes& attrs);
			
		//
		//	/**
		//	 * Insert a new element without attributes.
		//	 * @param namespaceURI The namespace of the element found by the SAX parser.
		//	 * @param lName The local name of the element found by the SAX parser.
		//	 * @param qName The QName of the element found by the SAX parser.
		//	 * @throws XBRLException if the node cannot be appended.
		//	 */
		//	void appendElement(
		//			const std::string& namespaceURI, 
		//			const std::string& lName, 
		//			const std::string& qName);
		//
			void endElement(
					const XMLCh* namespaceURI,
					const XMLCh* lName,
					const XMLCh* qName
					);
		//
		//	/**
		//	 * Append a notation declaration.
		//	 */
		//	void appendNotationDecl(
		//			const std::string& name, 
		//			const std::string& publicId, 
		//			const std::string& systemId
		//			);
		//	
		//	/**
		//	 * Append an unparsed entity declaration.
		//	 */
		//	void appendUnparsedEntityDecl(
		//			const std::string& name, 
		//			const std::string& publicId,
		//			const std::string& systemId, 
		//			const std::string& notationName); 
		//	/**
		//	 * Append an element DTD declaration.
		//	 */
		//	void appendElementDecl(
		//			const std::string& name, 
		//			const std::string& model
		//			);	
		//	
		//	/**
		//	 * Append an internal entity DTD declaration.
		//	 */
		//	void appendInternalEntityDecl(
		//			const std::string& name, 
		//			const std::string& value
		//			);
		//
		//	/**
		//	 * Append an external entity DTD declarations.
		//	 */
		//	void appendExternalEntityDecl(
		//			const std::string& name, 
		//			const std::string& publicId, 
		//			const std::string& systemId
		//			);
		//
		//	/**
		//	 * Append an attribute DTD declaration
		//	 */
		//	void appendAttributeDecl(
		//			const std::string& eName, 
		//			const std::string& aName, 
		//			const std::string& type,
		//			const std::string& valueDefault, 
		//			const std::string& value
		//			);
		//
		//	
		//	/**
		//	 * Set a metadata attribute.
		//	 * @param name The name of the attribute.
		//	 * @param value The value of the attribute.
		//	 **/
		//	void setMetaAttribute(const std::string& name, const std::string& value) ;
		//	
		//	/**
		//	 * @see Builder#getMetaAttribute(String)
		//	 **/
		//	const std::string& getMetaAttribute(const std::string& name) ;
		//	
		//    /**
		//     * @see Builder#hasMetaAttribute(String)
		//     **/
		//    boolean hasMetaAttribute(const std::string& name) ;	
		//
		//	/**
		//	 * Remove a metadata attribute.
		//	 * @param name The name of the attribute.
		//	 **/
		//	void removeMetaAttribute(const std::string& name) ;
		//	
		//    /**
		//     * Appends a child element to the root metadata element.
		//     * @param eName Name of the element to be added (no namespaces are used).
		//     * @param attributes A map from attribute name keys to attribute values.
		//     * @throws XBRLException if the metadata element cannot be appended.
		//     */
		//    void appendMetadataElement(const std::string& eName, Map<String,String> attributes);
		//    
		//    /**
		//     * Removes a child element from the metadata root element by 
		//     * specifying the name of the child and the value of the element's 
		//     * text content and/or the value of a named attribute.  All specified 
		//     * information must match for the deletion to succeed.
		//     * @param eName Name of the element to be added (no namespaces are used).
		//     * @param attributes A hashmap from attribute name keys to attribute values.
		//     * @throws XBRLException if the metadata element cannot be removed.
		//     */
		//    void removeMetadataElement(const std::string& eName, HashMap<String,String> attributes);
		//
		//
		//	private:
		//	/**
		//	 * Set up the data and metadata elements.
		//	 * The element that will contain the data itself is a child of the metadata element.
		//	 * The metadata element becomes the root of the XML fragment that is stored in the data store.
		//	 */
		//	 void setupBuilder() ;
		//	/**
		//	 * Get the XML DOM node.
		//	 * @return the DOM node.
		//	 */
		//	Document getDOM();
		//    /**
		//     * Set the insertion point for new fragment material
		//     * @param e The element that is the current insertion point for data.
		//     */
		//    void setInsertionPoint(Element e) ;
		//    
		//    /**
		//     * Append a node to the data.
		//     * @param child The node to be appended.
		//     * @throws XBRLException if the first node to be appended
		//     * is not an Element node.
		//     */
		//    void appendChild(Node child);
		//
		//    const std::string& getPrefixFromQName(const std::string& qname);
		//    
		//	const std::string& getLocalNameFromQName(const std::string& qname);
		//
		//	/**
		//	 * Create an element node.
		//	 * @param namespaceURI The namespace of the element found by the SAX parser.
		//	 * @param lName The local name of the element found by the SAX parser.
		//	 * @param qName The QName of the element found by the SAX parser.
		//	 * @param attrs The set of attributes found by the SAX parser.
		//	 */
		//	Element createElement(
		//			const std::string& namespaceURI, 
		//			const std::string& lName,
		//			const std::string& qName, 
		//			Attributes attrs);
	};
}