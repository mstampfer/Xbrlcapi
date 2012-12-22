
#include "Constants.h"

namespace xbrlcapi
{
	// protected Logger logger(Logger.getLogger(Constants.class);
	const std::string XMLConstants::XML_NS_URI("http://www.w3.org/XML/1998/namespace");
	const std::string XMLConstants::XML_NS_PREFIX("xml");
	const std::string XMLConstants::XMLNS_ATTRIBUTE_NS_URI("http://www.w3.org/2000/xmlns/");
	const std::string XMLConstants::XMLNS_ATTRIBUTE("xmlns");
	const std::string XMLConstants::W3C_XML_SCHEMA_NS_URI("http://www.w3.org/2001/XMLSchema");
	const std::string XMLConstants::W3C_XML_SCHEMA_INSTANCE_NS_URI("http://www.w3.org/2001/XMLSchema-instance");
	const std::string XMLConstants::W3C_XPATH_DATATYPE_NS_URI("http://www.w3.org/2003/11/xpath-datatypes");
	const std::string XMLConstants::XML_DTD_NS_URI("http://www.w3.org/TR/REC-xml");
	const std::string XMLConstants::RELAXNG_NS_URI("http://relaxng.org/ns/structure/1.0");
	const std::string XMLConstants::FEATURE_SECURE_PROCESSING("http://javax.xml.XMLConstants/feature/secure-processing");
	const std::string XMLConstants::XMLPrefix("xml");
	const std::string XMLConstants::XLinkPrefix("xlink");
	const std::string XMLConstants::XBRL21Prefix("xbrli");
	const std::string XMLConstants::GenericLinkPrefix("gen");
	const std::string XMLConstants::XBRL21LinkPrefix("link");
	const std::string XMLConstants::GenericLabelPrefix("genlab");
	const std::string XMLConstants::GenericReferencePrefix("genref");
	const std::string XMLConstants::XBRLAPIPrefix("xbrlapi");
	const std::string XMLConstants::CompPrefix("comp");
	const std::string XMLConstants::XBRLAPIEntitiesPrefix("entity");
	const std::string XMLConstants::XBRLAPILanguagesPrefix("lang");
	const std::string XMLConstants::XMLSchemaPrefix("xsd");
	const std::string XMLConstants::XMLSchemaInstancePrefix("xsi");
	const std::string XMLConstants::FragmentRootElementName("fragment");
	const std::string XMLConstants::FragmentDataContainerElementName("data");
	const std::string XMLConstants::XMLNamespace(XMLConstants::XML_NS_URI);
	const std::string XMLConstants::XMLNSNamespace("http://www.w3.org/2000/xmlns/");
	const std::string XMLConstants::XLinkNamespace("http://www.w3.org/1999/xlink");
	const std::string XMLConstants::XBRL21Namespace("http://www.xbrl.org/2003/instance");
	const std::string XMLConstants::XBRL21LinkNamespace("http://www.xbrl.org/2003/linkbase");
	const std::string XMLConstants::GenericLinkNamespace("http://xbrl.org/2008/generic");
	const std::string XMLConstants::GenericLabelNamespace("http://xbrl.org/2008/label");
	const std::string XMLConstants::GenericReferenceNamespace("http://xbrl.org/2008/reference");
	const std::string XMLConstants::XBRLAPINamespace("http://xbrlapi.org/");
	const std::string XMLConstants::CompNamespace("http://xbrlapi.org/composite");
	const std::string XMLConstants::XBRLAPIEntitiesNamespace("http://xbrlapi.org/entities");
	const std::string XMLConstants::XBRLAPIMeasuresNamespace("http://xbrlapi.org/measures");
	const std::string XMLConstants::XBRLAPIEquivalentEntitiesArcrole("http://xbrlapi.org/arcrole/equivalent-entity");
	const std::string XMLConstants::XBRLAPILanguagesNamespace("http://xbrlapi.org/rfc1766/languages");    
	//const std::string XMLConstants::XMLSchemaNamespace(XMLConstants.W3C_XML_SCHEMA_NS_URI;
	//const std::string XMLConstants::XMLSchemaInstanceNamespace(XMLConstants.W3C_XML_SCHEMA_INSTANCE_NS_URI);
	const std::string XMLConstants::LabelArcrole("http://www.xbrl.org/2003/arcrole/concept-label");
	const std::string XMLConstants::GenericLabelArcrole("http://xbrl.org/arcrole/2008/element-label");
	const std::string XMLConstants::ReferenceArcrole("http://www.xbrl.org/2003/arcrole/concept-reference");
	const std::string XMLConstants::GenericReferenceArcrole("http://xbrl.org/arcrole/2008/element-reference");
	const std::string XMLConstants::CalculationArcrole("http://www.xbrl.org/2003/arcrole/summation-item");
	const std::string XMLConstants::PresentationArcrole("http://www.xbrl.org/2003/arcrole/parent-child");
	const std::string XMLConstants::GeneralSpecialArcrole("http://www.xbrl.org/2003/arcrole/general-special");
	const std::string XMLConstants::EssenceAliasArcrole("http://www.xbrl.org/2003/arcrole/essence-alias");
	const std::string XMLConstants::SimilarTuplesArcrole("http://www.xbrl.org/2003/arcrole/similar-tuples");
	const std::string XMLConstants::RequiresElementArcrole("http://www.xbrl.org/2003/arcrole/requires-element");
	const std::string XMLConstants::FactFootnoteArcrole("http://www.xbrl.org/2003/arcrole/fact-footnote");
	const std::string XMLConstants::StandardLabelRole("http://www.xbrl.org/2003/role/label");
	const std::string XMLConstants::TerseLabelRole("http://www.xbrl.org/2003/role/terseLabel");
	const std::string XMLConstants::VerboseLabelRole("http://www.xbrl.org/2003/role/verboseLabel");
	const std::string XMLConstants::PositiveLabelRole("http://www.xbrl.org/2003/role/positiveLabel");
	const std::string XMLConstants::PositiveTerseLabelRole("http://www.xbrl.org/2003/role/positiveTerseLabel");
	const std::string XMLConstants::PositiveVerboseLabelRole("http://www.xbrl.org/2003/role/positiveVerboseLabel");
	const std::string XMLConstants::NegativeLabelRole("http://www.xbrl.org/2003/role/negativeLabel");
	const std::string XMLConstants::NegativeTerseLabelRole("http://www.xbrl.org/2003/role/negativeTerseLabel");
	const std::string XMLConstants::NegativeVerboseLabelRole("http://www.xbrl.org/2003/role/negativeVerboseLabel");
	const std::string XMLConstants::ZeroLabelRole("http://www.xbrl.org/2003/role/zeroLabel");
	const std::string XMLConstants::ZeroTerseLabelRole("http://www.xbrl.org/2003/role/zeroTerseLabel");
	const std::string XMLConstants::ZeroVerboseLabelRole("http://www.xbrl.org/2003/role/zeroVerboseLabel");
	const std::string XMLConstants::TotalLabelRole("http://www.xbrl.org/2003/role/totalLabel");
	const std::string XMLConstants::PeriodStartLabelRole("http://www.xbrl.org/2003/role/periodStartLabel");
	const std::string XMLConstants::PeriodEndLabelRole("http://www.xbrl.org/2003/role/periodEndLabel");
	const std::string XMLConstants::DocumentationLabelRole("http://www.xbrl.org/2003/role/documentationLabel");
	const std::string XMLConstants::DefinitionGuidanceLabelRole("http://www.xbrl.org/2003/role/definitionGuidanceLabel");
	const std::string XMLConstants::DisclosureGuidanceLabelRole("http://www.xbrl.org/2003/role/disclosureGuidanceLabel");
	const std::string XMLConstants::PresentationGuidanceLabelRole("http://www.xbrl.org/2003/role/presentationGuidanceLabel");
	const std::string XMLConstants::MeasurementGuidanceLabelRole("http://www.xbrl.org/2003/role/measurementGuidanceLabel");
	const std::string XMLConstants::CommentaryGuidanceLabelRole("http://www.xbrl.org/2003/role/commentaryGuidanceLabel");
	const std::string XMLConstants::ExampleGuidanceLabelRole("http://www.xbrl.org/2003/role/exampleGuidanceLabel");
	const std::string XMLConstants::StandardReferenceRole("http://www.xbrl.org/2003/role/reference");
	const std::string XMLConstants::DefinitionReferenceRole("http://www.xbrl.org/2003/role/definitionRef");
	const std::string XMLConstants::DisclosureReferenceRole("http://www.xbrl.org/2003/role/disclosureRef");
	const std::string XMLConstants::MandatoryDisclosureReferenceRole("http://www.xbrl.org/2003/role/mandatoryDisclosureRef");
	const std::string XMLConstants::RecommendedDisclosureReferenceRole("http://www.xbrl.org/2003/role/recommendedDisclosureRef");
	const std::string XMLConstants::UnspecifiedDisclosureReferenceRole("http://www.xbrl.org/2003/role/unspecifiedDisclosureGuidanceLabel");
	const std::string XMLConstants::PresentationReferenceRole("http://www.xbrl.org/2003/role/presentationRef");
	const std::string XMLConstants::MeasurementReferenceRole("http://www.xbrl.org/2003/role/measurementRef");
	const std::string XMLConstants::CommentaryReferenceRole("http://www.xbrl.org/2003/role/commentaryRef");
	const std::string XMLConstants::ExampleReferenceRole("http://www.xbrl.org/2003/role/exampleRef");
	const std::string XMLConstants::StandardLinkRole("http://www.xbrl.org/2003/role/link");
	const std::string XMLConstants::ISO4217("http://www.xbrl.org/2003/iso4217");
	const std::string XMLConstants::StandardGenericLabelRole("http://www.xbrl.org/2008/role/label");
	const std::string XMLConstants::TerseGenericLabelRole("http://www.xbrl.org/2008/role/terseLabel");
	const std::string XMLConstants::VerboseGenericLabelRole("http://www.xbrl.org/2008/role/verboseLabel");
	const std::string XMLConstants::DocumentationGenericLabelRole("http://www.xbrl.org/2008/role/documentation");
	const std::string XMLConstants::StandardGenericReferenceRole("http://www.xbrl.org/2008/role/reference");
	const std::string XMLConstants::LinkbaseReferenceArcrole("http://www.w3.org/1999/xlink/properties/linkbase");
	const std::string XMLConstants::PresentationLinkbaseReferenceRole("http://www.xbrl.org/2003/role/presentationLinkbaseRef");
	const std::string XMLConstants::DefinitionLinkbaseReferenceRole("http://www.xbrl.org/2003/role/definitionLinkbaseRef");
	const std::string XMLConstants::CalculationLinkbaseReferenceRole("http://www.xbrl.org/2003/role/calculationLinkbaseRef");
	const std::string XMLConstants::LabelLinkbaseReferenceRole("http://www.xbrl.org/2003/role/labelLinkbaseRef");
	const std::string XMLConstants::ReferenceLinkbaseReferenceRole("http://www.xbrl.org/2003/role/referenceLinkbaseRef");
};