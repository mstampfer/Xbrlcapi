
#pragma once
#include "Logger.h"


#include "Fragment.h"
#include "Concept.h"
#include "Unit.h"
#include "Context.h"
#include "FootnoteResource.h"
#include "ExtendedLink.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>



namespace xbrlcapi
{
	struct Item;
	/**
	
	*/

	class Tuple;
	class EntityResource;
	struct Fact;

	struct Instance : public Fragment {

		/**
		* Get the list of schemaRef fragments in the instance
		* Returns null if none are contained by the XBRL instance.
		* @throws XBRLException
		*/
		virtual std::vector<SimpleLink> getSchemaRefs();    

		/**
		* Get the list of linkbaseRef fragments in the instance
		* Returns null if none are contained by the XBRL instance.
		* @throws XBRLException
		*/
		virtual std::vector<SimpleLink> getLinkbaseRefs();    

		/**
		* Get list contexts contained in the instance.
		* Returns null if none are contained by the XBRL instance.
		* @throws XBRLException
		*/
		virtual std::vector<Context> getContexts();    

		/**
		* Get a specified context from the instance based on its id.
		* @param id The id of the context fragment
		* @return the context fragment
		* @throws XBRLException if the context does not exist
		*/
		virtual Context getContext(const std::string& id);

		/**
		* Get the list of units contained in the instance.
		* Returns null if none are contained by the XBRL instance.
		*
		* @throws XBRLException
		*/
		virtual std::vector<Unit> getUnits();    

		/**
		* Get a specified unit from the instance based on its id.
		* @param id The id of the unit fragment
		* @return the unit fragment
		* @throws XBRLException if the unit is not in this instance.
		*/
		virtual Unit getUnit(const std::string& id);

		/**
		* Get a list of footnote link fragments
		* Returns null if none are contained by the XBRL instance.
		* @throws XBRLException
		*/
		virtual std::vector<ExtendedLink> getFootnoteLinks();    

		/**
		* @return a list containing all of the footnote resources in the instance.
		* @throws XBRLException
		*/
		virtual std::vector<FootnoteResource> getFootnotes();
		/**
		* Get the list of facts that are children of the instance.
		* Facts that are within tuples are not included in this list.
		* @return the list of facts that are children of the instance.
		* @throws XBRLException
		*/
		virtual std::vector<Fact&> getChildFacts();

		/**
		* @return all facts (tuples and facts within tuples also) in this instance.
		* @throws XBRLException
		*/
		virtual std::vector<Fact&> getAllFacts();

		/**
		* @return the list of concepts that have facts that are children of 
		* this XBRL instance (rather than being children of tuples).
		* @throws XBRLException
		*/
		virtual std::vector<Concept> getChildConcepts();

		/**
		* @return the list of all concepts that have facts in this 
		* XBRL instance, including nested within tuples.
		* @throws XBRLException
		*/
		virtual std::vector<Concept> getAllConcepts();

		/**
		* @return the number of concepts that have facts that are children of
		* this XBRL instance (rather than being nested within tuples).
		* @throws XBRLException
		*/
		virtual long getChildConceptsCount();

		/**
		* @return the number of concepts that have facts in this instance.
		* @throws XBRLException
		*/
		virtual long getAllConceptsCount();    

		/**
		* @return the number of child facts in the instance (excludes 
		* facts that are contained within tuples).
		* @throws XBRLException
		*/
		virtual long getChildFactsCount();

		/**
		* @return the number of facts in the instance including tuples and
		* those facts within tuples.
		* @throws XBRLException
		*/
		virtual long getAllFactsCount();

		/**
		* @return the value of the earliest start 
		* date or instance in a context period in the XBRL instance.
		* Returns null if the XBRL instance does not contain a context that does not
		* have a value of forever.
		* @throws XBRLException
		*/
		virtual std::string getEarliestPeriod();

		/**
		* @return the value of the latest start 
		* date or instance in a context period in the XBRL instance.
		* Returns null if the XBRL instance does not contain a context that does not
		* have a value of forever.
		* @throws XBRLException
		*/
		virtual std::string getLatestPeriod();

		/**
		* @return the list of entity resources for entities with facts in the instance.
		* @throws XBRLException
		*/
		virtual std::vector<EntityResource> getEntityResources(); 

		/**
		* @return A map, indexed by entity identifier schemes, of sets of the entity identifiers
		* for those schemes, as contained in this XBRL instance.
		* @throws XBRLException
		*/
		virtual std::unordered_map<std::string, std::unordered_set<std::string>> getEntityIdentifiers();

		/**
		* @return the list of tuples that are children of the instance.
		* Tuples that are within tuples are not included in this list.
		* The list is empty if the instance does not contain tuples.
		* @throws XBRLException
		*/
		virtual std::vector<Tuple> getTuples();    

		/**
		* @return the list of all items that are children of the instance.
		* Tuples (and the items that they contain are not included in the list).
		* @throws XBRLException
		*/
		virtual std::vector<Item> getChildItems();

		/**
		* @return the list of all items in the instance including those in
		* tuples.
		* @throws XBRLException
		*/
		virtual std::vector<Item> getAllItems();    

		/**
		* @param namespace The namespace of the facts to select.
		* @param localname The local name of the facts to select.
		* @return the list of facts in the instance with the given 
		* namespace and local name.
		* @throws XBRLException if either parameter is null.
		*/
		virtual std::vector<Fact&> getFacts(const std::string& Namespace, const std::string& localname);

		/**
		* @param concept the concept to get the facts for.
		* @return the list of facts in this instance that are
		* reporting values for the specified concept.
		* @throws XBRLException if the parameter is null.
		*/
		virtual std::vector<Fact&> getFacts(const Concept& concept);

	
private:
Logger logger;
};
}
