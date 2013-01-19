#pragma once
#include "PimplImpl.h"
#include <string>
#include "boost/filesystem.hpp"

namespace xbrlcapi
{
	class CacheFile
	{
	private:
		struct Impl;
		Pimpl<Impl> pImpl;

	public:
		~CacheFile();
		CacheFile(const char* name = "c:\\temp\\default.cache");
		CacheFile(const std::string& name);

		CacheFile(const CacheFile& rhs);
		CacheFile& operator=(const CacheFile& rhs);
		CacheFile(CacheFile&& rhs);
		CacheFile& operator=(CacheFile&& rhs);
		bool operator==(const CacheFile& rhs);
		bool operator!=(const CacheFile& rhs);

		operator bool() const;
		std::string getFilename();
		boost::filesystem::path& getPath();
		void setPath(const boost::filesystem::path& p);
		boost::filesystem::path& getUriPath();
		boost::filesystem::path& getBasePath();
		void makeDir(const std::string& newPath);
		operator bool();
	};
}