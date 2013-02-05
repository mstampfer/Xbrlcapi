#pragma once
#include "PimplImpl.h"
#include <string>
#include "Fragment.h"
#include "UsedOn.h"

namespace xbrlcapi
{

	class CustomType : public Fragment 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		CustomType();
		~CustomType();
		CustomType(const CustomType& rhs);
		CustomType& operator=(const CustomType& rhs);
		CustomType(CustomType&& rhs);
		CustomType& operator=(CustomType&& rhs);
		bool operator==(const CustomType& rhs);
		bool operator!=(const CustomType& rhs);

		/**
		* Get the id of the customType.
		* @return the id of the custom type or null if none is provided
		* @throws XBRLException
		* @see org.xbrlapi.CustomType#getCustomTypeId()
		*/
		std::string getCustomTypeId();

		/**
		* Get the custom URI being defined.
		* @return the custom URI being defined.
		* @throws XBRLException if the custom URI is not specified.
		* @see org.xbrlapi.CustomType#getCustomURI()
		*/
		std::string getCustomURI();

		/**
		* @see org.xbrlapi.CustomType#getDefinition()
		*/
		std::string  getDefinition();

		/**
		* @see org.xbrlapi.CustomType#isUsedCorrectly(Fragment)
		*/
		bool isUsedCorrectly(const Fragment& fragment);

		/**
		* @see org.xbrlapi.CustomType#isUsedOn(String,String)
		*/
		bool isUsedOn(const std::string& Namespace, const std::string& localname);

		/**
		* @see org.xbrlapi.CustomType#getUsedOns()
		*/
		std::list<UsedOn> getUsedOns();

	};
}