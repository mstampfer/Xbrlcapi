#include "stdafx.h"
#include "FragmentImpl.h"

namespace xbrlcapi
{
/**
* Implements the functionality that is common to all types of XBRL fragments.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
		/**
		//* @see Fragment#getAncestorOrSelf(String)
		//*/
		//Fragment FragmentImpl::getAncestorOrSelf(const std::string& type)
		//{
		//	if (getType().equals(type)) return this;
		//	Fragment parent = this.getParent();
		//	if (parent == null) throw new XBRLException("No ancestor (or self) fragments match the given type: " + type);
		//	return parent.getAncestorOrSelf(type);
		//}

		///**
		//* @see Fragment#getChildren(String)
		//*/
		//template <typename F> FragmentImpl::std::vector<F> getChildren(const std::string& type)
		//{
		//	std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='org.xbrlapi.impl." + type + "Impl']";
		//	if (type.indexOf(".") > -1) {
		//		query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + type + "']";
		//	}

		//	std::vector<F> fragments = getStore().<F>queryForXMLResources(query);
		//	return fragments;
		//}

		///**
		//* @see Fragment#getChildren(Class)
		//*/
		//template <typename F> FragmentImpl::std::vector<F> getChildren(Class<?> requiredClass)
		//{
		//	std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + requiredClass.getName() + "']";        
		//	std::vector<F> fragments = getStore().<F>queryForXMLResources(query);
		//	return fragments;
		//}    

		///**
		//* @see Fragment#getChildrenIndices(String)
		//*/
		//std::unordered_set<String> FragmentImpl::getChildrenIndices(const std::string& type)
		//{
		//	std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + type + "']";
		//	return getStore().queryForIndices(query);
		//}    

		///**
		//* @see Fragment#getSimpleLinks()
		//*/
		//std::vector<SimpleLink> FragmentImpl::getSimpleLinks()
		//{
		//	return this.getStore().<SimpleLink>getChildFragments(SimpleLinkImpl.class,this.getIndex());
		//}

		///**
		//* @see Fragment#getAllChildren()
		//*/
		//std::vector<Fragment> FragmentImpl::getAllChildren()
		//{
		//	std::string xpath = "#roots#[@parentIndex='" + getIndex() + "']";
		//	std::vector<Fragment> fragments = getStore().<Fragment>queryForXMLResources(xpath);
		//	return fragments;
		//}

		///**
		//* @see Fragment#getAllChildrenIndices()
		//*/
		//std::unordered_set<String> FragmentImpl::getAllChildrenIndices()
		//{
		//	std::string xpath = "#roots#[@parentIndex='" + getIndex() + "']";
		//	return getStore().queryForIndices(xpath);
		//}    

		///**
		//* @see Fragment#getChild(String, int)
		//*/
		//Fragment FragmentImpl::getChild(const std::string& type, int index)
		//{
		//	std::vector<Fragment> children = getChildren(type);
		//	if (children == null) return null;
		//	if (index >= children.size()) throw new XBRLException("The index is too high.");
		//	if (index < 0) throw new XBRLException("The index is too low.");
		//	return children.get(index);   
		//}

		///**
		//* @see Fragment#getDataRootElement()
		//*/
		//Element FragmentImpl::getDataRootElement()
		//{
		//	Element dataContainer;

		//	if (getBuilder() != null) {
		//		dataContainer = getBuilder().getData();
		//	} else {
		//		dataContainer = (Element) getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),Constants.FragmentDataContainerElementName).item(0);
		//	}

		//	NodeList children = dataContainer.getChildNodes();
		//	for (int i=0; i< children.getLength(); i++) 
		//		if (children.item(i).getNodeType() == Node.ELEMENT_NODE) return (Element) children.item(i);
		//	throw new XBRLException("The data element of the fragment could not be found.");
		//}

		///**
		//* @see Fragment#isNewFragment()
		//*/
		//bool FragmentImpl::isNewFragment()
		//{
		//	if (getBuilder() == null) return false;
		//	return getBuilder().isNewFragment();
		//}

