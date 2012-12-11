#include "Stdafx.h"
#include "BaseStoreImpl.h"
#include "StubImpl.h"
#include "LoaderImpl.h"

///**
// * Abstract base implementation of the data store
// * providing all methods of the store interface that
// * do not depend on the nature of the underlying data store
// * implementation.
// * 
// * @author Geoffrey Shuetrim (geoff@galexy.net)
// */

namespace xbrlcapi
{
	//    /**
	//     * @see Store#getNumberOfXMLResources(Class)
	//     */
	//    public long getNumberOfXMLResources(Class<?> specifiedClass)
	//            {
	//         std::string query = "for $root in #roots# where $root/@type='" + specifiedClass.getName() + "' return $root";
	//        return this.queryCount(query);
	//    }

	BaseStoreImpl::BaseStoreImpl() {}

	BaseStoreImpl& BaseStoreImpl::operator=(BaseStoreImpl&& rhs)
	{
		loadingStatus = std::move(rhs.loadingStatus);
		matcher = std::move(rhs.matcher);
		return *this;
	}

	BaseStoreImpl::BaseStoreImpl(BaseStoreImpl&& rhs) : matcher(rhs.matcher), loadingStatus(rhs.loadingStatus)
	{}
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#setMatcher(Matcher)
	//     */
	//    public synchronized void setMatcher(Matcher matcher) {
	//        if (matcher == null) throw new XBRLException("The matcher cannot be null");
	//        this.matcher = matcher;
	//    }
	//
	/**
	* @see org.xbrlapi.data.Store#getMatcher()
	*/
	DefaultMatcherImpl BaseStoreImpl::getMatcher()
	{
		return matcher;
	}    
	    
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#setNamespaceBinding(String,String)
	//     */
	//    public synchronized void setNamespaceBinding( std::string namespace,  std::string prefix) {
	//        this.namespaceBindings.put(prefix, namespace);
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#removeNamespaceBinding(String)
	//     */
	//    public synchronized void removeNamespaceBinding( std::string prefix) {
	//        this.namespaceBindings.remove(prefix);
	//    }
	//
	//    /**
	//     * Set of URIs to use when filtering query results to only get matches
	//     * to a specific set of documents.
	//     */

	//
	//    /**
	//     * @see org.xbrlapi.data.Store#setFilteringURIs(Set)
	//     */
	//    public synchronized void setFilteringURIs(Set<URI> uris) {
	//        if (uris == null) this.uris = new HashSet<URI>();
	//        else this.uris = uris;
	//    }
	//    
	    /**
	     * @see org.xbrlapi.data.Store#getFilteringURIs()
	     */
	    std::unordered_set<Poco::URI> BaseStoreImpl::getFilteringURIs() 
		{
	        return uris;
	    }    
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#clearFilteringURIs()
	//     */
	//    public void clearFilteringURIs() {
	//        this.uris = new HashSet<URI>();
	//    }
	
	    /**
	     * @see org.xbrlapi.data.Store#isFilteringByURIs()
	     */
	    //synchronized 
		bool BaseStoreImpl::isFilteringByURIs() 
		{
	        return (! uris.empty());
	    }
	    
	    /**
	     * @return an X Query clause that restricts the set of fragments returned by 
	     * a query to those from a specific set of URIs.
	     */
	//synchronized  
	std::string BaseStoreImpl::getURIFilteringPredicate() 
	{
	
	        if (isFilteringByURIs()) {
	             std::string uriFilter = "0";
	            for (const Poco::URI& uri : getFilteringURIs()) 
				{
					uriFilter = uriFilter + std::string(" or @uri='") + uri.toString() + std::string("'");
	            }
	            uriFilter = "[" + uriFilter + "]";
	   //         logger.debug(uriFilter);
	            return uriFilter;
	        }
	        return "";
	    }
	//
	//	/**
	//	 * Does nothing.
	//	 * @see Store#close()
	//	 */
	//	public void close() {
	//	    ;
	//	}
	//	
	//    /**
	//     * @see org.xbrlapi.data.Store#persistLoaderState(Map)
	//     */
	//    public synchronized void persistLoaderState(Map<URI,String> documents) {
	//        try {
	//            for (URI uri: documents.keySet()) {
	//                persistStub(uri,documents.get(uri));
	//            }
	//        } catch (XBRLException e) {
	//            throw new XBRLException("The loader state could not be stored.",e);
	//        }
	//    }
	//
	//    /**
	//     * @see Store#persistStub(URI,String)
	//     */
	//    public void persistStub(URI uri,  std::string reason) {
	//
	//        try {
	//            deleteDocument(uri);
	//        } catch (XBRLException e) {
	//            reason += " (NB: Failed to delete the document from the data store. " + e.getMessage()+")";
	//        }
	//
	//         std::string documentId = getId(uri.toString() + "_stub");
	//        Stub stub = new StubImpl(documentId,uri,reason);
	//        persist(stub);
	//    }
	//    
	//    /**
	//     * Default implementation does nothing.
	//     * @see Store#sync()
	//     */
	//    public synchronized void sync() {
	//    }
	//
	    /**
	     * This implementation generates the an ID for a document being stored
	     * with a prefix that is a random string of characters 
	     * including a-z, A-Z and 0-9.
	     * If, by chance, the random string has already been 
	     * used for another document in the data store, then 
	     * another random string is generated and this repeats until
	     * the random string is unique in the data store.
	     * @see Store#getId(String)
	     */    
	    std::string BaseStoreImpl::getId(const std::string& input) 
		{
	        //
	        //// The document is not in the data store so generate a new document ID.
	        // std::string randomString = random();
	        //while (this.hasXMLResource(randomString + "_1") || this.hasXMLResource(randomString)) {
	        //    randomString = random();
	        //}
	        //return randomString;
		return false;
	    }
	//    
	//    /**
	//     * Generate a random string.
	//     * @return a randomly generated string consisting of digits and
	//     * a-z or A-Z only.
	//     */
	//    private  std::string random() {
	//         std::string random = "";
	//        for (int i=0; i<6; i++) {
	//            int code = (new Long(Math.round(Math.random()*61))).intValue();
	//            code = code + 48;
	//            if (code < 58) {
	//                random = random + new Character((char)code).toString();
	//            } else {
	//                code = code + 7;
	//                if (code < 91) {
	//                    random = random + new Character((char)code).toString();
	//                } else {
	//                    code = code + 6;
	//                    random = random + new Character((char)code).toString();
	//                }
	//            }
	//        }
	//        return random;
	//    }
	//    
	//    /**
	//     * @param bs The given byte array.
	//     * @return a hex string representation of the given byte array.
	//     */
	//    private  std::string bytesToHex(byte[] bs) {
	//        StringBuffer ret = new StringBuffer(bs.length);
	//        for (int i = 0; i < bs.length; i++) {
	//             std::string hex = Integer.toHexString(0x0100 + (bs[i] & 0x00FF)).substring(1);
	//            ret.append((hex.length() < 2 ? "0" : "") + hex);
	//        }
	//        return ret.toString();
	//    }    
	//
	//    /**
	//     * @see Store#serialize(Element, OutputStream)
	//     */
	//    public void serialize(Element what, OutputStream destination) {
	//
	//		try {
	//			XMLDOMSerializer.serialize(what, destination);
	///*		    LSSerializer writer = domImplementation.createLSSerializer();
	//		    writer.getDomConfig().setParameter("format-pretty-print",true);
	//		    LSOutput output = domImplementation.createLSOutput();
	//		    output.setByteStream(destination);
	//		    writer.write(what,output);
	//*/
	//		} catch (Exception e) {
	//			throw new XBRLException("The XML subtree could not be serialised.", e);
	//        }
	//    }
	//    
	//
	//    
	//    
	//    
	//    /**
	//     * @see Store#serialize(Element)
	//     */
	//    public  std::string serialize(Element what) {
	//		ByteArrayOutputStream baos = new ByteArrayOutputStream();
	//		serialize(what, baos);
	//		return baos.toString();
	//    }
	//    
	//    
	//    /**
	//     * Algorithm:
	//     * <ol>
	//     *  <li>Check if the matcher indicate that the URI has matching URIs.</li>
	//     *  <li>If the URI has matching URIs:
	//     *   <li>If the URI is the one used for the document in the data store:
	//     *    <li>Delete the URI from the matcher, getting the new matching URI back as
	//     *    a result of the deletion operation and update the document fragments to use 
	//     *    the new matching URI instead of the deleted URI.</li>
	//     *   </li>
	//     *   <li>Otherwise, just delete the URI from the matcher and we are done.</li>
	//     *  </li>
	//     *  <li>Otherwise, the URI does not have matching URIs so just delete the
	//     *  URI from the matcher and delete the relevant fragments from the data store.</li>
	//     * </ol>
	//	 * @see org.xbrlapi.data.Store#deleteDocument(URI)
	//     */
	//    public void deleteDocument(URI uri) {
	//
	//        logger.debug("Deleting " + uri + " from the data store.");
	//        URI matchURI = getMatcher().getMatch(uri);
	//        URI newMatchURI = getMatcher().delete(uri);
	//        
	//         std::string query = "for $fragment in #roots# where $fragment/@uri='"+ matchURI + "' return $fragment";
	//
	//        if (newMatchURI == null) {
	//            Set<String> indices = this.queryForIndices(query);
	//            for ( std::string index: indices) {
	//                remove(index);
	//            }
	//            return;
	//        } else if (matchURI.equals(newMatchURI)) {
	//            return;
	//        }
	//
	//        Set<String> indices = this.queryForIndices(query);
	//        for ( std::string index: indices) {
	//            Fragment fragment = this.<Fragment>getXMLResource(index);
	//            fragment.setURI(newMatchURI);
	//            persist(fragment);
	//        }
	//
	//        // Eliminate any document stub
	//        std::vector<Stub> stubs = this.getStubs(uri);
	//        for (Stub stub: stubs) {
	//            this.removeStub(stub);
	//        }
	//        
	//    }
	//
	//    /**
	//     * @see Store#deleteRelatedDocuments(URI)
	//     */
	//    public void deleteRelatedDocuments(URI uri) {
	//        
	//        HashMap<URI,bool> documentsToDelete = new HashMap<URI,bool>();    	
	//        
	//        deleteDocument(uri);
	//    	
	//        std::vector<Fragment> fragments = this.<Fragment>queryForXMLResources("#roots#[@targetDocumentURI='"+ uri + "']");
	//    	
	//        for (const Fragment& fragment: fragments) {
	//            if (! documentsToDelete.containsKey(fragment.getURI())) {
	//                documentsToDelete.put(fragment.getURI(),new bool(true));
	//            }
	//    		Iterator<URI> iterator = documentsToDelete.keySet().iterator();
	//    		while (iterator.hasNext()) {
	//    			URI myURI = iterator.next();
	//    			if (documentsToDelete.get(myURI)) {
	//        			deleteRelatedDocuments(myURI);
	//        			documentsToDelete.put(myURI,new bool(false));
	//    			}
	//    		}
	//    	}
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getReferencingDocuments(URI)
	//     */
	//    public std::vector<URI> getReferencingDocuments(URI uri) {
	//         std::string query = "for $root in #roots#[@targetDocumentURI='"+ uri + "'] return string($root/@uri)";
	//        Set<String> strings = queryForStrings(query);
	//
	//        std::vector<URI> uris = new Vector<URI>();
	//        for ( std::string string: strings) {
	//            try {
	//                uris.add(new URI(string));
	//            } catch (URISyntaxException e) {
	//                throw new XBRLException(string + " is an invalid URI.",e);
	//            }
	//        }
	//
	//        return uris;
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getReferencingFragments(URI)
	//     */
	//    public std::vector<Fragment> getReferencingFragments(URI uri) {
	//         std::string query = "for $root in #roots#[@targetDocumentURI='"+ uri + "'] return $root";
	//        std::vector<Fragment> fragments = this.<Fragment>queryForXMLResources(query);
	//        return fragments;
	//    }    
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getReferencedDocuments(URI)
	//     */
	//    public Set<URI> getReferencedDocuments(URI uri) {
	//        Set<URI> result = new HashSet<URI>(); 
	//         std::string query = "for $root in #roots#[@uri='" + uri + "' and @targetDocumentURI] return concat('',$root/@targetDocumentURI)";
	//        for ( std::string targetURI: queryForStrings(query)) {
	//            result.add(URI.create(targetURI));
	//        }
	//        return result;
	//    }
	//
	//    /**
	//     * @see Store#serialize(Element, File)
	//	 */
	//	public void serialize(Element what, File destination) {
	//		
	//		File parentFile = destination.getParentFile();
	//		
	//		if (parentFile != null) parentFile.mkdirs();
	//
	//		try {
	//			FileOutputStream fileOutputStream = new FileOutputStream(destination.toString());
	//			serialize(what, fileOutputStream);
	//		} catch (FileNotFoundException e) {
	//			throw new XBRLException("The file to be written to cannot be found.", e);
	//		}
	//		
	//	}
	//    
	//
	//	
	//    /**
	//     * @see Store#getDocumentURIs()
	//     */
	//    public Set<URI> getDocumentURIs() {
	//
	//        Set<URI> uris = new HashSet<URI>();
	//        
	//        Set<String> uriStrings =  this.queryForStrings("for $root in #roots#[@parentIndex=''] return string($root/@uri)");
	//
	//        try {
	//            for ( std::string uriString: uriStrings) {
	//                uris.add(new URI(uriString));
	//            }
	//        } catch (URISyntaxException e) {
	//            throw new XBRLException("A document URI has invalid syntax.",e);
	//        }
	//        return uris;
	//    }
	//

