#include "CacheFile.h"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem.hpp"

namespace xbrlcapi
{
	struct CacheFile::Impl 
	{

		boost::filesystem::path path;
		std::shared_ptr<boost::filesystem::fstream> os;

		Impl(const char* name = "c:\\temp\\default.cache") 
			: path(name),
			os(std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(path)))
		{}

		Impl(const std::string& name) 
			: path(name),
			os(std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(path)))
		{}

		Impl(const Impl& rhs) : path(rhs.path), os(rhs.os)
		{}

		operator bool() const
		{
			if (exists(path) && os) 
				return true;
			else 
				return false;
		}


		std::string getFilename()
		{
			return path.generic_string().data();
		}

		boost::filesystem::path& getPath()
		{
			return path;
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
}