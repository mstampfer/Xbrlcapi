

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Link.h"

/**

*/
struct Resulrce;
namespace xbrlcapi
{
	class Arc;
	class Locator;
	class XlinkDocumentation;
	struct Resource;

	struct ExtendedLink : public Link {

		/**
		* Get the list of locators contained by the extended link.
		* Returns null if the extended link contains no locators.
		* @throws XBRLException
		*/
		virtual std::vector<Locator> getLocators();

		/**
		* Get the list of Arc Ends (locators or resources) with a specified label in 
		* the extended link.
		* @param label The string value of the xlink:label attribute on the arc ends.
		* @return the list of matching fragments or the empty list if none are found.
		* @throws XBRLException
		*/
		template <typename E>
		std::vector<E> getArcEndsWithLabel(const std::string& label);

		/**
		* Get the list of locators with a specified label in the extended link.
		* @param label The string value of the xlink:label attribute on the locator.
		* @return the list of matching locator fragments or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Locator> getLocatorsWithLabel(const std::string& label);

		/**
		* Get the list of locators in the extended link with a specified absolute HREF.
		* @param href The resolved value of the xlink:href attribute on the locator.
		* @return the list of matching locator fragments or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Locator> getLocatorsWithHref(const std::string& href);

		/**
		* Get the list of arcs contained by the extended link.
		* @return the list of matching arc fragments or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcs();

		/**
		* @param arcrole The arcrole of the required arcs.
		* Get the list of arcs with the given arcrole that are 
		* contained by the extended link.
		* @return the list of matching arc fragments or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcsWithArcrole(const std::string& arcrole);


		/**
		* @param from The required value of the xlink:from attribute of the arcs.
		* @return the list of arcs with a given xlink:from label in extended link.
		* or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcsWithFromLabel(const std::string& from);

		/**
		* @param from The required value of the xlink:from attribute of the arcs.
		* @param arcrole The arcrole value for the arcs being sought.
		* @return the list of arcs in the extended link starting at the given xlink label 
		* and arcrole value or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcsWithFromLabelAndArcrole(const std::string& from, const std::string& arcrole);

		/**
		* @param to The required value of the xlink:to attribute of the arcs.
		* @return the list of arcs with a given xlink:from label in extended link
		* or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcsWithToLabel(const std::string& to);

		/**
		* @param to The required value of the xlink:to attribute of the arcs.
		* @param arcrole The arcrole value for the arcs being sought.
		* @return the list of arcs in the extended link ending at the given xlink label 
		* and arcrole value or the empty list if none are found.
		* @throws XBRLException
		*/
		virtual std::vector<Arc> getArcsWithToLabelAndArcrole(const std::string& to, const std::string& arcrole);

		/**
		* Get the list of resources contained by the extended link.
		* @return the list of resource fragments in the extended link.
		* @throws XBRLException
		*/
		virtual std::vector<Resource> getResources();

		/**
		* Get the list of resources with the specified label.
		* @param label The value of the label used to select resources in the extended link.
		* @return the list of resource fragments with the given xlink:label attribute value.
		* @throws XBRLException
		*/
		virtual std::vector<Resource> getResourcesWithLabel(const std::string& label);    

		/**
		* Get the list of documentation fragments contained by the extended link.
		* Returns the list of documentation fragments in the extended link.
		* @throws XBRLException
		*/
		virtual std::vector<XlinkDocumentation> getDocumentations();

		/**
		* @return A map, indexed by XLink label, of the XLink arc end indices
		* in an extended link.
		* @throws XBRLException
		*/
		virtual std::unordered_map<std::string,std::vector<std::string>> getArcEndIndicesByLabel();

		/**
		* @return a map of locator target indices indexed by the indices of the
		* locators that target them.
		* @throws XBRLException
		*/
		virtual std::unordered_map<std::string,std::string> getLocatorTargetIndices();
	};
}
