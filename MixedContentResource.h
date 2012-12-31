#pragma once

#include <string>
#include "Resource.h"
/**

*/
namespace xbrlcapi
{
	class NodeList;
	struct MixedContentResource : public Resource {

		///**
		//* Get the value of the resource as a NodeList containing all of the children 
		//* elements and text nodes nested in the resource.
		//* @return a list of child nodes of the resource including attributes, 
		//* XHTML elements, and text nodes.
		//* @throws XBRLException
		//*/
		//virtual NodeList getContentAsNodeList();

		///**
		//* @return the content of the resource as a string serialising the XHTML content
		//* of the resource.  If the resource only contains a string without XHTML markup
		//* then that string is what is returned.
		//* @throws XBRLException
		//*/
		//virtual std::string getContentAsXHTMLString();
	};
}

