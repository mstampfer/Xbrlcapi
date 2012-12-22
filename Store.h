
#pragma once
#include "Logger.h"

#include <vector>
#include <memory>
#include <unordered_set>
#include <set>
#include <unordered_map>


#include <Poco/URI.h>
#include <xercesc/dom/DOMDocument.hpp>

#include "StoreImpl.h"

namespace xbrlcapi
{
	class Analyser;
	class Arc;
	class ArcroleType;
	class Collection;
	class Concept;
	class Element;
	struct ExtendedLink;
	class File;
	struct Fragment;
	class LabelResource;
	class Language;
	class Loader;
	struct Matcher;
	class Network;
	class Networks;
	class OutputStream;
	class ReferenceResource;
	class Relationship;
	class RoleType;
	class Schema;
	class Stub;
	struct XML;
	struct Fact;
	struct Item;
	class DefaultMatcherImpl;
	class Loader;


	/**
	* The data store interface, defining all methods that need to be 
	* implemented by a data store to support the XBRLAPI.
	* 
	* The store constructor needs to initialise the data structure.  
	* For example, the constructor would be required to
	* establish a database connection if an XML database is being
	* used to handle the underlying data.  Alternatively, the constructor
	* would establish an XML DOM document if an XML DOM were being used
	* as the underlying data structure.  Similarly, initialisation
	* steps would be taken if XML data binding to Java objects were
	* being used to handle the underlying data.
	*
	
	*/
	//template <typename F>
	class Store// extends Serializable 
	{
		std::unique_ptr<StoreImpl> pimpl;
		void swap(Store& rhs)
		{
			if (pimpl)
				pimpl = std::move(rhs.pimpl);
			else
				pimpl.swap(rhs.pimpl);
		}

	public:
		Store() : pimpl(new StoreImpl()) {}
		Store(const std::string& database, const std::string& container, const int size)
			:pimpl(new StoreImpl(database,container,size))
		{}

		Store(const std::string& database, const std::string& container)
			:pimpl(new StoreImpl(database,container))
		{}

		Store& operator=(Store& rhs)
		{
			swap(rhs);
			return *this;
		}

		Store& operator=(Store&& rhs) 
		{
			swap(rhs);
			return *this;
		}

		Store(Store& rhs)
		{
			swap(rhs);
		}

		Store(Store&& rhs)
		{
			swap(rhs);
		}

		/**
		* Close the data store.
		* This method must be synchronized.
		* Throws XBRLException if the data store cannot be closed. 
		*/
				void close()
				{
					pimpl->close();
				}
		//
		//		/**
		//		* Store a fragment.
		//		* Implementations of this method must always be synchronized. 
		//		* @param xml The fragment to be added to the store.
		//		* @throws XBRLException if the fragment cannot be added to the store.
		//		*/
		//		void persist(const XML& xml)
		//		{
		//			pimpl->persist(xml);
		//		}    
		//
		//		/**
		//		* Test if a store contains a specific fragment, as identified by
		//		* its index.
		//		* Implementations of this method must be synchronized.
		//		* @param index The index of the fragment to test for.
		//		* @return true iff the store contains a fragment with the specified 
		//		* fragment index.
		//		* @throws XBRLException If the test cannot be conducted.
		//		*/
		//		bool hasXMLResource(const std::string& index)
		//		{
		//			pimpl->hasXMLResource(index);
		//		}
		//
		//		/**
		//		* Retrieves an XML Resource from a data store.
		//		* Implementations of this method must be synchronized.
		//		* @param index The index of the XML resource.
		//		* @return The XML resource corresponding to the specified index.
		//		* @throws XBRLException if the XML resource cannot be retrieved.
		//		*/
		//		//F getXMLResource(const std::string& index)
		//		//{
		//		//	pimpl->getXMLResource(index);
		//		//}
		//
		//		/**
		//		* Remove a fragment from the underlying data structure.
		//		* If a fragment with the same ID does not already exist in the 
		//		* data store then no action is required.
		//		* Implementations of this method must be synchronized.
		//		* @param index The index of the fragment to be removed from the DTS store.
		//		* @throws XBRLException if the fragment cannot be removed from the store.
		//		*/
		//		void remove(const std::string& index)
		//		{
		//			pimpl->remove(index);
		//		}
		//
		//		/**
		//		* Remove a XML resource from the underlying data structure.
		//		* If a XML resource with the same ID does not already exist in the 
		//		* data store then no action is required.
		//		* @param xml The XML resource to remove.
		//		* @throws XBRLException if the XML resource cannot be removed from the store.
		//		*/
		//		void remove(const XML& xml)
		//		{
		//			pimpl->remove(xml);
		//		}	
		//
		//		/**
		//		* @param namespace The namespace to bind a prefix to for querying
		//		* @param prefix The prefix to bind to the namespace for querying
		//		* @throws XBRLException if either argument is null.
		//		*/
		//		void setNamespaceBinding(const std::string& Namespace, const std::string& prefix)
		//		{
		//			pimpl->setNamespaceBinding(Namespace,prefix);
		//		}
		//
		//		/**
		//		* This should not need to be called but is available if the number of mappings
		//		* in the namepace mapping table grows innefficiently large.
		//		* @param prefix the prefix to remove the namespace binding for
		//		* @throws XBRLException
		//		*/
		//		void removeNamespaceBinding(const std::string& prefix)
		//		{
		//			pimpl->removeNamespaceBinding(prefix);
		//		}
		//
		//		/**
		//		* This deletion method does not ensure that all other documents that
		//		* link to the document being deleted are also deleted.  This can cause
		//		* relationships in the data store to be non-resolvable.
		//		* @param uri The URI of the document to delete from the data store.
		//		* @throws XBRLException
		//		*/
		//		void deleteDocument(const Poco::URI& uri)
		//		{
		//			pimpl->deleteDocument(uri);
		//		}
		//
		//		/**
		//		* This deletion method ensures that all related documents
		//		* are also deleted from the data store.  A related document is defined
		//		* as a document that causes the discovery of this document.
		//		* Note that this means that applying this method to an XBRL instance 
		//		* only causes the XBRL instance to be deleted because no other documents
		//		* cause discovery of this document.
		//		* This method is intended to allow document deletions to occur without 
		//		* violating the closure property of a DTS.  In otherwords, if you want
		//		* to delete the specified document from the DTS defined by the content of the
		//		* data store, you also delete all documents that would require it to be 
		//		* in the DTS.
		//		* @param uri The URI of the document to delete.
		//		* @throws XBRLException
		//		*/
		//		void deleteRelatedDocuments (const Poco::URI&  uri)
		//		{
		//			pimpl->deleteRelatedDocuments(uri);
		//		}
		//
		//		/**
		//		* Run a query against the collection of all fragments in the store.
		//		* Implementations of this method must be synchronized.
		//		* @param query The XQuery query to run against the set of fragments.
		//		* Any occurrences of the string #roots# in a query will be deemed to 
		//		* be a marker for the root elements of the fragments in an XML database collection 
		//		* and it will be substituted with the necessary
		//		* expression to identify those roots in the data store.
		//		* @return a list of matching fragments or the empty list if no matching fragments
		//		* exist.
		//		* @throws XBRLException if the query cannot be executed.
		//		*/
		//		//std::vector<F> queryForXMLResources(const std::string& query)
		//		//{
		//		//	pimpl->queryForXMLResources(query);
		//		//}
		//
		//		/**
		//		* Run a query against the collection of all fragments in the store.
		//		* Implementations of this method must be synchronized.
		//		* @param query The XQuery query to run against the set of fragments.
		//		* Any occurrences of the string #roots# in a query will be deemed to 
		//		* be a marker for the root elements of the fragments in an XML database collection 
		//		* and it will be substituted with the necessary
		//		* expression to identify those roots in the data store.
		//		* The query <strong>MUST</strong> return a sequence of XML resource metadata root elements
		//		* matching the query.  Otherwise, results from the query will be unpredictable.
		//		* @return a set of the indices of XML resources matching 
		//		* the query.
		//		* @throws XBRLException if the query cannot be executed.
		//		*/
		//		std::unordered_set<std::string>  queryForIndices(const std::string& query)
		//		{
		//			pimpl->queryForIndices(query);
		//		}
		//
		//		/**
		//		* This method must be synchronised
		//		* @param query The XQuery to run.
		//		* Any occurrences of the string #roots# in a query will be deemed to 
		//		* be a marker for the root elements of the fragments in an XML database collection 
		//		* and it will be substituted with the necessary
		//		* expression to identify those roots in the data store.
		//		* @return a count of the number of results returned by the query.
		//		* @throws XBRLException if the query cannot be executed.
		//		*/
		//		long queryCount(const std::string& query)
		//		{
		//			pimpl->queryCount(query);
		//		}    
		
