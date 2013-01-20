#include "builder.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include "Constants.h"
#include "XBRLException.h"



namespace xbrlcapi
{
	struct Builder::Impl 
	{
		Impl() {}	
		/**
		* The XML DOM used to build up fragments.
		*/
		std::shared_ptr<xercesc::DOMDocument> dom;

		/**
		* The metadata root element.
		*/
		std::shared_ptr<xercesc::DOMElement>  metadata;

		/**
		* The element to append new content during construction.
		*/
		std::shared_ptr<xercesc::DOMElement>  insertionPoint;

		/**
		* Flag to indicate that a fragment has yet to have any data inserted into it.
		*/
		bool newFragment;

		Impl(const xercesc::DOMDocument& dom)
		{
			//		this->dom = std::shared_ptr<xercesc::DOMDocument>(&dom);
			setupBuilder();
		}

		void setupBuilder() 
		{
			/*			metadata = dom->createElementNS(XMLConstants::XBRLAPINamespace,
			XMLConstants::XBRLAPIPrefix + ":" + 
			XMLConstants::FragmentRootElementName);

			std::shared_ptr<xercesc::DOMElement>  container = 
			dom->createElementNS(XMLConstants::XBRLAPINamespace,
			XMLConstants::XBRLAPIPrefix + ":" + 
			XMLConstants::FragmentDataContainerElementName);

			setInsertionPoint(container);
			metadata->appendChild(container);*/		
		}



		//public BuilderImpl() throws XBRLException {
		//	if (dom == null) {
		//		dom = (new XMLDOMBuilder()).newDocument();
		//	}		
		//	setupBuilder();
		//}



		//public void close() {
		//	dom = null;
		//}
		//


		//private Document getDOM() {
		//	return dom;
		//}



		//public std::shared_ptr<xercesc::DOMElement>  getData() throws XBRLException {
		//	NodeList dataElements = getMetadata().getElementsByTagNameNS(Constants.XBRLAPINamespace,Constants.FragmentDataContainerElementName);
		//	if (dataElements.getLength() > 1) throw new XBRLException("The XML Resource being built has more than one data fragment.");
		//       if (dataElements.getLength() == 0) throw new XBRLException("The XML Resource being built has no data fragments.");
		//	return ((Element) dataElements.item(0));
		//}



		std::shared_ptr<xercesc::DOMElement>  getMetaData() 
		{
			return metadata;
		}



		bool isNewFragment() 
		{
			return newFragment;
		}



		//   public std::shared_ptr<xercesc::DOMElement>  getInsertionPoint() {
		//   	return insertionPoint;
		//   }



		void setInsertionPoint(const std::shared_ptr<xercesc::DOMElement>& e) 
		{
			insertionPoint = e;
		}



		void appendChild(const xercesc::DOMNode& child)
		{
			//if (isNewFragment) 
			//{
			//	if (child.getNodeType() != xercesc::DOMElement::ELEMENT_NODE) 
			//		throw XBRLException("The first child to be inserted must be an element node");
			//	getInsertionPoint().appendChild(child);
			//	isNewFragment = false;
			//} 
			//else 
			//{
			//	getInsertionPoint().appendChild(child);
			//}
			//if (child.getNodeType() == Element.ELEMENT_NODE) setInsertionPoint((Element) child);
		}



		void appendText(const std::string& text)
		{
			//			appendChild(dom.createTextNode(text));
		}



		void appendProcessingInstruction(const std::string& target, const std::string& data)
		{
			//			appendChild(dom->createProcessingInstruction(XercesString(target), XercesString(data)));
		}

		//public void appendComment(String text) throws XBRLException
		//{
		//	appendChild(getDOM().createComment(text));
		//}

		void appendElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName, 
			const xercesc::Attributes& attrs)
		{

			//std::shared_ptr<xercesc::DOMElement>  newElement = createElement(namespaceURI, lName, qName, attrs);
			//if (newElement == null) {
			//	throw new XBRLException("Could not create element: " + namespaceURI + " " + lName);
			//}
			//appendChild(newElement);
		}

		//   private String getPrefixFromQName(String qname) {
		//       // Get the required namespace prefix from the QName
		//       String prefix = "";
		//       int delimiterIndex = qname.indexOf(':');
		//       if (delimiterIndex > 0) {
		//           prefix = qname.substring(0,delimiterIndex);
		//       }
		//       return prefix;
		//   }