		///**
		//* @see Fragment#getURI()
		//*/
		//URI FragmentImpl::getURI()
		//{
		//	try {
		//		return new URI(this.getMetaAttribute("uri"));
		//	} catch (URISyntaxException e) {
		//		throw new XBRLException(this.getMetaAttribute("uri") + " has an invalid URI syntax.");
		//	}
		//}

		///**
		//* @see Fragment#setURI(URI)
		//*/
		//void FragmentImpl::setURI(URI uri)
		//{
		//	this.setMetaAttribute("uri",uri.toString());
		//}

		///**
		//* @see Fragment#getReferencingLocators()
		//*/
		//std::vector<Locator> FragmentImpl::getReferencingLocators()
		//{

		//	// Construct the Query
		//	std::string predicate = "*/link:loc and @targetDocumentURI='"+ getURI() +"' and (";
		//	NodeList xptrs = this.getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),"xptr");
		//	for (int i=0; i<xptrs.getLength(); i++) {
		//		std::string value = ((Element) xptrs.item(i)).getAttribute("value").trim();
		//		predicate += "@targetPointerValue='" + value +"'";
		//		if (i == (xptrs.getLength()-1)) 
		//			predicate += ")";
		//		else
		//			predicate += " or ";
		//	}
		//	std::string query = "#roots#[" + predicate + "]";

		//	return getStore().<Locator>queryForXMLResources(query);
		//}

		///**
		//* @see Fragment#getLabels()
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabels()
		//{
		//	logger.info("Getting labels for " + getIndex());
		//	return getStore().getLabels(getIndex());
		//}    

		///**
		//* @see Fragment#getLabelsWithResourceRole(String)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabelsWithResourceRole(const std::string& resourceRole)
		//{
		//	return getStore().getLabelsWithResourceRole(getIndex(),resourceRole);
		//}

		///**
		//* @see Fragment#getLabels(List, List)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabels(std::vector<String> languages, std::vector<String> resourceRoles)
		//{

		//	if (languages == null) {
		//		languages = new Vector<String>();
		//		languages.add(null);
		//	}
		//	if (resourceRoles == null) {
		//		resourceRoles = new Vector<String>();
		//		resourceRoles.add(null);
		//	}

		//	std::vector<LabelResource> result;
		//	for (const std::string& language: languages) {
		//		for (const std::string& role: resourceRoles) {
		//			result = this.getLabelsWithLanguageAndResourceRole(language,role);
		//			if (! result.isEmpty()) return result;
		//		}
		//	}
		//	result = this.getLabels();
		//	if (! result.isEmpty()) return result;
		//	return new Vector<LabelResource>();

		//}

		///**
		//* @see Fragment#getLabels(List, List, List)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabels(std::vector<String> languages, std::vector<String> labelRoles, std::vector<String> linkRoles)
		//{

		//	if (languages == null || labelRoles == null || linkRoles == null) {
		//		throw new XBRLException("Null parameters are not allowed.");
		//	}

		//	std::vector<LabelResource> result;
		//	for (const std::string& linkRole: linkRoles) {
		//		for (const std::string& labelRole: labelRoles) {
		//			for (const std::string& language: languages) {
		//				result = this.getLabelsWithLanguageAndResourceRoleAndLinkRole(language,labelRole, linkRole);
		//				if (! result.isEmpty()) return result;
		//			}
		//		}
		//	}

		//	result = this.getLabels();
		//	if (! result.isEmpty()) return result;

		//	return new Vector<LabelResource>();

		//}    

		///**
		//* @see Fragment#getReferencesWithResourceRole(String)
		//*/
		//std::vector<ReferenceResource> FragmentImpl::getReferencesWithResourceRole(const std::string& role)
		//{
		//	return getStore().getReferencesWithLanguage(getIndex(),role);
		//}

