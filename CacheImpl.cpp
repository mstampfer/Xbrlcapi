#include "Stdafx.h"
#include "CacheImpl.h"
#include "Poco/Path.h"
#include "CacheFile.h"
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
* @author Geoffrey Shuetrim (geoff@galexy.net) 
*/


namespace xbrlcapi
{

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

	CacheImpl::CacheImpl(const CacheImpl& ) {}
	/**
	* Assignment constructor
	* Todo: implement later
	*/
	CacheImpl& CacheImpl::operator=(const CacheImpl& rhs)
	{
		return *this;
	}
	/**
	* Constructs a URI translator for usage with a local cache location.
	*/
	CacheImpl::CacheImpl() {}
	/**
	* Constructs a URI translator for usage with a local cache location.
	* @param cacheFile The root directory for the cache.
	* @throws XBRLException if the cacheFile is null or does not exist or cannot be
	* written to or read from.
	*/
	CacheImpl::CacheImpl(CacheFile& rhs) 
	{
		//if (cacheFile == null) throw new XBRLException("The cache root is null.");
		//if (! cacheFile.exists()) throw new XBRLException("The cache " + cacheFile + " does not exist.");
		//if (! cacheFile.canWrite()) throw new XBRLException("The cache " + cacheFile + " cannot be written to.");
		//if (! cacheFile.canRead()) throw new XBRLException("The cache " + cacheFile + " cannot be read.");
		//cacheFile = rhs;
	}

	/**
	* Constructs a URI translator for usage with a local cache location.
	* @param cacheFile
	* @param uriMap The hash map from original URIs to local URIs.
	* @throws XBRLException if the cacheFile is null or does not exist
	*/
	CacheImpl::CacheImpl(CacheFile& cf, const std::unordered_map<Poco::URI, Poco::URI>& map)
	{
		cacheFile = std::move(cf);
		uriMap = map;
	}	

	/**
	* @see org.xbrlapi.cache.Cache#isCacheURI(java.net.URI)
	*/
	bool CacheImpl::isCacheURI(const Poco::URI& uri) 
	{
		//			logger.debug("Checking if " + uri + " is in the cache.");

		if (! (uri.getScheme() == "file")) 
		{
			//				logger.debug("Protocol is wrong so not in cache.");
			return false;
		}
		//try 
		//{
		//logger.debug("The canonical path to the cache root is: " + cacheFile.getCanonicalPath());
		//logger.debug("The path component of the URI being tested is: " + uri.getPath());

		std::string uriPath("");
		//try 
		//{
		uriPath = uri.getPath(); //TODO is cannonical path?
		//				logger.debug("Canonicalised URI path is: " + uriPath);
		//} catch (Exception couldNotCanonicaliseURIPath) 
		//{
		//	logger.debug("Could not canonicalise URI Path " + uri.getPath() + " so we do not have a cache URI.");
		//	return false;
		//}
		auto frag = boost::filesystem::canonical(cacheFile.getPath()).string();
		if (uriPath.find(frag) == 0) 
		{
			//logger.debug("Path is right so is in cache.");
			return true;
		}

		//} catch (Exception e) 
		//{
		//	throw new XBRLException("The canonical cache root path cannot be determined.",e);
		//}
		//logger.debug("Path is wrong so not in cache.");    	
		return false;
	}