	//
	//    
	//    /**
	//     * @see Store#getDocumentAsDOM(URI)
	//     */
	//    public Element getDocumentAsDOM(URI uri) {
	//    	return getSubtree(this.getRootFragmentForDocument(uri));
	//    }
	//	
	//	/**
	//     * Get a single document in the store as a DOM including annotations.
	//     * @param uri The string representation of the URI of the 
	//     * document to be retrieved.
	//     * @return an annotated DOM Document containing the XML representation of the
	//     * file at the specified URI.  Returns null if the store does not
	//     * contain a document with the given URI.
	//     * @throws XBRLException if more or less than one document is found in the store matching 
	//     * the supplied URI.
	//     */
	//    private Element getAnnotatedDocumentAsDOM(URI uri) {
	//        URI matchURI = getMatcher().getMatch(uri);
	//        std::vector<Fragment> fragments = queryForXMLResources("#roots#[@uri='" + matchURI + "' and @parentIndex='']");
	//        if (fragments.size() > 1) throw new XBRLException("More than one document was found in the data store.");
	//        if (fragments.size() == 0) throw new XBRLException("No documents were found in the data store.");
	//        Fragment fragment = fragments.get(0);
	//        Element document = this.getAnnotatedSubtree(fragment);
	//        document.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index",fragment.getIndex());
	//        return document;
	//    }
	//    
	//	/**
	//	 * @see Store#getSubtree(Fragment)
	//	 */
	//	public Element getSubtree(const Fragment& f) {
	//
	//	    if (f == null) {
	//	        throw new XBRLException("The fragment must not be null.");
	//	    }
	//	    
	//		// Make sure that the DOM is initialised.
	//		if (storeDOM == null) {
	//			storeDOM = (new XMLDOMBuilder()).newDocument();
	//		}
	//
	//		// Get the DOM representation of the fragment
	//		Element d = null;
	//		try {
	//		    d = (Element) storeDOM.importNode(f.getDataRootElement(), true);
	//		} catch (Exception e) {
	//		    e.printStackTrace();
	//		    throw new XBRLException("The data could not be plugged into the DOM for fragment " + f.getIndex(),e);
	//		}
	//		    
	//		// Get the child fragment IDs
	//		List<Fragment> unorderedFragments = this.queryForXMLResources("#roots#[@parentIndex='" + f.getIndex() + "']");
	//		
	//		// With no children, just return the fragment
	//		if (unorderedFragments.size() == 0) {
	//			return d;
	//		}
	//
	//		// Sort the child fragments into insertion order
	//		TreeSet<Fragment> sortedFragments = new TreeSet<Fragment>(new FragmentComparator());
	//    	for (const Fragment& fragment: unorderedFragments) {
	//    		sortedFragments.add(fragment);
	//    	}
	//    	
	//    	// Iterate sorted child fragments in insertion order, inserting them
	//    	for (const Fragment& childFragment: sortedFragments) {
	//
	//    		// Get XML DOM for child fragment
	//    		Element child = getSubtree(childFragment);
	//
	//    		// Get parent element of child fragment in current fragment
	//    		Element parentElement = childFragment.getParentElement(d);
	//
	//            // Do the fragment insertion
	//    		parentElement.appendChild(child);
	//
	//    	}
	//		return d;
	//	}
	//	
	//    /**
	//     * Get the following sibling of this fragment's root in the parent fragment's data.
	//     * @param parentElement The parent element in the parent fragment's data.
	//     * @param precedingSiblings The number of sibling elements preceding the element of interest.
	//     * @return the following sibling of this fragment's root (or null if there is no preceding sibling).
	//     */
	//    protected Element getFollowingSibling(Element parentElement, int precedingSiblings) {
	//    	
	//    	// Traverse the parent data DOM to find the relevant child node
	//		int siblingCount = 0;
	//		NodeList children = parentElement.getChildNodes();
	//		for (int i=0; i<children.getLength(); i++) {
	//			Node child = children.item(i);
	//			if (child.getNodeType() == Node.ELEMENT_NODE) {
	//				siblingCount++;  // We have found a sibling element
	//				if (siblingCount > precedingSiblings) return (Element) child;
	//			}
	//		}
	//		return null;
	//    	
	//    }	
	//
	//	/**
	//	 * Returns the root element of the annotated subtree starting with the
	//	 * fragment with the specified index.  All subtrees for a given store
	//	 * instance are produced from the one XML DOM and so can be appended
	//	 * to eachother as required.
	//	 * @param f The fragment at the root of the subtree.
	//	 * @return the root element of the subtree headed by the fragment
	//	 * with the specified index.
	//	 * @throws XBRLException if the subtree cannot be constructed.
	//	 */
	//	private Element getAnnotatedSubtree(const Fragment& f) {
	//		
	//    	//logger.debug((new Date()) + ":Getting fragment " + f.getIndex());
	//    	
	//		// Make sure that the DOM is initialised.
	//		if (storeDOM == null) {
	//			storeDOM = (new XMLDOMBuilder()).newDocument();
	//		}
	//
	//		// Get the DOM representation of the fragment
	//		Element d = (Element) storeDOM.importNode(f.getDataRootElement(), true);
	//		
	//		// Get the child fragment IDs
	//		List<Fragment> fs = this.queryForXMLResources("/"+ Constants.XBRLAPIPrefix+ ":" + "fragment[@parentIndex='" + f.getIndex() + "']");
	//		
	//		// With no children, just return the fragment
	//		if (fs.size() == 0) {
	//			return d;
	//		}
	//
	//		// Sort the child fragments into insertion order
	//		TreeSet<Fragment> fragments = new TreeSet<Fragment>(new FragmentComparator());
	//		for (int i=0; i<fs.size(); i++) {
	//    		fragments.add(fs.get(i));
	//    	}
	//    	
	//    	// Iterate child fragments in insertion order, inserting them
	//    	Iterator<Fragment> iterator = fragments.iterator();
	//    	while (iterator.hasNext()) {
	//    		
	//    		// Get child fragment
	//    		Fragment childFragment = iterator.next();
	//
	//    		// Get XML DOM for child fragment using recursion
	//    		Element child = getAnnotatedSubtree(childFragment);
	//	    	child.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index",childFragment.getIndex());
	//
	//    		// Get parent element of child fragment in current fragment
	//    		Element parentElement = childFragment.getParentElement(d);
	//
	//    		// Do the fragment insertion
	//            parentElement.appendChild(child);
	//    		
	//    	}
	//		return d;
	//	}
	//	
	//	
	//    /**
	//     * @see Store#getStoreAsDOM()
	//     */
	//    public Document getStoreAsDOM() {
	//
	//		if (storeDOM == null) {
	//			storeDOM = (new XMLDOMBuilder()).newDocument();
	//		}
	//		
	//    	Element root = storeDOM.createElementNS(Constants.XBRLAPINamespace.toString(),Constants.XBRLAPIPrefix + ":dts");
	//		
	//		Set<URI> uris = getDocumentURIs();
	//		for (URI uri: uris) {
	//			Element e = getDocumentAsDOM(uri);
	//			root.appendChild(e);			
	//		}
	//    	storeDOM.appendChild(root);
	//    	return storeDOM;
	//    }
	//		
	//	/**
	//     * @see Store#getCompositeDocument()
	//     */
	//    public Document getCompositeDocument() {
	//    	
	//		if (storeDOM == null) {
	//			storeDOM = (new XMLDOMBuilder()).newDocument();
	//		}
	//		
	//    	Element root = storeDOM.createElementNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":dts");
	//		
	//		Set<URI> uris = getDocumentURIs();
	//		long counter = 1;
	//		for (URI uri: uris) {
	//	    	Element file = storeDOM.createElementNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":file");
	//	    	file.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":uri", uri.toString());
	//	    	file.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index","composite_" + new Long(counter++).toString());
	//			root.appendChild(file);
	//			file.appendChild(getAnnotatedDocumentAsDOM(uri));
	//		}
	//    	root.setAttributeNS(Constants.CompNamespace.toString(),Constants.CompPrefix + ":index","composite_" + new Long(counter++).toString());
	//    	storeDOM.appendChild(root);
	//    	return storeDOM;
	//    	
	//    }

