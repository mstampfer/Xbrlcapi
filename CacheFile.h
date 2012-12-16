#include "stdafx.h"
#pragma once
#include "Logger.h"
#include "boost/filesystem/fstream.hpp"
#include <string>
#include <memory>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem.hpp"

namespace xbrlcapi
{
	class CacheFile
	{
	private:
		boost::filesystem::path path;
		std::unique_ptr<boost::filesystem::fstream> os;
		CacheFile(const CacheFile&);
		CacheFile& operator=(const CacheFile&);

	public:
		CacheFile(const char* name = "c:\\temp\\default.cache") : path(name)
		{
			os = std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(path));
		}
		CacheFile(const std::string& name) : path(name)
		{
			os = std::unique_ptr<boost::filesystem::fstream>(new boost::filesystem::fstream(path));
		}

		CacheFile(CacheFile&& rhs)
		{
			os = std::move(rhs.os);
			path = std::move(rhs.path);
		}

		CacheFile& operator=(CacheFile&& rhs)
		{
			if (os != rhs.os)
			{
				os = std::move(rhs.os);
				path = std::move(rhs.path);
			}
			return *this;
		}

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
	private:
Logger logger;
};
}