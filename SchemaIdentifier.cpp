#include "SchemaIdentifier.h"
#include "SchemaGroupCompositor.h"
#include "SchemaAllCompositor.h"
#include "SchemaChoiceCompositor.h"
#include "SchemaSequenceCompositor.h"
#include "SimpleTypeDeclaration.h"
#include "AttributeDeclaration.h"
#include "AttributeGroupDeclaration.h"
#include "Schema.h"
#include "EntityResolver.h"
#include "XBRLException.h"
#include "Concept.h"
//#include "ReferencePartDeclaration.h"


#include "ContentHandler.h"
#include "Constants.h"
#include "XercesString.h"

#include <xercesc/util/XMLResourceIdentifier.hpp>
#include <xercesc/internal/MemoryManagerImpl.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/psvi/XSNamespaceItem.hpp>
#include <xercesc/framework/psvi/XSElementDeclaration.hpp>


namespace xbrlcapi
{
	struct SchemaIdentifier::Impl 
	{
		std::weak_ptr<SchemaIdentifier> outer;
		std::shared_ptr<XSModel> model;    
		std::shared_ptr<const XMLCh> targetNamespace;
		std::shared_ptr<ContentHandler> contentHandler;
		Impl() {}

		Impl(const std::shared_ptr<ContentHandler>& contentHandler) : contentHandler(contentHandler)
		{}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{
			std::shared_ptr<Fragment> fragment;

			if (namespaceURI == XS(XMLConstants::XMLSchemaNamespace)) 
			{
				if (lName == L"group")
				{
					fragment = std::make_shared<SchemaGroupCompositor>();
				} 
				else if (lName == L"all")
				{
					fragment = std::make_shared<SchemaAllCompositor>();
				} 
				else if (lName == L"choice")
				{
					fragment = std::make_shared<SchemaChoiceCompositor>();
				} 
				else if (lName == L"sequence")
				{
					fragment = std::make_shared<SchemaSequenceCompositor>();
				} 
				else if (lName == L"complexType")
				{
					fragment = std::make_shared<TypeDeclaration>();
				} 
				else if (lName == L"simpleType")
				{
					fragment = std::make_shared<SimpleTypeDeclaration>();
				} 
				else if (lName == L"attribute")
				{
					fragment = std::make_shared<AttributeDeclaration>();
				} 
				else if (lName == L"attributeGroup")
				{
					fragment = std::make_shared<AttributeGroupDeclaration>();
				} 
				else if (lName == L"schema")
				{
					fragment = std::make_shared<Schema>();
					setXSModel(constructXSModel());
					setTargetNamespace(std::shared_ptr<const XMLCh>(attrs.getValue(L"targetNamespace")));
				} 
				else if (lName == L"element")
				{
					auto elementName = std::shared_ptr<const XMLCh>(attrs.getValue(L"name"));

					if (!getXSModel().get()) 
					{
						throw new XBRLException("An XML Schema element declaration was found outside of an XML Schema.");
					}

					auto targetNamespace = getTargetNamespace(); 
					if (!targetNamespace.get()) 
					{
						throw new XBRLException("An XML Schema element was found without a target namespace.");
					}

					// Find the XS model element declaration for the element that has been started - if one can be found
					std::shared_ptr<XSElementDeclaration> declaration;

					// Handle anonymous schemas first - these are the tough case
					if (targetNamespace.get())
					{
						// Get the list of namespaces declared in the model
						auto nsItemList = std::shared_ptr<XSNamespaceItemList>(getXSModel()->getNamespaceItems());

						// For each namespace ...
						for (XMLSize_t i=0; i < nsItemList->size(); ++i) 
						{
							auto nsItem = std::shared_ptr<XSNamespaceItem>(nsItemList->elementAt(i));

							// Get a candidate element declaration if one exists
							auto candidateDeclaration = std::shared_ptr<XSElementDeclaration>(nsItem->getElementDeclaration(elementName.get()));


							if (candidateDeclaration.get()) 
							{
								// Get the URIs of the documents that were used to create elements in this namespace
								auto locations = std::shared_ptr<const StringList>(nsItem->getDocumentLocations());

								// Check to see if the current document URI is one of those documents and if so, the candidate could be good
								for (XMLSize_t j=0; j < locations->size(); ++j) 
								{
									auto location = locations->elementAt(j);
									if (to_string(location) == contentHandler->getURI().toString()) 
									{
										// Throw an exception if we find two feasible candidate element declarations in the Schema model
										if (declaration.get()) throw new XBRLException("Potentially ambiguous anonymous Schema problem.");
										declaration = candidateDeclaration;
									}
								}
							}
						}

						if (!declaration.get()) throw new XBRLException("An element declaration was found that could not be handled.");

						// Handle the easy case where the schema specifies its target namespace
					} 
					else if (elementName.get()) 
					{

						declaration = 
							std::shared_ptr<XSElementDeclaration>(
								getXSModel()->getElementDeclaration(elementName.get(), 
								getTargetNamespace().get()));
					}

					// Determine what substitution groups the element is in - if any.
					if (declaration.get()) 
					{
						auto sgDeclaration = std::shared_ptr<XSElementDeclaration>(declaration->getSubstitutionGroupAffiliation());
						while (sgDeclaration.get()) 
						{
							if (to_string(sgDeclaration->getNamespace()) == XMLConstants::XBRL21Namespace)
							{
								if (sgDeclaration->getName() == L"item")
								{
									fragment = std::shared_ptr<Concept>();
									break;
								} 
								else if (sgDeclaration->getName() == L"tuple")
								{
									fragment = std::shared_ptr<Concept>();
									break;
								}
							}

							if (to_string(sgDeclaration->getNamespace()) == XMLConstants::XBRL21LinkNamespace)
							{
								//if (sgDeclaration->getName() == L"part")
								//	fragment = std::shared_ptr<ReferencePartDeclaration>();
								break;
							}
							sgDeclaration = 
								std::shared_ptr<XSElementDeclaration>(sgDeclaration->getSubstitutionGroupAffiliation());
						}
					}

					if (!fragment.get()) 
					{
						fragment = std::shared_ptr<ElementDeclaration>();
					}
				}

				if (fragment.get()) 
				{
					outer.lock()->processFragment(fragment, attrs);
				}
			}
		}

		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{

			//		// This assumes that XML schemas do not nest XML schemas
			//		if (lName.equals("schema"))
			//			if (namespaceURI.equals(Constants.XMLSchemaNamespace.toString())) {
			//				setTargetNamespace(null);
			//			}

		}    