				/**
				* Run a query that is required to return a sequence of strings.
				* Implementations of this method must be synchronized.
				* @param query The XQuery query to run against the set of fragments.
				* Any occurrences of the string #roots# in a query will be deemed to 
				* be a marker for the root elements of the fragments in an XML database collection 
				* and it will be substituted with the necessary
				* expression to identify those roots in the data store.
				* @return a list of strings, each of which is a query result.
				* @throws XBRLException if the query cannot be executed or if the
				* query results are not strings.
				*/
				std::unordered_set<std::string>  queryForStrings(std::string& query)
				{
					pimpl->queryForStrings(query);
				}
		//
		//		/**
		//		* Run a query that is required to return a single string.
		//		* Implementations of this method must be synchronized.
		//		* @param query The XQuery query to run against the set of fragments.
		//		* Any occurrences of the string #roots# in a query will be deemed to 
		//		* be a marker for the root elements of the fragments in an XML database collection 
		//		* and it will be substituted with the necessary
		//		* expression to identify those roots in the data store.
		//		* @return a single string that is the query result or null if the query
		//		* does not return any strings.
		//		* @throws XBRLException if the query cannot be executed or if the
		//		* query result is not a single string.
		//		*/
		//		std::string queryForString(const std::string& query)
		//		{
		//			pimpl->(query);
		//		}
		//
		//		/**
		//		* Serialize the specified XML DOM to the specified destination.
		//		* @param what the root element of the DOM to be serialised.
		//		* @param destination The destination output stream to be serialised to.
		//		* @throws XBRLException if the DOM cannot be serialised
		//		* because the destination cannot be written to or some other
		//		* different problem occurs during serialisation.
		//		*/
		//		void serialize(const Element& what, OutputStream destination)
		//		{
		//			pimpl->serialize(destination);
		//		}
		//
		//		/**
		//		* Serialize the specified XML DOM to the specified destination.
		//		* @param what the root element of the DOM to be serialised.
		//		* @param destination The destination file to be serialised to.
		//		* @throws XBRLException if the DOM cannot be serialised
		//		* because the destination cannot be written to or some other
		//		* different problem occurs during serialisation.
		//		*/
		//		//void serialize(const Element& what, const File& destination)
		//		//{
		//		//	pimpl->serialize(destination);
		//		//}
		//
		//		/**
		//		* Serialize the specified XML DOM node.
		//		* @param what the root element of the DOM to be serialised.
		//		* @return a string containing the serialized XML.
		//		* @throws XBRLException
		//		*/
		//		std::string serialize(const Element& what)
		//		{
		//			pimpl->serialize(what);
		//		}    
		//
		//		/**
		//		* Get a single document in the store as a DOM.
		//		* @param uri The URI of the document to be retrieved.
		//		* @return a DOM Document containing the XML representation of the
		//		* file at the specified URI.  Returns null if the store does not
		//		* contain a document with the given URI.
		//		* @throws XBRLException if the document cannot be constructed as a DOM.
		//		*/
		//		//Element getDocumentAsDOM(const Poco::URI& uri)
		//		//{
		//		//	pimpl->getDocumentAsDOM(uri);
		//		//}
		//
		//		/**
		//		* Serializes the individual documents in the data store, 
		//		* saving them into a directory structure that is placed into
		//		* the specified directory.  The directory structure that is 
		//		* created mirrors the structure of the URIs of the documents. 
		//		* Note that the URIs of the documents that are written out
		//		* will be reflected in the paths to those documents
		//		* using the same rules as those applied for document caching.
		//		* @param destination The folder in which the directory structure and
		//		* the documents in the data store are to be saved.  
		//		* @throws XBRLException If the root folder does not exist or 
		//		* is not a directory or if the documents in the store cannot 
		//		* be saved to the local file system.
		//		*/
		//		void saveDocuments(const File& destination)
		//		{
		//			pimpl->saveDocuments(destination);
		//		}
		//
		//		/**
		//		* Serializes those documents in the data store with a URI that
		//		* begins with the specified URI prefix. They are saved to the local
		//		* file system in the same manner as is applied for the saveDocuments
		//		* method that operates on all documents in the data store.
		//		* @param destination The folder in which the directory structure and
		//		* the documents in the data store are to be saved.
		//		* @param uriPrefix All documents in the data store with a URI that begins 
		//		* with the string specified by uriPrefix will be saved to the local
		//		* file system.
		//		* @throws XBRLException If the root folder does not exist or 
		//		* is not a directory or if the documents in the store cannot 
		//		* be saved to the local file system.
		//		*/
		//		void saveDocuments(const File& destination, const std::string& uriPrefix)
		//		{
		//			pimpl->saveDocuments(destination, uriPrefix);
		//		}
		//
		//		/**
		//		* Creates a single DOM structure from all documents in the 
		//		* data store and saves this single XML structure in the
		//		* specified file.
		//		* @param file The file to save the Store content to.
		//		* @throws XBRLException if the documents in the store cannot be
		//		* saved to the single file.
		//		*/
		//		void saveStoreAsSingleDocument(const File& file)
		//		{
		//			pimpl->saveStoreAsSingleDocument(file);
		//		}
		//
		//		/**
		//		* Returns the root element of the subtree starting with the
		//		* fragment with the specified index.  All subtrees for a given store
		//		* instance are produced from the one XML DOM and so can be appended
		//		* to each other as required.
		//		* @param f The fragment at the root of the subtree.
		//		* @return The root element of the subtree headed by the fragment
		//		* with the specified index.
		//		* @throws XBRLException if the subtree cannot be constructed.
		//		*/
		//		//Element getSubtree(const Fragment& f)
		//		//{
		//		//	pimpl->getSubtree(f);
		//		//}
		//
		//		/**
		//		* Get all data in the store as a single XML DOM object.
		//		* @return the XML DOM representation of the XBRL information in the 
		//		* data store.
		//		* @throws XBRLException if the DOM cannot be constructed.
		//		*/
		//		std::shared_ptr<xercesc::DOMDocument> getStoreAsDOM()
		//		{
		//			pimpl->getStoreAsDOM();
		//		}
		//
		//		/**
		//		* Get all data in the store as a single XML DOM object including
		//		* the annotations used in the 
		//		* <a href="http:www.sourceforge.net/xbrlcomposer/">XBRLComposer</a> project.
		//		* @return the composed data store as a DOM object.
		//		* @throws XBRLException if the composed data store cannot be constructed.
		//		*/
		//		std::shared_ptr<xercesc::DOMDocument> getCompositeDocument()
		//		{
		//			pimpl->getCompositeDocument();
		//		}
		//
		//		/**
		//		* Get a list of the URIs that have been stored.
		//		* @return a list of the URIs in the data store.
		//		* @throws XBRLException if the list cannot be constructed.
		//		*/
		//		std::unordered_set<Poco::URI> getDocumentURIs()
		//		{
		//			pimpl->getDocumentURIs();
		//		}
		
