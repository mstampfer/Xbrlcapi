#pragma once
#include "PimplImpl.h"
#include "ElementDeclaration.h"
#include <string>

namespace xbrlcapi
{
	struct Fact;
	class Concept : public ElementDeclaration 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Concept();
		~Concept();
		Concept(const Concept& rhs);
		Concept& operator=(const Concept& rhs);
		Concept(Concept&& rhs);
		Concept& operator=(Concept&& rhs);
		bool operator==(const Concept& rhs);
		bool operator!=(const Concept& rhs);

		/**
		* @return the period attribute value (one of instant or duration) for concepts 
		* in the XBRL item substitution group and null for tuple concepts.
		* @throws XBRLException if the periodType is missing for concepts in 
		* the XBRL item substitution group.
		*/
		virtual std::string getPeriodType();

		/**
		* Get the concept's balance, one of debit or credit
		* or null if the balance is not defined.
		*
		* @throws XBRLException
		*/
		virtual std::string getBalance();

		/**
		* @return true if the concept is numeric.
		* @throws XBRLException
		*/
		virtual bool isNumeric();

		/**
		* @return the list of facts in the data store giving values for this concept
		* @throws XBRLException
		*/
		virtual std::vector<Fact> getFacts();

		/**
		* @return the list of root-level facts in the data store giving values for
		*         this concept. Root-level facts are facts that are children of
		*         XBRL-instance elements.
		* @throws XBRLException
		*/
		virtual std::vector<Fact> getRootFacts();    

		/**
		* @return the number of facts for this concept
		* @throws XBRLException
		*/
		virtual long getFactCount();

		/**
		* @return the set of indices of facts for this concept
		* @throws XBRLException
		*/
		virtual std::unordered_set<std::string> getFactIndices();    

		/**
		* @return the list of extended link roles for the 
		* presentation networks involving this concept as a 
		* source or a target.
		* @throws XBRLException
		*/
		virtual std::vector<std::string> getPresentationNetworkLinkroles();
	};  
}
