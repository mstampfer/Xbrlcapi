#include "SchemaIdentifier.h"
#include <string>
#include "ContentHandler.h"


namespace xbrlcapi
{
	struct SchemaIdentifier::Impl : public BaseIdentifier
	{

		//	XSModel model;    

		//	std::string targetNamespace;
		Impl() {}

		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler) 
		{}

		//void startElement(
		//	std::string namespaceURI, 
		//	std::string lName, 
		//	std::string qName,
		//	Attributes attrs) throws XBRLException {

		//		Fragment fragment;

		//		if (namespaceURI.equals(Constants.XMLSchemaNamespace.toString())) {

		//			if (lName.equals("group")) {

		//				fragment = new SchemaGroupCompositorImpl();

		//			} else if (lName.equals("all")) {

		//				fragment = new SchemaAllCompositorImpl();

		//			} else if (lName.equals("choice")) {

		//				fragment = new SchemaChoiceCompositorImpl();

		//			} else if (lName.equals("sequence")) {

		//				fragment = new SchemaSequenceCompositorImpl();

		//			} else if (lName.equals("complexType")) {

		//				fragment = new ComplexTypeDeclarationImpl();

		//			} else if (lName.equals("simpleType")) {

		//				fragment = new SimpleTypeDeclarationImpl();

		//			} else if (lName.equals("attribute")) {

		//				fragment = new AttributeDeclarationImpl();

		//			} else if (lName.equals("attributeGroup")) {

		//				fragment = new AttributeGroupDeclarationImpl();

		//			} else if (lName.equals("schema")) {

		//				fragment = new SchemaImpl();
		//				setXSModel(constructXSModel());
		//				setTargetNamespace(attrs.getValue("targetNamespace"));

		//			} else if (lName.equals("element")) {

		//				std::string elementName = attrs.getValue("name");

		//				if (getXSModel() == null) {
		//					throw new XBRLException("An XML Schema element declaration was found outside of an XML Schema.");
		//				}

		//				std::string targetNamespace = getTargetNamespace(); 
		//				if (targetNamespace == null) {
		//					throw new XBRLException("An XML Schema element was found without a target namespace.");
		//				}

		//				// Find the XS model element declaration for the element that has been started - if one can be found
		//				XSElementDeclaration declaration;

		//				// Handle anonymous schemas first - these are the tough case
		//				if (targetNamespace.equals("")) {

		//					// Get the list of namespaces declared in the model
		//					XSNamespaceItemList nsItemList = getXSModel().getNamespaceItems();

		//					// For each namespace ...
		//					for (int i=0; i<nsItemList.getLength(); i++) {
		//						XSNamespaceItem nsItem = nsItemList.item(i);

		//						// Get a candidate element declaration if one exists
		//						XSElementDeclaration candidateDeclaration = nsItem.getElementDeclaration(elementName);
		//						if (candidateDeclaration != null) {

		//							// Get the URIs of the documents that were used to create elements in this namespace
		//							StringList locations = nsItem.getDocumentLocations();

		//							// Check to see if the current document URI is one of those documents and if so, the candidate could be good
		//							for (int j=0; j<locations.getLength(); j++) {
		//								std::string location = locations.item(j);
		//								if (location.equals(getContentHandler().getURI().toString())) {
		//									// Throw an exception if we find two feasible candidate element declarations in the Schema model
		//									if (declaration != null) throw new XBRLException("Potentially ambiguous anonymous Schema problem.");
		//									declaration = candidateDeclaration;
		//								}
		//							}
		//						}
		//					}

		//					if (declaration == null) throw new XBRLException("An element declaration was found that could not be handled.");

		//					// Handle the easy case where the schema specifies its target namespace
		//				} else if (elementName != null) {
		//					declaration = getXSModel().getElementDeclaration(elementName, getTargetNamespace());
		//				}

		//				// Determine what substitution groups the element is in - if any.
		//				if (declaration != null) {
		//					XSElementDeclaration sgDeclaration = declaration.getSubstitutionGroupAffiliation();
		//					while (sgDeclaration != null) {

