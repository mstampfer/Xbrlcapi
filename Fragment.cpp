#include "Fragment.h"
#include "Builder.h"
#include "Store.h"
#include "LabelResource.h"
#include "ReferenceResource.h"
#include "SimpleLink.h"

namespace xbrlcapi
{


	struct Fragment::Impl : public XML
	{
		Impl() {}

		//		int getSiblingOrder(Element current);

		Fragment getAncestorOrSelf(const std::string& type)
		{
			//if (getType().equals(type)) return this;
			//Fragment parent = this.getParent();
			//if (parent == null) throw XBRLException("No ancestor (or self) fragments match the given type: " + type);
			//return parent.getAncestorOrSelf(type);
			return Fragment();
		}

		template <typename T> 
		std::vector<T> getChildren(const std::string& type)
		{
			//	std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='org.xbrlapi.impl." + type + "Impl']";
			//	if (type.indexOf(".") > -1) {
			//		query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + type + "']";
			//}

			//	std::vector<F> fragments = getStore().<F>queryForXMLResources(query);
			//	return fragments;
			return std::vector<T>();
		}

		template <typename T> 
		std::vector<T> getChildren(const T& requiredClass)
		{
			//std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + requiredClass.getName() + "']";        
			//std::vector<F> fragments = getStore().<F>queryForXMLResources(query);
			//return fragments;
			return std::vector<T>();
		}    

		std::unordered_set<std::string> getChildrenIndices(const std::string& type)
		{
			/*			std::string query = "#roots#[@parentIndex='" + getIndex() + "' and @type='" + type + "']";
			return getStore().queryForIndices(query)*/;
		return std::unordered_set<std::string>();
		}    

		//std::vector<SimpleLink> getSimpleLinks()
		//{
		//	//return this.getStore().<SimpleLink>getChildFragments(SimpleLinkImpl.class,this.getIndex());
		//	return std::vector<SimpleLink>();
		//}

		std::vector<Fragment> getAllChildren()
		{
			////std::string xpath = "#roots#[@parentIndex='" + getIndex() + "']";
			////std::vector<Fragment> fragments = getStore().<Fragment>queryForXMLResources(xpath);
			////return fragments;
			//return std::vector<Fragment>();
			return std::vector<Fragment>();
		}


		std::unordered_set<std::string> getAllChildrenIndices()
		{
			////std::string xpath = "#roots#[@parentIndex='" + getIndex() + "']";
			////return getStore().queryForIndices(xpath);
			//return std::unordered_set<std::string>();
			return std::unordered_set<std::string>();
		}    

		Fragment getChild(const std::string& type, int index)
		{
			//	std::vector<Fragment> children = getChildren(type);
			//	if (children == null) return null;
			//	if (index >= children.size()) throw XBRLException("The index is too high.");
			//	if (index < 0) throw XBRLException("The index is too low.");
			//	return children.get(index);   
			return Fragment();
		}

		std::shared_ptr<xercesc::DOMElement> getDataRootElement()
		{
			//Element dataContainer;

			//if (getBuilder() != null) {
			//	dataContainer = getBuilder().getData();
			//} else {
			//	dataContainer = (Element) getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),Constants.FragmentDataContainerElementName).item(0);
			//}

			//NodeList children = dataContainer.getChildNodes();
			//for (int i=0; i< children.getLength(); i++) 
			//	if (children.item(i).getNodeType() == Node.ELEMENT_NODE) return (Element) children.item(i);
			//throw XBRLException("The data element of the fragment could not be found.");
			return std::shared_ptr<xercesc::DOMElement>();
		}

		bool isNewFragment()
		{
			//if (getBuilder() == NULL) return false;
			//return getBuilder().isNewFragment();
		return false;
		}

		Poco::URI getURI()
		{
			//try {
			//	return new URI(this.getMetaAttribute("uri"));
			//} catch (URISyntaxException e) {
			//	throw XBRLException(this.getMetaAttribute("uri") + " has an invalid URI syntax.");
			//}
			return Poco::URI();
		}

		void setURI(const Poco::URI& uri)
		{
			setMetaAttribute("uri",uri.toString());
		}

