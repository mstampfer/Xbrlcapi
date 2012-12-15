#include "Stdafx.h"
#pragma once

#include "Fragment.h"
//#include "LabelResource.h"
//#include "Language.h"
//#include "Locator.h"
//#include "ReferenceResource.h"
//#include "SimpleLink.h"
//#include "Builder.h"
#include "Constants.h"
#include "XMLImpl.h"
#include <string>
#include <vector>

/**
* Implements the functionality that is common to all types of XBRL fragments.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class FragmentImpl : public XMLImpl , public Fragment 
	{
		/**
		* 
		*/
	private:

	public:
		/**
		* @see Fragment#getAncestorOrSelf(String)
		*/
		Fragment getAncestorOrSelf(const std::string& type);

		/**
		* @see Fragment#getChildren(String)
		*/
		template <typename F> std::vector<F> getChildren(const std::string& type);

		/**
		* @see Fragment#getChildren(Class)
		*/
//		template <typename F> std::vector<F> getChildren(T requiredClass);

		/**
		* @see Fragment#getChildrenIndices(String)
		*/
		std::unordered_set<std::string> getChildrenIndices(const std::string& type);

		/**
		* @see Fragment#getSimpleLinks()
		*/
		std::vector<SimpleLink> getSimpleLinks();

		/**
		* @see Fragment#getAllChildren()
		*/
		std::vector<Fragment> getAllChildren();

		/**
		* @see Fragment#getAllChildrenIndices()
		*/
		std::unordered_set<std::string> getAllChildrenIndices();

		/**
		* @see Fragment#getChild(String, int)
		*/
		Fragment getChild(const std::string& type, int index);

		/**
		* @see Fragment#getDataRootElement()
		*/
