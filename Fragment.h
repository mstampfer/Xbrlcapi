#pragma once
#include <xercesc/sax/Locator.hpp>

#include <string>
#include <vector>
#include <unordered_set>
#include <string>
#include <vector>

#include "XML.h"

#include <xercesc/dom/impl/DOMElementImpl.hpp>

/**
* Defines the functionality exposed by any fragment.
* @author Geoff Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{
	class Locator;
	class SimpleLink;
	class LabelResource;
	class ReferenceResource;

	class Fragment : public XML 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Fragment();
		~Fragment();
		Fragment(const Fragment& rhs);
		Fragment& operator=(const Fragment& rhs);
		Fragment(Fragment&& rhs);
		Fragment& operator=(Fragment&& rhs);
		bool operator==(const Fragment& rhs);
		bool operator!=(const Fragment& rhs);

		/**
		* Get the root element of the fragment data.
		* @return an XML Element that is the root of the fragment data.
		* @throws XBRLException if the fragment does not have fragment data.
		*/
		virtual std::shared_ptr<xercesc::DOMElement> getDataRootElement();

		/**
		* Tests if a fragment is new in the sense that it does not have a root data element.
		* This is only used by the SAX content builder to keep track of where the fragment
		* construction process is at.
		* @return true if the fragment is new.
		* @throws XBRLException
		*/
		virtual bool isNewFragment();

		/**
		* Get the URI of the document containing this fragment.
		* @throws XBRLException
		*/
		virtual Poco::URI getURI();

		/**
		* Set the URI of the fragment's document.
		* @param uri The string value of the document's absolute URI
		* @throws XBRLException.
		*/
		virtual void setURI(const Poco::URI&  uri);

		/**
		* Retrieves a list of all locators that target this fragment.
		* @return a list of all locators that target this fragment.  The list can be empty.
		* @throws XBRLException.
		*/
		virtual std::vector<xercesc::Locator> getReferencingLocators();    

		/**
		* Get the index of the parent fragment or null if the fragment
		* does not have a parent fragment.
		* @return The index of the parent fragment or null if the 
		* fragment does not have a parent fragment.
		* @throws XBRLException if the parent fragment index is not available.
		*/
		virtual std::string getParentIndex();

		/**
		* @return true if the fragment is the root of an XML document
		* and false otherwise.
		* @throws XBRLException
		* @see Fragment#isChild()
		*/
		virtual bool isRoot();

		/**
		* Get the sequence of steps through the parent fragment DOM to the parent element.
		* @return The sequence through the parent fragment data to the parent element of this fragment.
		* @throws XBRLException
		*/
		virtual std::vector<std::string> getSequenceToParentElement();   

		/**
		* @return the sequence of steps through the parent fragment DOM to the 
		* parent element of this fragment.
		* @throws XBRLException
		*/
		virtual std::string getSequenceToParentElementAsString();

		/**
		* Set the index of the parent fragment.
		* @param index The index of the parent fragment.
		* @throws XBRLException if the parent fragment index cannot be set.
		*/
		virtual void setParentIndex(const std::string& index);    

		/**
		* Get the XPath to the element in the parent fragment that is the 
		* parent element of this fragment's root element.
		* @return The required xpath.
		* @throws XBRLException
		*/
		virtual std::string getXPath();

		/**
		* Specifies the set of ancestor elements of the element in the parent
		* fragment that is the insertion point for this fragment's root element.
		* The ancestor elements are identified by their sibling order in the 
		* parent fragment (after all other fragments have been carved out of it).
		* Note that the root element of the parent fragment is not part of the sequence
		* because that is always identified by a value of 1 - being an only child.
		* @param parent The parent fragment.
		* @throws XBRLException
		*/
		virtual void setSequenceToParentElement(const Fragment& parent);

		/**
		* Add an ID (used in XPointer resolution) to the metadata.
		* @param id The value of the ID.
		* @throws XBRLException.
		*/
		virtual void appendID(const std::string& id);

		/**
		* Add an element Scheme XPointer Expression to the metadata.
		* @param expression The XPointer expression
		* @throws XBRLException
		*/
		virtual void appendElementSchemeXPointer(const std::string& expression);

		/**
		* @return the ID XPointer expression for this fragment or
		* the element Scheme XPointer expression if there is no shorthand 
		* ID-based XPointer expression.  What is returned is the entire string
		* that is to be appended to the relevant URI to identify the fragment, including
		* the # symbol and everything that follows it.
		* 
		* @throws XBRLException
		*/
		virtual std::string getXPointerExpression();

		/**
		* @return the element scheme XPointer expression for this fragment.
		* @throws XBRLException
		*/
		virtual std::string getElementSchemeXPointerExpression();

		/**
		* @return the shorthand ID XPointer expression for this fragment or null
		* if there is none.
		* @throws XBRLException
		*/
		virtual std::string getIDXPointerExpression();

		/**
		* Get the namespace of the fragment root element.
		*
		* @throws XBRLException if there is no data element
		* in the fragment.
		*/
		virtual std::string getNamespace();

		/**
		* Get the local name of the fragment's root element
		* @throws XBRLException
		*/
		virtual std::string getLocalname();

		/**
		* Get the element in the parent fragment that has this fragment as its child.
		* @param parentDataRootElement The root element of the parent fragment's data.
		* @return the element of the parent fragment that has this fragment as
		* its child (or null if no parent exists).
		* @throws XBRLException
		*/
		virtual std::shared_ptr<xercesc::DOMElement> getParentElement(const xercesc::DOMElement& parentDataRootElement);

		/**
		* Get the parent fragment of this fragment or null if there is none.
		* @return the parent fragment or null if none exists.
		* @throws XBRLException
		*/
		virtual Fragment getParent();

		/**
		* @return true iff the fragment has a parent fragment and
		* false otherwise.
		* @throws XBRLException
		*/
		virtual bool isChild();

		/**
		* @param descendant The candidate descendant fragment.
		* @return true if the candidate descendant is actually 
		* a descendant fragment and false otherwise.
		* @throws XBRLException
		*/
		virtual bool isAncestorOf(const Fragment& descendant);

		/**
		* Gets all child fragments.
		* @return the fragment list of children fragments or the empty list if no child
		* fragments exist in the data store.
		* @throws XBRLException
		*/
		virtual std::vector<Fragment> getAllChildren();

		/**
		* @return the set of indices of all child fragments of this fragment.
		* @throws XBRLException
		*/
		virtual std::unordered_set<std::string> getAllChildrenIndices();

		/**
		* @return the list of simple links that are children of this fragment.
		* @throws XBRLException
		*/
		virtual std::vector<SimpleLink> getSimpleLinks();    

		/**
		* Gets the ancestor (or self) fragment with the specified fragment type.
		* @param type The required fragment type of the ancestor (or self).
		* @return the first ancestor (or self) fragment that matches the specified fragment type
		* working up the XML document structure from the supplied fragment to the root
		* of the XML document.
		* TODO Modify to use Generics so the fragment returned can be of a specific type.
		* @throws XBRLException if no such ancestor fragment exists.
		*/
		virtual Fragment getAncestorOrSelf(const std::string& type);

		/**
		* Returns the Namespace for a QName in the context of a node in the fragment.
		* @param qname The qName value to resolve
		* @param node The node in the fragment data (as a DOM representation) to start QName resolution from.
		* @return the namespace declared on the fragment for the QName
		* @throws XBRLException if the namespace is not declared
		*/
		virtual std::string getNamespaceFromQName(const std::string& qname, const xercesc::DOMNode& node);

		/**
		* Returns the local name for a QName
		* 
		* @param qname The qName value to resolve
		* @return the local name for the QName.
		*/
		virtual std::string getLocalnameFromQName(const std::string& qname);

		/**
		* Returns the Namespace prefix for a QName
		* 
		* @param qname The qName value to resolve
		* @return the namespace prefix in the QName
		* @throws XBRLException 
		*/
		virtual std::string getPrefixFromQName(const std::string& qname);

		/**
		* @return a list of label resources for the fragment.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabels();

		/**
		* @param resourceRole The XLink role value
		* @return the list of labels for this fragment with the specified XLink role.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabelsWithResourceRole(const std::string& resourceRole);

		/**
		* @param languages the list of language codes in order of preference from most preferred to least
		* preferred, eventually allowing any language if no explicit preference match.
		* @param labelRoles the list of label resource roles in order of preference from most preferred 
		* to least preferred, eventually allowing any resource role.
		* @return the list of labels that best match the specified search criteria.
		* Note that a label role preference which 
		* takes precedence over a language preference.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabels(const std::vector<std::string>& languages, 
			const std::vector<std::string>& labelRoles);

		/**
		* @param languages
		*            the list of language codes in order of preference from most
		*            preferred to least preferred, eventually allowing any language
		*            if no explicit preference match.
		* @param labelRoles
		*            the list of label resource roles in order of preference from
		*            most preferred to least preferred, eventually allowing any
		*            resource role.
		* @param linkRoles
		*            the list of extended link roles in order of preference from
		*            most preferred to least preferred, eventually allowing any
		*            link role.
		* @return the list of labels that best match the specified search criteria.
		*         Note that a link role preference takes precedence over a label
		*         role preference which takes precedence over a language
		*         preference. Note also that if none of the preferences are met, an
		*         attempt is still made to return a list of all labels in the data store
		*         for this fragment.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabels(const std::vector<std::string>& languages,
			const std::vector<std::string>& labelRoles, 
			const std::vector<std::string>& linkRoles);    

		/**
		* @param role The XLink role value
		* @return the list of references for this fragment with the specified XLink role.
		* @throws XBRLException
		*/
		virtual std::vector<ReferenceResource> getReferencesWithResourceRole(const std::string& role);

		/**
		* @param language The xml:lang language codevalue
		* @return the list of labels for this fragment with the specified language code.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabelsWithLanguage(const std::string& language);

		/**
		* @param language The xml:lang language code value
		* @param role The XLink role value
		* @return the list of labels for this fragment with the specified language code and XLink role.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabelsWithLanguageAndResourceRole(const std::string& language, const std::string& role);

		/**
		* @param language The xml:lang language code value or null if not used as
		* a a label selection criterion.
		* @param resourceRole The XLink resource role value on the label or null if not used as
		* a a label selection criterion.
		* @param linkRole The XLink extended link role value on the
		* extended link containing the label or null if not used as
		* a a label selection criterion..
		* @return the list of labels for this fragment that match the specified criteria.
		* @throws XBRLException
		*/
		virtual std::vector<LabelResource> getLabelsWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const std::string& resourceRole, const std::string& linkRole);    

		/**
		* @return a list of references for the fragment based on XBRL 2.1 reference arcs.
		* @throws XBRLException
		*/
		virtual std::vector<ReferenceResource> getReferences();

		/**
		* @param language The xml:lang language code value
		* @return the list of references for this fragment with the specified language code.
		* @throws XBRLException
		*/
		virtual std::vector<ReferenceResource> getReferencesWithLanguage(const std::string& language);

		/**
		* @param language The xml:lang language code value
		* @param role The XLink role value
		* @return the list of references for this fragment with the specified language code and XLink role.
		* @throws XBRLException
		*/
		virtual std::vector<ReferenceResource> getReferencesWithLanguageAndRole(const std::string& language, const Poco::URI& role);

		/**
		* @param language The xml:lang language code value
		* @param resourceRole The XLink resource role value on the reference
		* @param linkRole The XLink extended link role value on the
		* extended link containing the reference.
		* @return the list of references for this fragment with the specified language code and XLink resource and link roles.
		* @throws XBRLException
		*/
		virtual std::vector<ReferenceResource> getReferencesWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const Poco::URI& resourceRole, const Poco::URI& linkRole);    

		/**
		* Get a specific child fragment.
		* @param type The fragment type of the required child
		* @param index The index of the required child fragment (among other children of the same type)
		* with the first child being at index 0.
		* @return the child fragment or null if there are no children fragments of the specified type.
		* @throws XBRLException if the index is out of bounds
		*/
		virtual Fragment getChild(const std::string& type, int index);

		/**
		* Gets the child fragments with the specified fragment type.
		* @param type The required fragment type of the child.
		* EG: If a list of
		*  org.xbrlapi.impl.ReferenceArcImpl fragments is required then
		*  this parameter would have a value of "ReferenceArc".
		*  Note that if the parameter contains full stops, then it is used directly
		*  as the value for the fragment type, enabling fragment extensions to exploit this
		*  method without placing fragment implementations in the org.xbrlapi package.
		* @return the fragment list of children fragments that match the specified fragment type
		* @throws XBRLException
		*/

		template <typename T>
		std::vector<T> getChildren(const std::string& type);

		template <typename T>
		std::vector<T> getChildren(const T& requiredClass);


		/**
		* Gets the child fragments with the specified fragment type.
		* 
		* @param requiredClass
		*            The required fragment class of the child fragments.
		* @return the fragment list of children fragments that match the specified
		*         fragment type
		* @throws XBRLException
		*/

		//		template <typename F>
		//		virtual std::vector<F> getChildren(F requiredClass);

		/**
		* @param type
		*            The fragment type
		* @return The list of all fragments of the given fragment type.
		* @throws XBRLException
		*/
		virtual std::unordered_set<std::string> getChildrenIndices(const std::string& type);

		/**
		* @param node The XML node to get the XML language fragment for.
		* @return the value of the xml:lang attribute applying to the given node
		* or null if no such attribute is applicable.
		* @throws XBRLException
		*/
		virtual std::string getLanguage(const xercesc::DOMNode& node);

		/**
		* @return the value of the xml:lang attribute applying to the fragment root
		*         element or null if no such attribute is applicable. This takes
		*         into account xml:lang attribute inheritance though the XML
		*         heirarchy within an XML document.
		* @throws XBRLException
		*/
		virtual std::string getLanguage();

		/**
		* @param languageNameEncoding The language encoding of the language name, available
		* in the data store in the form of a Language XML resource.
		* @see org.xbrlapi.Language for details of these objects.
		* @return the name of the language used for the fragment or 
		* null if none is specified or no appropriate Language resource 
		* is available in the data store.
		* @throws XBRLException
		*/
		virtual std::string getLanguageName(const std::string& languageNameEncoding);

		/**
		* @return the name of the language used for the fragment or null if none is 
		* specified or none is available. The name is obtained by working through the
		* list of language encodings from first to last, returning the first name that 
		* is available in the data store in the form of a Language XML resource.
		* @throws XBRLException
		*/
		virtual std::string getLanguageName(const std::vector<std::string>& languageNameEncodings);
	};
}