		std::vector<xercesc::Locator> getReferencingLocators()
		{

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
			return std::vector<xercesc::Locator>();
		}


		std::vector<LabelResource> getLabels()
		{
			//logger.info("Getting labels for " + getIndex());
			//return getStore().getLabels(getIndex());
			return std::vector<LabelResource>();

		}    


		std::vector<LabelResource> getLabelsWithResourceRole(const std::string& resourceRole)
		{
			//return getStore().getLabelsWithResourceRole(getIndex(),resourceRole);
			return std::vector<LabelResource>();
		}


		std::vector<LabelResource> getLabels(const std::vector<std::string>& languages, 
			const std::vector<std::string>& resourceRoles)
		{

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
			return std::vector<LabelResource>();
		}


		std::vector<LabelResource> getLabels(const std::vector<std::string>& languages, 
			const std::vector<std::string>& labelRoles, 
			const std::vector<std::string>& linkRoles)
		{

			//	if (languages == null || labelRoles == null || linkRoles == null) {
			//		throw XBRLException("Null parameters are not allowed.");
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
			return std::vector<LabelResource>();
		}    

		std::vector<ReferenceResource> getReferencesWithResourceRole(const std::string& role)
		{
			return getStore().getReferencesWithLanguage(getIndex(),role);
		}

		std::vector<LabelResource> getLabelsWithLanguage(const std::string& language)
		{
			return getStore().getLabelsWithLanguage(getIndex(),language);
		}

		std::vector<LabelResource> getLabelsWithLanguageAndResourceRole(const std::string& language, const std::string& role)
		{
			return getStore().getLabels(getIndex(),role, language);
		}

		std::vector<LabelResource> getLabelsWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const std::string& resourceRole, const std::string& linkRole)
		{
			return getStore().getLabels(getIndex(),linkRole, resourceRole, language);
		}    

		std::vector<ReferenceResource> getReferences()
		{
			//std::vector<ReferenceResource> references = getStore().getTargets(getIndex(),null,Constants.ReferenceArcrole);
			//std::vector<ReferenceResource> genericReferences = getStore().getTargets(getIndex(),null,Constants.GenericReferenceArcrole);
			//references.addAll(genericReferences);
			//return references;
			return std::vector<ReferenceResource>();
		}

		std::vector<ReferenceResource> getReferencesWithLanguage(const std::string& language)
		{
			//std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
			//std::vector<ReferenceResource> candidates = this.getReferences();
			//for (ReferenceResource reference: candidates) {
			//	std::string l = reference.getLanguage();
			//	if (l == null) references.add(reference);
			//	else if (l.equals(language)) references.add(reference);
			//}
			//return references;
			return std::vector<ReferenceResource> ();
		}


		std::vector<ReferenceResource> getReferencesWithLanguageAndRole(const std::string& language, const Poco::URI& role)
		{
			//std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
			//std::vector<ReferenceResource> candidates = this.getReferences();
			//for (ReferenceResource reference: candidates) {
			//	std::string l = reference.getLanguage();
			//	std::string r = reference.getResourceRole();
			//	if (l != null && r != null) {
			//		if (l.equals(language) && r.equals(role)) references.add(reference);
			//	} else if (l != null) {
			//		if (l.equals(language) && role == null) references.add(reference);
			//	} else if (r != null) {
			//		if (r.equals(role) && language == null) references.add(reference);
			//	} else {
			//		if (role == null && language == null) references.add(reference);
			//	}
			//}
			//return references;
			return std::vector<ReferenceResource> ();
		}

		std::vector<ReferenceResource> getReferencesWithLanguageAndResourceRoleAndLinkRole(const std::string& language, 
			const Poco::URI& resourceRole, 
			const Poco::URI& linkRole)
		{
			//std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
			//std::vector<ReferenceResource> candidates = this.getReferences();
			//for (ReferenceResource reference: candidates) {
			//	if (linkRole == null || reference.getExtendedLink().getLinkRole().equals(linkRole)) {
			//		std::string l = reference.getLanguage();
			//		std::string r = reference.getResourceRole();
			//		if (l != null && r != null) {
			//			if (l.equals(language) && r.equals(resourceRole)) references.add(reference);
			//		} else if (l != null) {
			//			if (l.equals(language) && resourceRole == null) references.add(reference);
			//		} else if (r != null) {
			//			if (r.equals(resourceRole) && language == null) references.add(reference);
			//		} else {
			//			if (resourceRole == null && language == null) references.add(reference);
			//		}
			//	}
			//}
			//return references;
			return std::vector<ReferenceResource>();
		}    