	/**
	* @see org.xbrlapi.data.Store#getStubs()
	*/
	std::vector<Stub> BaseStoreImpl::getStubs() 
	{
		std::vector<Stub> stubs = getXMLResources("Stub");
		return stubs;
	return std::vector<Stub>();
	}
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getStubs(URI)
	//     */
	//    public std::vector<Stub> getStubs(URI uri) {
	//        return this.<Stub>queryForXMLResources("#roots#[@type='org.xbrlapi.impl.StubImpl' and @resourceURI='" + uri + "']");
	//    }
	//    
	//    /**
	//     * @see Store#removeStub(Stub)
	//     */
	//    public void removeStub(Stub stub) {
	//        if (hasXMLResource(stub.getIndex())) remove(stub);
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#remove(XML)
	//     */
	//    public void remove(const XML& xml) {
	//        remove(xml.getIndex());
	//    }    
	//
	/**
	* @see org.xbrlapi.data.Store#getDocumentsToDiscover()
	*/
	//synchronized 
	std::vector<Poco::URI> BaseStoreImpl::getDocumentsToDiscover() 
	{
		std::vector<Stub> stubs = getStubs();
		std::vector<Poco::URI> v;
		for (Stub& stub : stubs) {
			v.push_back(stub.getResourceURI());
		}
		return v;
	}
	//    
	//	/**
	//     * @see Store#saveDocuments(File)
	//	 */
	//	public void saveDocuments(File destination) {
	//		saveDocuments(destination, "");
	//	}
	//	
	//	/**
	//     * @see Store#saveDocuments(File, String)
	//	 */
	//	public void saveDocuments(File destination,  std::string uriPrefix) {
	//		
	//		if (! destination.exists()) throw new XBRLException("The specified directory does not exist.");
	//		
	//		if (! destination.isDirectory()) throw new XBRLException("A directory rather than a file must be specified.");
	//		
	//		Set<URI> uris = getDocumentURIs();
	//		Iterator<URI> iterator = uris.iterator();
	//		while (iterator.hasNext()) {			
	//			URI uri = iterator.next();
	//			if (uri.toString().startsWith(uriPrefix)) {
	//				Cache cache = new CacheImpl(destination);
	//				File file = cache.getCacheFile(uri);
	//				Element e = getDocumentAsDOM(uri);
	//				serialize(e,file);
	//			}
	//		}
	//		
	//	}
	//	
	//	/**
	//	 * @see Store#saveStoreAsSingleDocument(File)
	//	 */
	//	public void saveStoreAsSingleDocument(File file) {
	//		serialize(getStoreAsDOM().getDocumentElement(),file);
	//	}
	//    
	//    /**
	//     * Convert a DOM element (and its descendents) to a string.
	//     * @param element The element to convert to a string.
	//     * @return The string that is the serialised element.
	//     * @throws XBRLException if an IO exception occurs.
	//     */
	//    protected  std::string DOM2String(Element element) {
	//        try {
	//            LSSerializer writer = domImplementation.createLSSerializer();
	//            return writer.writeToString(element);
	//        } catch (Exception e) {
	//            throw new XBRLException("The XML DOM element could not be written to a string for persisting.",e);
	//        }
	//    }