		///**
		//* @see Fragment#getLabelsWithLanguage(String)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabelsWithLanguage(const std::string& language)
		//{
		//	return getStore().getLabelsWithLanguage(getIndex(),language);
		//}

		///**
		//* @see Fragment#getLabelsWithLanguageAndResourceRole(String, String)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabelsWithLanguageAndResourceRole(const std::string& language, const std::string& role)
		//{
		//	return getStore().getLabels(getIndex(),role, language);
		//}

		///**
		//* @see Fragment#getLabelsWithLanguageAndResourceRole(String, String)
		//*/
		//std::vector<LabelResource> FragmentImpl::getLabelsWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const std::string& resourceRole, const std::string& linkRole)
		//{
		//	return getStore().getLabels(getIndex(),linkRole, resourceRole, language);
		//}    

		///**
		//* @see Fragment#getReferences()
		//*/
		//std::vector<ReferenceResource> FragmentImpl::getReferences()
		//{
		//	std::vector<ReferenceResource> references = getStore().getTargets(getIndex(),null,Constants.ReferenceArcrole);
		//	std::vector<ReferenceResource> genericReferences = getStore().getTargets(getIndex(),null,Constants.GenericReferenceArcrole);
		//	references.addAll(genericReferences);
		//	return references;
		//}

		///**
		//* @see Fragment#getReferencesWithLanguage(String)
		//*/
		//std::vector<ReferenceResource> FragmentImpl::getReferencesWithLanguage(const std::string& language)
		//{
		//	std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
		//	std::vector<ReferenceResource> candidates = this.getReferences();
		//	for (ReferenceResource reference: candidates) {
		//		std::string l = reference.getLanguage();
		//		if (l == null) references.add(reference);
		//		else if (l.equals(language)) references.add(reference);
		//	}
		//	return references;
		//}

		///**
		//* @see Fragment#getReferencesWithLanguageAndRole(String, URI)
		//*/
		//std::vector<ReferenceResource> FragmentImpl::getReferencesWithLanguageAndRole(const std::string& language, URI role)
		//{
		//	std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
		//	std::vector<ReferenceResource> candidates = this.getReferences();
		//	for (ReferenceResource reference: candidates) {
		//		std::string l = reference.getLanguage();
		//		std::string r = reference.getResourceRole();
		//		if (l != null && r != null) {
		//			if (l.equals(language) && r.equals(role)) references.add(reference);
		//		} else if (l != null) {
		//			if (l.equals(language) && role == null) references.add(reference);
		//		} else if (r != null) {
		//			if (r.equals(role) && language == null) references.add(reference);
		//		} else {
		//			if (role == null && language == null) references.add(reference);
		//		}
		//	}
		//	return references;
		//}

		///**
		//* @see Fragment#getReferencesWithLanguageAndResourceRoleAndLinkRole(String, URI, URI)
		//*/
		//std::vector<ReferenceResource> FragmentImpl::getReferencesWithLanguageAndResourceRoleAndLinkRole(const std::string& language, URI resourceRole, URI linkRole)
		//{
		//	std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
		//	std::vector<ReferenceResource> candidates = this.getReferences();
		//	for (ReferenceResource reference: candidates) {
		//		if (linkRole == null || reference.getExtendedLink().getLinkRole().equals(linkRole)) {
		//			std::string l = reference.getLanguage();
		//			std::string r = reference.getResourceRole();
		//			if (l != null && r != null) {
		//				if (l.equals(language) && r.equals(resourceRole)) references.add(reference);
		//			} else if (l != null) {
		//				if (l.equals(language) && resourceRole == null) references.add(reference);
		//			} else if (r != null) {
		//				if (r.equals(resourceRole) && language == null) references.add(reference);
		//			} else {
		//				if (resourceRole == null && language == null) references.add(reference);
		//			}
		//		}
		//	}
		//	return references;
		//}    

		///**
		//* @see Fragment#getParentIndex()
		//*/
		//std::string FragmentImpl::getParentIndex()
		//{
		//	return getMetaAttribute("parentIndex");
		//}