		std::string getParentIndex()
		{
			return getMetaAttribute("parentIndex");
		}

		bool isChild()
		{
			//	return (! getParentIndex().equals(""));
			return false;
		}


		bool isAncestorOf(const Fragment& descendant)
		{
			//if (! descendant.isChild()) return false;
			//if (this.getIndex().equals(descendant.getParentIndex())) return true;
			//return this.isAncestorOf(descendant.getParent());
			return false;
		}

		bool isRoot()
		{
			//	return (getParentIndex().equals(""));
			return false;
		}

		void setParentIndex(const std::string& index)
		{
			setMetaAttribute("parentIndex",index);
		}


		std::string getXPath()
		{
			//std::string value = getMetaAttribute("sequenceToParentElement");
			//if (value.equals("")) return ".";

			//String[] sequence = value.split(" ");
			//StringBuffer xpath = new StringBuffer(".");
			//for (int i=0; i<sequence.length; i++) {
			//	xpath.append("/*[" + sequence[i] + "]");
			//}    	
			//return xpath.toString();
			return std::string();
		}


		int getSiblingOrder(const xercesc::DOMElement& current) 
		{

			//	Node previous = current.getPreviousSibling();

			//	while (previous != null) {
			//		if (previous.getNodeType() != Node.ELEMENT_NODE) 
			//			previous = previous.getPreviousSibling();
			//		else break;
			//	}

			//	if (previous == null) return 1;
			//	return getSiblingOrder((Element) previous) + 1;
			return 0;
		}

		void setSequenceToParentElement(const Fragment& parent)
		{

			//Builder parentBuilder = parent.getBuilder();
			//if (parentBuilder == null) throw XBRLException("This method is not usable after the fragment has been built.");
			//Element current = parentBuilder.getInsertionPoint();
			//Element next = (Element) current.getParentNode();
			//Stack<Integer> values = new Stack<Integer>();

			//while (! next.getNamespaceURI().equals(Constants.XBRLAPINamespace.toString())) {
			//	values.push(new Integer(getSiblingOrder(current)));
			//	current = next;
			//	next = (Element) next.getParentNode();
			//}

			//StringBuffer value = new StringBuffer("");
			//while (! values.empty()) {
			//	Integer v = values.pop();
			//	if (value.length() == 0) {
			//		value.append(v.toString());
			//	} else {
			//		value.append(" " + v.toString()); 
			//	}
			//}

			//std::string result = value.toString();
			//if (! result.equals(""))
			//	setMetaAttribute("sequenceToParentElement",result);

		}

		std::vector<std::string> getSequenceToParentElement()
		{
			//			return getSequenceToParentElementAsString().split(" ");
			return std::vector<std::string>();
		}


		std::string getSequenceToParentElementAsString()
		{
			std::string value = getMetaAttribute("sequenceToParentElement");
			if (value.empty()) return "";
			return value;
		}    

		void appendID(const std::string& id)
		{
			std::unordered_map<std::string,std::string> attributes;
			attributes.insert(std::make_pair("id",id));
			appendMetadataElement("ID",attributes);
		}

		void appendElementSchemeXPointer(const std::string& expression)
		{
			std::unordered_map<std::string, std::string> attributes;
			attributes.insert(std::make_pair("value",expression));
			appendMetadataElement("xptr",attributes);
		}

		std::string getNamespace()
		{
			/*	if (getDataRootElement() == null) {
			throw XBRLException("The XML fragment root node is null.");
			}
			return getDataRootElement().getNamespaceURI();*/
			return std::string();
		}

