#include "CacheFile.h"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem.hpp"
#include <boost/algorithm/string.hpp>
#include "XercesString.h"
#include "XBRLException.h"

namespace xbrlcapi
{
	struct CacheFile::Impl 
	{

		boost::filesystem::path basePath, uriPath, path;
		std::shared_ptr<boost::filesystem::fstream> os;

		Impl(const char* name = "c:\\temp\\default.cache") :
			basePath(name),
			path(name),
			os(std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(name)))
		{
			makeDir(name);

			char scheme[250];
			strcpy(scheme,"file:\\");
			uriPath = strcat(scheme,name);
		}

		Impl(const std::string& name) :
			basePath(name),
			uriPath("file:\\" + name),
			path(name),
			os(std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(name)))
		{
			makeDir(name);
		}

		Impl(const Impl& rhs) : 
			basePath(rhs.basePath), 
			uriPath(rhs.uriPath), 
			path(rhs.path), 
			os(rhs.os)
		{}

		operator bool() const
		{
			if (exists(uriPath) && exists(path) && os) 
				return true;
			else 
				return false;
		}

		void makeDir(std::string p)
		{
			boost::algorithm::replace_first(p, "file://", "");
			boost::algorithm::replace_first(p, "file:/", "");
			boost::algorithm::replace_first(p, "file:\\", "");
			boost::filesystem::path newPath(p);
			try
			{
				boost::system::error_code ec;
				auto status = boost::filesystem::status(newPath,ec);

				switch(status.type())
				{
				case boost::filesystem::file_type::file_not_found:
					boost::filesystem::create_directories(newPath);
					path = newPath;
					break;
				case boost::filesystem::file_type::directory_file:
					break;
				default:
					throw XBRLException("Cannot create cache directory. Error code: " + status.type());
				}
			}
			catch (const boost::filesystem::filesystem_error& e)
			{
				throw XBRLException("Cannot create cache file. ",e.what());
			}
			catch (const std::exception& e)
			{
				throw XBRLException("Cannot create cache file. Filesystem full. ",e.what());
			}
		}


		std::string getFilename()
		{
			return path.generic_string().data();
		}

		boost::filesystem::path& getPath()
		{
			return path;
		}

		void setPath(const boost::filesystem::path& p)
		{
			path = p;
		}

		boost::filesystem::path& getUriPath()
		{
			return uriPath;
		}

		boost::filesystem::path& getBasePath()
		{
			return basePath;
		}

	};

	CacheFile::CacheFile(const char* name) : pImpl(name)
	{}

	CacheFile::CacheFile(const std::string& name) : pImpl(name)
	{}
	CacheFile::~CacheFile() {} 

	CacheFile::CacheFile(const CacheFile& rhs) 
		: pImpl(rhs.pImpl)
	{}

	CacheFile& CacheFile::operator=(const CacheFile& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			////pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	CacheFile::CacheFile(CacheFile&& rhs) 
		: pImpl(std::move(pImpl))
	{}

	CacheFile& CacheFile::operator=(CacheFile&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool CacheFile::operator==(const CacheFile& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool CacheFile::operator!=(const CacheFile& rhs)
	{
		return !this->operator==(rhs);
	}

	CacheFile::operator bool()
	{
		return pImpl->operator bool();
	}

	std::string CacheFile::getFilename()
	{
		return pImpl->getFilename();
	}

	boost::filesystem::path& CacheFile::getPath()
	{
		return pImpl->getPath();
	}

	void CacheFile::setPath(const boost::filesystem::path& p)
	{
		return pImpl->setPath(p);
	}

	boost::filesystem::path& CacheFile::getUriPath()
	{
		return pImpl->getUriPath();
	}

	boost::filesystem::path& CacheFile::getBasePath()
	{
		return pImpl->getBasePath();
	}

	void CacheFile::makeDir(const std::string& newPath)
	{
		pImpl->makeDir(newPath);
	}

}