		///**
		//* @see Fragment#isChild()
		//*/
		//bool FragmentImpl::isChild()
		//{
		//	return (! this.getParentIndex().equals(""));
		//}

		///**
		//* @see Fragment#isAncestorOf(Fragment)
		//*/
		//bool FragmentImpl::isAncestorOf(const Fragment& descendant)
		//{
		//	if (! descendant.isChild()) return false;
		//	if (this.getIndex().equals(descendant.getParentIndex())) return true;
		//	return this.isAncestorOf(descendant.getParent());
		//}

		///**
		//* @see Fragment#isRoot()
		//*/
		//bool FragmentImpl::isRoot()
		//{
		//	return (getParentIndex().equals(""));
		//}

		///**
		//* @see Fragment#setParentIndex(String)
		//*/
		//void FragmentImpl::setParentIndex(const std::string& index)
		//{
		//	setMetaAttribute("parentIndex",index);
		//}

		///**
		//* @see Fragment#getXPath()
		//*/
		//std::string FragmentImpl::getXPath()
		//{

		//	std::string value = getMetaAttribute("sequenceToParentElement");
		//	if (value.equals("")) return ".";

		//	String[] sequence = value.split(" ");
		//	StringBuffer xpath = new StringBuffer(".");
		//	for (int i=0; i<sequence.length; i++) {
		//		xpath.append("/*[" + sequence[i] + "]");
		//	}    	
		//	return xpath.toString();
		//}

		///**
		//* Determines the sibling order of 
		//* @param current The element that we are determining
		//* the sibling order for.  
		//* @return the order of the element, counting sibling 
		//* elements from the left in document order.
		//*/
		//private:
		//	int FragmentImpl::getSiblingOrder(Element current) {

		//	Node previous = current.getPreviousSibling();

		//	while (previous != null) {
		//		if (previous.getNodeType() != Node.ELEMENT_NODE) 
		//			previous = previous.getPreviousSibling();
		//		else break;
		//	}

		//	if (previous == null) return 1;
		//	return getSiblingOrder((Element) previous) + 1;
		//}

		///**
		//* @see Fragment#setSequenceToParentElement(Fragment)
		//*/
		//void FragmentImpl::setSequenceToParentElement(const Fragment& parent)
		//{

		//	Builder parentBuilder = parent.getBuilder();
		//	if (parentBuilder == null) throw new XBRLException("This method is not usable after the fragment has been built.");
		//	Element current = parentBuilder.getInsertionPoint();
		//	Element next = (Element) current.getParentNode();
		//	Stack<Integer> values = new Stack<Integer>();

		//	while (! next.getNamespaceURI().equals(Constants.XBRLAPINamespace.toString())) {
		//		values.push(new Integer(getSiblingOrder(current)));
		//		current = next;
		//		next = (Element) next.getParentNode();
		//	}

		//	StringBuffer value = new StringBuffer("");
		//	while (! values.empty()) {
		//		Integer v = values.pop();
		//		if (value.length() == 0) {
		//			value.append(v.toString());
		//		} else {
		//			value.append(" " + v.toString()); 
		//		}
		//	}

		//	std::string result = value.toString();
		//	if (! result.equals(""))
		//		setMetaAttribute("sequenceToParentElement",result);

		//}

		///**
		//* @see Fragment#getSequenceToParentElement()
		//*/
		//std::vector<std::string> FragmentImpl::getSequenceToParentElement()
		//{
		//	return this.getSequenceToParentElementAsString().split(" ");
		//}

		///**
		//* @see Fragment#getSequenceToParentElementAsString()
		//*/
		//std::string FragmentImpl::getSequenceToParentElementAsString()
		//{
		//	std::string value = this.getMetaAttribute("sequenceToParentElement");
		//	if (value == null) return "";
		//	return value;
		//}    