		//   private String getLocalNameFromQName(String qname) {
		//       String localname = qname;
		//       int delimiterIndex = qname.indexOf(':');
		//       if (delimiterIndex > 0) {
		//           localname = qname.substring(delimiterIndex+1,qname.length());
		//       }
		//       return localname;
		//   }    
		//   

		//private std::shared_ptr<xercesc::DOMElement>  createElement(
		//		String namespaceURI, 
		//		String lName,
		//		String qName, 
		//		Attributes attrs)  {

		//	// Keep track of namespace prefixes used by the element or its attributes
		//	Set<String> prefixes = new HashSet<String>();
		//	prefixes.add(getPrefixFromQName(qName));

		//	std::shared_ptr<xercesc::DOMElement>  newElement = getDOM().createElementNS(namespaceURI, qName);
		//			
		//	// Handle elements created with a null attrs array (not created from SAX parsing input)
		//	if (attrs == null)
		//		return newElement;
		//
		//	// Insert all attributes with namespaces
		//	for (int i=0; i<attrs.getLength(); i++) {
		//		if (attrs.getURI(i).equals(Constants.XMLNamespace)) {
		//               newElement.setAttributeNS(attrs.getURI(i), attrs.getQName(i),attrs.getValue(i));
		//			prefixes.add(Constants.XMLPrefix);
		//		} else if (! attrs.getURI(i).equals("")) {
		//			newElement.setAttributeNS(attrs.getURI(i), attrs.getQName(i),attrs.getValue(i));
		//			prefixes.add(getPrefixFromQName(attrs.getQName(i)));
		//		}
		//	}
		//	
		//	for (int i = 0; i < attrs.getLength(); i++) {
		//           if (! attrs.getURI(i).equals(""))
		//               ; 
		//           else if (! attrs.getQName(i).startsWith("xmlns")) {
		//               newElement.setAttribute(attrs.getQName(i),attrs.getValue(i));
		//           } else {
		//               String qname = attrs.getQName(i);
		//               String declaration = "";
		//               if (qname.contains(":")) declaration = qname.substring(6);
		//               if (! prefixes.contains(declaration)) {
		//                   newElement.setAttribute(attrs.getQName(i),attrs.getValue(i));
		//               }
		//           }
		//	}

		//	return newElement;
		//}		
		//

		//public void appendElement(
		//		String namespaceURI, 
		//		String lName, 
		//		String qName) throws XBRLException	
		//{
		//	appendElement(namespaceURI,lName,qName,null);
		//}

		//
		//

		void endElement(
			const XMLCh* namespaceURI,
			const XMLCh* lName,
			const XMLCh* qName)
		{
			//	
			//	// Make sure that the insertion point is stepping up from an element node (to an element or document node)
			//	if (getInsertionPoint().getNodeType() != Node.ELEMENT_NODE)
			//		throw new XBRLException("The fragment insertion point is pointing to the wrong kind of node: " + getInsertionPoint().getNodeType() + ".");
			//	
			//	Node parentNode = getInsertionPoint().getParentNode();
			//	if (parentNode != null) {
			//		if (parentNode.getNodeType() != Element.ELEMENT_NODE) {
			//			throw new XBRLException("The fragment builder insertion point is trying to move to a non-element node.");
			//		}
			//		setInsertionPoint((Element) parentNode);
			//	}
			//	
		}

		//public void appendNotationDecl(
		//		String name, 
		//		String publicId, 
		//		String systemId
		//		) throws XBRLException {
		//    StringBuffer b = new StringBuffer("<!NOTATION ");
		//    b.append(name);
		//    if (publicId != null)
		//      b.append(" PUBLIC \"").append(publicId).append('"');
		//    if (systemId != null)
		//      b.append(" SYSTEM \"").append(systemId).append('"');
		//    b.append('>');
		//	// TODO How do I add a notation node to the DOM when fragment building
		//}
		//

		//public void appendUnparsedEntityDecl(
		//		String name, 
		//		String publicId,
		//		String systemId, 
		//		String notationName) 
		//throws XBRLException {
		//    StringBuffer b = new StringBuffer("<!ENTITY ");
		//    b.append(name);
		//    if (publicId != null)
		//      b.append(" PUBLIC \"").append(publicId).append('"');
		//    if (systemId != null)
		//      b.append(" SYSTEM \"").append(systemId).append('"');
		//    b.append(" NDATA \"").append(notationName).append('"');
		//    b.append('>');
		//    
		//	// TODO How to add an unparsed Entity Declaration to a DOM.
		//    throw new XBRLException("Not yet implemented.");
		//}