	/**
	* @see org.xbrlapi.cache.Cache#getCacheURI(java.net.URI)
	*/
	Poco::URI CacheImpl::getCacheURI(const Poco::URI& uri) 
	{

		// logger.debug("About to get the cache URI for " + uri);

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
		//try 
		//{
		boost::filesystem::path& cacheFilePath = getCacheFile(originalURI);
		if (!cacheFile)
		{
			//copyToCache(originalURI,cacheFile); TODO
		}
		return Poco::URI(cacheFile.getPath().string());
		//} catch (XBRLException e) 
		//{
		//	logger.debug(e.getMessage());
		//	return originalURI;
		//}

	}
	/**
	* @see org.xbrlapi.cache.Cache#getOriginalURI(java.net.URI)
	*/
	Poco::URI CacheImpl::getOriginalURI(const Poco::URI& uri) 
	{

		//			logger.debug("Getting original URI for " + uri);

		// Just return the URI if it is not a cache URI
		if (! isCacheURI(uri)) 
		{
			//logger.debug("Returning the URI as it is already original.");
			return uri;
		}

		std::string data = uri.getPath();

		//try 
		//{
		Poco::Path path(data); 
		data = path.absolute(path).toString();
		//} catch (IOException e) 
		//{
		//	throw new XBRLException("Canonical path could not be obtained from the URI.",e);
		//}

		// Eliminate the cacheFile part of the path
		//try 
		//{
		auto part = boost::filesystem::canonical(cacheFile.getPath()).string().substr(1);
		data = data.replace(data.find(part),part.length(),"").substr(2);
		//} catch (IOException e) 
		//{
		//	throw new XBRLException("The original URI could not be determined for " + uri);
		//}

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

		//try 
		//{
		std::string authority;
		if (user != "")
			authority = user + "@" + host + ":" + std::to_string(port);
		else
			authority = host + ":" + std::to_string(port);
		Poco::URI originalURI(scheme, authority, path.toString(), query, fragment);
		//logger.debug("Got the original URI " + originalURI);
		return originalURI;
		//} catch (URISyntaxException e) 
		//{
		//	throw new XBRLException("Malformed original URI.",e);
		//}
	}

	///**
	//* @param file The file to test.
	//* @return true if the file is in the cache and false otherwise.
	//*/
	//private bool CacheImpl::isCacheFile(File file) 
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
	//public URI CacheImpl::getOriginalURI(File file) 
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
	//		throw new XBRLException("Canonical path could not be obtained from the URI.",e);
	//	}

	//	// Eliminate the cacheFile part of the path
	//	try 
	//{
	//		data = data.replace(cacheFile.getCanonicalPath().toString().substring(1),"").substring(2);
	//	} catch (IOException e) 
	//{
	//		throw new XBRLException("The original URI could not be determined for " + file);
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
	//		throw new XBRLException("Malformed original URI.",e);
	//	}

	//}    

	/**
	* @see org.xbrlapi.cache.Cache#getCacheFile(java.net.URI)
	*/

//	logger.debug("Getting the cache file for " + uri);
boost::filesystem::path CacheImpl::getCacheFile(const Poco::URI& uri)
{
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
        //StringTokenizer tokenizer = new StringTokenizer(path, "/");
        //while (tokenizer.hasMoreTokens()) {
        //    std:.string token = tokenizer.nextToken();
        //    if (File.separator.equals("\\")) // If on windows a : is not allowed in a directory name so use _drive instead
        //        if (token.matches("\\w\\Q:\\E"))
        //            token = token.substring(0,1) + "_drive";
        //    if (token != null)
        //        if (! token.equals(""))
        //            relativeLocation = relativeLocation.concat(s+token);
        //}

        //try {
        //    logger.debug("Got cacheFile" + cacheFile);
            return absolutePath;
        //} catch (Exception e) {
        //    throw new XBRLException(uri + " cannot be translated into a location in the cache");
        //}
    	
    }

	///**
	//* @see org.xbrlapi.cache.Cache#copyToCache(java.net.URI, java.io.File)
	//*/
	//public void copyToCache(URI originalURI, File cacheFile) 
	//{

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
	//}

	///**
	//* @see org.xbrlapi.cache.Cache#copyToCache(java.net.URI, java.lang.String)
	//*/
	//public void CacheImpl::copyToCache(URI originalURI,  std::string xml) 
	//{

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
	//		throw new XBRLException("The  std::string resource could not be cached.",e);
	//	}
	//}    

	///**
	//* @see org.xbrlapi.cache.Cache#purge(java.net.URI)
	//*/
	//public void CacheImpl::purge(URI uri) 
	//{
	//	File file = this.getCacheFile(uri);
	//	file.delete();
	//	logger.debug("Purged " + file);
	//}

	///**
	//* @return the root directory containing the cache.
	//*/
	//public File CacheImpl::getCacheRoot() 
	//{
	//	return this.cacheFile;
	//}

	///**
	//* @see Cache#getAllUris(URI)
	//*/
	//public std::vector<URI> CacheImpl::getAllUris(URI uri) 
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
	//	};
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
	//	};
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
	//	public int CacheImpl::hashCode() 
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
	//	public bool CacheImpl::equals(Object obj) 
	//{
	//		if (this == obj)
	//			return true;
	//		if (obj == null)
	//			return false;
	//		if (getClass() != obj.getClass())
	//			return false;
	//		CacheImpl other = (CacheImpl) obj;
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
}