	/**
	* @see org.xbrlapi.data.Store#getXMLResources(String)
	*/
	std::vector<Stub> BaseStoreImpl::getXMLResources(const std::string& interfaceName) 
	{
		std::string query = "for $root in #roots# where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
		if (interfaceName.find(".") > -1) {
			query = "for $root in #roots# where $root/@type='" + interfaceName + "' return $root";
		}
		return queryForXMLResources(query);
	return std::vector<Stub>();
	}
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getXMLResources(Class)
	//     */
	//    public <F extends XML> std::vector<F> getXMLResources(Class<?> specifiedClass) {
	//         std::string query = "for $root in #roots# where $root/@type='" + specifiedClass.getName() + "' return $root";
	//        return this.<F>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getChildFragments(String, String)
	//     */
	//    public <F extends Fragment> std::vector<F> getChildFragments( std::string interfaceName,  std::string parentIndex) {
	//    	return this.<F>queryForXMLResources("#roots#[@type='org.xbrlapi.impl." + interfaceName + "Impl' and @parentIndex='" + parentIndex + "']");
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getChildFragments(Class, String)
	//     */
	//    public <F extends Fragment> std::vector<F> getChildFragments(Class<?> childClass,  std::string parentIndex) {
	//        return this.<F>queryForXMLResources("#roots#[@type='" + childClass.getName() + "' and @parentIndex='" + parentIndex + "']");
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getNetworks()
	//     */
	//    public Networks getNetworks() {
	//
	//        Networks networks = new NetworksImpl(this);
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = new AllAnalyserImpl(this);
	//            std::vector<Relationship> relationships = analyser.getAllRelationships();
	//            networks.addRelationships(relationships);
	//            return networks;
	//        }
	//        
	//        // First get the set of arcs using the arc role
	//        Set<String> arcIndices = getArcIndices();
	//        for ( std::string index: arcIndices) {
	//            Arc arc = this.getXMLResource(index);
	//            std::vector<ArcEnd> sources = arc.getSourceFragments();
	//            std::vector<ArcEnd> targets = arc.getTargetFragments();
	//            for (ArcEnd source: sources) {
	//                for (ArcEnd target: targets) {
	//                    Fragment s = null;
	//                    Fragment t = null;
	//                    if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                        s = ((Locator) source).getTarget();
	//                    else s = source;
	//                    if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                        t = ((Locator) target).getTarget();
	//                    else t = target;
	//                    networks.addRelationship(new RelationshipImpl(arc,s,t));
	//                }
	//            }
	//        }
	//        return networks;        
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getNetworks(String)
	//     */
	//    public Networks getNetworks( std::string arcrole) {
	//
	//        Networks networks = new NetworksImpl(this);
	//    	
	//        for ( std::string linkRole: getLinkRoles(arcrole)) {
	//            Set<String> linkIndices = getExtendedLinkIndices(linkRole);
	//            for ( std::string linkIndex: linkIndices) {
	//
	//                Set<String> arcIndices = getArcIndices(arcrole,linkIndex);
	//                for ( std::string index: arcIndices) {
	//                    Arc arc = this.getXMLResource(index);
	//                    std::vector<ArcEnd> sources = arc.getSourceFragments();
	//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
	//                    for (ArcEnd source: sources) {
	//                        for (ArcEnd target: targets) {
	//                            Fragment s = null;
	//                            Fragment t = null;
	//                            if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                                s = ((Locator) source).getTarget();
	//                            else s = source;
	//                            if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                                t = ((Locator) target).getTarget();
	//                            else t = target;
	//                            networks.addRelationship(new RelationshipImpl(arc,s,t));
	//                        }
	//                    }
	//                }
	//            }
	//        }
	//        
	//        logger.debug("network size = " + networks.getSize());
	//    	return networks;    	
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getNetworks(String,String)
	//     */
	//    public Networks getNetworks( std::string linkRole,  std::string arcrole) {
	//
	//        Networks networks = new NetworksImpl(this);
	//
	//        // Use persisted relationships if they are being used.
	//        if (this.isPersistingRelationships()) {
	//            networks.addRelationships(getAnalyser().getRelationships(linkRole,arcrole));
	//            return networks;
	//        }
	//        
	//        Set<String> linkIndices = getExtendedLinkIndices(linkRole);
	//        logger.debug(linkIndices.size() + " extended links with given link and arc roles.");
	//        for ( std::string linkIndex: linkIndices) {
	//
	//            Set<String> arcIndices = getArcIndices(arcrole,linkIndex);
	//            logger.debug(arcIndices.size() + " arcs with arcrole in given extended link.");
	//            for ( std::string index: arcIndices) {
	//                Arc arc = this.getXMLResource(index);
	//                std::vector<ArcEnd> sources = arc.getSourceFragments();
	//                std::vector<ArcEnd> targets = arc.getTargetFragments();
	//                for (ArcEnd source: sources) {
	//                    for (ArcEnd target: targets) {
	//                        Fragment s = null;
	//                        Fragment t = null;
	//                        if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                            s = ((Locator) source).getTarget();
	//                        else s = source;
	//                        if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) 
	//                            t = ((Locator) target).getTarget();
	//                        else t = target;
	//                        networks.addRelationship(new RelationshipImpl(arc,s,t));
	//                    }
	//                }
	//            }
	//        } 
	//        
	//        logger.debug("network size = " + networks.getSize());
	//        return networks;        
	//    }
	//
	//    
	//    /**
	//     * @param arcrole The arcrole to use to identify the arcs to retrieve.
	//     * @return the list of arc fragments with a given arc role value.
	//     * @throws XBRLException
	//     */
	//    private std::vector<Arc> getArcsWithArcrole( std::string arcrole) {
	//    	 std::string query = "#roots#[*/*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]";
	//    	List<Arc> arcs = this.<Arc>queryForXMLResources(query);
	//    	logger.debug("#arcs with given arcrole = " + arcs.size());
	//    	return arcs;
	//    }
	//    
	//    /**
	//     * @see Store#getLabels(String, String, String, String)
	//     */
	//    public std::vector<LabelResource> getLabels( std::string fragment,  std::string linkRole,  std::string resourceRole,  std::string language) {
	//
	//        if (this.isPersistingRelationships()) {
	//             std::string query = "#roots#[@label and @type='" + RelationshipImpl.class.getName() + "' and @sourceIndex='" + fragment + "'";
	//            if (linkRole != null) query += " and @linkRole='" + linkRole + "'"; 
	//            if (resourceRole != null) query += " and @targetRole='" + resourceRole + "'"; 
	//            if (language != null) query += " and @targetLanguage='" + language + "'"; 
	//            query += "]";
	//            
	//            std::vector<Relationship> relationships = this.<Relationship>queryForXMLResources(query);
	//            std::vector<LabelResource> labels = new Vector<LabelResource>();
	//            for (const Relationship& relationship: relationships) {
	//                labels.add(relationship.<LabelResource>getTarget());
	//            }
	//            return labels;
	//        }
	//
	//        try {
	//
	//            Networks labelNetworks = this.getNetworksFrom(fragment,linkRole,Constants.LabelArcrole);
	//            labelNetworks.addAll(this.getNetworksFrom(fragment,linkRole,Constants.GenericLabelArcrole));
	//            
	//            std::vector<LabelResource> labels = new Vector<LabelResource>();
	//            for (const Network& network: labelNetworks) {
	//                RELATIONSHIPS: for (const Relationship& relationship: network.getAllActiveRelationships()) {
	//                    LabelResource label = (LabelResource) relationship.getTarget();
	//                    if (resourceRole == null && language == null) {
	//                        labels.add(label);
	//                        continue RELATIONSHIPS;
	//                    }
	//                    bool languagesMatch = false;
	//                    bool resourceRolesMatch = false;
	//                     std::string l = label.getLanguage();
	//                     std::string r = label.getResourceRole();
	//                    
	//                    if (language == null) languagesMatch = true;
	//                    else if (l != null && l.equals(language)) languagesMatch = true; 
	//
	//                    if (resourceRole == null) resourceRolesMatch = true;
	//                    else if (resourceRole != null && resourceRole != null && r.equals(resourceRole)) resourceRolesMatch = true; 
	//
	//                    if (languagesMatch && resourceRolesMatch) labels.add(label); 
	//                }
	//            }
	//            return labels;            
	//        } catch (XBRLException e) {
	//            throw e;
	//        }
	//        
	//        
	//    }
	//
	//    /**
	//     * @see Store#getLabels(String, String, String)
	//     */
	//    public std::vector<LabelResource> getLabels( std::string fragment,  std::string resourceRole,  std::string language) {
	//        return this.getLabels(fragment,null,resourceRole,language);
	//    }
	//    
	//    /**
	//     * @see Store#getLabelsWithLanguage(String, String)
	//     */
	//    public std::vector<LabelResource> getLabelsWithLanguage( std::string fragment,  std::string language) {
	//        return this.getLabels(fragment,null,null,language);
	//    }
	//    
	//    /**
	//     * @see Store#getLabels(String)
	//     */
	//    public std::vector<LabelResource> getLabels( std::string fragment) {
	//        return this.getLabels(fragment,null,null,null);
	//    }    
	//    
	//    /**
	//     * @see Store#getLabelsWithResourceRole(String, String)
	//     */
	//    public std::vector<LabelResource> getLabelsWithResourceRole( std::string fragment,  std::string resourceRole) {
	//        return this.getLabels(fragment,null,resourceRole,null);
	//    }
	//    
	//    /**
	//     * @see Store#getReferences(String, String, String, String)
	//     */
	//    public std::vector<ReferenceResource> getReferences( std::string fragment,  std::string linkRole,  std::string resourceRole,  std::string language) {
	//
	//        if (this.isPersistingRelationships()) {
	//             std::string query = "#roots#[@reference and @sourceIndex='" + fragment + "'";
	//            if (linkRole != null) query += " and @linkRole='" + linkRole + "'"; 
	//            if (resourceRole != null) query += " and @targetRole='" + resourceRole + "'"; 
	//            if (language != null) query += " and @targetLanguage='" + language + "'"; 
	//            query += "]";
	//            std::vector<Relationship> relationships = this.<Relationship>queryForXMLResources(query);
	//            std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
	//            for (const Relationship& relationship: relationships) {
	//                references.add(relationship.<ReferenceResource>getTarget());
	//            }
	//            return references;
	//        }
	//
	//        try {
	//
	//            Networks referenceNetworks = this.getNetworksFrom(fragment,linkRole,Constants.ReferenceArcrole);
	//            referenceNetworks.addAll(this.getNetworksFrom(fragment,linkRole,Constants.GenericReferenceArcrole));
	//            
	//            std::vector<ReferenceResource> references = new Vector<ReferenceResource>();
	//            for (const Network& network: referenceNetworks) {
	//                RELATIONSHIPS: for (const Relationship& relationship: network.getAllActiveRelationships()) {
	//                    ReferenceResource reference = (ReferenceResource) relationship.getTarget();
	//                    if (resourceRole == null && language == null) {
	//                        references.add(reference);
	//                        continue RELATIONSHIPS;
	//                    }
	//                    bool languagesMatch = false;
	//                    bool resourceRolesMatch = false;
	//                     std::string l = reference.getLanguage();
	//                     std::string r = reference.getResourceRole();
	//                    
	//                    if (language == null) languagesMatch = true;
	//                    else if (l != null && l.equals(language)) languagesMatch = true; 
	//
	//                    if (resourceRole == null) resourceRolesMatch = true;
	//                    else if (resourceRole != null && resourceRole != null && r.equals(resourceRole)) resourceRolesMatch = true; 
	//
	//                    if (languagesMatch && resourceRolesMatch) references.add(reference); 
	//                }
	//            }
	//            return references;            
	//        } catch (XBRLException e) {
	//            throw e;
	//        }        
	//    }
	//        
	//    /**
	//     * @see Store#getReferences(String, String, String)
	//     */
	//    public std::vector<ReferenceResource> getReferences( std::string fragment,  std::string resourceRole,  std::string language) {
	//        return this.getReferences(fragment,null,resourceRole,language);
	//    }
	//    
	//    /**
	//     * @see Store#getReferencesWithLanguage(String, String)
	//     */
	//    public std::vector<ReferenceResource> getReferencesWithLanguage( std::string fragment,  std::string language) {
	//        return this.getReferences(fragment,null,null,language);
	//    }
	//    
	//    /**
	//     * @see Store#getReferences(String)
	//     */
	//    public std::vector<ReferenceResource> getReferences( std::string fragment) {
	//        return this.getReferences(fragment,null,null,null);
	//    }        
	//    
	//    /**
	//     * @see Store#getReferencesWithResourceRole(String, String)
	//     */
	//    public std::vector<ReferenceResource> getReferencesWithResourceRole( std::string fragment,  std::string resourceRole) {
	//        return this.getReferences(fragment,null,resourceRole,null);
	//    }
	//    
	//    /**
	//     * @see Store#getArcs(URI, String)
	//     */
	//    public std::vector<Arc> getArcs(URI arcrole,  std::string linkIndex) {
	//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]";
	//        std::vector<Arc> arcs = this.<Arc>queryForXMLResources(query);
	//        logger.debug("#arcs with given arcrole in given extended link = " + arcs.size());
	//        return arcs;
	//    }
	//    
	//    /**
	//     * @see Store#getArcs(String)
	//     */
	//    public std::vector<Arc> getArcs( std::string linkIndex) {
	//         std::string query = "#roots#[@type='org.xbrlapi.impl.ArcImpl' and @parentIndex='" + linkIndex + "']";
	//        std::vector<Arc> arcs = this.<Arc>queryForXMLResources(query);
	//        return arcs;
	//    }    
	//    
	//    /**
	//     * @see Store#getArcIndicesWithArcrole(String)
	//     */
	//    public Set<String> getArcIndicesWithArcrole( std::string arcrole) {
	//         std::string query = "#roots#[*/*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]/@index";
	//        return this.queryForStrings(query);
	//    }
	//    
	//    /**
	//     * @param arcrole The arcrole to use to identify the arcs to retrieve.
	//     * @param linkIndex The index of the extended link containing the arcs to retrieve.
	//     * @return the list of indices of arcs matching the selection criteria.
	//     * @throws XBRLException
	//     */
	//    private Set<String> getArcIndices( std::string arcrole,  std::string linkIndex) {
	//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*[@xlink:arcrole='" + arcrole + "' and @xlink:type='arc']]/@index";
	//        Set<String> indices = this.queryForStrings(query);
	//        return indices;
	//    }
	//    
	//    /**
	//     * @see Store#getArcIndicesWithLinkIndex(String)
	//     */
	//    public Set<String> getArcIndicesWithLinkIndex( std::string linkIndex) {
	//         std::string query = "#roots#[@parentIndex='" + linkIndex + "' and */*/@xlink:type='arc']/@index";
	//        Set<String> indices = this.queryForStrings(query);
	//        return indices;
	//    }    
	//    
	//    /**
	//     * @see Store#getExtendedLinkIndices(String)
	//     */
	//    public Set<String> getExtendedLinkIndices( std::string linkRole) {
	//         std::string query = "#roots#[*/*[@xlink:role='" + linkRole + "' and @xlink:type='extended']]/@index";
	//        Set<String> indices = this.queryForStrings(query);
	//        logger.debug("# extended links with given link role = " + indices.size());
	//        return indices;
	//    }
	//
	//    /**
	//     * @return the list of indices of arcs in the data store.
	//     * @throws XBRLException
	//     */
	//    private Set<String> getArcIndices() {
	//         std::string query = "for $root in #roots#[@type='"+ArcImpl.class.getName()+"'] return $root/@index";
	//        return this.queryForStrings(query);
	//    }    
	//
	//    /**
	//     * @see Store#getFragmentsFromDocument(URI, String)
	//     */
	//    public <F extends Fragment> std::vector<F> getFragmentsFromDocument(URI uri,  std::string interfaceName) {
	//        URI matchURI = getMatcher().getMatch(uri);
	//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='org.xbrlapi.impl." + interfaceName + "Impl']";        
	//        if (interfaceName.indexOf(".") > -1) {
	//            query = "#roots#[@uri='"+ matchURI + "' and @type='" + interfaceName + "']";
	//        }
	//        return this.<F>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see Store#getFragmentsFromDocument(URI, Class)
	//     */
	//    public <F extends Fragment> std::vector<F> getFragmentsFromDocument(URI uri, Class<?> fragmentClass) {
	//        URI matchURI = getMatcher().getMatch(uri);
	//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='"+fragmentClass.getName()+"']";        
	//        return this.<F>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see Store#getFragmentIndicesFromDocument(URI, String)
	//     */
	//    public Set<String> getFragmentIndicesFromDocument(URI uri,  std::string interfaceName) {
	//        URI matchURI = getMatcher().getMatch(uri);
	//         std::string query = "#roots#[@uri='"+ matchURI + "' and @type='org.xbrlapi.impl." + interfaceName + "Impl']";        
	//        if (interfaceName.indexOf(".") > -1) {
	//            query = "#roots#[@uri='"+ matchURI + "' and @type='" + interfaceName + "']";
	//        }
	//        Set<String> result = this.queryForIndices(query);
	//        return result;
	//    }
	//    
	//    /**
	//     * @see Store#getFragmentIndicesFromDocument(URI)
	//     */
	//    public Set<String> getFragmentIndicesFromDocument(URI uri) {
	//        URI matchURI = getMatcher().getMatch(uri);
	//         std::string query = "#roots#[@uri='"+ matchURI + "']";
	//        Set<String> result = this.queryForIndices(query);
	//        return result;
	//        
	//    }
	//    
	//    /**
	//     * @see Store#getFragmentIndices(String)
	//     */
	//    public Set<String> getFragmentIndices( std::string interfaceName) {
	//        long start = System.currentTimeMillis();
	//         std::string query = "#roots#[@type='org.xbrlapi.impl." + interfaceName + "Impl']";        
	//        if (interfaceName.indexOf(".") > -1) {
	//            query = "#roots#[@type='" + interfaceName + "']";
	//        }
	//        query += "/@index";
	//        Set<String> result = this.queryForStrings(query);
	//        Double seconds = new Double(System.currentTimeMillis() - start) / new Double(1000);
	//        logger.debug("Seconds required = " + seconds);
	//        return result;
	//    }    
	//
	//    /**
	//     * @see Store#getFacts()
	//     */
	//    public list<Fact&> getFacts() {
	//    	List<Instance> instances = this.<Instance>getXMLResources("Instance");
	//    	return getFactsFromInstances(instances);
	//    }
	//
	//    /**
	//     * Helper method for common code in the getTuple methods.
	//     * @param instances The instances to retrieve tuples for.
	//     * @return a list of root tuples in the instances.
	//     * @throws XBRLException
	//     */
	//    private std::vector<Tuple> getTuplesFromInstances(List<Instance> instances) {
	//        std::vector<Tuple> tuples = new Vector<Tuple>();
	//        for (Instance instance: instances) {
	//            tuples.addAll(instance.getTuples());
	//        }
	//        return tuples;
	//    }    
	//
	//    /**
	//     * @see Store#getFacts(URI)
	//     */
	//    public list<Fact&> getFacts(URI uri) {
	//    	List<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
	//    	return this.getFactsFromInstances(instances);
	//    }
	//    
	//    /**
	//     * @see Store#getAllFacts(URI)
	//     */
	//    public list<Fact&> getAllFacts(URI uri) {
	//         std::string query = "for $root in #roots#[@uri='"+ uri +"' ] where $root/@fact return $root";
	//        return this.<Fact>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see Store#getAllFacts()
	//     */
	//    public list<Fact&> getAllFacts() {
	//         std::string query = "for $root in #roots# where $root/@fact return $root";
	//        return this.<Fact>queryForXMLResources(query);
	//    }    
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getRootFragmentForDocument(URI)
	//     */
	//    public <F extends Fragment> F getRootFragmentForDocument(URI uri) {
	//    	List<F> fragments = this.<F>queryForXMLResources("#roots#[@uri='" + uri + "' and @parentIndex='']");
	//    	if (fragments.size() == 0) return null;
	//    	if (fragments.size() > 1) throw new XBRLException("Two fragments identify themselves as roots of the one document.");
	//    	return fragments.get(0);
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getRootFragments()
	//     */
	//    public <F extends Fragment> std::vector<F> getRootFragments() {
	//    	List<F> roots =  this.<F>queryForXMLResources("#roots#[@uri and @parentIndex='']");
	//    	return roots;
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getRootFragments(String)
	//     */
	//    public <F extends Fragment> std::vector<F> getRootFragments( std::string interfaceName) {
	//         std::string query = "for $root in #roots#[@parentIndex=''] where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
	//        if (interfaceName.indexOf(".") > -1) {
	//            query = "for $root in #roots#[@parentIndex=''] where $root/@type='" + interfaceName + "' return $root";
	//        }
	//        return this.<F>queryForXMLResources(query);
	//    }    
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getLanguage(String, String)
	//     */
	//    public Language getLanguage( std::string encoding,  std::string code) {
	//        if (encoding == null) throw new XBRLException("The language code must not be null.");
	//        if (code == null) throw new XBRLException("The language name encoding must not be null.");
	//         std::string query = "#roots#[@type='org.xbrlapi.impl.LanguageImpl' and "+ Constants.XBRLAPIPrefix+ ":" + "data/lang:language/lang:encoding='" + encoding + "' and " + Constants.XBRLAPIPrefix + ":" + "data/lang:language/lang:code='" + code + "']";
	//        std::vector<Language> languages = this.<Language>queryForXMLResources(query);
	//        if (languages.size() == 0) return null;
	//        return languages.get(0);
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getLanguages(String)
	//     */
	//    public std::vector<Language> getLanguages( std::string code) {
	//        if (code == null) throw new XBRLException("The language code must not be null.");
	//         std::string query = "#roots#[@type='org.xbrlapi.impl.LanguageImpl' and */lang:language/lang:code='" + code + "']";
	//        return this.<Language>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getLanguageMap(String)
	//     */
	//    public Map<String,Language> getLanguageMap( std::string code) {
	//        std::vector<Language> languages = this.getLanguages(code);
	//        Map<String,Language> result = new HashMap<String,Language>();
	//        for (Language language: languages) {
	//            result.put(language.getEncoding(),language);
	//        }
	//        return result;
	//    }    
	//
	//    /**
	//     * @see Store#queryForString(String)
	//     */
	//    public  std::string queryForString( std::string query) {
	//        Set<String> strings = queryForStrings(query);
	//        if (strings.size() == 0) return null;
	//        if (strings.size() > 1) throw new XBRLException(query + " returned more than one string.");
	//        for ( std::string string: strings) return string;
	//        throw new XBRLException("This exception cannot be thrown. There is a bug in the software.");
	//    }
	//
	//    /**
	//     * This method is provided as a helper method for the getFact methods.
	//     * @param instances The list of instance fragments to extract facts from.
	//     * @return The list of facts in the instances.
	//     * @throws XBRLException
	//     */
	//    private list<Fact&> getFactsFromInstances(List<Instance> instances) {
	//        list<Fact&> facts = new Vector<Fact>();
	//        for (Instance instance: instances) {
	//            facts.addAll(instance.getChildFacts());
	//        }
	//        return facts;
	//    }
	//    
	//    /**
	//     * Helper method for common code in the getItem methods.
	//     * @param instances The instances to retrieve items for.
	//     * @return a list of root items in the instances.
	//     * @throws XBRLException
	//     */
	//    private std::vector<Item> getItemsFromInstances(List<Instance> instances) {
	//        std::vector<Item> items = new Vector<Item>();
	//        for (Instance instance: instances) {
	//            items.addAll(instance.getChildItems());
	//        }
	//        return items;
	//    }
	//
	//    /**
	//     * @see Store#getItems()
	//     */
	//    public std::vector<Item> getItems() {
	//        std::vector<Instance> instances = this.<Instance>getXMLResources("Instance");
	//        return getItemsFromInstances(instances);
	//    }
	//    
	//    /**
	//     * @see Store#getTuples()
	//     */
	//    public std::vector<Tuple> getTuples() {
	//        return this.<Tuple>getXMLResources(TupleImpl.class);
	//    }
	//
	//    /**
	//     * @see Store#getItems(URI)
	//     */
	//    public std::vector<Item> getItems(URI uri) {
	//        std::vector<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
	//        return this.getItemsFromInstances(instances);
	//    }
	//    
	//    /**
	//     * @see Store#getTuples(URI)
	//     */
	//    public std::vector<Tuple> getTuples(URI uri) {
	//        std::vector<Instance> instances = this.<Instance>getFragmentsFromDocument(uri,"Instance");
	//        return this.getTuplesFromInstances(instances);
	//    }
	//
	//    /**
	//     * @see Store#getNetworkRoots(String, String)
	//     */
	//    public <F extends Fragment> Set<F> getNetworkRoots( std::string linkRole,  std::string arcrole) {
	//        
	//        if (this.isPersistingRelationships()) {
	//            return getAnalyser().<F>getRoots(linkRole,arcrole);
	//        }
	//        
	//        // Get the links that contain the network declaring arcs.
	//         std::string linkQuery = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl' and "+ Constants.XBRLAPIPrefix+ ":" + "data/*[@xlink:role='" + linkRole + "']]";
	//        std::vector<ExtendedLink> links = this.<ExtendedLink>queryForXMLResources(linkQuery);
	//        
	//        // Get the arcs that declare the relationships in the network.
	//        // For each arc map the ids of the fragments at their sources and targets.
	//        HashMap<String,String> sourceIds = new HashMap<String,String>();
	//        HashMap<String,String> targetIds = new HashMap<String,String>();
	//        for (int i=0; i<links.size(); i++) {
	//            ExtendedLink link = links.get(i);
	//            std::vector<Arc> arcs = link.getArcs();
	//            for (const Arc& arc: arcs) {
	//                if (arc.getArcrole().equals(arcrole)) {
	//                    std::vector<ArcEnd> sources = arc.getSourceFragments();
	//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
	//                    for (int k=0; k<sources.size(); k++) {
	//                        sourceIds.put(sources.get(k).getIndex(),"");
	//                    }
	//                    for (int k=0; k<sources.size(); k++) {
	//                        targetIds.put(targets.get(k).getIndex(),"");
	//                    }
	//                }
	//            }
	//        }
	//        
	//        // Get the root resources in the network
	//        Set<F> roots = new TreeSet<F>();
	//        for ( std::string id: sourceIds.keySet()) {
	//            if (! targetIds.containsKey(id)) {
	//                roots.add(this.<F>getXMLResource(id));
	//            }
	//        }
	//        return roots;
	//    }    
	//    
	//    
	//    /**
	//     * @see Store#getConcept(String, String)
	//     */
	//    public Concept getConcept( std::string namespace,  std::string name) {
	//        return this.<Concept>getGlobalDeclaration(namespace,name);
	//    }
	//    
	//    /**
	//     * @see Store#getGlobalDeclaration(String, String)
	//     */
	//    public <D extends SchemaDeclaration> D getGlobalDeclaration( std::string namespace,  std::string name) {
	//        Schema schema = this.getSchema(namespace);
	//        D declaration = schema.<D>getGlobalDeclaration(name);
	//        if (declaration == null) {
	//            throw new XBRLException("No matching global schema declarations were found for " + namespace + ":" + name + ".");
	//        }
	//        return declaration;
	//    }    
	//
	//    /**
	//     * @return a list of roleType fragments
	//     * @throws XBRLException
	//     */
	//    public std::vector<RoleType> getRoleTypes() {
	//        return this.<RoleType>getXMLResources("RoleType");
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getRoleTypes(String)
	//     */
	//    public std::vector<RoleType> getRoleTypes( std::string uri) {
	//         std::string query = "#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/link:roleType/@roleURI='" + uri + "']";
	//        return this.<RoleType>queryForXMLResources(query);
	//    }    
	//    
	//    /**
	//     * @see Store#getArcroleTypes()
	//     */
	//    public std::vector<ArcroleType> getArcroleTypes() {
	//        return this.<ArcroleType>getXMLResources("ArcroleType");
	//    }
	//    
	//    /**
	//     * @see Store#getArcroleTypes(String)
	//     */
	//    public std::vector<ArcroleType> getArcroleTypes( std::string uri) {
	//         std::string query = "#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/link:arcroleType/@arcroleURI='" + uri + "']";
	//        return this.<ArcroleType>queryForXMLResources(query);
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getResourceRoles()
	//     */
	//    public std::vector<String> getResourceRoles() {
	//        HashMap<String,String> roles = new HashMap<String,String>();
	//        list<Resource> resources = this.<Resource>queryForXMLResources("#roots#["+ Constants.XBRLAPIPrefix+ ":" + "data/*/@xlink:type='resource']");
	//        for (Resource resource: resources) {
	//        	 std::string role = resource.getResourceRole();
	//            if (! roles.containsKey(role)) roles.put(role,"");
	//        }
	//        std::vector<String> result = new Vector<String>();
	//        result.addAll(roles.keySet());
	//        return result;
	//    }    
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getMinimumDocumentSet(URI)
	//     */
	//    public Set<URI> getMinimumDocumentSet(URI uri) {
	//        std::vector<URI> starters = new Vector<URI>();
	//        starters.add(uri);
	//        return this.getMinimumDocumentSet(starters);
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getMinimumDocumentSet(Collection)
	//     */
	//    public Set<URI> getMinimumDocumentSet(Collection<URI> starters) {
	//        
	//        Set<URI> minimumDocumentSet = new HashSet<URI>();
	//        Set<URI> checkThese = new HashSet<URI>();
	//        checkThese.addAll(starters);
	//        
	//        while (checkThese.size() > 0) {
	//            URI document = checkThese.iterator().next();
	//            for (URI referencedDocument: getReferencedDocuments(document)) {
	//                if ((! minimumDocumentSet.contains(referencedDocument)) && (! checkThese.contains(referencedDocument)))
	//                    checkThese.add(referencedDocument);
	//            }
	//            
	//            minimumDocumentSet.add(document);
	//            checkThese.remove(document);
	//        }
	//        
	//        return minimumDocumentSet;
	//
	//    }
	// 
	//    /**
	//     * @see Store#getExtendedLinks(String)
	//     */
	//    public std::vector<ExtendedLink> getExtendedLinks( std::string linkrole) {
	//         std::string query = "#roots#[*/*[@xlink:type='extended' and @xlink:role='" + linkrole + "']]";
	//        std::vector<ExtendedLink> links = this.<ExtendedLink>queryForXMLResources(query);
	//        return links;
	//    }
	//
	//    /**
	//     * @see Store#getMinimalNetworksWithArcrole(Fragment, String)
	//     */
	//    public synchronized Networks getMinimalNetworksWithArcrole(const Fragment& fragment,  std::string arcrole) {
	//        Set<Fragment> set = new HashSet<Fragment>();
	//        set.add(fragment);
	//        return this.getMinimalNetworksWithArcrole(set,arcrole);
	//    }    
	//    
	//    /**
	//     * @see Store#getMinimalNetworksWithArcrole(Set, String)
	//     */
	//    public synchronized Networks getMinimalNetworksWithArcrole(Set<Fragment> fragments,  std::string arcrole) {
	//
	//        try {
	//            Networks networks = new NetworksImpl(this);
	//            for (const Fragment& fragment: fragments) {
	//                augmentNetworksForFragment(fragment,arcrole,networks);
	//            }
	//            return networks;
	//        } catch (Throwable t) {
	//            throw new XBRLException("There was a problem getting minimal networks with arcrole " + arcrole,t);
	//        }
	//    }
	//    
	//    /**
	//     * @see Store#augmentNetworksForFragment(Fragment, String, Networks)
	//     */
	//    public synchronized void augmentNetworksForFragment(const Fragment& fragment,  std::string arcrole, Networks networks) {
	//        for (const Network& network: networks.getNetworks(arcrole)) {
	//            if (network.hasActiveRelationshipsTo(fragment.getIndex())) return;
	//        }
	//        
	//        for (const Relationship& relationship: this.getRelationshipsTo(fragment.getIndex(),null,arcrole)) {
	//            networks.addRelationship(relationship);
	//        }
	//        
	//        for (const Network& network: networks.getNetworks(arcrole)) {
	//            SortedSet<Relationship> activeRelationships = network.getActiveRelationshipsTo(fragment.getIndex());
	//            for (const Relationship& activeRelationship: activeRelationships) {
	//                Fragment source = activeRelationship.getSource();
	//                augmentNetworksForFragment(source,arcrole,networks);
	//            }
	//        }
	//    }
	//    
	//    /**
	//     * @see Store#augmentNetworkForFragment(Fragment, Network)
	//     */
	//    public synchronized void augmentNetworkForFragment(const Fragment& fragment, const Network& network) {
	//
	//        if (network.hasActiveRelationshipsTo(fragment.getIndex())) return;
	//                
	//        for (const Relationship& relationship: this.getRelationshipsTo(fragment.getIndex(),network.getLinkRole(),network.getArcrole())) {
	//            network.addRelationship(relationship);
	//        }
	//        SortedSet<Relationship> activeRelationships = network.getActiveRelationshipsTo(fragment.getIndex());
	//        for (const Relationship& activeRelationship: activeRelationships) {
	//            Fragment source = activeRelationship.getSource();
	//            augmentNetworkForFragment(source,network);
	//        }
	//    }
	//    
	//    /**
	//     * @see Store#getMinimalNetwork(Set, String, String)
	//     */
	//    public Network getMinimalNetwork(Set<Fragment> fragments,  std::string linkRole,  std::string arcrole) {
	//
	//        try {
	//            Network network = new NetworkImpl(this, linkRole, arcrole);
	//            for (const Fragment& fragment: fragments) {
	//                augmentNetworkForFragment(fragment,network);
	//            }
	//            return network;
	//        } catch (Throwable t) {
	//            throw new XBRLException("There was a problem getting minimal networks with arcrole " + arcrole,t);
	//        }    
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getArcroles()
	//     */
	//    public Set<String> getArcroles() {
	//         std::string query = "#roots#/*/*[@xlink:type='arc']/@xlink:arcrole";
	//        Set<String> values = this.queryForStrings(query);
	//        Set<String> arcroles = new TreeSet<String>();
	//        for ( std::string value: values) arcroles.add(value);
	//        return arcroles;
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getLinkRoles()
	//     */
	//    public Set<String> getLinkRoles() {
	//         std::string query = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl']/*/*/@xlink:role";
	//        Set<String> values = this.queryForStrings(query);
	//        Set<String> linkRoles = new TreeSet<String>();
	//        for ( std::string value: values) linkRoles.add(value);
	//        return linkRoles;
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getLinkRoles(String)
	//     */
	//    public Set<String> getLinkRoles( std::string arcrole) {
	//        
	//         std::string query = "#roots#[*/*[@xlink:type='arc' and @xlink:arcrole='" + arcrole + "']]/@parentIndex";
	//        Set<String> linkIndices = this.queryForStrings(query);
	//        Set<String> linkRoles = new TreeSet<String>();
	//        for ( std::string index: linkIndices) {
	//            ExtendedLink link = this.getXMLResource(index);
	//            linkRoles.add(link.getLinkRole());
	//        }
	//        return linkRoles;
	//    }
	//    
	//    /**
	//     * @see org.xbrlapi.data.Store#getArcroles(String)
	//     */
	//    public Set<String> getArcroles( std::string linkRole) {
	//        
	//         std::string query = "#roots#[@type='org.xbrlapi.impl.ExtendedLinkImpl' and */*/@xlink:role='" + linkRole + "']/@index";
	//        Set<String> linkIndices = this.queryForStrings(query);
	//        Set<String> arcroles = new TreeSet<String>();
	//        for ( std::string linkIndex: linkIndices) {
	//            query = "#roots#[@parentIndex='" + linkIndex + "' and */*/@xlink:type='arc']/*/*/@xlink:arcrole";
	//            Set<String> candidates = queryForStrings(query);
	//            arcroles.addAll(candidates);
	//        }
	//        Set<String> result = new TreeSet<String>();
	//		for ( std::string arcrole : arcroles) result.add(arcrole);
	//
	//        return result;
	//
	//    }
	//
	//    /**
	//     * @see Store#getTargets(String, String, String)
	//     */
	//    @SuppressWarnings("unchecked")
	//    public <F extends Fragment> std::vector<F> getTargets( std::string sourceIndex,  std::string linkRole,  std::string arcrole) {
	//        
	//        SortedSet<Relationship> relationships = this.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
	//        Set<F> targets = new HashSet<F>();
	//        for (const Relationship& relationship: relationships) {
	//            try {
	//                targets.add((F) relationship.getTarget());
	//            } catch (ClassCastException e) {
	//                throw new XBRLException("A target fragment is of the wrong type: " + relationship.getTarget().getType(),e);
	//            }
	//        }
	//        return new Vector<F>(targets);
	//        
	//    }
	//    
	//    /**
	//     * @see Store#getSources(String, String, String)
	//     */
	//    @SuppressWarnings("unchecked")
	//    public <F extends Fragment> std::vector<F> getSources( std::string targetIndex,  std::string linkRole,  std::string arcrole) {
	//        
	//        SortedSet<Relationship> relationships = this.getRelationshipsTo(targetIndex,linkRole,arcrole);
	//        Set<F> sources = new HashSet<F>();
	//        for (const Relationship& relationship: relationships) {
	//            try {
	//                sources.add((F) relationship.getSource());
	//            } catch (ClassCastException e) {
	//                throw new XBRLException("A source fragment is of the wrong type: " + relationship.getSource().getType(),e);
	//            }
	//        }
	//        return new Vector<F>(sources);        
	//
	//    }
	//    
	//    /**
	//     * @see Store#getSourceIndices(String, String, String)
	//     */
	//    public Set<String> getSourceIndices( std::string targetIndex,  std::string linkRole,  std::string arcrole) {
	//        if (this.isPersistingRelationships()) {
	//             std::string lr = "";
	//             std::string ar = "";
	//            if (linkRole != null) {
	//                lr = " and @linkRole='"+ linkRole +"'";            
	//            }
	//            if (arcrole != null) {
	//                ar = " and @arcRole='"+ arcrole +"'";            
	//            }
	//             std::string query = "for $root in #roots#[@targetIndex='"+ targetIndex +"'" + ar + lr + "] return string($root/@sourceIndex)";
	//            return this.queryForStrings(query);
	//        } 
	//        
	//        Set<String> indices = new HashSet<String>();
	//        Networks networks = this.getNetworksTo(targetIndex,linkRole,arcrole);
	//        for (const Network& network: networks) {
	//            for (const Relationship& r: network.getActiveRelationshipsTo(targetIndex)) {
	//                indices.add(r.getSourceIndex());                    
	//            }
	//        }
	//        return indices;
	//
	//    }
	//    
	//    /**
	//     * @see Store#getRelationshipsFrom(String,String,String)
	//     */
	//    public SortedSet<Relationship> getRelationshipsFrom( std::string sourceIndex, std::string linkRole,  std::string arcrole) {
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = this.getAnalyser();
	//            return analyser.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
	//        }
	//
	//        SortedSet<Relationship> relationships = new TreeSet<Relationship>(new RelationshipOrderComparator());
	//        Networks networks = this.getNetworksFrom(sourceIndex,linkRole,arcrole);
	//        for (const Network& network: networks) {
	//            relationships.addAll(network.getActiveRelationshipsFrom(sourceIndex));
	//        }
	//        return relationships;
	//    }
	//    
	//    /**
	//     * @see Store#hasAllRelationships(URI)
	//     */
	//    public bool hasAllRelationships(URI document) {
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = this.getAnalyser();
	//            return analyser.hasAllRelationships(document);
	//        }
	//        return false;
	//
	//    }    
	//
	//    /**
	//     * @see Store#getRelationshipsTo(String, String, String)
	//     */
	//    public SortedSet<Relationship> getRelationshipsTo( std::string targetIndex, std::string linkRole,  std::string arcrole) {
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = this.getAnalyser();
	//            return analyser.getRelationshipsTo(targetIndex,linkRole,arcrole);
	//        }
	//        SortedSet<Relationship> relationships = new TreeSet<Relationship>(new RelationshipOrderComparator());
	//        Networks networks = this.getNetworksTo(targetIndex,linkRole,arcrole);
	//        logger.debug("# networks = " + networks.getSize());
	//        for (const Network& network: networks) {
	//            relationships.addAll(network.getActiveRelationshipsTo(targetIndex));
	//        }
	//        
	//        return relationships;
	//    }    
	//    
	//    /**
	//     * @see Store#getNetworksFrom(String,String,String)
	//     */
	//    public Networks getNetworksFrom( std::string sourceIndex, std::string linkRole,  std::string arcrole) {
	//
	//        Networks networks = new NetworksImpl(this);
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = new AllAnalyserImpl(this);
	//            SortedSet<Relationship> relationships = analyser.getRelationshipsFrom(sourceIndex,linkRole,arcrole);
	//            logger.debug("# relationships from = " + relationships.size());
	//            networks.addRelationships(relationships);
	//            return networks;
	//        }
	//        
	//        Fragment source = this.getXMLResource(sourceIndex);
	//
	//        Relationship relationship = null;
	//
	//        // If we have a resource, it could be related directly via arcs to relatives.
	//        if (source.isa(ResourceImpl.class)) {
	//            if ((linkRole == null) || ((Resource) source).getExtendedLink().getLinkRole().equals(linkRole)) {
	//                
	//                std::vector<Arc> arcs = null;
	//                if (arcrole == null) arcs = ((ArcEnd) source).getArcsFrom();
	//                else  arcs = ((ArcEnd) source).getArcsFromWithArcrole(arcrole);
	//
	//                for (const Arc& arc: arcs) {
	//                    std::vector<ArcEnd> targets = arc.getTargetFragments();
	//                    for (ArcEnd end: targets) {
	//                        if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
	//                            Fragment target = ((Locator) end).getTarget();
	//                            relationship = new RelationshipImpl(arc,source,target);
	//                        } else {
	//                            relationship = new RelationshipImpl(arc,source,end);
	//                        }               
	//                        networks.addRelationship(relationship);
	//                    }
	//                }
	//            }
	//        }
	//
	//        HashMap<String,ExtendedLink> links = new HashMap<String,ExtendedLink>();
	//        
	//        // Next get the locators for the fragment to find indirect relatives
	//        std::vector<Locator> locators = source.getReferencingLocators();
	//        
	//        LOCATORS: for (Locator locator: locators) {
	//            if (linkRole != null) {
	//                ExtendedLink link = null;
	//                 std::string parentIndex = locator.getParentIndex();
	//                if (links.containsKey(parentIndex)) {
	//                    link = links.get(parentIndex);
	//                } else {
	//                    link = locator.getExtendedLink();
	//                    links.put(parentIndex,link);
	//                }
	//                if (! link.getLinkRole().equals(linkRole)) continue LOCATORS;
	//            }
	//            std::vector<Arc> arcs = locator.getArcsFromWithArcrole(arcrole);
	//            for (const Arc& arc: arcs) {
	//                std::vector<ArcEnd> targets = arc.getTargetFragments();
	//                for (ArcEnd end: targets) {
	//                    if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
	//                        Fragment target = ((Locator) end).getTarget();
	//                        relationship = new RelationshipImpl(arc,source,target);
	//                    } else {
	//                        relationship = new RelationshipImpl(arc,source,end);
	//                    }
	//                    networks.addRelationship(relationship);
	//                }
	//            }
	//        }
	//        return networks;        
	//
	//    }
	//    
	//    /**
	//     * @see Store#getNetworksTo(String,String,String)
	//     */
	//    public Networks getNetworksTo( std::string targetIndex, std::string linkRole,  std::string arcrole) {
	//        
	//        Networks networks = new NetworksImpl(this);
	//
	//        if (this.isPersistingRelationships()) {
	//            Analyser analyser = new AllAnalyserImpl(this);
	//            SortedSet<Relationship> relationships = analyser.getRelationshipsTo(targetIndex,linkRole,arcrole);
	//            logger.debug("# relationships to = " + relationships.size());
	//            networks.addRelationships(relationships);
	//            return networks;
	//        }
	//
	//        Fragment target = this.getXMLResource(targetIndex);
	//
	//        Relationship relationship = null;
	//
	//        // If we have a resource, it could be related directly via arcs to relatives.
	//        if (target.isa(ResourceImpl.class)) {
	//            if ((linkRole == null) || ((Resource) target).getExtendedLink().getLinkRole().equals(linkRole)) {
	//                std::vector<Arc> arcs = null;
	//                if (arcrole == null) arcs = ((ArcEnd) target).getArcsTo();
	//                else  arcs = ((ArcEnd) target).getArcsToWithArcrole(arcrole);
	//
	//                for (const Arc& arc: arcs) {
	//                    std::vector<ArcEnd> targets = arc.getSourceFragments();
	//                    for (ArcEnd end: targets) {
	//                        if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
	//                            Fragment source = ((Locator) end).getTarget();
	//                            relationship = new RelationshipImpl(arc,source,target);
	//                        } else {
	//                            relationship = new RelationshipImpl(arc,end,target);
	//                        }               
	//                        networks.addRelationship(relationship);
	//                    }
	//                }
	//            }
	//        }
	//
	//        HashMap<String,ExtendedLink> links = new HashMap<String,ExtendedLink>();
	//        
	//        // Next get the locators for the fragment to find indirect relatives
	//        std::vector<Locator> locators = target.getReferencingLocators();
	//        logger.debug("# locators to " + targetIndex + " = " + locators.size());
	//        LOCATORS: for (Locator locator: locators) {
	//            
	//            if (linkRole != null) {
	//                
	//                // Make extended link retrieval use simple caching.
	//                ExtendedLink link = null;
	//                 std::string parentIndex = locator.getParentIndex();
	//                if (links.containsKey(parentIndex)) {
	//                    link = links.get(parentIndex);
	//                } else {
	//                    link = locator.getExtendedLink();
	//                    links.put(parentIndex,link);
	//                }
	//                
	//                // Ignore locator if the link role does not match.
	//                if (! link.getLinkRole().equals(linkRole)) continue LOCATORS;
	//            }
	//            
	//            std::vector<Arc> arcs = locator.getArcsToWithArcrole(arcrole);
	//            logger.debug("# arcs to " + targetIndex + " = " + arcs.size());
	//            for (const Arc& arc: arcs) {
	//                std::vector<ArcEnd> sources = arc.getSourceFragments();
	//                for (ArcEnd end: sources) {
	//                    if (end.getType().equals("org.xbrlapi.impl.LocatorImpl")) {
	//                        Fragment source = ((Locator) end).getTarget();
	//                        relationship = new RelationshipImpl(arc,source,target);
	//                    } else {
	//                        relationship = new RelationshipImpl(arc,end,target);
	//                    }
	//                    networks.addRelationship(relationship);
	//                }
	//            }
	//        }
	//
	//        return networks;        
	//
	//    }    
	//
	//    // The persisted networks analyser
	//    transient private Analyser analyser = null;
	//    
	//    /**
	//     * @see Store#getAnalyser()
	//     */
	//    public Analyser getAnalyser() {
	//        return analyser;
	//    }
	//    
	//    /**
	//     * @see Store#setAnalyser(Analyser)
	//     */
	//    public void setAnalyser(Analyser analyser) {
	//        this.analyser = analyser;
	//    }
	//    
	//    /**
	//     * @see Store#isPersistingRelationships()
	//     */
	//    public bool isPersistingRelationships() {
	//        return (analyser != null);
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getNetworksFrom(java.lang.String, String)
	//     */
	//    public Networks getNetworksFrom( std::string sourceIndex,  std::string arcrole) {
	//        return getNetworksFrom(sourceIndex,null,arcrole);       
	//    }
	//    
	//    /**
	//     * @see Store#getNetworksFrom(String)
	//     */
	//    public Networks getNetworksFrom( std::string sourceIndex) {
	//        return getNetworksFrom(sourceIndex,null,null);       
	//    }    
	//
	//    /**
	//     * @see Store#getNetworksTo(String, String)
	//     */
	//    public Networks getNetworksTo( std::string targetIndex,  std::string arcrole) {
	//        return getNetworksTo(targetIndex,null,arcrole);
	//    }
	//    
	//    /**
	//     * @see Store#getNetworksTo(String)
	//     */
	//    public Networks getNetworksTo( std::string targetIndex) {
	//        return getNetworksTo(targetIndex,null,null);
	//    }
	//
	//    /**
	//     * @see Store#getMissingDocumentURIs()
	//     */
	//    public Set<URI> getMissingDocumentURIs() {
	//        Set<URI> result = new HashSet<URI>();
	//         std::string query = "for $targetURI in #roots#[*/*[@xlink:type='locator' or @xlink:type='simple'], return distinct-values(string($fragment/@targetDocumentURI))";
	//        Set<String> uris = this.queryForStrings(query);
	//        for ( std::string uri: uris) {
	//            try {
	//                result.add(new URI(uri));
	//            } catch (URISyntaxException e) {
	//                throw new XBRLException(uri + " has invalid syntax.",e);
	//            }
	//        }
	//        Set<URI> storedURIs = this.getDocumentURIs();
	//        result.removeAll(storedURIs);
	//        return result;
	//    }
	//
	//    /**
	//     * Set of loaders that are currently loading data into this store.
	//     */
	//    transient private int loadingStatus = 0;
	//    
	//    /**
	//     * This property is used to co-ordinate the document
	//     * loading activities of loaders that are operating in
	//     * parallel on the one data store.  It is used to 
	//     * prevent the same document from being simultaneously
	//     * loaded by several of the loaders.
	//     */
	//    transient private HashMap<URI,LoaderImpl> loadingRights = new HashMap<URI,LoaderImpl>();
	//    
	    /**
	     * @see Store#requestLoadingRightsFor(LoaderImpl, URI)
	     */
	    //public synchronized 
			bool BaseStoreImpl::requestLoadingRightsFor(LoaderImpl& loader, const Poco::URI& document) 
			{
	       // if (document == null) throw new XBRLException("Cannot start loading a document with a null URI");
	        if (loadingRights.find(document) == loadingRights.end()) 
			{
	         //   loadingRights.insert(std::make_pair(document,loader));
	            return true;
	        }
	        if (*loadingRights[document] == loader) 
			{
	            return true;
	        }
	        //logger.debug("Two loaders have been seeking loading rights for " + document);
	        return false;
	    }
	
