#pragma once
#include "PimplImpl.h"
#include <string>
#include "CustomType.h"
#include "Networks.h"


namespace xbrlcapi
{
	class ArcroleType : public CustomType
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		ArcroleType();
		~ArcroleType();
		ArcroleType(const ArcroleType& rhs);
		ArcroleType& operator=(const ArcroleType& rhs);
		ArcroleType(ArcroleType&& rhs);
		ArcroleType& operator=(ArcroleType&& rhs);
		bool operator==(const ArcroleType& rhs);
		bool operator!=(const ArcroleType& rhs);

		/**
		* Get the cyclesAllowed attribute value (one of any, directed or none).
		* @return the value of the cyclesAllowed attribute (even if it is not one of the valid values).
		* @throws XBRLException if no attribute value is provided.
		* @see org.xbrlapi.ArcroleType#getCyclesAllowed()
		*/
		std::string getCyclesAllowed();

		/**
		* get the collection of networks expressed using arcs that involve this 
		* arc role.
		*/
		Networks getNetworks();

	};
}
