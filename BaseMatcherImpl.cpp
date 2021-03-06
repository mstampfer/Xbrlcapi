
#include "BaseMatcherImpl.h"
#include "XBRLException.h"
#include <fstream>

//#include "Signer.h"

namespace xbrlcapi
{

	/**
	
	*/


	Cache BaseMatcherImpl::getCache() 
	{
		return cache;
	}

	void BaseMatcherImpl::setCache(Cache& cache) 
	{
		this->cache = cache;
	}

	//Signer getSigner() 
	//{
	//	return signer;
	//}

	std::vector<std::string> BaseMatcherImpl::getResourceContent(std::ifstream& file)
	{
					try 
					{
		//				BufferedReader reader = new BufferedReader(new FileReader(file));
		std::vector<std::string> lines;
		std::string line;
		/*			while ((line=reader.readLine()) != null) 
		{
		lines.insert(line);
		}*/
		//reader.close();
		return lines;
		} 
		catch (std::ifstream::failure e) 
		{
			throw XBRLException("There was a problem reading from the cache.",e.what());
		}
	}

	std::vector<std::string> BaseMatcherImpl::getResourceContent(const Poco::URI& uri)
	{
		try 
		{
		//InputStream stream = uri.toURL().openStream();
		//BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
		std::vector<std::string> lines;
		std::string line;
		//while ((line=reader.readLine()) != null) 
		//{
		//	lines.insert(line);
		//}
		//reader.close();
		return lines;
		}
		catch (std::ifstream::failure e) 
		{
			throw XBRLException("There was a problem reading from the cache.",e.what());
		}
	}    




	/**
	* @see java.lang.Object#hashCode()
	*/

	//int BaseMatcherImpl::hashCode() 
	//{
	//	const int prime = 31;
	//	int result = 1;
	//	result = prime * result + ((cache == null) ? 0 : cache.hashCode());
	//	result = prime * result + ((signer == null) ? 0 : signer.hashCode());
	//	return result;
	//}
	/* (non-Javadoc)
	* @see java.lang.Object#equals(java.lang.Object)
	*/
	/*		bool BaseMatcherImpl::equals(Object obj) 
	{
	if (this == obj)
	return true;
	if (obj == null)
	return false;
	if (getClass() != obj.getClass())
	return false;
	BaseMatcherImpl other = (BaseMatcherImpl) obj;
	if (cache == null) 
	{
	if (other.cache != null)
	return false;
	} else if (!cache.equals(other.cache))
	return false;
	if (signer == null) 
	{
	if (other.signer != null)
	return false;
	} else if (!signer.equals(other.signer))
	return false;
	return true;
	}   */ 
	void BaseMatcherImpl::setSigner(Signer& signer) 
	{
		this->signer = signer;
	}

	/**
	* @param cache The resource cache to be used by the matcher when accessing
	* resources to determine their signature.
	* @param signature The object used to generate resource signatures.
	* @throws XBRLException if either parameter is null.
	*/
	BaseMatcherImpl::BaseMatcherImpl(Cache& cache, Signer& signature) :  signer(signature) 
	{
		setCache(cache);
	}

	/**
	* @see org.xbrlapi.data.resource.Matcher#getSignature(URI)
	*/
	//std::string BaseMatcherImpl::getSignature(const Poco::URI& uri)
	//{

	//	cache.getCacheURI(uri); // Caches the URI if it is not already cached.
	//	CacheFile cacheFile = cache.getCacheFile(uri);

	//	if (cacheFile) 
	//	{
	//		return getSigner().getSignature(getResourceContent(cacheFile));
	//	}

	//	std::vector<std::string> content;
	//	content.insert(uri.toString());
	//	return getSigner().getSignature(content);

	//}
}