	    /**
	     * @see Store#recindLoadingRightsFor(LoaderImpl, URI)
	     */
	    //synchronized 
			void BaseStoreImpl::recindLoadingRightsFor(LoaderImpl& loader, const Poco::URI& document) 
			{
	        if (document == NULL) return;
//	        if (loadingRights.find(document) == loadingRights.end()) return;
//	        if (loadingRights[document] == loader) loadingRights.erase(document); //TODO
	    }
	//    
	//    protected void finalize() throws Throwable {
	//        try {
	//            sync();
	//            close();
	//        } finally {
	//            super.finalize();
	//        }
	//    }
	//
	//    /**
	//     * @see java.lang.Object#hashCode()
	//     */
	//    @Override
	//    public int hashCode() {
	//        final int prime = 31;
	//        int result = 1;
	//        result = prime * result
	//                + ((analyser == null) ? 0 : analyser.hashCode());
	//        result = prime * result + ((matcher == null) ? 0 : matcher.hashCode());
	//        result = prime
	//                * result
	//                + ((namespaceBindings == null) ? 0 : namespaceBindings
	//                        .hashCode());
	//        result = prime * result + ((uris == null) ? 0 : uris.hashCode());
	//        return result;
	//    }
	//
	//    /**
	//     * @see java.lang.Object#equals(java.lang.Object)
	//     */
	//    @Override
	//    public bool equals(Object obj) {
	//        if (this == obj)
	//            return true;
	//        if (obj == null)
	//            return false;
	//        if (getClass() != obj.getClass())
	//            return false;
	//        BaseStoreImpl other = (BaseStoreImpl) obj;
	//        if (matcher == null) {
	//            if (other.matcher != null)
	//                return false;
	//        } else if (matcher instanceof InStoreMatcherImpl) {
	//            // Avoid using Matcher.equals() test to prevent infinite recursion.
	//            if (! (other.matcher instanceof InStoreMatcherImpl)) return false;
	//            if (((InStoreMatcherImpl) matcher).getStore() != this) return false;
	//            if (((InStoreMatcherImpl) other.matcher).getStore() != other) return false;
	//        }
	//        if (namespaceBindings == null) {
	//            if (other.namespaceBindings != null)
	//                return false;
	//        } else if (!namespaceBindings.equals(other.namespaceBindings))
	//            return false;
	//        if (uris == null) {
	//            if (other.uris != null)
	//                return false;
	//        } else if (!uris.equals(other.uris))
	//            return false;
	//        return true;
	//    }
	//
	//    /**
	//     * @see Store#isLoading()
	//     */
	//    public synchronized bool isLoading() {
	//        return (loadingStatus > 0);
	//    }

