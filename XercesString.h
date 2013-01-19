#pragma once

#include <xercesc/util/XMLString.hpp>
#include <Poco/URI.h>
#include <string>
#include <memory>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif

namespace xbrlcapi
{
	class XercesString
	{
		XMLCh *_wstr;
	public:
		XercesString();
		XercesString(const std::string& str);
		XercesString(const Poco::URI& str);
		XercesString(const char *str);
		XercesString(XMLCh *wstr);
		XercesString(const XMLCh *wstr);
		XercesString(const XercesString &copy);
		~XercesString();
		bool append(const XMLCh *tail);
		bool erase(const XMLCh *head, const XMLCh *tail);
		const XMLCh* begin() const;
		const XMLCh* end() const;
		int size() const;
		XMLCh & operator [] (const int i);
		const XMLCh operator [] (const int i) const;
		operator const XMLCh * () const { return _wstr; };
	};

	std::string toNative(const XMLCh* str);
	std::string toNative(const std::basic_string<XMLCh>& str); 
	typedef XercesString XS;
}