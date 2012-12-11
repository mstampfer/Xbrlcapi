#include "Stdafx.h"
#pragma once

#include <memory>
#include <stack>
#include <deque>
#include <map>
#include <unordered_set>
#include <utility>

#include <xercesc/dom/DOMDocument.hpp>
#include "Poco/URI.h"

#include "Fragment.h"
#include "LoaderImpl.h"
#include "Store.h"

/**
* Loader defines the functions required to get a DTS
* into the data store ready for interactions via the 
* XBRL API.  In many regards, this performs a similar
* role to an XML parser in that it triggers the
* exploration process and eventually populates a data
* structure.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/


namespace xbrlcapi
{
	class EntityResolver;
	class XLinkProcessor;
	class EntityResolver;
	class HashFunctions;
	struct Cache;
	class ElementState;
	struct History;

	class Loader // Serializable 
	{
		std::shared_ptr<LoaderImpl> pimpl;
	public:
		Loader() : pimpl(new LoaderImpl()){}
		//~Loader() {}

		Loader(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver)
			: pimpl(new LoaderImpl(store, xlinkProcessor, entityResolver)) {}

		Loader(Store& store, XLinkProcessor& xlinkProcessor, EntityResolver& entityResolver, const std::vector<Poco::URI>& uris)
			: pimpl(new LoaderImpl(store, xlinkProcessor, entityResolver, uris)) {}

		/**
		* Get the DTS storage implementation
		* @return The DTS store to be used for holding 
		* the information in the DTS
		*/
		std::shared_ptr<Store> getStore()
		{
			pimpl->getStore();
		}	

		/**
		* Get the XLink processor
		* @return The XLink processor used in the DTS discovery process
		*/
		XLinkProcessor getXlinkProcessor()
		{
			pimpl->getXlinkProcessor();
		}

		/**
		* Set the resolver for the resolution of entities found during 
		* the loading and XLink processing
		* @param resolver An entity resolver implementation or null if
		* the loader is to use a default entity resolver that does not 
		* allow for caching.
		*/
		void setEntityResolver(EntityResolver& resolver)
		{
			pimpl->setEntityResolver(resolver);
		}

		/**
		* This method specifies a cache to use when loading 
		* data into the data store.  The cache is only useful (and
		* thus only needs to be specified) when discovering XML that
		* is provided as a string rather than a resource that actually
		* exists at a specified URI.  This is because generally the
		* caching mechanism available via the entityResolver will handle
		* caching for documents that actually exist at the specified URI.
		* care must be taken to ensure that the cache used by the loader 
		* is using the same local root folder as the cache used by the 
		* entityResolver.  This is because the documents cached by the 
		* loader can then be sought in the cache by the entity resolver.
		* @param cache The cache to use in the loader.
		*/
		void setCache(Cache& cache)
		{
			pimpl->setCache(cache);
		}

		/**
		* @return The cache to be used by the loader.
		* @throws XBRLException if the cache is null.
		*/
		Cache getCache()
		{
//			pimpl->getCache();
		}

		/**
		* @return The document node of the XML DOM used
		* by this loader's fragment builders.
		* This should only be used when creating a new
		* fragment using the loader.
		* @throws XBRLException
		*/
		std::shared_ptr<xercesc::DOMDocument> getBuilderDOM()
		{
//			pimpl->getBuilderDOM();
		}

		/**
		* @return the list of documents that are known to still need parsing
		* into the data store.
		*/
		std::vector<Poco::URI> getDocumentsStillToAnalyse()
		{
			pimpl->getDocumentsStillToAnalyse();
		}

		/**
		* Begin the XBRL DTS discovery process with the URIs that
		* are already in the loading/discovery queue.
		* If the store is using persisted networks, then once a discovery
		* process completes without having any failures and without being
		* interrupted, then it will automatically update the persisted
		* networks to reflect relationships defined by 
		* all newly added XLink arcs.
		* @throws XBRLException if the discovery process fails.
		*/
		void discover()
		{
			pimpl->discover();
		}

		/**
		* Parses the next document in the queue of documents
		* to be discovered.  This updates the data store and
		* updates the queue with any new documents that are 
		* identified.
		* Note that this does not update the persisted relationships
		* because there is no guarantee that when the method finishes
		* the data store represents an actual DTS.
		* @throws XBRLException if the discovery process fails.
		*/
		void discoverNext()
		{
			pimpl->discoverNext();
		}

		/**
		* Perform a discovery starting with an XML document that is represented as a string.
		* @param uri The URI to be used for the document that is supplied as a string.
		* @param xml The string representation of the XML document to be parsed.
		* @throws XBRLException if the discovery process fails.
		*/
		void discover(const Poco::URI& uri, const std::string& xml)
		{
			pimpl->discover(uri, xml);
		}

		/**
		* Begin the XBRL DTS discovery process with the specified
		* URIs given in the provided list.
		* @param startingURIs The starting point URIs for the DTS
		* discovery process
		* Trigger the discovery process given the starting URIs.
		* @throws XBRLException if the input list contains objects 
		* other than java.net.URIs.
		*/
		void discover(const std::vector<Poco::URI>& startingURIs)
		{
			pimpl->discover(startingURIs);
		}

		/**
		* Trigger the discovery process given a single URI.
		* @param uri The URI to discover.
		* @throws XBRLException
		*/
		void discover(const Poco::URI& uri)
		{
			pimpl->discover(uri);
		}

		/**
		* Trigger the discovery process given a single URI.
		* @param uri The URI to discover.
		* @throws XBRLException
		*/
		void discover(const std::string& uri)
		{
//			pimpl->discover(uri);
		}	

		/**
		* Stash a URI to await loading into DTS.
		* @param uri The absolute URI to be stashed (any relative
		* URI gets resolved against the Base URI before stashing.
		* @throws XBRLException if the URI cannot be stored for 
		* later exploration or if the URI is not absolute.
		*/
		void stashURI(const Poco::URI& uri)
		{
			pimpl->stashURI(uri);
		}

		/**
		* @param uris The list of URIs to be stashed.
		* @throws XBRLException
		*/
		void stashURIs(const std::vector<Poco::URI>& uris)
		{
			pimpl->stashURIs(uris);
		}


		/**
		* @return the fragment being built currently by the loader 
		* or null if no fragments are currently being build by the loader.
		* @throws XBRLException
		*/
		Fragment getFragment()
		{
			pimpl-> getFragment();
		}

		/**
		* This is particularly useful when you can only fully determine the fragment type
		* by reading in the complex element content of the data corresponding to the fragment.
		* A case in point is the fractionItem fragment type.
		* @param replacement the fragment to replace the current fragment being build with.
		* @throws XBRLException if there is no current fragment.
		*/
		void replaceCurrentFragment(const Fragment& replacement)
		{
			pimpl->replaceCurrentFragment(replacement);
		}	

		/**
		* @return true if and only if the loader has one or more fragments
		* on the stack of fragments being built.
		*/
		bool isBuildingAFragment()
		{
			pimpl->isBuildingAFragment();
		}

		/**
		* @return true if the loader is current engaged in 
		* document discovery and false otherwise.
		*/
		bool isDiscovering()
		{
			pimpl->isDiscovering();
		}

		/**
		* Push a new fragment onto the stack of fragments that are being built
		* by the loader.
		* @param fragment The fragment to be added to the stack of fragments
		* being built by the loader.
		* @param state The state of the element that is the root of the fragment.
		* @throws XBRLException
		*/
		void add(const Fragment& fragment, const ElementState& state)
		{
//			pimpl->add(fragment, state);
		}

		/**
		* Tests if the element that has just been found has triggered the addition of a fragment.
		* Sets the flag to false once it has been tested, ready for the next element to be parsed.
		* @return true iff the element that has just been found has triggered the addition of a fragment.
		* @throws XBRLException.
		*/
		/*	 bool addedAFragment()
		{
		pimpl->addedAFragment();
		}*/

		/**
		* If a fragment is completed, remove the fragment from the 
		* stack being maintained by the loader, store it in the data store and
		* make the necessary update to the stack of child counts for the fragments.
		* @param state The element state for the element currently being parsed.
		* @throws XBRLException
		*/
		void updateState(const ElementState& state)
		{
//			pimpl->updateState(state);
		}



		/**
		* Also increments the fragment index as a side-effect.
		* TODO eliminate the side-effect of the getNextFragmentId method.
		* @return the next unique fragment index
		* @throws XBRLException
		*/
		std::string getNextFragmentId()
		{
			pimpl->getNextFragmentId();
		}

		/**
		* Returns the current fragment index (the one before the next fragment index)
		* @return the next unique fragment index
		* @throws XBRLException
		*/
		std::string getCurrentFragmentId()
		{
			pimpl->getCurrentFragmentId();
		}	

		/**
		* Get the URI for the document being parsed. 
		* @return The original (non-cache) URI of the document being parsed.
		*/
		Poco::URI getDocumentURI()
		{
//			pimpl->getDocumentURI();
		}

		/**
		* Return the entity resolver being used by the loader.
		* @return the entity resolver being used by the loader.
		*/
		EntityResolver getEntityResolver()
		{
			pimpl->getEntityResolver();
		}

		/**
		* The default behaviour is to ignore the content of XML Schema 
		* instance schemaLocation attributes.
		* @return true if the loader is required to discover documents
		* identified in XML Schema instance schemaLocation attributes. 
		*/
		bool useSchemaLocationAttributes()
		{
			pimpl->useSchemaLocationAttributes();
		}

		/**
		* @param useThem must be set to true if you want to discover documents identified
		* in XML Schema instance schemaLocation attributes and false otherwise.
		*/
		void setSchemaLocationAttributeUsage(bool useThem)
		{
			pimpl->setSchemaLocationAttributeUsage(useThem);
		}

		/**
		* Interrupts the loading process once the current 
		* document discovery has been completed.
		* This can be useful when the loader is shared among
		* several threads.
		*/
		void requestInterrupt()
		{
//			pimpl->requestInterrupt();
		}

		/**
		* Cancels a request for an interrupt.
		*/
		void cancelInterrupt()
		{
			pimpl->cancelInterrupt();
		}

		/**
		* Stores the stubs for the documents still to be analysed in
		* the data store being used by the loader.
		* @throws XBRLException
		*/
		void storeDocumentsToAnalyse()
		{
			pimpl->storeDocumentsToAnalyse();
		}

		/**
		* @param history The history recording system
		* to use for all new documents being loaded.
		* If this is null then the history is set to a 
		* naive history that just logs the historic 
		* information.
		*/
		void setHistory(const History& history)
		{
//			pimpl->setHistory(history);
		}

		/**
		* @return the history recording system being used
		* to record the documents being loaded.
		*/
		std::shared_ptr<History> getHistory()
		{
			pimpl->getHistory();
		}

		/**
		* @return true if the loader is using a history recording system
		* to record the URIs being loaded and their 
		* document identifiers.
		*/
		bool hasHistory()
		{
			pimpl->hasHistory();
		}

	};
}
