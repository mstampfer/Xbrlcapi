

#pragma once


#include "Fragment.h"
#include <string>
#include <vector>

namespace xbrlcapi
{

	/**

	*/
	class Title;
	struct Xlink : public Fragment {

		/**
		* Get the xlink type (The xxlink:type attribute value).
		* This is one of simple or extended
		*
		* @throws XBRLException
		*/
		//virtual std::string getXlinkType();



		///**
		//* Get the  title (The xlink:title attribute value).
		//* @return the value of the xlink:title attribute or null if none is supplied. 
		//* @throws XBRLException
		//*/
		//virtual std::string getTitleAttribute();    



		///**
		//* Get a list of titles (The xlink:title children elements).
		//* @return a fragment list of title elements or null if there are none.
		//* @throws XBRLException
		//*/
		//virtual std::vector<Title> getTitleElements();

		///**
		//* Get a list of titles (The xlink:title children elements).
		//* Returns null if there are no title children elements.
		//*
		//* @param index The index of the required title element
		//* @return The specified title fragment
		//* @throws XBRLException
		//*/
		//virtual Title getTitleElement(int index);

		///**
		//* Get a non-xlink attribute value.
		//* @param namespace The namespace of the attribute to retrieve
		//* @param localname The local name of the attribute to retrieve
		//* @throws XBRLException if the namespace URI is for the XLink namespace.
		//*/
		//virtual std::string getAttribute(const std::string& Namespace, const std::string& localname);

		///**
		//* Get a no-namespace attribute value.
		//* @param name The name of the no-namespace attribute to retrieve
		//* @throws XBRLException
		//*/
		//virtual std::string getAttribute(const std::string& name);
	};
}
