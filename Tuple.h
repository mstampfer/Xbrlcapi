#pragma once
#include "PimplImpl.h"
#include <string>
#include <list>
#include "Fact.h"

namespace xbrlcapi
{
	class Tuple : public Fact
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Tuple();
		~Tuple();
		Tuple(const Tuple& rhs);
		Tuple& operator=(const Tuple& rhs);
		Tuple(Tuple&& rhs);
		Tuple& operator=(Tuple&& rhs);
		bool operator==(const Tuple& rhs);
		bool operator!=(const Tuple& rhs);
		/**
		* Get the list of child facts
		* @return list of child fact fragments for the tuple
		* @throws XBRLException
		* @see org.xbrlapi.Tuple#getChildFacts()
		*/
		std::list<Fact> getChildFacts();

		/**
		* Get a list of facts matching the specified fact name.
		* @param namespace The namespace of the desired facts
		* @param name The local name of the desired facts
		* @return the specified facts.
		* @throws XBRLException
		* @see org.xbrlapi.Tuple#getChildFacts(String, String)
		*/
		std::list<Fact> getChildFacts(const std::string& Naamespace, const std::string& name);

		/**
		* Get a list of facts matching the specified fact name and context id.
		* @param namespace The namespace of the desired facts
		* @param name The local name of the desired facts
		* @param contextRef The value of the context reference for the required facts.
		* @return the specified facts.
		* @throws XBRLException
		* @see org.xbrlapi.Tuple#getChildFacts(String, String, String)
		*/
		std::list<Fact> getChildFacts(const std::string& Namespace, const std::string& name, const std::string& contextRef) ;
	};
}