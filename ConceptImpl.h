
#pragma once
#include "Logger.h"

#include <string>
#include <vector>
#include <unordered_set>
#include "Concept.h"
#include "ElementDeclarationImpl.h"

namespace xbrlcapi
{
	/**
		
	*/

	class ConceptImpl : public ElementDeclarationImpl, Concept 
	{

		/**
		* The serial version UID.
		* @see 
		* http://java.sun.com/javase/6/docs/platform/serialization/spec/version.html#6678
		* for information about what changes will require the serial version UID to be
		* modified.
		*/
	private:

	public: 
		/**
		* @see org.xbrlapi.Concept#getPeriodType()
		*/
		std::string getPeriodType();

		/**
		* @see org.xbrlapi.Concept#getBalance()
		*/
		std::string getBalance();

		/**
		* Retrieves the fragment that is the schema for this concept.
		* @return a Schema fragment for the parent schema of this concept.
		* @throws XBRLException
		* @see org.xbrlapi.Concept#getSchema()
		*/
		Schema getSchema();

		/**
		* @see org.xbrlapi.Concept#getFacts()
		*/
		std::vector<Fact&> getFacts();

		/**
		* @see org.xbrlapi.Concept#getRootFacts()
		*/
		std::vector<Fact&> getRootFacts(); 

		/**
		* @see org.xbrlapi.Concept#getFactCount()
		*/
		long getFactCount();

		/**
		* @see org.xbrlapi.Concept#getFactIndices()
		*/
		std::unordered_set<std::string> getFactIndices();    

		/**
		* @see org.xbrlapi.Concept#getPresentationNetworkLinkroles()
		*/
		std::vector<std::string> getPresentationNetworkLinkroles();

		/**
		* @see Concept#isNumeric()
		*/
		bool isNumeric();
		private:
Logger logger;
};
}