		std::string getLocalname()
		{
			//	return getDataRootElement().getLocalName();
			return std::string();
		}

		std::string getPrefixFromQName(const std::string& qname) 
		{
			//// Get the required namespace prefix from the QName
			//std::string prefix = "";
			//int delimiterIndex = qname.indexOf(':');
			//if (delimiterIndex > 0) {
			//	prefix = qname.substring(0,delimiterIndex);
			//}
			//return prefix;
			return std::string();
		}

		std::string getNamespaceFromQName(const std::string& qname, const xercesc::DOMNode& node)
		{

			//	if (this.getPrefixFromQName(qname).equals("xml")) return Constants.XMLNamespace;

			//	// If we have an attribute - go straight to working with the parent element.
			//	if (node.getNodeType() == Node.ATTRIBUTE_NODE) {
			//		Node parent = node.getParentNode();
			//		if (parent == null) throw XBRLException("The attribute has no parent element so the namespace for " + qname + " cannot be determined.");
			//		return getNamespaceFromQName(qname, parent);
			//	}

			//	if (node.getNodeType() == Node.ELEMENT_NODE) {
			//		Element element = (Element) node;

			//		// Go to parent fragment if we are looking at the container element for the fragment data.
			//		std::string elementNamespace = element.getNamespaceURI();
			//		if (elementNamespace != null) {
			//			if (elementNamespace.equals(Constants.XBRLAPINamespace.toString()))
			//			{
			//				if (this.isRoot()) throw XBRLException("No namespace is defined for QName " + qname);
			//				Fragment parent = getParent();
			//				if (parent == null) throw XBRLException("A parent fragment is missing from the data store preventing QName resolution for " + qname);
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
			return std::string();
		}

		//	throw XBRLException("An element or attribute node is expected.");

		//}

		std::string getLanguage(const xercesc::DOMNode& node)
		{

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
			//				throw XBRLException("A parent fragment is missing from the data store preventing language code identification.");
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
			return std::string();

		}

		std::string getLanguage()
		{
			//			return getLanguage(getDataRootElement());
			return std::string();
		}



		std::string getLanguageName(const std::string& language)
		{
			//Language l  = getStore().getLanguage(language,this.getLanguage());
			//if (l == null) return null;
			//return l.getName();
			return std::string();
		}

		std::string getLanguageName(const std::vector<std::string>& languages)
		{
			//for (const std::string& language: languages) {
			//	Language l  = getStore().getLanguage(language,this.getLanguage());
			//	if (l != null) return l.getName();
			//}
			//return null;
			return std::string();
		}    

		Fragment getParent()
		{
			//if (! this.isChild()) return null;
			//std::string parentIndex = this.getParentIndex();
			//return getStore().getXMLResource(parentIndex);
			return Fragment();
		}


		std::shared_ptr<xercesc::DOMElement> getParentElement(const xercesc::DOMElement& parentDataRootElement)
		{

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
			//			throw XBRLException("The sequence to the parent element is incorrect.");
			//		}
			//	}
			//	return current;
			return std::shared_ptr<xercesc::DOMElement>();
		}


		std::string getLocalnameFromQName(const std::string& qname) {
			//std::string localname = qname;
			//int delimiterIndex = qname.indexOf(':');
			//if (delimiterIndex > 0) {
			//	localname = qname.substring(delimiterIndex+1,qname.length());
			//}
			//return localname;
			return std::string();
		}

		std::string getXPointerExpression()
		{
			//std::string expression = this.getIDXPointerExpression();
			//if (expression != null) {
			//	return "#" + expression;
			//}
			//expression = this.getElementSchemeXPointerExpression();
			//return "#" + "element(" + expression + ")";
			return std::string();
		}

		std::string getElementSchemeXPointerExpression()
		{
			//NodeList nodes = getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),"xptr");
			//if (nodes.getLength() == 0) throw XBRLException("The fragment is missing its element scheme XPointer expression.");
			//Element xptrElement = (Element) nodes.item(0);
			//if (xptrElement.hasAttribute("value")) return xptrElement.getAttribute("value");
			//throw XBRLException("An element-scheme XPointer expression is corrupted for this fragment.");        
			return std::string();
		}