		///**
		//* @see Fragment#appendID(String)
		//* TODO Eliminate the ID metadata element given the existence of the xptr elements.
		//*/
		//void FragmentImpl::appendID(const std::string& id)
		//{
		//	HashMap<String,String> attributes = new HashMap<String,String>();
		//	attributes.put("id",id);
		//	appendMetadataElement("ID",attributes);
		//}

		///**
		//* @see Fragment#appendElementSchemeXPointer(String)
		//*/
		//void FragmentImpl::appendElementSchemeXPointer(const std::string& expression)
		//{
		//	HashMap<String,String> attributes = new HashMap<String,String>();
		//	attributes.put("value",expression);
		//	appendMetadataElement("xptr",attributes);
		//}

		///**
		//* @see Fragment#getNamespace()
		//*/
		//std::string FragmentImpl::getNamespace()
		//{
		//	if (getDataRootElement() == null) {
		//		throw new XBRLException("The XML fragment root node is null.");
		//	}
		//	return getDataRootElement().getNamespaceURI();
		//}

		///**
		//* @see Fragment#getLocalname()
		//*/
		//std::string getLocalname()
		//{
		//	return getDataRootElement().getLocalName();
		//}

		///**
		//* @see Fragment#getPrefixFromQName(String)
		//*/
		//std::string FragmentImpl::getPrefixFromQName(const std::string& qname) {
		//	// Get the required namespace prefix from the QName
		//	std::string prefix = "";
		//	int delimiterIndex = qname.indexOf(':');
		//	if (delimiterIndex > 0) {
		//		prefix = qname.substring(0,delimiterIndex);
		//	}
		//	return prefix;
		//}

		///**
		//* Algorithm is as follows:
		//* <ol>
		//*  <li>If the node is an attribute, redo with the parent node.</li>
		//*  <li>If the node is a XBRLAPI metadata element redo with right node in parent fragment.</li>
		//*  <li>If the node is an element in the fragment data:</li>
		//*   <ol>
		//*    <li>Generate namespace declaration attribute name - 'xmlns:...' to search for.</li>
		//*    <li>Try to match the QName prefix to the element's prefix to see if the element namespace is appropriate to return.</li>
		//*    <li>Try to find the attribute doing the namespace declaration on the element and use that.</li>
		//*    <li>If that fails, redo the search using the parent node.</li>
		//*   </ol>
		//* </ol>
		//* 
		//* @see Fragment#getNamespaceFromQName(String, Node)
		//*/
		//std::string FragmentImpl::getNamespaceFromQName(const std::string& qname, Node node)
		//{

		//	if (this.getPrefixFromQName(qname).equals("xml")) return Constants.XMLNamespace;

		//	// If we have an attribute - go straight to working with the parent element.
		//	if (node.getNodeType() == Node.ATTRIBUTE_NODE) {
		//		Node parent = node.getParentNode();
		//		if (parent == null) throw new XBRLException("The attribute has no parent element so the namespace for " + qname + " cannot be determined.");
		//		return getNamespaceFromQName(qname, parent);
		//	}

		//	if (node.getNodeType() == Node.ELEMENT_NODE) {
		//		Element element = (Element) node;

		//		// Go to parent fragment if we are looking at the container element for the fragment data.
		//		std::string elementNamespace = element.getNamespaceURI();
		//		if (elementNamespace != null) {
		//			if (elementNamespace.equals(Constants.XBRLAPINamespace.toString()))
		//			{
		//				if (this.isRoot()) throw new XBRLException("No namespace is defined for QName " + qname);
		//				Fragment parent = getParent();
		//				if (parent == null) throw new XBRLException("A parent fragment is missing from the data store preventing QName resolution for " + qname);
		//				Element parentElement = getParentElement(parent.getDataRootElement());
		//				return parent.getNamespaceFromQName(qname, parentElement);
		//			}
		//		}

		//		// Try to exploit a known namespace mapping for the element or one of its attributes
		//		std::string prefix = getPrefixFromQName(qname);