				/**
				* Test if a particular URI is already in the data store.
				* @param uri the string representation of the URI to be tested for.
				* @return true if the document is in the store and false otherwise.
				* @throws XBRLException.
				*/
				bool hasDocument(const Poco::URI& uri)
				{
					return pimpl->hasDocument(uri);
				}
		//
		//		/**
		//		* Stores the state of the document discovery process.
		//		* @param documents The map from URIs of the documents 
		//		* remaining to be discovered to the textual reason why 
		//		* the document has not yet been discovered.
		//		* @throws XBRLException
		//		*/
		//		void persistLoaderState(std::unordered_map<Poco::URI,std::string> documents)
		//		{
		//			pimpl->persistLoaderState(documents);
		//		}    
		//
		//		/**
		//		* @return the number of fragments in the data store.
		//		* @throws XBRLException if the number of fragments cannot be determined.
		//		*/
		//		int getSize()
		//		{
		//			pimpl->getSize();
		//		}

		/**
		* @return the list of URIs of the documents remaining to be analysed.
		* @throws XBRLException if any of the document URIs are malformed.
		*/
		std::vector<Poco::URI> getDocumentsToDiscover()
		{
			return pimpl->getDocumentsToDiscover();
		}
		//
		//		/**
		//		* @return a list of stub fragments (Those fragments indicating a 
		//		* document that needs to be added to the data store).
		//		* @throws XBRLException
		//		*/
		//		std::vector<Stub> getStubs()
		//		{
		//			pimpl->getStubs();
		//		}
		//
		//		/**
		//		* @param uri The string value of the URI of the document to get the stub for.
		//		* @return the list of stub fragments for the given URI.
		//		*/
		//		std::vector<Stub> getStubs(const Poco::URI& uri)
		//		{
		//			pimpl->getStubs(uri);
		//		}
		//
		//		/**
		//		* @param document The document to store a stub for.
		//		* @param reason The reason the document has not been stored.
		//		* @throws XBRLException
		//		*/
		//		void persistStub(const Poco::URI& document, const std::string& reason)
		//		{
		//			pimpl->persistStub(document, reason);
		//		}    
		//
		//		/**
		//		* @param stub The stub to be removed from the data store.
		//		* @throws XBRLException
		//		*/
		//		void removeStub(const Stub& stub)
		//		{
		//			pimpl->removeStub(stub);
		//		}
		//
		//		/**
		//		* Return a list of XML resources in a data store
		//		* that have a type corresponding to the specified XML resource interface name.
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*  org.xbrlapi.impl.ReferenceArcImpl fragments is required then
		//		*  this parameter would have a value of "ReferenceArc".
		//		*  Note that if the parameter contains full stops, then it is used directly
		//		*  as the value for the fragment type, enabling fragment extensions to exploit this
		//		*  method without placing fragment implementations in the org.xbrlapi package.
		//		*  
		//		* @return a list of XML resources with the given fragment type.
		//		* @throws XBRLException
		//		*/
		//		template <typename F>
		//		std::vector<F> getXMLResources(const std::string& interfaceName)
		//		{
		//			pimpl->getXMLResources(interfaceName);
		//		}
		//
		//		/**
		//		* Return a list of XML resources in a data store
		//		* that have a type corresponding to the specified XML resource interface name.
		//		* @param specifiedClass The class of XML resources to retrieve.
		//		* @return a list of XML resources with the given fragment type.
		//		* @throws XBRLException
		//		*/
		//		//std::vector<F> getXMLResources(F specifiedClass)
		//		//{
		//		//	pimpl->getXMLResources(specifiedClass);
		//		//}
		//
		//		/**
		//		* @param specifiedClass The class of XML resource to count.
		//		* @return The number of XML resources of the given class type in the data store.
		//		* @throws XBRLException
		//		*/
		//		//long getNumberOfXMLResources(F specifiedClass)
		//		//{
		//		//	pimpl->getNumberOfXMLResources(specifiedClass);
		//		//}
		//
		//		/**
		//		* @deprecated
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*  org.xbrlapi.impl.ReferenceArcImpl fragments is required then
		//		*  this parameter would have a value of "ReferenceArc".
		//		*  Note that this method does not yet recognise fragment subtypes so 
		//		*  a request for an Arc would not return all ReferenceArcs as well as other
		//		*  types of arcs.
		//		*  @param parentIndex The index of the parent fragment.
		//		* @return a list of fragments with the given fragment type 
		//		* and with the given parent fragment.  The list is empty if there
		//		* are not child fragments.
		//		* @throws XBRLException
		//		*/
		//		//std::vector<F> getChildFragments(const std::string& interfaceName, const std::string& parentIndex)
		//		//{
		//		//	pimpl->getChildFragments(interfaceName, parentIndex);
		//		//}
		//
		//		/**
		//		* @param linkRole The linkrole of the networks.
		//		* @param arcrole The arcrole of the networks.
		//		* @return the collection of networks expressed using arcs that involve this 
		//		* linkrole and arcrole.
		//		* @throws XBRLException
		//		*/
		//		//Networks getNetworks(const std::string& linkRole, const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworks(linkRole, arcrole);
		//		//}
		//
		//		/**
		//		* @param arcrole The XLink arcrole value.
		//		* @return the collection of networks expressed using arcs 
		//		* that involve this arc role.
		//		* @throws XBRLException
		//		*/
		//		//Networks getNetworks(const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworks(arcrole);
		//		//}
		//
		//		/**
		//		* Note that this can massively overload resources if the 
		//		* data store is large because much of the information in the 
		//		* store will be reflected in -in-memory objects.  Use this method
		//		* with care.
		//		* @return the collection of all networks in the store.
		//		* @throws XBRLException
		//		*/
		///*		Networks getNetworks()
		//		{
		//			pimpl->getNetworks();
		//		}   */ 
		//
		//		/**
		//		* @param <F> The type of fragment.
		//		* @param sourceIndex The index of the source fragment.
		//		* @param linkRole The XLink link role.
		//		* @param arcrole The XLink arcrole. 
		//		* @return the list of targets from the specified source where the
		//		* relationship has the given link role and arcrole. If the link role
		//		* is null then targets of relationships with any linkrole are returned. If the 
		//		* arcrole is null then targets of relationships with any arcrole are returned.
		//		* @throws XBRLException
		//		*/
		//		template <typename F>
		//		std::vector<F> getTargets(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
		//		{
		//			pimpl->getTargets(sourceIndex, linkRole, arcrole);
		//		}
		//
		//		/**
		//		* @param <F> The type of fragment.
		//		* @param targetIndex The index of the target fragment.
		//		* @param linkRole The XLink link role.
		//		* @param arcrole The XLink arcrole. 
		//		* @return the set of sources related to the specified target where the
		//		* relationship has the given link role and arcrole. If the link role
		//		* is null then sources of relationships with any linkrole are returned. If the 
		//		* arcrole is null then sources of relationships with any arcrole are returned.
		//		* @throws XBRLException
		//		*/
		//		//std::vector<F> getSources(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
		//		//{
		//		//	pimpl->getSources(targetIndex, linkRole, arcrole);
		//		//}
		//
		//		/**
		//		* @param targetIndex The index of the target fragment.
		//		* @param linkRole The XLink link role.
		//		* @param arcrole The XLink arcrole. 
		//		* @return the set of indices of sources related to the specified target where the
		//		* relationship has the given link role and arcrole. If the link role
		//		* is null then sources of relationships with any linkrole are returned. If the 
		//		* arcrole is null then indices of sources of relationships with any arcrole are returned.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getSourceIndices(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
		//		{
		//			pimpl->getSourceIndices(targetIndex, linkRole, arcrole);
		//		}    
		//
		//		/**
		//		* @param analyser The persisted network analyser
		//		* to use for network analysis when building the
		//		* aspect model.  Set to null if you do not want to 
		//		* build the aspect model using persisted network information.
		//		*/
		//		void setAnalyser(Analyser analyser)
		//		{
		//			pimpl->setAnalyser(analyser);
		//		}
		//
		//		/**
		//		* @return the persisted network analyser if one is being used
		//		* and null otherwise.
		//		*/
		//		//Analyser getAnalyser()
		//		//{
		//		//	pimpl->getAnalyser();
		//		//} 
		//
		//		/**
		//		* @return true if the store is using
		//		* persisted network information rather than using the 
		//		* raw network information embodied in XBRL fragments. Returns
		//		* false otherwise.
		//		* @see org.xbrlapi.networks.Analyser
		//		*/
		//		bool isPersistingRelationships()
		//		{
		//			pimpl->isPersistingRelationships();
		//		}    
		//
		//		/**
		//		* Utility method to return a list of fragments in a data store
		//		* that have a type corresponding to the specified fragment interface name and
		//		* that are in the document with the specified URI.
		//		* @param uri The URI of the document to get the fragments from.
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*   fragments is required then
		//		*  this parameter would have a value of "ReferenceArc".
		//		*  Note that this method does not yet recognise fragment subtypes so 
		//		*  a request for an Arc would not return all ReferenceArcs as well as other
		//		*  types of arcs.
		//		* @return a list of fragments with the given fragment type and in the given document.
		//		* @throws XBRLException
		//		*/
		//		//std::vector<F> getFragmentsFromDocument (const Poco::URI&  uri, const std::string& interfaceName)
		//		//{
		//		//	pimpl->getFragmentsFromDocument(uri, interfaceName);
		//		//}
		//
		//		/**
		//		* @param uri The URI of the document to get the fragments from.
		//		* @param fragmentClass The class of fragment being sought.
		//		* @return a list of fragments in the given fragment class and in the given document.
		//		* @throws XBRLException
		//		* @see Store#getFragmentsFromDocument(URI, String)
		//		*/
		///*		std::vector<F> getFragmentsFromDocument (const Poco::URI&  uri, F fragmentClass)
		//		{
		//			pimpl->getFragmentsFromDocument(uri, fragmentClass);
		//		}*/    
		//
		//
		//		/**
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*  Concept fragments is required then this parameter would have a value of "Concept".
		//		*  Note that this method does not yet recognise fragment subtypes so 
		//		*  a request for an ElementDeclaration would not return all concepts as well as
		//		*  other XML Schema element declarations.
		//		* @return a list of fragment indices with the given fragment type.
		//		* @throws XBRLException
		//		*/    
		//		std::unordered_set<std::string>  getFragmentIndices(const std::string& interfaceName)
		//		{
		//			pimpl->getFragmentIndices(interfaceName);
		//		}
		//
		//		/**
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*  Concept fragments is required then this parameter would have a value of "Concept".
		//		*  Note that this method does not yet recognise fragment subtypes so 
		//		*  a request for an ElementDeclaration would not return all concepts as well as
		//		*  other XML Schema element declarations.
		//		* @return a list of root fragment indices with the given fragment type.
		//		* @throws XBRLException
		//		*/    
		//		std::unordered_set<std::string>  getRootFragmentIndices(const std::string& interfaceName)
		//		{
		//			pimpl->getRootFragmentIndices(interfaceName);
		//		}    
		//
		//		/**
		//		* @param uri The URI of the document to get the fragments from.
		//		* @param interfaceName The name of the interface.  EG: If a list of
		//		*  concept fragments is required then
		//		*  this parameter would have a value of "Concept".
		//		*  Note that this method does not yet recognise fragment subtypes so 
		//		*  a request for an ElementDeclaration would not return all concepts as well as
		//		*  other XML Schema element declarations.
		//		* @return a list of fragment indices with the given fragment type and in the given document.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getFragmentIndicesFromDocument(const Poco::URI& uri, const std::string& interfaceName)
		//		{
		//			pimpl->getFragmentIndicesFromDocument(uri, interfaceName);
		//		}
		//
		//		/**
		//		* @param uri The URI of the document to get the fragments from.
		//		* @return a list of indices for fragments in the given document.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getFragmentIndicesFromDocument(const Poco::URI& uri)
		//		{
		//			pimpl->getFragmentIndicesFromDocument(uri);
		//		}    
		//
		//		/**
		//		* @param <F> The fragment extension class
		//		* @param uri The URI of the document to get the root fragment for.
		//		* @return the root fragment of the document with the given URI or null if no
		//		* root fragment is available for the given URI.
		//		* @throws XBRLException if more than one root fragment is found in the data store.
		//		*/
		//		//F getRootFragmentForDocument (const Poco::URI&  uri)
		//		//{
		//		//	pimpl->getRootFragmentForDocument(uri);
		//		//}
		//
		//		/**
		//		* @param <F> The fragment extension class
		//		* @return the list of root fragments of the documents in the store.
		//		* @throws XBRLException if more than one root fragment is found in the data store.
		//		*/
		//		//std::vector<F> getRootFragments()
		//		//{
		//		//	pimpl->getRootFragments();
		//		//}
		//
		//		/**
		//		* @param type The type of fragment to select by.
		//		* {@link Store#getXMLResources(String)} gives details on how the type
		//		* parameter is to be used.
		//		* @param <F> The fragment extension class
		//		* @return the list of root fragments of the documents in the store where the root fragments
		//		* are of the specified type.
		//		* @throws XBRLException
		//		*/
		///*		std::vector<F> getRootFragments(const std::string& type)
		//		{
		//			pimpl->getRootFragments(type);
		//		}*/    
		//
		//		/**
		//		* Close and then delete the data store.
		//		* This method must be synchronized.
		//		* @throws XBRLException if the data store cannot be deleted.
		//		*/
		//		void Delete()
		//		{
		//			pimpl->Delete();
		//		}    
		//
		/**
		* @param input The string that may be used to generate the id.
		* @return the ID to be used for storing XML resources in the data store.
		* One of these IDs is generated for each document in the data store and 
		* then a counter is appended to that ID to get uniqueness for each fragment
		* in that document.  These IDs are also used for a variety of other kinds
		* of XML resources stored in the data store.
		* @throws XBRLException
		*/
		std::string getId(const std::string& input)
		{
			return pimpl->getId(input);
		}
		//
		//		/**
		//		* @param encoding The code identifying the language that the name of the
		//		* language is expressed in.
		//		* @param code The code that identifies the language being named.
		//		* @return the Language fragment that specifies the name of the language
		//		* for the given code, expressed in the language identified by the encoding or 
		//		* null or if there is no matching language name 
		//		* in the data store.  The input parameters are converted to upper case before
		//		* processing.
		//		* @throws XBRLException if either parameter equals null.
		//		*/
		//		//Language getLanguage(const std::string& encoding, const std::string& code)
		//		//{
		//		//	pimpl->getLanguage(encoding, code);
		//		//}
		//
		//		/**
		//		* @param code The language code to get the language fragments for.  The code
		//		* is converted to upper case before processing.
		//		* @return the list of language fragments giving names for the language
		//		* associated with the specified language code.
		//		* @throws XBRLException if the language code is null.
		//		*/
		//		std::vector<Language> getLanguages(const std::string& code)
		//		{
		//			pimpl->getLanguages(code);
		//		}
		//
		//		/**
		//		* @param code The language code to get a map of language fragments for.  
		//		* @return a map of languages. Each fragment in the map is keyed by the 
		//		* fragment encoding and it is a fragment supplying a name in 
		//		* the encoding for the language identified by the code.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_map<std::string,Language> getLanguageMap(const std::string& code)
		//		{
		//			pimpl->getLanguageMap(code);
		//		}
		//
		//		/**
		//		* Sets the matcher for the store to use.  Care should be taken to ensure
		//		* that the one matcher is used for all documents in the store.
		//		* @param matcher the matcher to use to identify identical resources.
		//		* @throws XBRLException if the matcher is null;
		//		*/
		//		void setMatcher(const Matcher& matcher)
		//		{
		//			pimpl->setMatcher(matcher);
		//		}
		//
		//		/**
		//		* @return the matcher used by the store to identify identical resources.
		//		*/
		//		DefaultMatcherImpl getMatcher()
		//		{
		//			pimpl->getMatcher();
		//		}
		//
		//		/**
		//		* @param uri The URI of the referenced document.
		//		* @return a list of the URIs of the documents directly referencing
		//		* the specified document as targets of their XLinks (custom or otherwise).
		//		* @throws XBRLException if the list of referencing documents cannot be populated.
		//		*/
		//		std::vector<Poco::URI> getReferencingDocuments(const Poco::URI& uri)
		//		{
		//			pimpl->getReferencingDocuments(uri);
		//		}
		//
		//		/**
		//		* @param uri The URI of the referenced document.
		//		* @return a list of the fragments directly referencing
		//		* the specified document as targets of their XLinks (custom or otherwise).
		//		* The list is empty if there are no fragments with the specified URI as
		//		* the target URI of their link.
		//		* @throws XBRLException.
		//		*/
		//		std::vector<Fragment> getReferencingFragments(const Poco::URI& uri)
		//		{
		//			pimpl->getReferencingFragments(uri);
		//		}    
		//
		//		/**
		//		* Override this method in a data store implementation if the data store 
		//		* implementation supports XQuery (rather than XPath).
		//		* 
		//		* @param uri The URI of the referencing document.
		//		* @return a set of the documents directly referenced by this document.
		//		* @throws XBRLException if the set of referenced documents cannot be populated.
		//		*/
		//		std::unordered_set<Poco::URI> getReferencedDocuments(const Poco::URI& uri)
		//		{
		//			pimpl->getReferencedDocuments(uri);
		//		}    
		//
		//		/**
		//		* @param uris The set of URIs to restrict query results to coming from.
		//		* The set of URIs is set to the empty set if this parameter is null.
		//		*/
		//		void setFilteringURIs(std::unordered_set<Poco::URI> uris)
		//		{
		//			pimpl->setFilteringURIs(uris);
		//		}
		//
				/**
				* @return the set of URIs to filter query results.  Empty set
				* if no URIs are being used to filter query results.
				*/
				std::unordered_set<Poco::URI> getFilteringURIs()
				{
					pimpl->getFilteringURIs();
				}
		//
		//		/**
		//		* Specify that the data store is not to filter query results to only come
		//		* from a specified set of URIs.
		//		*/
		//		void clearFilteringURIs()
		//		{
		//			pimpl->clearFilteringURIs();
		//		}
		//
		//		/**
		//		* @return true if the data store is restricting query results to come 
		//		* from a specific set of documents and false otherwise.
		//		*/
				bool  isFilteringByURIs()
				{
					pimpl->isFilteringByURIs();
				}
		
