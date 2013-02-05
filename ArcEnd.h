#pragma once

#include <string>
#include <vector>
#include "ExtendedLinkContent.h"

/**

*/
namespace xbrlcapi
{
	class Arc;

	class ArcEnd : public ExtendedLinkContent 
	{

		///**
		//* Get the xlink:label attribute value.
		//* @return the xlink:label attribute value.
		//* @throws XBRLException if the xlink:label attribute does not exist.
		//*/
		//virtual std::string getLabel();

		///**
		//* Get the xlink:role attribute value.
		//* @return the value of the XLink role attribute
		//* on the ArcEnd fragment or null if no such attribute exists.
		//* @throws XBRLException
		//*/
		//virtual std::string getRole();

		///**
		//* Get the id attribute value.
		//* @return the value of the id attribute or null if no
		//* such attribute exists.
		//* @throws XBRLException
		//*/
		//virtual std::string getArcEndId();

		///**
		//* @return Get the list of arcs that are from the arc end.  
		//* The list is empty if there are no arcs from the arc end.
		//*/
		//virtual std::vector<Arc> getArcsFrom();

		///**
		//* @return Get the list of arcs that are to the arc end.  
		//* The list is empty if there are no arcs to the arc end.
		//*/
		//virtual std::vector<Arc> getArcsTo();

		///**
		//* @param arcrole the required arcrole.
		//* @return Get the list of arcs with the given arcrole 
		//* that are from the arc end.  
		//* The list is empty if there are no matching arcs.
		//*/
		//virtual std::vector<Arc> getArcsFromWithArcrole(const std::string& arcrole);



		///**
		//* @param arcrole the required arcrole.
		//* @return Get the list of arcs with the given arcrole 
		//* that are to the arc end.  
		//* The list is empty if there are no matching arcs.
		//*/
		//virtual std::vector<Arc> getArcsToWithArcrole(const std::string& arcrole);

	};
}

