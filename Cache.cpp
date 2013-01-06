#include "Cache.h"
#include "CacheFile.h"
#include "HashFunctions.h"
#include "Poco/Path.h"
#include "XBRLException.h"
#include <Poco/Exception.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <memory>
#include <regex>


/**
* Translates 
* 1. original URIs into cache File objects or cache URI objects
* 2. cache URIs into original URI objects
* The translation from cache URIs to original URIs is a hack that
* enables relative URIs in cached files to be identified as such an
* resolved to obtain the original URI of the resource identified
* by the relative URI.
* This class also provides a method for testing if a URI is a cache URI.

*/


namespace xbrlcapi
{
	struct Cache::Impl
	{

		//TODO move to utility class
		std::vector<std::string> split(std::string& input, const char* regex) 
		{
			// passing -1 as the submatch index parameter performs splitting
			const char* cinput = input.c_str();
			std::regex ws_re(regex);
			std::sregex_token_iterator first(input.begin(), input.end(), ws_re, -1);
			std::sregex_token_iterator last;
			std::vector<std::string> v(first, last);
			return v;
		}

		CacheFile cacheFile;
		std::unordered_map<Poco::URI, Poco::URI> uriMap;

		Impl() {}
		Impl(const Impl& rhs) : cacheFile(rhs.cacheFile), uriMap(rhs.uriMap) {}

		Impl(CacheFile& rhs) : cacheFile(rhs)
		{
			if (! exists(cacheFile.getPath())) throw XBRLException("The cache " + cacheFile.getFilename() + " does not exist.");
		}
		Impl(const CacheFile& cf, const std::unordered_map<Poco::URI, Poco::URI>& map) : cacheFile(cf), uriMap(map)
		{}	

		Impl& operator=(Impl&& rhs)
		{
			if (this != &rhs)
			{
				cacheFile = rhs.cacheFile;
			}
			return *this;
		}

		bool operator==(Impl& rhs)
		{
			return cacheFile == rhs.cacheFile;
		}

		bool operator==(const Impl& rhs)
		{
			return ( 
				cacheFile == rhs.cacheFile &&
				uriMap == rhs.uriMap 
				);
		}

		operator bool() 
		{
			return ( 
				cacheFile.getFilename().empty() &&
				uriMap.empty()
				);
		}

		bool isCacheURI(const Poco::URI& uri) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("Checking if " + uri.toString() + " is in the cache.");

			if (! (uri.getScheme() == "file")) 
			{
				logger.debug("Protocol is wrong so not in cache.");
				return false;
			}
			try 
			{
				//logger.debug("The canonical path to the cache root is: " + cacheFile.getCanonicalPath()); TODO
				logger.debug("The path component of the URI being tested is: " + uri.getPath());

				std::string uriPath("");
				try 
				{
					uriPath = uri.getPath(); //TODO is cannonical path?
					logger.debug("Canonicalised URI path is: " + uriPath);
				} 
				catch (const std::exception& couldNotCanonicaliseURIPath) 
				{
					logger.debug("Could not canonicalise URI Path " + uri.getPath() + " so we do not have a cache URI.");
					return false;
				}
				auto frag = boost::filesystem::canonical(cacheFile.getPath()).string();
				if (uriPath.find(frag) == 0) 
				{
					logger.debug("Path is right so is in cache.");
					return true;
				}

			} 
			catch (const std::exception& e) 
			{
				throw XBRLException("The canonical cache root path cannot be determined.",e.what());
			}
			logger.debug("Path is wrong so not in cache.");    	
			return false;
		}

		Poco::URI getCacheURI(const Poco::URI& uri) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("About to get the cache URI for " + uri.toString());

			// First determine the original URI
			Poco::URI originalURI = uri;
			if (isCacheURI(uri)) 
			{
				originalURI = getOriginalURI(uri);
			} 
			else 
			{
				if (uriMap.find(uri) != uriMap.end()) 
				{
					originalURI = uriMap[uri];
				}
			}

