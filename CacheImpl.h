#include "Stdafx.h"
#pragma once
#include "Logger.h"

#include "HashFunctions.h"
#include "CacheFile.h"
#include <fstream>
#include <unordered_map>
#include <map>

/**
* Translates 
* 1. original URIs into cache File objects or cache URI objects
* 2. cache URIs into original URI objects
* The translation from cache URIs to original URIs is a hack that
* enables relative URIs in cached files to be identified as such an
* resolved to obtain the original URI of the resource identified
* by the relative URI.
* This class also provides a method for testing if a URI is a cache URI.
* @author Geoffrey Shuetrim (geoff@galexy.net) 
*/


namespace xbrlcapi
{
	class CacheImpl 
	{
		/**
		* The serial version UID.
		* @see 
		* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
		* for information about what changes will require the serial version UID to be
		* modified.
		*/
	private:
		/**
		* Root of the local document cache.
		*/
		CacheFile cacheFile;

		/**
		* The map of local URIs to use in place of
		* original URIs.  The original URI points to the 
		* local URI in the map that is used.
		*/
		std::unordered_map<Poco::URI,Poco::URI> uriMap;

		/**
		* @param file The file to test.
		* @return true if the file is in the cache and false otherwise.
		*/
		bool isCacheFile(CacheFile& file);
	public:
		/**
		* Copy constructor
		* Todo: implement later
		*/
		CacheImpl(const CacheImpl& rhs);
		CacheImpl(std::ostream& os, const std::unordered_map<Poco::URI,Poco::URI>& uri);

		/**
		* Assignment constructor
		* Todo: implement later
		*/
		CacheImpl& operator=(const CacheImpl& rhs);

		/**
		* Constructs a URI translator for usage with a local cache location.
		*/
		CacheImpl();

		/**
		* Constructs a URI translator for usage with a local cache location.
		* @param cacheFile The root directory for the cache.
		* @throws XBRLException if the cacheFile is null or does not exist or cannot be
		* written to or read from.
		*/
		CacheImpl::CacheImpl(CacheFile& rhs);

		/**
		* Constructs a URI translator for usage with a local cache location.
		* @param cacheFile
		* @param uriMap The hash map from original URIs to local URIs.
		* @throws XBRLException if the cacheFile is null or does not exist
		*/
		CacheImpl(CacheFile& cacheFile, const std::unordered_map<Poco::URI, Poco::URI>& uriMap);

		/**
		* @see org.xbrlapi.cache.Cache#isCacheURI(java.net.URI)
		*/
		bool isCacheURI(const Poco::URI& uri);

		/**
		* @see org.xbrlapi.cache.Cache#getCacheURI(java.net.URI)
		*/
		Poco::URI getCacheURI(const Poco::URI& uri);

		bool operator==(const CacheImpl& rhs);

		explicit operator bool();


		/**
		* @see org.xbrlapi.cache.Cache#getOriginalURI(java.net.URI)
		*/
		Poco::URI getOriginalURI(const Poco::URI& uri);

		/**
		* @see org.xbrlapi.cache.Cache#getOriginalURI(File)
		*/
		Poco::URI getOriginalURI(CacheFile& file);

		/**
		* @see org.xbrlapi.cache.Cache#getCacheFile(java.net.URI)
		*/
		boost::filesystem::path getCacheFile(const Poco::URI& uri);

		/**
		* @see org.xbrlapi.cache.Cache#copyToCache(java.net.URI, java.io.File)
		*/
		void copyToCache(const Poco::URI& originalURI, CacheFile& cacheFile);

		/**
		* @see org.xbrlapi.cache.Cache#copyToCache(java.net.URI, java.lang.String)
		*/
		void copyToCache(const Poco::URI& originalURI,  std::string xml);

		/**
		* @see org.xbrlapi.cache.Cache#purge(java.net.URI)
		*/
		void purge(const Poco::URI& uri);

		/**
		* @return the root directory containing the cache.
		*/
		CacheFile& getCacheRoot();

		/**
		* @see Cache#getAllUris(const Poco::URI&)
		*/
		std::vector<Poco::URI> getAllUris(const Poco::URI& uri);

		/**
		* @see java.lang.Object#hashCode()
		*/
		int hashCode();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
		//bool equals(Object obj);
		private:
Logger logger;
};
}