		std::shared_ptr<XSModel> getXSModel() 
		{
			return model;
		}

		void setXSModel(const std::shared_ptr<XSModel>& model)
		{
			this->model = model;
		}

		std::shared_ptr<const XMLCh> getTargetNamespace() 
		{
			return targetNamespace;
		}    

		void setTargetNamespace(std::shared_ptr<const XMLCh> targetNamespace) 
		{
			this->targetNamespace = targetNamespace;
		}    

		std::shared_ptr<XSModel> constructXSModel()
		{
			//auto memMgr = std::shared_ptr<xercesc::MemoryManager>(new xercesc::MemoryManagerImpl());
			//auto grammarPool = std::shared_ptr<xercesc::XMLGrammarPoolImpl>(new xercesc::XMLGrammarPoolImpl(memMgr.get()));
			//auto preparser = std::shared_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader(
			//	memMgr.get(), grammarPool.get()));

			//// now must reset features for actual parsing:
			//try
			//{
			//	preparser->setProperty(L"http://apache.org/xml/properties/internal/grammar-pool", grammarPool.get());
			//	preparser->setFeature(L"http://xml.org/sax/features/namespaces", true);
			//	preparser->setFeature(L"http://xml.org/sax/features/validation", true);
			//	preparser->setFeature(L"http://apache.org/xml/features/validation/schema", true);
			//	preparser->setFeature(L"http://apache.org/xml/features/validation/schema-full-checking", true);

			//	EntityResolver entityResolver = contentHandler->getLoader()->getEntityResolver();
			//	preparser->setEntityResolver(&entityResolver);
			//	preparser->setErrorHandler(contentHandler.get());        
			//	preparser->setContentHandler(contentHandler.get());     


			//	// TODO make sure that this XML Resource Identifier is being initialised correctly.
			//	const XMLCh* uri = XS(contentHandler->getURI().toString());
			//	XMLResourceIdentifier xri(xercesc::XMLResourceIdentifier::ResourceIdentifierType::SchemaGrammar, 
			//		uri, uri, uri);

			//	auto inputSource = entityResolver.resolveEntity(&xri);
			//	auto grammar = preparser->loadGrammar(*inputSource, xercesc::Grammar::SchemaGrammarType, true);
			//	return grammar->toXSModel();    
			//} 
			//catch 
			//	(const std::exception& e) 
			//{
			//	throw XBRLException("The parser features could not be set.", e.what());
			//}
			return std::shared_ptr<XSModel>();
		}

		void setOuter(const std::weak_ptr<SchemaIdentifier>& schemaIdentifier)
		{
			outer = std::weak_ptr<SchemaIdentifier>(schemaIdentifier);
		}
	};

	SchemaIdentifier::SchemaIdentifier() {}
	
	SchemaIdentifier::SchemaIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
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
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->startElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}

	void SchemaIdentifier::endElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(namespaceURI, 
			lName, 
			qName,
			attrs);
	}

	std::weak_ptr<SchemaIdentifier> SchemaIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void SchemaIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}

}