		//		if ((node.getPrefix() == null) && (prefix.equals(""))) {
		//			return node.getNamespaceURI();
		//		}

		//		if ((node.getPrefix() != null) && (node.getPrefix().equals(prefix))) {
		//			return node.getNamespaceURI();
		//		}
		//		NamedNodeMap attrs = node.getAttributes();
		//		for (int i=0; i<attrs.getLength(); i++) {
		//			Node attr = attrs.item(i);

		//			if ((attr.getPrefix() == null) && (prefix.equals(""))) {
		//				return attr.getNamespaceURI();
		//			}

		//			if ((attr.getPrefix() != null) && (attr.getPrefix().equals(prefix))) {
		//				return attr.getNamespaceURI();
		//			}
		//		}

		//		// Create NS prefix declaration for the QName being sought.
		//		std::string declaration = "xmlns";
		//		if (!prefix.equals("")) {
		//			declaration = declaration + ":" + prefix;
		//		}

		//		// Check for a namespace declaration on the current element
		//		if (element.hasAttribute(declaration)) {
		//			std::string ns = element.getAttribute(declaration);
		//			if (ns.equals("")) {
		//				return null;// The namespace prefix has been undefined by the declaration.
		//			}
		//			return ns;
		//		}

		//		return getNamespaceFromQName(qname, element.getParentNode());

		//	}

		//	throw new XBRLException("An element or attribute node is expected.");

		//}

		///**
		//* Algorithm is as follows:
		//* <ol>
		//*  <li>If the node is an attribute, redo with the parent node.</li>
		//*  <li>If the node is a XBRLAPI metadata element redo with right node in parent fragment.</li>
		//*  <li>If the node is an element in the fragment data:</li>
		//*   <ol>
		//*    <li>Try to find the XML lang attribute and use its value.</li>
		//*    <li>If that fails, redo the search using the parent node.</li>
		//*   </ol>
		//* </ol>
		//* 
		//* @see Fragment#getLanguage(Node)
		//*/
		//std::string FragmentImpl::getLanguage(Node node)
		//{

		//	// If we have an attribute - go straight to working with the parent element.
		//	if (node.getNodeType() != Node.ELEMENT_NODE) {
		//		Node parentNode = node.getParentNode();
		//		if (parentNode == null) return null;
		//		return getLanguage(parentNode);
		//	}

		//	Element element = (Element) node;

		//	// Go to parent fragment if we are looking at the container element for the fragment data.
		//	std::string elementNamespace = element.getNamespaceURI();
		//	if (elementNamespace != null) {
		//		if (elementNamespace.equals(Constants.XBRLAPINamespace.toString())) {
		//			if (this.isRoot()) {
		//				return null;
		//			}
		//			Fragment parent = getParent();
		//			if (parent == null) {
		//				throw new XBRLException("A parent fragment is missing from the data store preventing language code identification.");
		//			}
		//			Element parentElement = getParentElement(parent.getDataRootElement());
		//			return parent.getLanguage(parentElement);
		//		}
		//	}

		//	// Check for a language code on the current element
		//	if (element.hasAttributeNS(Constants.XMLNamespace.toString(), "lang")) {
		//		return element.getAttributeNS(Constants.XMLNamespace.toString(), "lang");
		//	}

		//	// Check for a language code on the parent element
		//	return getLanguage(element.getParentNode());

		//}

		///**
		//* @see Fragment#getLanguage()
		//* @see Fragment#getLanguage(Node)
		//*/
		//std::string FragmentImpl::getLanguage()
		//{
		//	return this.getLanguage(this.getDataRootElement());
		//}



		///**
		//* @see Fragment#getLanguageName(String)
		//*/
		//std::string getLanguageName(const std::string& language)
		//{
		//	Language l  = getStore().getLanguage(language,this.getLanguage());
		//	if (l == null) return null;
		//	return l.getName();
		//}