		//public void appendElementDecl(
		//		String name, 
		//		String model
		//		) throws XBRLException {
		//	// TODO How to add an element DTD declaration to a DOM
		//    throw new XBRLException("Not yet implemented.");
		//}	
		//


		//public void appendInternalEntityDecl(
		//		String name, 
		//		String value
		//		) throws XBRLException {
		//	// TODO How to add an internal entity declaration
		//    throw new XBRLException("Not yet implemented.");
		//}


		//public void appendExternalEntityDecl(
		//		String name, 
		//		String publicId, 
		//		String systemId
		//		) throws XBRLException {
		//	// TODO Determine how to add an external entity declaration
		//    throw new XBRLException("Not yet implemented.");
		//}

		//public void appendAttributeDecl(
		//		String eName, 
		//		String aName, 
		//		String type,
		//		String valueDefault, 
		//		String value
		//		) throws XBRLException {
		//	// TODO How to add an attribute DTD declaration
		//    throw new XBRLException("Not yet implemented.");
		//}

		//public void setMetaAttribute(String name, String value) {
		//	getMetadata().setAttribute(name,value);		
		//}
		//

		//public String getMetaAttribute(String name) {
		//    if (! hasMetaAttribute(name)) return null;
		//    return getMetadata().getAttribute(name); 
		//}
		//

		//   public bool hasMetaAttribute(String name) {
		//       return getMetadata().hasAttribute(name); 
		//   }	

		//public void removeMetaAttribute(String name) {
		//	getMetadata().removeAttribute(name);		
		//}
		//

		//   public void appendMetadataElement(String eName, Map<String,String> attributes) throws XBRLException {

		//	std::shared_ptr<xercesc::DOMElement>  child = getDOM().createElementNS(Constants.XBRLAPINamespace,Constants.XBRLAPIPrefix + ":" + eName);
		//	Iterator<String> attributeNames = attributes.keySet().iterator();
		//	while (attributeNames.hasNext()) {
		//		String aName = attributeNames.next();
		//		String aValue = attributes.get(aName);
		//		if (aName != null) {
		//			if (aValue == null) throw new XBRLException("A metadata element is being added but attribute, " + aName + ", has a null value.");
		//			child.setAttribute(aName,aValue); 
		//		} else throw new XBRLException("A metadata element is being added with an attribute with a null name.");
		//	}
		//	getMetadata().appendChild(child);
		//	
		//   }
		//   


		//   public void removeMetadataElement(String eName, HashMap<String,String> attributes) throws XBRLException {

		//	NodeList children = getMetadata().getElementsByTagNameNS(Constants.XBRLAPINamespace,eName);
		//	for (int i=0; i<children.getLength(); i++) {
		//		bool match = true;
		//		std::shared_ptr<xercesc::DOMElement>  child = (Element) children.item(i);
		//		Iterator<String> attributeNames = attributes.keySet().iterator();
		//		while (attributeNames.hasNext()) {
		//			String aName = attributeNames.next();
		//			String aValue = attributes.get(aName);
		//			if (aName != null) {
		//				if (aValue == null) throw new XBRLException("A metadata element is being checked but attribute, " + aName + ", has a null value.");
		//				if (! child.getAttribute(aName).equals(aValue)) {
		//					match = false;
		//				}
		//			} else throw new XBRLException("A metadata element is being checked against an attribute with a null name.");
		//		}
		//		
		//		if (match) {
		//			getMetadata().removeChild(child);
		//			break;
		//		}
		//	}
		//   	
		//   }

	};

	Builder::Builder() {}
	Builder::~Builder() {} 

	Builder::Builder(const Builder& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Builder& Builder::operator=(const Builder& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Builder::Builder(Builder&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Builder& Builder::operator=(Builder&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Builder::operator==(const Builder& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Builder::operator!=(const Builder& rhs)
	{
		return !this->operator==(rhs);
	}

	std::shared_ptr<xercesc::DOMElement>  Builder::getMetadata()
	{
		return pImpl->getMetaData();
	}

	void Builder::appendText(const std::string& text)
	{
		pImpl->appendText(text);
	}

	void Builder::endElement(
		const XMLCh* namespaceURI,
		const XMLCh* lName,
		const XMLCh* qName
		)
	{
		pImpl->endElement(
			namespaceURI,
			lName,
			qName);
	}

	void Builder::appendElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName, 
		const xercesc::Attributes& attrs)
	{
		pImpl->appendElement(namespaceURI,lName,qName,attrs);
	}
	void Builder::appendProcessingInstruction(const std::string& target, const std::string& data)
	{
		pImpl->appendProcessingInstruction(target, data);
	}
}


