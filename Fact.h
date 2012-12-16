
#include "Stdafx.h"
#pragma once
#include "Logger.h"


//#include "Instance.h"
//#include "Concept.h"

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	struct Instance;
	class Concept;
	class Tuple;

	struct Fact : public Fragment {

		Fact(){}
		/**
		* Return true if the fact is a tuple and false otherwise
		*/
		virtual bool isTuple();

		/**
		* Get the instance that this fact is a part of
		* 
		* @return the xbrl instance fragment
		* @throws XBRLException
		*             if the fact is not part of an instance.
		*/
		virtual Instance getInstance();

		/**
		* Get the tuple that this fact is a part of
		* 
		* @return the xbrl tuple fragment or null if this
		* @throws XBRLException
		*/
		virtual Tuple getTuple();

		/**
		* Get the concept that defines the syntax for this fact.
		* 
		* @return the appropriate concept fragment from the data store.
		* @throws XBRLException
		*             if the concept cannot be found.
		*/
		virtual Concept getConcept();

		/**
		* @return true if the fact is reported with units and false otherwise.
		* @throws XBRLException
		*/
		virtual bool isNumeric();

		/**
		* @return true if the fact is a fraction item type or derived therefrom and
		*         false otherwise.
		* @throws XBRLException
		*/
		virtual bool isFraction();

		/**
		* Return true if the fact has a nill value.
		* 
		* @throws XBRLException
		*/
		virtual bool isNil();

	private:
Logger logger;
};
}
