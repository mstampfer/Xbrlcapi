#pragma once
#include "PimplImpl.h"
#include <string>
#include <xercesc/dom/DOMNode.hpp>
#include <fstream>

namespace xbrlcapi
{
	class XMLDOMSerializer 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		XMLDOMSerializer();
		~XMLDOMSerializer();
		XMLDOMSerializer(const XMLDOMSerializer& rhs);
		XMLDOMSerializer& operator=(const XMLDOMSerializer& rhs);
		XMLDOMSerializer(XMLDOMSerializer&& rhs);
		XMLDOMSerializer& operator=(XMLDOMSerializer&& rhs);
		bool operator==(const XMLDOMSerializer& rhs);
		bool operator!=(const XMLDOMSerializer& rhs);

		//   static std::string serialize(const xercesc::DOMNode& what); 
		
		static void serialize(const xercesc::DOMNode& what, std::ofstream& outputStream);
	};
}