//		Element getDataRootElement();

		/**
		* @see Fragment#isNewFragment()
		*/
		bool isNewFragment();

		/**
		* @see Fragment#getURI()
		*/
		Poco::URI getURI();

		/**
		* @see Fragment#setURI(URI)
		*/
		void setURI(const Poco::URI& uri);

		/**
		* @see Fragment#getReferencingLocators()
		*/
		std::vector<Locator> getReferencingLocators();


		/**
		* @see Fragment#getLabels()
		*/
		std::vector<LabelResource> getLabels();  

		/**
		* @see Fragment#getLabelsWithResourceRole(String)
		*/
		std::vector<LabelResource> getLabelsWithResourceRole(const std::string& resourceRole);

		/**
		* @see Fragment#getLabels(List, List)
		*/
		std::vector<LabelResource> getLabels(std::vector<std::string> languages, std::vector<std::string> resourceRoles);

		/**
		* @see Fragment#getLabels(List, List, List)
		*/
		std::vector<LabelResource> getLabels(std::vector<std::string> languages, std::vector<std::string> labelRoles, std::vector<std::string> linkRoles);   

		/**
		* @see Fragment#getReferencesWithResourceRole(String)
		*/
		std::vector<ReferenceResource> getReferencesWithResourceRole(const std::string& role);

		/**
		* @see Fragment#getLabelsWithLanguage(String)
		*/
		std::vector<LabelResource> getLabelsWithLanguage(const std::string& language);

		/**
		* @see Fragment#getLabelsWithLanguageAndResourceRole(String, String)
		*/
		std::vector<LabelResource> getLabelsWithLanguageAndResourceRole(const std::string& language, const std::string& role);

		/**
		* @see Fragment#getLabelsWithLanguageAndResourceRole(String, String)
		*/
		std::vector<LabelResource> getLabelsWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const std::string& resourceRole, const std::string& linkRole);  

		/**
		* @see Fragment#getReferences()
		*/
		std::vector<ReferenceResource> getReferences();

		/**
		* @see Fragment#getReferencesWithLanguage(String)
		*/
		std::vector<ReferenceResource> getReferencesWithLanguage(const std::string& language);

		/**
		* @see Fragment#getReferencesWithLanguageAndRole(String, URI)
		*/
		std::vector<ReferenceResource> getReferencesWithLanguageAndRole(const std::string& language, const Poco::URI& role);

		/**
		* @see Fragment#getReferencesWithLanguageAndResourceRoleAndLinkRole(String, URI, URI)
		*/
		std::vector<ReferenceResource> getReferencesWithLanguageAndResourceRoleAndLinkRole(const std::string& language, const Poco::URI& resourceRole, const Poco::URI& linkRole);   

		/**
		* @see Fragment#getParentIndex()
		*/
		std::string getParentIndex();

		/**
		* @see Fragment#isChild()
		*/
		bool isChild();

		/**
		* @see Fragment#isAncestorOf(Fragment)
		*/
		bool isAncestorOf(const Fragment& descendant);

		/**
		* @see Fragment#isRoot()
		*/
		bool isRoot();

		/**
		* @see Fragment#setParentIndex(String)
		*/
		void setParentIndex(const std::string& index);

		/**
		* @see Fragment#getXPath()
		*/
		std::string getXPath();

		/**
		* Determines the sibling order of 
		* @param current The element that we are determining
		* the sibling order for.  
		* @return the order of the element, counting sibling 
		* elements from the left in document order.
		*/
	private:
		int getSiblingOrder(Element current);

	public:

		/**
		* @see Fragment#setSequenceToParentElement(Fragment)
		*/
		void setSequenceToParentElement(const Fragment& parent);

		/**
		* @see Fragment#getSequenceToParentElement()
		*/
		std::string getSequenceToParentElement();

		/**
		* @see Fragment#getSequenceToParentElementAsString()
		*/
		virtual std::vector<std::string> getSequenceToParentElementAsString();   

		/**
		* @see Fragment#appendID(String)
		* TODO Eliminate the ID metadata element given the existence of the xptr elements.
		*/
		void appendID(const std::string& id);

		/**
		* @see Fragment#appendElementSchemeXPointer(String)
		*/
		void appendElementSchemeXPointer(const std::string& expression);

		/**
		* @see Fragment#getNamespace()
		*/
		std::string getNamespace();

		/**
		* @see Fragment#getLocalname()
		*/
		std::string getLocalname();

		/**
		* @see Fragment#getPrefixFromQName(String)
		*/
		std::string getPrefixFromQName(const std::string& qname);

		/**
		* Algorithm is as follows:
		* <ol>
		*  <li>If the node is an attribute, redo with the parent node.</li>
		*  <li>If the node is a XBRLAPI metadata element redo with right node in parent fragment.</li>
		*  <li>If the node is an element in the fragment data:</li>
		*   <ol>
		*    <li>Generate namespace declaration attribute name - 'xmlns:...' to search for.</li>
		*    <li>Try to match the QName prefix to the element's prefix to see if the element namespace is appropriate to return.</li>
		*    <li>Try to find the attribute doing the namespace declaration on the element and use that.</li>
		*    <li>If that fails, redo the search using the parent node.</li>
		*   </ol>
		* </ol>
		* 
		* @see Fragment#getNamespaceFromQName(String, Node)
		*/
		std::string getNamespaceFromQName(const std::string& qname, Node node);

		/**
		* Algorithm is as follows:
		* <ol>
		*  <li>If the node is an attribute, redo with the parent node.</li>
		*  <li>If the node is a XBRLAPI metadata element redo with right node in parent fragment.</li>
		*  <li>If the node is an element in the fragment data:</li>
		*   <ol>
		*    <li>Try to find the XML lang attribute and use its value.</li>
		*    <li>If that fails, redo the search using the parent node.</li>
		*   </ol>
		* </ol>
		* 
		* @see Fragment#getLanguage(Node)
		*/
		std::string getLanguage(Node node);

		/**
		* @see Fragment#getLanguage()
		* @see Fragment#getLanguage(Node)
		*/
		std::string getLanguage();

		/**
		* @see Fragment#getLanguageName(String)
		*/
		std::string getLanguageName(const std::string& language);

		/**
		* @see Fragment#getLanguageName(List)
		*/
		std::string getLanguageName(std::vector<std::string> languages);    

		/**
		* @see Fragment#getParent()
		*/
		Fragment getParent();

	/**
	* This method operates as follows:
	* <ol>
	*  <li>If the sequence to the parent element indicates that the 
	*  data root element is the parent - use that.</li>
	*  <li>Loop through the sequence to the parent element.</li>
	* </ol>
	* @see Fragment#getParentElement(Element)
	*/
//	Element getParentElement(Element parentDataRootElement);

	/**
	* @see Fragment#getLocalnameFromQName(String)
	*/
	std::string getLocalnameFromQName(const std::string& qname);

	/**
	* @see Fragment#getXPointerExpression()
	*/
	std::string getXPointerExpression();

	/**
	* @see Fragment#getElementSchemeXPointerExpression()
	*/
	std::string getElementSchemeXPointerExpression();

	/**
	* @see Fragment#getIDXPointerExpression()
	*/
	std::string getIDXPointerExpression();

};
}