		//						if (sgDeclaration.getNamespace().equals(Constants.XBRL21Namespace.toString())) {
		//							if (sgDeclaration.getName().equals("item")) {
		//								fragment = new ConceptImpl();
		//								break;
		//							} else if (sgDeclaration.getName().equals("tuple")) {
		//								fragment = new ConceptImpl();
		//								break;
		//							}
		//						}

		//						if (sgDeclaration.getNamespace().equals(Constants.XBRL21LinkNamespace.toString())) {
		//							if (sgDeclaration.getName().equals("part"))
		//								fragment = new ReferencePartDeclarationImpl();
		//							break;
		//						}

		//						sgDeclaration = sgDeclaration.getSubstitutionGroupAffiliation();
		//					}
		//				}

		//				if ((fragment == null)) {
		//					fragment = new ElementDeclarationImpl();
		//				}

		//			}

		//			if (fragment != null) {
		//				this.processFragment(fragment,attrs);
		//			}
		//		}
		//}

		//void endElement(
		//	std::string namespaceURI, 
		//	std::string lName, 
		//	std::string qName,
		//	Attributes attrs) throws XBRLException {

		//		// This assumes that XML schemas do not nest XML schemas
		//		if (lName.equals("schema"))
		//			if (namespaceURI.equals(Constants.XMLSchemaNamespace.toString())) {
		//				setTargetNamespace(null);
		//			}

		//}    

		//XSModel getXSModel() {
		//	return this.model;
		//}

		//void setXSModel(XSModel model) throws XBRLException {
		//	if (model == null) throw new XBRLException("The XML Schema model must not be null.");
		//	this.model = model;
		//}

		//std::string getTargetNamespace() {
		//	return this.targetNamespace;
		//}    

		//void setTargetNamespace(const std::string& targetNamespace) {
		//	this.targetNamespace = targetNamespace;
		//}    

		//XSModel constructXSModel() throws XBRLException {
		//	try {

		//		XMLGrammarPreparser preparser = new XMLGrammarPreparser();
		//		preparser.registerPreparser(XMLGrammarDescription.XML_SCHEMA, null);
		//		//preparser.setProperty("http://apache.org/xml/properties/internal/grammar-pool", GrammarCacheImpl.getGrammarPool());
		//		//preparser.setGrammarPool(GrammarCacheImpl.getGrammarPool());
		//		preparser.setFeature("http://xml.org/sax/features/namespaces", true);
		//		preparser.setFeature("http://xml.org/sax/features/validation", true);
		//		preparser.setFeature("http://apache.org/xml/features/validation/schema", true);
		//		preparser.setFeature("http://apache.org/xml/features/validation/schema-full-checking", true);

		//		XMLEntityResolver entityResolver = this.getLoader().getEntityResolver();
		//		preparser.setEntityResolver(entityResolver);

		//		// TODO make sure that this XML Resource Identifier is being initialised correctly.
		//		std::string uri = this.getContentHandler().getURI().toString();
		//		XMLResourceIdentifier xri = new XMLResourceIdentifierImpl("", uri, uri, uri);

		//		XMLInputSource xmlInputSource = entityResolver.resolveEntity(xri);

		//		XSGrammar grammar = (XSGrammar) preparser.preparseGrammar(XMLGrammarDescription.XML_SCHEMA, xmlInputSource);

		//		return grammar.toXSModel();         

		//	} 
		//	catch (IOException e) 
		//	{
		//		throw new XBRLException("Grammar model construction for schema at URI: " + getContentHandler().getURI() + " failed.",e);
		//	}
		//}    

	};
	SchemaIdentifier::SchemaIdentifier() {}
	SchemaIdentifier::SchemaIdentifier(const ContentHandler& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	SchemaIdentifier::~SchemaIdentifier() {} 

	SchemaIdentifier::SchemaIdentifier(SchemaIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	SchemaIdentifier& SchemaIdentifier::operator=(SchemaIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	SchemaIdentifier::SchemaIdentifier(SchemaIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	SchemaIdentifier& SchemaIdentifier::operator=(SchemaIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool SchemaIdentifier::operator==(const SchemaIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool SchemaIdentifier::operator!=(const SchemaIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	void SchemaIdentifier::startElement(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}

	void SchemaIdentifier::endElement(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}

}



