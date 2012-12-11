#include "Stdafx.h"
#pragma once




/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/
#include "FactDimensionContainer.h"

namespace xbrlcapi
{
	class Entity;
	class Scenario;
	class Period;

	struct Context : public FactDimensionContainer {

		/**
		* Get the entity of the context.
		* @throws XBRLException if the entity is missing or if more than one entity is in the context.
		*/
		virtual Entity getEntity();

		/**
		* Get the period of the context.
		*
		* @throws XBRLException
		*/
		virtual Period getPeriod();

		/**
		* Get the scenario of the context.
		* Returns null if there is no scenario.
		*
		* @throws XBRLException
		*/
		virtual Scenario getScenario();

		/**
		* Tests if the context is c-equal to another context
		* returning true if they are c-equal.
		* See the XBRL 2.1 specification for a definition of c-equal. 
		*
		* @param context The context being compared.
		* @throws XBRLException
		*/
		virtual bool equals(Context context);    

	};
}