	/**
	* @see Store#startLoading(LoaderImpl)
	*/
	void BaseStoreImpl::startLoading() 
	{
		loadingStatus++;
	}

	/**
	* @see Store#stopLoading(LoaderImpl)
	*/
	//synchronized
	void BaseStoreImpl::stopLoading() 
	{
		loadingStatus--;
	}
	//    
	//    /**
	//     * @see Store#getSchemaContent(String, String)
	//     */
	//    public <F extends SchemaContent> F getSchemaContent( std::string namespace,  std::string name) {
	//        try {
	//
	//            // Get the uris of the containing schemas.
	//             std::string query = "for $root in #roots#[@parentIndex=''] where $root/xbrlapi:data/xsd:schema/@targetNamespace='" + namespace + "' return string($root/@uri)";
	//            Set<String> uris = this.queryForStrings(query);
	//            if (uris.size() == 0) throw new XBRLException("The namespace does not match a schema in the data store.");
	//             std::string uriCriteria = "";
	//            for ( std::string uri: uris) {
	//                uriCriteria += " or @uri='"+uri+"'";
	//            }
	//            uriCriteria = uriCriteria.substring(4);// Delete the first or.
	//            uriCriteria = "(" + uriCriteria + ")";
	//            query = "for $root in #roots#["+uriCriteria+"] where $root/xbrlapi:data/*/@name='" + name + "' return $root";
	//            std::vector<F> candidates = this.<F>queryForXMLResources(query);
	//            if (candidates.size() == 0) throw new XBRLException("The local name does not match content in a schema with the given namespace.");
	//            for (F candidate: candidates) {
	//                Schema schema = candidate.getSchema();
	//                if (namespace.equals(schema.getTargetNamespace()) && schema.isAncestorOf(candidate)) 
	//                    return candidate;
	//            }
	//        } catch (Throwable e) {
	//            logger.error(e.getMessage());
	//        }
	//        return null;
	//    }
	//
	//    /**
	//     * @see org.xbrlapi.data.Store#getSchema(String)
	//     */
	//    public Schema getSchema( std::string targetNamespace) {
	//        if (targetNamespace == null) throw new XBRLException("The target namespace of the schema must not be null.");
	//         std::string query = "for $root in #roots#[@type='"+SchemaImpl.class.getName()+"'] where $root/*/xsd:schema/@targetNamespace='" + targetNamespace + "' return $root";
	//        std::vector<Schema> candidates = this.<Schema>queryForXMLResources(query);
	//        if (candidates.size() == 1) return candidates.get(0);
	//        if (candidates.size() == 0) return null;
	//         std::string message = "";
	//        for (Schema schema: candidates) {
	//            message += ": " + schema.getURI();
	//        }
	//        throw new XBRLException("Schemas with URLs" + message + ", have the target namespace " + targetNamespace);
	//    }
	//
	//    /**
	//     * @param fragmentClass The full name of the class of fragment being handled
	//     * @return a map from fragment index to parent fragment index for all fragments with the given class name (type).
	//     * @throws XBRLException
	//     */
	//    private Map<String,String> getIndexMap(Class<?> fragmentClass) {
	//         std::string query = "for $root in #roots#[@type='" + fragmentClass.getName() + "'] return concat($root/@index,'#',$root/@parentIndex)";
	//        Set<String> pairs = this.queryForStrings(query);
	//        Map<String,String> map = new HashMap<String,String>();
	//        for ( std::string pair: pairs) {
	//            String[] indices = pair.split("#");
	//            map.put(indices[0],indices[1]);
	//        }
	//        return map;
	//    }
	//    
	//    /**
	//     * @see Store#getFactIndices()
	//     */
	//    public Set<String> getFactIndices() {
	//        
	//        // Build a map from fact indices to their parent fragment indices
	//        Map<String,String> factMap = getIndexMap(SimpleNumericItemImpl.class);
	//        factMap.putAll(getIndexMap(FractionItemImpl.class));
	//        factMap.putAll(getIndexMap(NonNumericItemImpl.class));
	//        Map<String,String> tupleMap = getIndexMap(TupleImpl.class);
	//        factMap.putAll(tupleMap);
	//        factMap.putAll(getIndexMap(FractionItemImpl.class));
	//        
	//        // Choose only fact indices where their parent indices are not tuple indices
	//        Set<String> result = new HashSet<String>();
	//        Set<String> factIndices = factMap.keySet();
	//        Set<String> tupleIndices = tupleMap.keySet();
	//        for ( std::string index: factIndices) {
	//            if (! tupleIndices.contains(factMap.get(index))) {
	//                result.add(index);
	//            }
	//        }
	//        return result;
	//    }
	//
	//    /**
	//     * @param fragmentClass The full name of the class of fragment being handled
	//     * @return a map from fragment index to parent fragment index for all fragments with the given class name (type).
	//     * @throws XBRLException
	//     */
	//    private Set<String> getIndexSet(Class<?> fragmentClass) {
	//         std::string query = "for $root in #roots#[@type='" + fragmentClass.getName() + "'] return $root";
	//        Set<String> indices = this.queryForIndices(query);
	//        return indices;
	//    }
	//    
	//    /**
	//     * @see Store#getAllFactIndices()
	//     */
	//    public Set<String> getAllFactIndices() {
	//        Set<String> indices = getIndexSet(SimpleNumericItemImpl.class);
	//        indices.addAll(getIndexSet(FractionItemImpl.class));
	//        indices.addAll(getIndexSet(NonNumericItemImpl.class));
	//        indices.addAll(getIndexSet(TupleImpl.class));
	//        indices.addAll(getIndexSet(FractionItemImpl.class));
	//        return indices;
	//    }
	//
	//    /**
	//     * @see Store#getRootFragmentIndices(String)
	//     */
	//    public Set<String> getRootFragmentIndices( std::string interfaceName)
	//            {
	//         std::string query = "for $root in #roots#[@parentIndex=''] where $root/@type='org.xbrlapi.impl." + interfaceName + "Impl' return $root";
	//        if (interfaceName.indexOf(".") > -1) {
	//            query = "for $root in #roots#[@parentIndex=''] where $root/@type='" + interfaceName + "' return $root";
	//        }
	//        return this.queryForIndices(query);
	//    }    
	//
	//    /**
	//     * @see Store#getFacts(String, String)
	//     */
	//    public list<Fact&> getFacts( std::string namespace,  std::string localname)
	//            {
	//        if (namespace == null) throw new XBRLException("The namespace must not be null.");
	//        if (localname == null) throw new XBRLException("The local name must not be null.");
	//        this.setNamespaceBinding(namespace,"xbrlapi_factNamespacePrefix");
	//         std::string query = "for $root in #roots#[@fact and xbrlapi:data/xbrlapi_factNamespacePrefix:" + localname + "] return $root";
	//		return this.queryForXMLResources(query); 
	//    }
	//    
	//    /**
	//     * @see Store#getFacts(Concept)
	//     */
	//    public list<Fact&> getFacts(const Concept& concept)
	//            {
	//        if (concept == null) throw new XBRLException("The concept must not be null.");
	//        return this.getFacts(concept.getTargetNamespace(), concept.getName());
	//    }    
	//    
}