				/**
				* Flush all database updates to the data store. 
				* @throws XBRLException if the sync operation fails.
				*/
				void sync()
				{
					pimpl->sync();
				}
		//
		//
		//		/**
		//		* @return a list of all of the root-level facts in the data store (those facts
		//		* that are children of the root element of an XBRL instance).  Returns an empty list 
		//		* if no facts are found.
		//		* @throws XBRLException
		//		* @see Store#getFacts()
		//		* @see Store#getAllFacts()
		//		*/
		//		std::vector<Fact&> getFacts()
		//		{
		//			pimpl->getFacts();
		//		}
		//
		//		/**
		//		* @return a set of the indices of all root-level facts (those facts
		//		* that are children of the root element of an XBRL instance).  Returns an empty set
		//		* if no such facts are found in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getFactIndices()
		//		{
		//			pimpl->getFactIndices();
		//		}
		//
		//		/**
		//		* @return a set of the indices of all facts (including those facts
		//		* that are children of tuples).  Returns an empty set
		//		* if no such facts are found in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getAllFactIndices()
		//		{
		//			pimpl->getAllFactIndices();
		//		}        
		//
		//		/**
		//		* @return a list of all of the items in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Item> getItems()
		//		{
		//			pimpl->getItems();
		//		}
		//
		//		/**
		//		* @return a list of all of the tuples in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::vector<std::tuple<std::string>> getTuples()
		//		{
		//			pimpl->getTuples();
		//		}
		//
		//		/**
		//		* @param targetNamespace The target namespace of the schema.
		//		* @return the root fragment of the schema or null 
		//		* if there are no schemas with the specified target namespace.
		//		* @throws XBRLException if there is more than one schema with the
		//		* given target namespace or if the target namespace is null.
		//		*/
		//		//Schema getSchema(const std::string& targetNamespace)
		//		//{
		//		//	pimpl->getSchema(targetNamespace);
		//		//}
		//
		//		/**
		//		* @param uri The URI of the document to get the facts from.
		//		* @return a list of all of the root-level facts in the specified document.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Fact&> getFacts (const Poco::URI&  uri)
		//		{
		//			pimpl->getFacts(uri);
		//		}
		//
		//		/**
		//		* @param uri The URI of the document to get the facts from.
		//		* @return a list of all of the facts (root level and those nested in tuples) 
		//		* in the document with the specified URI.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Fact&> getAllFacts (const Poco::URI&  uri)
		//		{
		//			pimpl->getAllFacts(uri);
		//		}
		//
		//		/**
		//		* @return a list of all of the facts (root level and those nested in tuples) 
		//		* in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Fact&> getAllFacts()
		//		{
		//			pimpl->getAllFacts();
		//		}
		//
		//		/**
		//		* @param uri The URI of the document to get the items from.
		//		* @return a list of all of the root-level items in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Item> getItems (const Poco::URI&  uri)
		//		{
		//			pimpl->getItems(uri);
		//		}
		//
		//		/**
		//		* @param uri The URI of the document to get the facts from.
		//		* @return a list of all of the root-level tuples in the specified document.
		//		* @throws XBRLException
		//		*/
		//		std::vector<std::tuple<std::string>> getTuples (const Poco::URI&  uri)
		//		{
		//			pimpl->getTuples(uri);
		//		}
		//
		//		/**
		//		* This implementation is not as strict as the XBRL 2.1 specification
		//		* requires but it is generally faster and delivers sensible results.
		//		* It will only fail if people use the same link role and arc role but
		//		* rely on arc or link element differences to distinguish networks.<br/><br/>
		//		* 
		//		* Implementation strategy is:<br/>
		//		* 1. Get all extended link elements with the given link role.<br/>
		//		* 2. Get all arcs with the given arc role.<br/>
		//		* 3. Get all resources at the source of the arcs.<br/>
		//		* 4. Return only those source resources that that are not target resources also.<br/>
		//		* 
		//		* @param linkRole the role on the extended links that contain the network arcs.
		//		* @param arcrole the arcrole on the arcs describing the network.
		//		* @return The list of fragments for each of the resources that is identified as a root
		//		* of the specified network (noting that a root resource is defined as a resource that is
		//		* at the source of one or more relationships in the network and that is not at the target 
		//		* of any relationships in the network).
		//		* @throws XBRLException
		//		*/
		//		//std::unordered_set<F> getNetworkRoots(const std::string& linkRole, const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworkRoots(linkRole, arcrole);
		//		//}
		//
		//		/**
		//		* @param namespace The namespace for the concept.
		//		* @param name The local name for the concept.
		//		* @return the concept fragment for the specified namespace and name.
		//		* @throws XBRLException if more than one matching concept is found in the data store
		//		* or if no matching concepts are found in the data store.
		//		*/
		//		//Concept getConcept(const std::string& Namespace, const std::string& name)
		//		//{
		//		//	pimpl->getConcept(Namespace, name);
		//		//}
		//
		//		/**
		//		* @param namespace The target namespace for the schema containing the global declaration.
		//		* @param name The local name for the global declaration.
		//		* @return the declaration fragment with the specified namespace and name.
		//		* @throws XBRLException if more than one matching declaration is found in the data store
		//		* or if no matching declarations are found in the data store.
		//		*/
		//		template <typename D>
		//		D getGlobalDeclaration(const std::string& Namespace, const std::string& name)
		//		{
		//			pimpl->getGlobalDeclaration(Namespace, name);
		//		}    
		//
		//		/**
		//		* @return a list of arcroleType fragments
		//		* @throws XBRLException
		//		*/
		//		std::vector<ArcroleType> getArcroleTypes()
		//		{
		//			pimpl->getArcroleTypes();
		//		}
		//
		//		/**
		//		* @return a list of arcroleType fragments with a given arcrole
		//		* @throws XBRLException
		//		*/
		//		std::vector<ArcroleType> getArcroleTypes(const std::string& uri)
		//		{
		//			pimpl->getArcroleTypes(uri);
		//		}
		//
		//		/**
		//		* @return a list of roleType fragments
		//		* @throws XBRLException
		//		*/
		//		std::vector<RoleType> getRoleTypes()
		//		{
		//			pimpl->getRoleTypes();
		//		}
		//
		//		/**
		//		* @return a list of RoleType fragments with a given role
		//		* @throws XBRLException
		//		*/
		//		std::vector<RoleType> getRoleTypes(const std::string& uri)
		//		{
		//			pimpl->getRoleTypes(uri);
		//		}    
		//
		//		/**
		//		* @return a hash map indexed by resource roles that are used in extended links in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::vector<std::string> getResourceRoles()
		//		{
		//			pimpl->getResourceRoles();
		//		}    
		//
		//		/**
		//		* @param starters The collection of URIs of the documents to use as 
		//		* starting points for analysis.
		//		* @return set of URIs for the documents in the data store
		//		* that are referenced, directly or indirectly, by any of the documents
		//		* identified by the supplied collection of document URIs.
		//		* @throws XBRLException if some of the referenced documents are not in
		//		* the data store.
		//		*/
		//		//std::unordered_set<Poco::URI> getMinimumDocumentSet(Collection<Poco::URI> starters)
		//		//{
		//		//	pimpl->getMinimumDocumentSet(starters);
		//		//}
		//
		//
		//		/**
		//		* This is just a convenience method.
		//		* @param uri The single document URI to use as 
		//		* starting points for analysis.
		//		* @return set of URIs for the documents in the data store
		//		* that are referenced, directly or indirectly, by the document
		//		* identified by the supplied URI.
		//		* @throws XBRLException if some of the referenced documents are not in
		//		* the data store.
		//		*/
		//		std::unordered_set<Poco::URI> getMinimumDocumentSet (const Poco::URI&  uri)
		//		{
		//			pimpl->getMinimumDocumentSet(uri);
		//		}
		//
		//		/**
		//		* @param linkrole The required linkrole value.
		//		* @return the list of extended links with the specified linkrole.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ExtendedLink> getExtendedLinks(const std::string& linkrole)
		//		{
		//			pimpl->getExtendedLinks(linkrole);
		//		}
		//
		//		/**
		//		* @param linkRole The link role to use to identify the extended links to retrieve.
		//		* @return the list of indices of extended links with the given link role value.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getExtendedLinkIndices(const std::string& linkRole)
		//		{
		//			pimpl->getExtendedLinkIndices(linkrole);
		//		}
		//
		//		/**
		//		* @param arcrole The arcrole to use to identify the arcs to retrieve.
		//		* @param linkIndex The index of the extended link containing the arcs to retrieve.
		//		* @return the list of indices of arcs matching the selection criteria.
		//		* @throws XBRLException
		//		* @return the list of arc fragments matching the selection criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Arc> getArcs (const Poco::URI&  arcrole, const std::string& linkIndex)
		//		{
		//			pimpl->getArcs(arcrole, linkIndex);
		//		}
		//
		//		/**
		//		* @param linkIndex The index of the extended link containing the arcs to retrieve.
		//		* @return the list of indices of arcs matching the selection criteria.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getArcIndicesWithLinkIndex(const std::string& linkIndex)
		//		{
		//			pimpl->getArcIndicesWithLinkIndex(linkIndex);
		//		}
		//
		//		/**
		//		* @param arcrole The arcrole to use to identify the arcs to retrieve.
		//		* @return the list of indices of arcs with a given arc role value.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getArcIndicesWithArcrole(const std::string& arcrole)
		//		{
		//			pimpl->getArcIndicesWithArcrole(arcrole);
		//		}    
		//
		//
		//		/**
		//		* @param linkIndex The index of the extended link containing the arcs to retrieve.
		//		* @return the list of indices of arcs matching the selection criteria.
		//		* @throws XBRLException
		//		* @return the list of arc fragments matching the selection criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<Arc> getArcs(const std::string& linkIndex)
		//		{
		//			pimpl->getArcs(linkIndex);
		//		}    
		//
		//
		//		/**
		//		* Get the networks that, at a minimum, contain the relationships
		//		* from each of the given fragments working back through ancestor relationships
		//		* as far as possible.  This is useful for building up networks of relationships
		//		* where you know the leaf nodes you want and need to get the necessary branches back to the
		//		* relevant heirarchy roots but do not want any branches leading to other leaf nodes.
		//		* The method only generates networks using active relationships (not overridden or
		//		* prohibited relationships).
		//		* @param fragments The fragments to analyse.
		//		* @param arcrole The required arcrole.
		//		* @return The networks containing the relationships.
		//		* @throws XBRLException
		//		*/
		//		//Networks getMinimalNetworksWithArcrole(std::unordered_set<Fragment> fragments, const std::string& arcrole)
		//		//{
		//		//	pimpl->getMinimalNetworksWithArcrole(fragments, arcrole);
		//		//}
		//
		//		/**
		//		* Convenience method for a single fragment.
		//		* @see Store#getMinimalNetworksWithArcrole(Set,String)
		//		*/
		//		//Networks getMinimalNetworksWithArcrole(const Fragment& fragment, const std::string& arcrole)
		//		//{
		//		//	pimpl->getMinimalNetworksWithArcrole(fragment, arcrole);
		//		//}
		//
		//		/**
		//		* @param fragments The set of target node fragments in the network.
		//		* @param linkRole The network link role value.
		//		* @param arcrole The network arcrole value.
		//		* @return the network built out from relevant roots to the supplied fragments.
		//		* Branches (and trees) with no nodes in them that correspond to the supplied 
		//		* fragments are not included in the returned network.
		//		* @throws XBRLException
		//		*/
		//		//Network getMinimalNetwork(std::unordered_set<Fragment> fragments, const std::string& linkRole, const std::string& arcrole)
		//		//{
		//		//	pimpl->getMinimalNetwork(fragments, linkRole, arcrole);
		//		//}
		//
		//		/**
		//		* This method is recursive.
		//		* @param fragment The fragment to use as the target for the relationships to be added to the networks.
		//		* @param network The network that is to be augmented.
		//		* @throws XBRLException
		//		*/
		//		void augmentNetworkForFragment(const Fragment& fragment, const Network& network)
		//		{
		//			pimpl->augmentNetworkForFragment(fragment, network);
		//		}
		//
		//		/**
		//		* This method is recursive.
		//		* @param fragment The fragment to use as the target for the relationships to be added to the networks.
		//		* @param arcrole The arcrole for the networks to augment.
		//		* @param networks The networks to augment.
		//		* @throws XBRLException
		//		*/
		//		void augmentNetworksForFragment(const Fragment& fragment, const std::string& arcrole, Networks networks)
		//		{
		//			pimpl->augmentNetworksForFragment(fragment, arcrole, networks);
		//		}
		//
		//		/**
		//		* @return a list of arc roles that are used in extended links in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getArcroles()
		//		{
		//			pimpl->getArcroles();
		//		}
		//
		//		/**
		//		* @param linkRole the specified linkrole to use in selecting arcroles.
		//		* @return a list of arc roles that are used in extended links 
		//		* with the given link role.
		//		* @throws XBRLException if any of the arcroles is not a valid URI.
		//		*/
		//		std::unordered_set<std::string>  getArcroles(const std::string& linkRole)
		//		{
		//			pimpl->getArcroles(linkRole);
		//		}    
		//
		//		/**
		//		* @return a hash map indexed by link roles that are used in extended links in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getLinkRoles()
		//		{
		//			pimpl->getLinkRoles();
		//		}
		//
		//		/**
		//		* @param arcrole The arcrole determining the extended links that are to be examined for
		//		* linkroles that are used on links containing arcs with the required arcrole.
		//		* @return a hashmap of link roles, with one entry for each link role that is used on an
		//		* extended link that contains an arc with the required arcrole.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<std::string>  getLinkRoles(const std::string& arcrole)
		//		{
		//			pimpl->getLinkRoles(arcrole);
		//		}    
		//
		//		/**
		//		* Implemented by {@link Store#getNetworksFrom(const std::string&,std::string,String)}.
		//		* @param sourceIndex The source fragment index
		//		* @param arcrole The XLink arcrole
		//		* @return a set of networks comprising the relationships
		//		* from the source fragment with the given arcrole.
		//		* @throws XBRLException
		//		*/
		//		//Networks getNetworksFrom(const std::string& sourceIndex, const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworksFrom(sourceIndex, arcrole);
		//		//}
		//
		//		/**
		//		* Implemented by {@link Store#getNetworksFrom(const std::string&,std::string,String)}.
		//		* @param sourceIndex The source fragment index
		//		* @return a set of networks comprising the relationships
		//		* from the source fragment.
		//		* @throws XBRLException
		//		*/
		///*		Networks getNetworksFrom(const std::string& sourceIndex)
		//		{
		//			pimpl->getNetworksFrom(sourceIndex);
		//		}  */  
		//
		//		/**
		//		* @param sourceIndex The source fragment index
		//		* @param linkRole The XLink link role
		//		* @param arcrole The XLink arcrole
		//		* @return a set of networks comprising the relationships
		//		* from the source fragment with the given link role and arcrole.
		//		* @throws XBRLException
		//		*/
		///*		Networks getNetworksFrom(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
		//		{
		//			pimpl->getNetworksFrom(sourceIndex, linkRole, arcrole);
		//		}   */ 
		//
		//		/**
		//		* If using persisted relationships then the set of relationships used to 
		//		* generate the results can be modified by appropriate choice of 
		//		* @link org.xbrlapi.networks.Analyser implementation.  Otherwise only active
		//		* relationships are used (those that are not prohibited or over-ridden).
		//		* @param targetIndex The target fragment index
		//		* @param linkRole The XLink link role or null if networks for 
		//		* all link roles are sought
		//		* @param arcrole The XLink arcrole  or null if networks for 
		//		* all arcroles are sought
		//		* @return a set of networks comprising the relationships
		//		* to the target fragment meeting the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		//Networks getNetworksTo(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworksTo(targetIndex, linkRole, arcrole);
		//		//}
		//
		//		/**
		//		* Implemented by {@link Store#getNetworksTo(const std::string&,std::string,String)}.
		//		* @param targetIndex The target fragment index
		//		* @param arcrole The XLink arcrole
		//		* @return a set of networks comprising the relationships
		//		* to the target fragment with the given arcrole.
		//		* @throws XBRLException
		//		*/
		//		//Networks getNetworksTo(const std::string& targetIndex, const std::string& arcrole)
		//		//{
		//		//	pimpl->getNetworksTo(targetIndex, arcrole);
		//		//}
		//
		//		/**
		//		* Implemented by {@link Store#getNetworksTo(const std::string&,std::string,String)}.
		//		* @param targetIndex The target fragment index
		//		* @return a set of networks comprising the relationships
		//		* to the target fragment.
		//		* @throws XBRLException
		//		*/
		///*		Networks getNetworksTo(const std::string& targetIndex)
		//		{
		//			pimpl->getNetworksTo(targetIndex);
		//		}  */  
		//
		//		/**
		//		* If using persisted relationships then the set of relationships used to 
		//		* generate the results can be modified by appropriate choice of 
		//		* @link org.xbrlapi.networks.Analyser implementation.  Otherwise only active
		//		* relationships are used (those that are not prohibited or over-ridden).
		//		* @param sourceIndex The source fragment index
		//		* @param linkRole The XLink link role
		//		* @param arcrole The XLink arcrole
		//		* @return a sorted set of active relationships from the 
		//		* source fragment with the given link role and arcrole that
		//		* have been persisted.  The relationships are ordered by the order
		//		* attributes on the arcs expressing the relationships.
		//		* @throws XBRLException
		//		*/
		//		std::set<Relationship> getRelationshipsFrom(const std::string& sourceIndex, const std::string& linkRole, const std::string& arcrole)
		//		{
		//			pimpl->getRelationshipsFrom(sourceIndex, linkRole, arcrole);
		//		}
		//
		//		/**
		//		* @param document The document URI.
		//		* @return true if the store contains persisted relationships
		//		* for all of the relationships expressed by the arcs in the 
		//		* specified document and false otherwise.
		//		* @throws XBRLException
		//		*/
		//		bool  hasAllRelationships (const Poco::URI&  document)
		//		{
		//			pimpl->hasAllRelationships(document);
		//		}    
		//
		//		/**
		//		* @param targetIndex The target fragment index
		//		* @param linkRole The XLink link role
		//		* @param arcrole The XLink arcrole
		//		* @return a sorted set of active relationships to the 
		//		* target fragment with the given link role and arcrole.
		//		* The relationships are ordered by the order attribute on 
		//		* the arcs expressing them.
		//		* The linkRole and the arcrole are ignored as selection criteria
		//		* if they are null.
		//		* @throws XBRLException
		//		*/
		//		std::set<Relationship> getRelationshipsTo(const std::string& targetIndex, const std::string& linkRole, const std::string& arcrole)
		//		{
		//			pimpl->getRelationshipsTo(targetIndex, linkRole, arcrole);
		//		}    
		//
		//		/**
		//		* If using persisted relationships then the set of relationships used to 
		//		* generate the results can be modified by appropriate choice of 
		//		* @link org.xbrlapi.networks.Analyser implementation.  Otherwise only active
		//		* relationships are used (those that are not prohibited or over-ridden).
		//		* @param fragment the index of the fragment that we are getting labels for
		//		* @param linkRole The required link role or null if not used.
		//		* @param resourceRole The required resource role or null if not used.
		//		* @param language The required language code or null if not used.
		//		* @return the set of labels matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<LabelResource> getLabels(const std::string& fragment, const std::string& linkRole, const std::string& resourceRole, const std::string& language)
		//		{
		//			pimpl->getLabels(fragment, linkRole, resourceRole, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getLabels(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting labels for
		//		* @param resourceRole The required resource role or null if not used.
		//		* @param language The required language code or null if not used.
		//		* @return the set of labels matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<LabelResource> getLabels(const std::string& fragment, const std::string& resourceRole, const std::string& language)
		//		{
		//			pimpl->getLabels(fragment, resourceRole, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getLabels(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting labels for
		//		* @param language The required language code or null if not used.
		//		* @return the set of labels matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<LabelResource> getLabelsWithLanguage(const std::string& fragment, const std::string& language)
		//		{
		//			pimpl->getLabelsWithLanguage(fragment, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getLabels(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting labels for
		//		* @return the set of labels matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<LabelResource> getLabels(const std::string& fragment)
		//		{
		//			pimpl->getLabels(fragment);
		//		}    
		//
		//		/**
		//		* Implemented by {@link Store#getLabels(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting labels for
		//		* @param resourceRole The required resource role or null if not used.
		//		* @return the set of labels matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<LabelResource> getLabelsWithResourceRole(const std::string& fragment, const std::string& resourceRole)
		//		{
		//			pimpl->getLabelsWithResourceRole(fragment, resourceRole);
		//		}
		//
		//		/**
		//		* If using persisted relationships then the set of relationships used to 
		//		* generate the results can be modified by appropriate choice of 
		//		* @link org.xbrlapi.networks.Analyser implementation.  Otherwise only active
		//		* relationships are used (those that are not prohibited or over-ridden).
		//		* @param fragment the index of the fragment that we are getting references for
		//		* @param linkRole The required link role or null if not used.
		//		* @param resourceRole The required resource role or null if not used.
		//		* @param language The required language code or null if not used.
		//		* @return the set of references matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ReferenceResource> getReferences(const std::string& fragment, const std::string& linkRole, const std::string& resourceRole, const std::string& language)
		//		{
		//			pimpl->getReferences(fragment, linkRole, resourceRole, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getReferences(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting references for
		//		* @param resourceRole The required resource role or null if not used.
		//		* @param language The required language code or null if not used.
		//		* @return the set of references matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ReferenceResource> getReferences(const std::string& fragment, const std::string& resourceRole, const std::string& language)
		//		{
		//			pimpl->getReferences(fragment, resourceRole, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getReferences(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting references for
		//		* @param language The required language code or null if not used.
		//		* @return the set of references matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ReferenceResource> getReferencesWithLanguage(const std::string& fragment, const std::string& language)
		//		{
		//			pimpl->getReferencesWithLanguage(fragment, language);
		//		}
		//
		//		/**
		//		* Implemented by {@link Store#getReferences(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting references for
		//		* @return the set of references matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ReferenceResource> getReferences(const std::string& fragment)
		//		{
		//			pimpl->getReferences(fragment);
		//		}    
		//
		//		/**
		//		* Implemented by {@link Store#getReferences(const std::string&,std::string,std::string,String)}.
		//		* @param fragment the index of the fragment that we are getting references for
		//		* @param resourceRole The required resource role or null if not used.
		//		* @return the set of references matching the specified criteria.
		//		* @throws XBRLException
		//		*/
		//		std::vector<ReferenceResource> getReferencesWithResourceRole(const std::string& fragment, const std::string& resourceRole)
		//		{
		//			pimpl->(fragment, resourceRole);
		//		}    
		//
		//		/**
		//		* @return a list of the URIs of documents that are discoverable given the 
		//		* content of the data store but that are not themselves in the data store.
		//		* @throws XBRLException
		//		*/
		//		std::unordered_set<Poco::URI> getMissingDocumentURIs()
		//		{
		//			pimpl->getReferencesWithResourceRole();
		//		}
		//
				/**
				* Loaders need to call this method to indicate that they are going to take 
				* responsibility for loading the document.
				* This can be used to prevent the same document from being loaded by several
				* loaders operating in parallel.
				* @param loader The loader claiming loading rights.
				* @param document The URI of the document that a loader is about
				* to start loading.
				* @return false if the document is already claimed by a different loader and true otherwise.  
				* Only start loading if this function returns true.
				* @throws XBRLException
				*/
				bool  requestLoadingRightsFor(const Poco::URI& document, const Loader& loader)
				{
					return pimpl->requestLoadingRightsFor(document, loader);
				}
		