			// Second determine the cache file from the original URI
			// so that we can try to cache it if that is necessary.
			try 
			{
				boost::filesystem::path& cacheFilePath = getCacheFile(originalURI);
				if (!cacheFile)
				{
					copyToCache(originalURI,cacheFile); 
				}

				//TODO generalize using following
				//Poco::URI r(cacheFile.getPath().string());
				//r.normalize();
				//return r;


				std::string path(cacheFile.getPath().string());
				boost::replace_all(path,"\\","/");
				boost::replace_all(path,"c:","file:/c:");
				return Poco::URI(path);
			} 
			catch (const XBRLException& e) 
			{
				logger.debug(e.getMessage());
				return originalURI;
			}

		}

		Poco::URI getOriginalURI(const Poco::URI& uri) 
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("Getting original URI for " + uri.toString());

			// Just return the URI if it is not a cache URI
			if (! isCacheURI(uri)) 
			{
				//logger.debug("Returning the URI as it is already original.");
				return uri;
			}

			std::string data = uri.getPath();
			boost::filesystem::path path;
			try 
			{
				path = boost::filesystem::path(data); 
				data = boost::filesystem::canonical(path).string();
			} catch (const boost::filesystem::filesystem_error&  e) 
			{
				throw XBRLException("Canonical path could not be obtained from the URI.",e.what());
			}

			//Eliminate the cacheFile part of the path
			try 
			{
				auto part = boost::filesystem::canonical(cacheFile.getPath()).string().substr(1);
				data = data.replace(data.find(part),part.length(),"").substr(2);
			} 
			catch (const boost::filesystem::filesystem_error& e) 
			{
				throw XBRLException("The original URI could not be determined for " + uri.toString(), e.what());
			}

			std::vector<std::string> parts = split(data, "\\");

			std::string scheme = parts[0];
			if (scheme == "null") scheme = "";
			std::string user = parts[1];
			if (user == "null") user = "";
			std::string host = parts[2];
			if (host == "null") host = "";
			int port = std::stoi(parts[3]);
			std::string query = parts[4];
			if (query == "null") query = "";
			std::string fragment = parts[5];
			if (fragment == "null") fragment = "";
			std::string thePath = "";

			//for (int i=6; i<parts.size(); i++) 
			//{
			//	if (i == 6)
			//		if (File.separator.matches("////"))
			//			if (parts.[i].matches("//w_drive"))
			//				parts[i] = parts[i].substr(0,0) + ":";          
			//	path += "/" + parts.[i];
			//}

			try 
			{
				std::string authority;
				if (user != "")
					authority = user + "@" + host + ":" + std::to_string(port);
				else
					authority = host + ":" + std::to_string(port);
				Poco::URI originalURI(scheme, authority, path.string(), query, fragment);
				logger.debug("Got the original URI " + originalURI.toString());
				return originalURI;
			} 
			catch (const Poco::SyntaxException& e) 
			{
				throw XBRLException("Malformed original URI.",e);
			}
		}

		///**
		//* @param file The file to test.
		//* @return true if the file is in the cache and false otherwise.
		//*/
		//private bool isCacheFile(File file) 
		//{
		//	File parent = file;
		//	while (parent != null) 
		//{
		//		if (parent.equals(this.cacheFile)) 
		//{
		//			return true;
		//		}
		//		parent = parent.getParentFile();
		//	}
		//	return false;
		//}

		///**
		//* @see org.xbrlapi.cache.Cache#getOriginalURI(File)
		//*/
		//public URI getOriginalURI(File file) 
		//{

		//	logger.debug("Getting original URI for " + file);

		//	// Just return the URI version of the file if it is not a cache file
		//	if (! isCacheFile(file)) 
		//{
		//		return file.toURI();
		//	}

		//	 std::string data = "";
		//	try 
		//{
		//		data = file.getCanonicalPath();
		//	} catch (IOException e) 
		//{
		//		throw XBRLException("Canonical path could not be obtained from the URI.",e);
		//	}

		//	// Eliminate the cacheFile part of the path
		//	try 
		//{
		//		data = data.replace(cacheFile.getCanonicalPath().toString().substring(1),"").substring(2);
		//	} catch (IOException e) 
		//{
		//		throw XBRLException("The original URI could not be determined for " + file);
		//	}

		//	List<String> parts = new Vector<String>();
		//	logger.debug(data);
		//	StringTokenizer tokenizer = new StringTokenizer(data, File.separator);
		//	while (tokenizer.hasMoreTokens()) 
		//{
		//		 std::string token = tokenizer.nextToken();
		//		if (token != null)
		//			if (! token.equals("")) 
		//{
		//				logger.debug(token);
		//				parts.add(token);
		//			}
		//	}

		//	 std::string scheme = parts.get(0);
		//	if (scheme.equals("null")) scheme = null;
		//	 std::string user = parts.get(1);
		//	if (user.equals("null")) user = null;
		//	 std::string host = parts.get(2);
		//	if (host.equals("null")) host = null;
		//	int port = new Integer(parts.get(3)).intValue();
		//	 std::string query = parts.get(4);
		//	if (query.equals("null")) query = null;
		//	 std::string fragment = parts.get(5);
		//	if (fragment.equals("null")) fragment = null;

		//	 std::string path = "";
		//	for (int i=6; i<parts.size(); i++) 
		//{
		//		if (i == 6)
		//			if (File.separator.matches("////"))
		//				if (parts.get(i).matches("//w_drive"))
		//					parts.set(i,parts.get(i).substring(0,1) + ":");          
		//		path += "/" + parts.get(i);
		//	}

		//	try 
		//{
		//		URI originalURI = new URI(scheme, user,host, port, path,query,fragment);
		//		logger.debug("Got the original URI " + originalURI);
		//		return originalURI;
		//	} catch (URISyntaxException e) 
		//{
		//		throw XBRLException("Malformed original URI.",e);
		//	}

		//}    



		boost::filesystem::path getCacheFile(const Poco::URI& uri)
		{
			log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
			logger.debug("Getting the cache file for " + uri.toString());
			std::string scheme = uri.getScheme();
			std::string user = uri.getUserInfo();
			std::string host = uri.getHost();
			std::string port = std::to_string(uri.getPort());
			std::string path = uri.getPath();
			std::string query = uri.getQuery();
			std::string fragment = uri.getFragment();

			boost::filesystem::path absolutePath = cacheFile.getPath();
			absolutePath /= boost::filesystem::path(user);
			absolutePath /= boost::filesystem::path(user);
			absolutePath /= boost::filesystem::path(host);
			absolutePath /= boost::filesystem::path(port);
			absolutePath /= boost::filesystem::path(query);
			absolutePath /= boost::filesystem::path(fragment);

			std::vector<std::string> parts = split(path, "/");
			std::regex pattern("\w\Q:\E"); 
			std::smatch results;

			for (auto & part : parts)
			{
				if ( std::regex_search(part, results, pattern))
					part += part.substr(0,1) + "_drive"; 
				absolutePath /=  boost::filesystem::path(part);
			}

			try 
			{
				log4cpp::Category&  logger = log4cpp::Category::getInstance( std::string("log_sub1") );
				logger.debug("Got cacheFile" + cacheFile);
				return absolutePath;
			} 
			catch (std::exception& e) 
			{
				throw XBRLException(uri.toString() + " cannot be translated into a location in the cache", e.what());
			}

		}

		void copyToCache(const Poco::URI& originalURI, const CacheFile& cacheFile) 
		{

			//	// If necessary, create the directory to contain the cached resource
			//	File parent = cacheFile.getParentFile();
			//	if (parent != null) parent.mkdirs();

			//	try 
			//{

			//		// Establish the connection to the original CacheURIImpl data source
			//		InputStream inputStream = null;

			//		if (originalURI.getScheme().equals("file")) 
			//{
			//			 std::string path = originalURI.getPath();
			//			File f = new File(path);
			//			inputStream = new FileInputStream(f);
			//		} else 
			//{
			//			inputStream =  originalURI.toURL().openConnection().getInputStream();
			//		}

			//		BufferedInputStream bis = new BufferedInputStream(inputStream);

			//		// Establish the connection to the destination file
			//		FileOutputStream fos = new FileOutputStream(cacheFile);
			//		BufferedOutputStream bos = new BufferedOutputStream(fos);

			//		// Write the source file to the destination file
			//		int bite = bis.read();
			//		while (bite != -1) 
			//{
			//			bos.write(bite);
			//			bite = bis.read();
			//		}

			//		// Clean up the reader and writer
			//		bos.flush();
			//		bis.close();
			//		bos.close();

			//	} catch (java.net.NoRouteToHostException e) 
			//{
			//		logger.debug(e.getMessage());
			//	} catch (FileNotFoundException e) 
			//{
			//		logger.debug(e.getMessage());
			//	} catch (IOException e) 
			//{
			//		logger.debug(e.getMessage());
			//	}
		}

		void copyToCache(const Poco::URI& originalURI,  const std::string& xml) 
		{

			//	logger.debug("Attempting to cache a string XML document using : " + originalURI);

			//	File cacheFile = this.getCacheFile(originalURI);

			//	logger.debug("The cache file is : " + cacheFile.toString());

			//	// If necessary, create the directory to contain the cached resource
			//	File parent = cacheFile.getParentFile();
			//	if (parent != null) parent.mkdirs();

			//	try 
			//{
			//		FileWriter out = new FileWriter(cacheFile);

			//		out.write(xml);
			//		out.close();		
			//	} catch (IOException e) 
			//{
			//		throw XBRLException("The  std::string resource could not be cached.",e);
			//	}
		}    

		///**
		//* @see org.xbrlapi.cache.Cache#purge(java.net.URI)
		//*/
		//public void purge(URI uri) 
		//{
		//	File file = this.getCacheFile(uri);
		//	file.delete();
		//	logger.debug("Purged " + file);
		//}

		///**
		//* @return the root directory containing the cache.
		//*/
		//public File getCacheRoot() 
		//{
		//	return this.cacheFile;
		//}

		///**
		//* @see Cache#getAllUris(URI)
		//*/
		//public std::vector<URI> getAllUris(URI uri) 
		//{

		//	// Get the relevant directory in the cache.
		//	File file = this.getCacheFile(uri);
		//	while (!file.isDirectory() && file.getParentFile() != null) 
		//{
		//		file = file.getParentFile();
		//	}

		//	List<URI> result = new Vector<URI>();
		//	FileFilter fileFilter = new FileFilter() 
		//{
		//		public bool accept(File file) 
		//{
		//			return (!file.isDirectory());
		//		}

		//};
		//	for (File childFile: file.listFiles(fileFilter)) 
		//{
		//		result.add(this.getOriginalURI(childFile));
		//	}

		//	FileFilter directoryFilter = new FileFilter() 
		//{
		//		public bool accept(File file) 
		//{
		//			return (file.isDirectory());
		//		}
		//};
		//	for (File childDirectory: file.listFiles(directoryFilter)) 
		//{
		//		result.addAll(getAllUris(this.getOriginalURI(childDirectory)));
		//	}
		//	return result;
		//}

		///**
		//* @see java.lang.Object#hashCode()
		//*/
		//@Override
		//	public int hashCode() 
		//{
		//		final int prime = 31;
		//		int result = 1;
		//		result = prime * result
		//			+ ((cacheFile == null) ? 0 : cacheFile.hashCode());
		//		result = prime * result + ((uriMap == null) ? 0 : ((Map<URI,URI>) uriMap).hashCode());
		//		return result;
		//}

		///**
		//* @see java.lang.Object#equals(java.lang.Object)
		//*/
		//@Override
		//	public bool equals(Object obj) 
		//{
		//		if (this == obj)
		//			return true;
		//		if (obj == null)
		//			return false;
		//		if (getClass() != obj.getClass())
		//			return false;
		//		Impl other = (Impl) obj;
		//		if (cacheFile == null) 
		//{
		//			if (other.cacheFile != null)
		//				return false;
		//		} else if (!cacheFile.equals(other.cacheFile))
		//			return false;
		//		if (uriMap == null) 
		//{
		//			if (other.uriMap != null)
		//				return false;
		//		} else if (!((Map<URI,URI>) uriMap).equals((other.uriMap)))
		//			return false;
		//		return true;
		//}
	};

	Cache::Cache() {}

	Cache::~Cache() {}

	Cache::Cache(const Cache& rhs) 
		: pImpl(rhs.pImpl)
	{}

	Cache& Cache::operator=(const Cache& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Cache::Cache(Cache&& rhs) 
		: pImpl(std::move(rhs.pImpl)) 
	{}

	Cache& Cache::operator=(Cache&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	Cache::Cache(CacheFile& cacheFile) 
		: pImpl(cacheFile)
	{}

	Cache::Cache(CacheFile& cacheFile, const std::unordered_map<Poco::URI, Poco::URI>& map) 
		: pImpl(cacheFile, map)
	{}

	bool Cache::operator==(const Cache& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Cache::operator!=(const Cache& rhs)
	{
		return !this->operator==(rhs);
	}


	Cache::operator bool()
	{
		return pImpl->operator bool();
	}

	Poco::URI Cache::getCacheURI(const Poco::URI& uri)
	{
		return pImpl->getCacheURI(uri);
	}

	bool Cache::isCacheURI(const Poco::URI& uri) 
	{
		return pImpl->isCacheURI(uri);
	}

	boost::filesystem::path Cache::getCacheFile(const Poco::URI& uri)
	{
		return pImpl->getCacheFile(uri);
	}

}