		std::string getIDXPointerExpression()
		{
			/*		NodeList nodes = getMetadataRootElement().getElementsByTagNameNS(Constants.XBRLAPINamespace.toString(),"ID");
			if (nodes.getLength() == 0) return null;
			Element idElement = (Element) nodes.item(0);
			if (idElement.hasAttribute("id")) return idElement.getAttribute("id");
			throw XBRLException("The shorthand ID for this fragment is missing.");*/
			return std::string();
		}
	};

	Fragment::Fragment() {}
	Fragment::~Fragment() {} 

	Fragment::Fragment(const Fragment& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Fragment& Fragment::operator=(const Fragment& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Fragment::Fragment(Fragment&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Fragment& Fragment::operator=(Fragment&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Fragment::operator==(const Fragment& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Fragment::operator!=(const Fragment& rhs)
	{
		return !this->operator==(rhs);
	}

	Fragment Fragment::getAncestorOrSelf(const std::string& type)
	{
		return pImpl->getAncestorOrSelf(type);
	}

	template <typename T> 
	std::vector<T> Fragment::getChildren(const std::string& type)
	{
		return pImpl->getChildren<T>(type);
	}

	template <typename T> 
	std::vector<T> Fragment::getChildren(const T& requiredClass)
	{
		return pImpl->getChildren<T>(requiredClass);
	}

	std::unordered_set<std::string> Fragment::getChildrenIndices(const std::string& type)
	{
		return pImpl->getChildrenIndices(type);
	}

	std::vector<SimpleLink> Fragment::getSimpleLinks()
	{
//		return pImpl->getSimpleLinks();
		return std::vector<SimpleLink>();
	}

	std::vector<Fragment> Fragment::getAllChildren()
	{
		return pImpl->getAllChildren();
	}

	std::unordered_set<std::string> Fragment::getAllChildrenIndices()
	{
		return pImpl->getAllChildrenIndices();
	}

	Fragment Fragment::getChild(const std::string& type, int index)
	{
		return pImpl->getChild(type,index);
	}

	std::shared_ptr<xercesc::DOMElement> Fragment::getDataRootElement()
	{
		return pImpl->getDataRootElement();
	}

	bool Fragment::isNewFragment()
	{
		return pImpl->isNewFragment();
	}

	Poco::URI Fragment::getURI()
	{
		return pImpl->getURI();
	}

	void Fragment::setURI(const Poco::URI& uri)
	{
		return pImpl->setURI(uri);
	}

	std::vector<xercesc::Locator> Fragment::getReferencingLocators()
	{
		return pImpl->getReferencingLocators();
	}

	std::vector<LabelResource> Fragment::getLabels()
	{
//		return pImpl->getLabels();
		return std::vector<LabelResource>();
	}  

	std::vector<LabelResource> Fragment::getLabelsWithResourceRole(const std::string& resourceRole)
	{
		return pImpl->getLabelsWithResourceRole(resourceRole);
	}

	std::vector<LabelResource> Fragment::getLabels(const std::vector<std::string>& languages, 
		const std::vector<std::string>& resourceRoles)
	{
		return pImpl->getLabels(languages, resourceRoles);
	}

	std::vector<LabelResource> Fragment::getLabels(const std::vector<std::string>& languages, 
		const std::vector<std::string>& labelRoles, 
		const std::vector<std::string>& linkRoles)
	{
		return pImpl->getLabels(languages, labelRoles, linkRoles);
	}   

	std::vector<ReferenceResource> Fragment::getReferencesWithResourceRole(const std::string& role)
	{
		return pImpl->getReferencesWithResourceRole(role);
	}

	std::vector<LabelResource> Fragment::getLabelsWithLanguage(const std::string& language)
	{
		return pImpl->getLabelsWithLanguage(language);
	}

	std::vector<LabelResource> Fragment::getLabelsWithLanguageAndResourceRole(const std::string& language, const std::string& role)
	{
		return pImpl->getLabelsWithLanguageAndResourceRole(language,role);
	}

	std::vector<LabelResource> Fragment::getLabelsWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const std::string& resourceRole, const std::string& linkRole)
	{
		return pImpl->getLabelsWithLanguageAndResourceRoleAndLinkRole(language,resourceRole,linkRole);
	}  

	std::vector<ReferenceResource> Fragment::getReferences()
	{
		return pImpl->getReferences();
	}

	std::vector<ReferenceResource> Fragment::getReferencesWithLanguage(const std::string& language)
	{
		return pImpl->getReferencesWithLanguage(language);
	}

	std::vector<ReferenceResource> Fragment::getReferencesWithLanguageAndRole(const std::string& language, 
		const Poco::URI& role)
	{
		return pImpl->getReferencesWithLanguageAndRole(language,role);
	}

	std::vector<ReferenceResource> Fragment::getReferencesWithLanguageAndResourceRoleAndLinkRole(const std::string& language, 
		const Poco::URI& resourceRole, 
		const Poco::URI& linkRole)
	{
		return pImpl->getReferencesWithLanguageAndResourceRoleAndLinkRole(language,resourceRole,linkRole);
	}   

	std::string Fragment::getParentIndex()
	{
		return pImpl->getParentIndex();
	}

	bool Fragment::isChild()
	{
		return pImpl->isChild();
	}

	bool Fragment::isAncestorOf(const Fragment& descendant)
	{
		return pImpl->isAncestorOf(descendant);
	}

	bool Fragment::isRoot()
	{
		return pImpl->isRoot();
	}

	void Fragment::setParentIndex(const std::string& index)
	{
		return pImpl->setParentIndex(index);
	}

	std::string Fragment::getXPath()
	{
		return pImpl->getXPath();
	}

	void Fragment::setSequenceToParentElement(const Fragment& parent)
	{
		return pImpl->setSequenceToParentElement(parent);
	}

	std::vector<std::string> Fragment::getSequenceToParentElement()
	{
		return pImpl->getSequenceToParentElement();
	}

	std::string Fragment::getSequenceToParentElementAsString()
	{
		return pImpl->getSequenceToParentElementAsString();
	}   

	void Fragment::appendID(const std::string& id)
	{
		return pImpl->appendID(id);
	}

	void Fragment::appendElementSchemeXPointer(const std::string& expression)
	{
		return pImpl->appendElementSchemeXPointer(expression);
	}

	std::string Fragment::getNamespace()
	{
		return pImpl->getNamespace();
	}

	std::string Fragment::getLocalname()
	{
		return pImpl->getLocalname();
	}

	std::string Fragment::getPrefixFromQName(const std::string& qname)
	{
		return pImpl->getPrefixFromQName(qname);
	}

	std::string Fragment::getNamespaceFromQName(const std::string& qname, const xercesc::DOMNode& node)
	{
		return pImpl->getNamespaceFromQName(qname,node);
	}

	std::string Fragment::getLanguage(const xercesc::DOMNode& node)
	{
		return pImpl->getLanguage(node);
	}

	std::string Fragment::getLanguage()
	{
		return pImpl->getLanguage();
	}

	std::string Fragment::getLanguageName(const std::string& language)
	{
		return pImpl->getLanguageName(language);
	}

	std::string Fragment::getLanguageName(const std::vector<std::string>& languages)
	{
		return pImpl->getLanguageName(languages);
	}    

	Fragment Fragment::getParent()
	{
		return pImpl->getParent();
	}

	std::shared_ptr<xercesc::DOMElement> Fragment::getParentElement(const xercesc::DOMElement& parentDataRootElement)
	{
		return pImpl->getParentElement(parentDataRootElement);
	}

	std::string Fragment::getLocalnameFromQName(const std::string& qname)
	{
		return pImpl->getLocalnameFromQName(qname);
	}

	std::string Fragment::getXPointerExpression()
	{
		return pImpl->getXPointerExpression();
	}

	std::string Fragment::getElementSchemeXPointerExpression()
	{
		return pImpl->getElementSchemeXPointerExpression();
	}

	std::string Fragment::getIDXPointerExpression()
	{
		return pImpl->getIDXPointerExpression();
	}
}