#include <string>
#pragma once

namespace xbrlcapi
{
	/**
	* Helper to convert const char * to wide character 
	*
	*/
	const std::wstring getWC(const char *c)
	{
		const size_t cSize = strlen(c)+1;
		std::wstring wc( cSize, L'#' );
		mbstowcs( &wc[0], c, cSize);
		return wc;
	}

	const std::wstring getWC(const std::string s)
	{
		const size_t cSize = s.length()+1;
		std::wstring wc( cSize, L'#' );
		mbstowcs( &wc[0], s.c_str(), cSize);
		return wc;
	}
}