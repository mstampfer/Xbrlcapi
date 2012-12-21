#include "Stdafx.h"
#pragma once
#include "Logger.h"

#include <Poco/URI.h>
#include <string>

/**
* Template specialization for unordered containers
* with Poco::URI template parameters
*/
namespace std
{
	template <> struct hash<Poco::URI>
	{
		typedef size_t result_type;
		typedef Poco::URI argument_type;

		size_t operator()(const Poco::URI& uri) const;
	};

	template <> struct equal_to<Poco::URI>
	{
		typedef size_t result_type;
		typedef Poco::URI argument_type;

		bool operator()( const Poco::URI& lhs, const Poco::URI& rhs ) const;
	};

	template <> struct less<Poco::URI>
	{
		typedef size_t result_type;
		typedef Poco::URI argument_type;

		bool operator()(const Poco::URI& lhs, const Poco::URI& rhs ) const;
	};
}
