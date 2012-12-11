#include "Stdafx.h"
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
/**
* Defines a range of constants (namespaces etc) that are used throughout the
* XBRLAPI implementation
* 
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

#include <string>

namespace xbrlcapi 
{
	struct XMLConstants 
	{
		/**
		* <p>Namespace URI to use to represent that there is no Namespace.</p>
		*
		* <p>Defined by the Namespace specification to be "".</p>
		*
		* @see <a href="http://www.w3.org/TR/REC-xml-names/#defaulting">
		* Namespaces in XML, 5.2 Namespace Defaulting</a>
		*/
	public:
		static const std::string NULL_NS_URI;

		/**
		* <p>Prefix to use to represent the default XML Namespace.</p>
		*
		* <p>Defined by the XML specification to be "".</p>
		*
		* @see <a
		* href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">
		* Namespaces in XML, 3. Qualified Names</a>
		*/

		static const std::string DEFAULT_NS_PREFIX;

		/**
		* <p>The official XML Namespace name URI.</p>
		*
		* <p>Defined by the XML specification to be
		* "<code>http://www.w3.org/XML/1998/namespace</code>".</p>
		*
		* @see <a
		* href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">
		* Namespaces in XML, 3. Qualified Names</a>
		*/

		static const std::string XML_NS_URI;

		/**
		* <p>The official XML Namespace prefix.</p>
		*
		* <p>Defined by the XML specification to be "<code>xml</code>".</p>
		*
		* @see <a
		* href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">
		* Namespaces in XML, 3. Qualified Names<</a>
		*/

		static const std::string XML_NS_PREFIX;

		/**
		* <p>The official XML attribute used for specifying XML Namespace
		* declarations, {@link #XMLNS_ATTRIBUTE
		* XMLConstants.XMLNS_ATTRIBUTE}, Namespace name URI.</p>
		*
		* <p>Defined by the XML specification to be
		* "<code>http://www.w3.org/2000/xmlns/</code>".</p>
		*
		* @see <a
		* href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">
		* Namespaces in XML, 3. Qualified Names</a>
		* @see <a
		* href="http://www.w3.org/XML/xml-names-19990114-errata">
		* Namespaces in XML Errata</a>
		*/

		static const std::string XMLNS_ATTRIBUTE_NS_URI;

		/**
		* <p>The official XML attribute used for specifying XML Namespace
		* declarations.</p>
		*
		* <p>It is <strong><em>NOT</em></strong> valid to use as a
		* prefix.  Defined by the XML specification to be
		* "<code>xmlns</code>".</p>
		*
		* @see <a
		* href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">
		* Namespaces in XML, 3. Qualified Names</a>
		*/

		static const std::string XMLNS_ATTRIBUTE;

		/**
		* <p>W3C XML Schema Namespace URI.</p>
		*
		* <p>Defined to be "<code>http://www.w3.org/2001/XMLSchema</code>".
		*
		* @see <a href=
		*  "http://www.w3.org/TR/xmlschema-1/#Instance_Document_Constructions">
		*  XML Schema Part 1:
		*  Structures, 2.6 Schema-Related Markup in Documents Being Validated</a>
		*/

		static const std::string W3C_XML_SCHEMA_NS_URI;

		/**
		* <p>W3C XML Schema Instance Namespace URI.</p>
		*
		* <p>Defined to be "<code>http://www.w3.org/2001/XMLSchema-instance</code>".</p>
		*
		* @see <a href=
		*  "http://www.w3.org/TR/xmlschema-1/#Instance_Document_Constructions">
		*  XML Schema Part 1:
		*  Structures, 2.6 Schema-Related Markup in Documents Being Validated</a>
		*/

		static const std::string W3C_XML_SCHEMA_INSTANCE_NS_URI;

		/**
		* <p>W3C XPath Datatype Namespace URI.</p>
		*
		* <p>Defined to be "<code>http://www.w3.org/2003/11/xpath-datatypes</code>".</p>
		*
		* @see <a href="http://www.w3.org/TR/xpath-datamodel">XQuery 1.0 and XPath 2.0 Data Model</a>
		*/

		static const std::string W3C_XPATH_DATATYPE_NS_URI;

		/**
		* <p>XML Document Type Declaration Namespace URI as an arbitrary value.</p>
		*
		* <p>Since not formally defined by any existing standard, arbitrarily define to be "<code>http://www.w3.org/TR/REC-xml</code>".
		*/

		static const std::string XML_DTD_NS_URI;

		/**
		* <p>RELAX NG Namespace URI.</p>
		*
		* <p>Defined to be "<code>http://relaxng.org/ns/structure/1.0</code>".</p>
		*
		* @see <a href="http://relaxng.org/spec-20011203.html">RELAX NG Specification</a>
		*/

		static const std::string RELAXNG_NS_URI;
		/**
		* <p>Feature for secure processing.</p>
		*
		* <ul>
		*   <li>
		*     <code>true</code> instructs the implementation to process XML securely.
		*     This may set limits on XML constructs to avoid conditions such as denial of service attacks.
		*   </li>
		*   <li>
		*     <code>false</code> instructs the implementation to process XML acording the letter of the XML specifications
		*     ingoring security issues such as limits on XML constructs to avoid conditions such as denial of service attacks.
		*   </li>
		* </ul>
		*/

		// protected static Logger logger;
		static const std::string FEATURE_SECURE_PROCESSING;
		static const std::string XMLPrefix;
		static const std::string XLinkPrefix;
		static const std::string XBRL21Prefix;
		static const std::string GenericLinkPrefix;
		static const std::string XBRL21LinkPrefix;
		static const std::string GenericLabelPrefix;
		static const std::string GenericReferencePrefix;
		static const std::string XBRLAPIPrefix;
		static const std::string CompPrefix;
		static const std::string XBRLAPIEntitiesPrefix;
		static const std::string XBRLAPILanguagesPrefix;
		static const std::string XMLSchemaPrefix;
		static const std::string XMLSchemaInstancePrefix;
		static const std::string FragmentRootElementName;
		static const std::string FragmentDataContainerElementName;
		static const std::string XMLNamespace;
		static const std::string XMLNSNamespace;
		static const std::string XLinkNamespace;
		static const std::string XBRL21Namespace;
		static const std::string XBRL21LinkNamespace;
		static const std::string GenericLinkNamespace;
		static const std::string GenericLabelNamespace;
		static const std::string GenericReferenceNamespace;
		static const std::string XBRLAPINamespace;
		static const std::string CompNamespace;
		static const std::string XBRLAPIEntitiesNamespace;
		static const std::string XBRLAPIMeasuresNamespace;
		static const std::string XBRLAPIEquivalentEntitiesArcrole;
		static const std::string XBRLAPILanguagesNamespace;
		static const std::string XMLSchemaNamespace;
		static const std::string XMLSchemaInstanceNamespace;
		static const std::string LabelArcrole;
		static const std::string GenericLabelArcrole;
		static const std::string ReferenceArcrole;
		static const std::string GenericReferenceArcrole;
		static const std::string CalculationArcrole;
		static const std::string PresentationArcrole;
		static const std::string GeneralSpecialArcrole;
		static const std::string EssenceAliasArcrole;
		static const std::string SimilarTuplesArcrole;
		static const std::string RequiresElementArcrole;
		static const std::string FactFootnoteArcrole;
		static const std::string StandardLabelRole;
		static const std::string TerseLabelRole;
		static const std::string VerboseLabelRole;
		static const std::string PositiveLabelRole;
		static const std::string PositiveTerseLabelRole;
		static const std::string PositiveVerboseLabelRole;
		static const std::string NegativeLabelRole;
		static const std::string NegativeTerseLabelRole;
		static const std::string NegativeVerboseLabelRole;
		static const std::string ZeroLabelRole;
		static const std::string ZeroTerseLabelRole;
		static const std::string ZeroVerboseLabelRole;
		static const std::string TotalLabelRole;
		static const std::string PeriodStartLabelRole;
		static const std::string PeriodEndLabelRole;
		static const std::string DocumentationLabelRole;
		static const std::string DefinitionGuidanceLabelRole;
		static const std::string DisclosureGuidanceLabelRole;
		static const std::string PresentationGuidanceLabelRole;
		static const std::string MeasurementGuidanceLabelRole;
		static const std::string CommentaryGuidanceLabelRole;
		static const std::string ExampleGuidanceLabelRole;
		static const std::string StandardReferenceRole;
		static const std::string DefinitionReferenceRole;
		static const std::string DisclosureReferenceRole;
		static const std::string MandatoryDisclosureReferenceRole;
		static const std::string RecommendedDisclosureReferenceRole;
		static const std::string UnspecifiedDisclosureReferenceRole;
		static const std::string PresentationReferenceRole;
		static const std::string MeasurementReferenceRole;
		static const std::string CommentaryReferenceRole;
		static const std::string ExampleReferenceRole;
		static const std::string StandardLinkRole;
		static const std::string ISO4217;
		static const std::string StandardGenericLabelRole;
		static const std::string TerseGenericLabelRole;
		static const std::string VerboseGenericLabelRole;
		static const std::string DocumentationGenericLabelRole;
		static const std::string StandardGenericReferenceRole;
		static const std::string LinkbaseReferenceArcrole;
		static const std::string PresentationLinkbaseReferenceRole;
		static const std::string DefinitionLinkbaseReferenceRole;
		static const std::string CalculationLinkbaseReferenceRole;
		static const std::string LabelLinkbaseReferenceRole;
		static const std::string ReferenceLinkbaseReferenceRole;
	};
}
#endif