		///**
		//* @see Fragment#getLanguageName(List)
		//*/
		//std::string FragmentImpl::getLanguageName(std::vector<String> languages)
		//{
		//	for (const std::string& language: languages) {
		//		Language l  = getStore().getLanguage(language,this.getLanguage());
		//		if (l != null) return l.getName();
		//	}
		//	return null;
		//}    

		///**
		//* @see Fragment#getParent()
		//*/
		//Fragment FragmentImpl::getParent()
		//{
		//	if (! this.isChild()) return null;
		//	std::string parentIndex = this.getParentIndex();
		//	return getStore().getXMLResource(parentIndex);
		//}

		///**
		//* This method operates as follows:
		//* <ol>
		//*  <li>If the sequence to the parent element indicates that the 
		//*  data root element is the parent - use that.</li>
		//*  <li>Loop through the sequence to the parent element.</li>
		//* </ol>
		//* @see Fragment#getParentElement(Element)
		//*/
		//Element FragmentImpl::getParentElement(Element parentDataRootElement)
		//{

		//	String[] sequence = getSequenceToParentElement();

		//	// If there is no data about the sequence then just return the given parent data root element
		//	if (sequence[0].equals("")) {
		//		return parentDataRootElement;
		//	}

		//	// Traverse the parent data DOM to find the parent element of this fragment's root element.
		//	Element current = parentDataRootElement;
		//	for (const std::string& value: sequence) {
		//		int elementOrder = (new Integer(value)).intValue();
		//		int elementsFound = 0;
		//		NodeList children = current.getChildNodes();
		//		int j = 0;
		//		// While there are still children to consider and we have not found 
		//		while ((elementsFound < elementOrder) && (j < children.getLength())) {
		//			Node child = children.item(j);
		//			if (child.getNodeType() == Node.ELEMENT_NODE) {
		//				elementsFound++;
		//				if (elementsFound == elementOrder) current = (Element) child;
		//			}
		//			j++;
		//		}
		//		if ((j==children.getLength()) && (elementsFound < elementOrder)) {
		//			throw new XBRLException("The sequence to the parent element is incorrect.");
		//		}
		//	}
		//	return current;

		//}

		///**
		//* @see Fragment#getLocalnameFromQName(String)
		//*/
		//std::string FragmentImpl::getLocalnameFromQName(const std::string& qname) {
		//	std::string localname = qname;
		//	int delimiterIndex = qname.indexOf(':');
		//	if (delimiterIndex > 0) {
		//		localname = qname.substring(delimiterIndex+1,qname.length());
		//	}
		//	return localname;
		//}

		///**
		//* @see Fragment#getXPointerExpression()
		//*/
		//std::string FragmentImpl::getXPointerExpression()
		//{
		//	std::string expression = this.getIDXPointerExpression();
		//	if (expression != null) {
		//		return "#" + expression;
		//	}
		//	expression = this.getElementSchemeXPointerExpression();
		//	return "#" + "element(" + expression + ")";
		//}

		///**
		//* @see Fragment#getElementSchemeXPointerExpression()
		//*/
		//std::string getElementSchemeXPointerExpression()
		//{
		//	NodeList nodes = getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),"xptr");
		//	if (nodes.getLength() == 0) throw new XBRLException("The fragment is missing its element scheme XPointer expression.");
		//	Element xptrElement = (Element) nodes.item(0);
		//	if (xptrElement.hasAttribute("value")) return xptrElement.getAttribute("value");
		//	throw new XBRLException("An element-scheme XPointer expression is corrupted for this fragment.");        
		//}

		///**
		//* @see Fragment#getIDXPointerExpression()
		//*/
		//std::string FragmentImpl::getIDXPointerExpression()
		//{
		//	NodeList nodes = getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),"ID");
		//	if (nodes.getLength() == 0) return null;
		//	Element idElement = (Element) nodes.item(0);
		//	if (idElement.hasAttribute("id")) return idElement.getAttribute("id");
		//	throw new XBRLException("The shorthand ID for this fragment is missing.");
		//}
}
