#pragma once
#include "PimplImpl.h"
#include <unordered_map>
#include <Poco/URI.h>
#include <boost/filesystem/path.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include "XercesString.h"

namespace xbrlcapi
{
	class CacheFile;
	class Cache //extends Serializable 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* Constructs a URI translator for usage with a local cache location.
		*/
		Cache();
		~Cache();
		Cache(const Cache& rhs);
		Cache& operator=(const Cache& rhs);
		Cache(Cache&& rhs);
		/**
		* Constructs a URI translator for usage with a local cache location.
		* @param cacheFile The root directory for the cache.
		* @throws XBRLException if the cacheFile is null or does not exist or cannot be
		* written to or read from.
		*/
		Cache(CacheFile&);
		/**
		* Constructs a URI translator for usage with a local cache location.
		* @param cacheFile
		* @param uriMap The hash map from original URIs to local URIs.
		* @throws XBRLException if the cacheFile is null or does not exist
		*/
		Cache(CacheFile& cf, const std::unordered_map<Poco::URI, Poco::URI>& map);


		Cache& operator=(Cache&& rhs);
		bool operator==(const Cache& rhs);
		bool operator!=(const Cache& rhs);
		operator bool();

		void setGrammarPool(const std::shared_ptr<xercesc::XMLGrammarPoolImpl>& pool);

		///**
		// * Tests if a URI is a URI of a resource in the local cache.
		// * @param uri The URI to be tested to see if it identifies a 
		// * resource in the local cache.
		// * @return true if and only if the URI is for a resource in the 
		// * local cache.
		// * @throws XBRLException if the URI status as a cache URI cannot be determined.
		// */
		bool isCacheURI(const Poco::URI& uri);

		/**
		* TODO Modify to use the java.net.URIEncoder and java.net.URIDecoder classes.
		* Adds the resource at the original URI to the cache if it is not already cached.
		* @param uri The URI to be translated into a cache URI (if necessary).
		* @return the cache URI corresponding to the provided URI.
		* @throws XBRLException if the resource cannot be cached.
		*/
	//	Poco::URI getCacheURI(const Poco::URI& uri);

		///**
		// * @param uri The URI to be translated into an original URI (if necessary).
		// * @return the original (non-cache) URI corresponding to the provided URI.
		// * @throws XBRLException if a caching operation fails 
		// * or if a cache file cannot be translated into a URI.
		// */
		//public abstract URI getOriginalURI(URI uri);
		//
		///**
		// * @param file The file to be translated into an original URI (if necessary).
		// * @return the original (non-cache) URI corresponding to the provided file.
		// * If the file is not a cache file then the returned URI is just a URI version of the
		// * file.  Otherwise, the original URI is derived from the file.
		// * @throws XBRLException if a caching operation fails 
		// * or if a cache file cannot be translated into a URI.
		// */
		//public abstract URI getOriginalURI(File file);    

		///**
		// * Gets the cache file for an original URI.
		// * @param uri The URI to obtain the cache file for,
		// * @return The File for the provided URI.
		// * @throws XBRLException if the URI cannot be translated into
		// * a location in the local cache.
		// */
		boost::filesystem::path getCachePath(const Poco::URI& uri);

		///**
		// * Copy the original resource into the local cache if the resource exists and is
		// * able to be copied into the cache and does nothing otherwise.  Thus, caching fails
		// * silently.
		// * @param originalURI the URI of the resource to be copied into the cache.
		// * @param cacheFile The file to be used to store the cache version of the resource.
		// */
		XercesString copyToCache(const Poco::URI& uri);


		///**
		// * Copy the original resource into the local cache.
		// * @param originalURI the URI of the resource to be copied into the cache.
		// * @param xml The XML to store in the cache at the given URI.
		// * @throws XBRLException if the resource cannot be copied into the local cache.
		// */
		//public abstract void copyToCache(URI originalURI,  std::string xml)
		//       ;

		///**
		// * Delete a resource from the cache.
		// * @param uri The original or the cache URI.
		// * @throws XBRLException if the cache file cannot be determined.
		// */
		//public abstract void purge(URI uri);
		//
		///**
		// * This method provides a useful means of getting a list of the URIs for
		// * all documents in a branch of the cache.  This can be very helpful when 
		// * trying to reload the cached documents into a data store.
		// * @param uri A URI that corresponds to a directory or file in the cache.
		// * @return the list of original URIs for the files in the specified directory
		// * (or the directory containing the specified file) and the original URIs for 
		// * all of the files in descendant directories of that directory.  
		// * @throws XBRLException
		// */
		//public abstract std::vector<URI> getAllUris(URI uri);
	};
}
