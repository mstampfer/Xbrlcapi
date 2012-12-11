
#include "Stdafx.h"
#pragma once

#include "FactDimensionContainer.h"
/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class NodeList;
	class Measure;

	struct Unit : public FactDimensionContainer {

		/**
		* Get the numerator set of measures for the unit
		* @return the numerator measure set
		* @throws XBRLException
		*/
		virtual NodeList getNumeratorMeasures();

		/**
		* Determines if the unit has a denominator
		* 
		* @return true if the unit has a denominator that has 
		* at least one measure in it, and false otherwise.
		* @throws XBRLException
		*/
		virtual bool hasDenominator();

		/**
		* Get the set of measure elements in the denominator.
		* @return the denominator measure set.
		* @throws XBRLException if the denominator does not exist.
		*/
		virtual NodeList getDenominatorMeasures();

		/**
		* Tests if the unit is u-equal to another unit
		* returning true if they are u-equal and false otherwise
		*
		* @param unit The unit being compared.
		* @return true if the two units are equal and false otherwise
		* @throws XBRLException
		*/
		virtual bool equals(Unit unit);

		/**
		* @return a list of resolved numerator measures.
		* @throws XBRLException
		*/
		virtual std::vector<Measure> getResolvedNumeratorMeasures();

		/**
		* @return a list of resolved denominator measures.
		* If there is no denominator then it returns an empty list.
		* @throws XBRLException
		*/
		virtual std::vector<Measure> getResolvedDenominatorMeasures();


	};
}