				/**
				* Loaders need to call this method to indicate that they are recinding 
				* responsibility for loading the document.
				* This can be used to prevent the same document from being loaded by several
				* loaders operating in parallel.
				* @param loader The loader recinding loading rights.
				* @param document The URI of the document whose loading rights are being recinded.
				* @link Store#loadingAboutToStart(URI)
				*/
				void recindLoadingRightsFor(const Poco::URI& document, const Loader& loader)
				{
					pimpl->recindLoadingRightsFor(document, loader);
				}
		
				/**
				* @param loader The loader that has started to use
				* this store for data loading.
				*/
				void startLoading()
				{
					pimpl->startLoading();
				}
		
		//		/**
		//		* @param loader The loader that has stopped using
		//		* this store for data loading.
		//		*/
		//		void stopLoading(const Loader& loader)
		//		{
		//			pimpl->stopLoading(loader);
		//		}
		//
		//		/**
		//		* @return true if the store is currently being 
		//		* used by any loader for loading data.
		//		*/
		//		bool  isLoading()
		//		{
		//			pimpl->isLoading();
		//		}    
		//
		//		/**
		//		* @param namespace The target namespace of the schema with the desired content.
		//		* @param name The name given to the schema component.
		//		* @return The Schema content fragment that contains the declaration of the desired
		//		* XML Schema component or null if no such fragment is in the data store.
		//		* @throws XBRLException
		//		*/
		//		//F getSchemaContent(const std::string& Namespace, const std::string& name)
		//		//{
		//		//	pimpl->getSchemaContent(Namespace, name);
		//		//}
		//
		//		/**
		//		* @param childClass The class of child fragment.
		//		*  @param parentIndex The index of the parent fragment.
		//		* @return a list of fragments in the given fragment class
		//		* and with the given parent fragment.  The list is empty if there
		//		* are no child fragments.
		//		* @throws XBRLException
		//		*/
		//		//std::vector<F> getChildFragments(F childClass, const std::string& parentIndex)
		//		//{
		//		//	pimpl->getChildFragments(childClass, parentIndex);
		//		//}
		//
		//		/**
		//		* @param namespace The namespace of the facts to select.
		//		* @param localname The local name of the facts to select.
		//		* @return the list of facts with the given namespace and local name in the data store.
		//		* @throws XBRLException if either parameter is null.
		//		*/
		//		std::vector<Fact&> getFacts(const std::string& Namespace, const std::string& localname)
		//		{
		//			pimpl->getFacts(Namespace, localname);
		//		}    
		//
		//		/**
		//		* @param concept The concept to get the facts for.
		//		* @return the list of facts in the data store 
		//		* reporting values for the specified concept.
		//		* @throws XBRLException if the parameter is null.
		//		*/
		//		std::vector<Fact&> getFacts(const Concept& concept)
		//		{
		//			pimpl->getFacts(concept);
		//		}    
	} ;
}
