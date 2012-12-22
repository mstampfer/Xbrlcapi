
#include "HashFunctions.h"
namespace std
{

	size_t hash<Poco::URI>::operator()(const Poco::URI& uri) const
	{
		return hash<string>()(uri.toString());
	}

	bool equal_to<Poco::URI>::operator()( const Poco::URI& lhs, const Poco::URI& rhs ) const
	{
		return equal_to<string>()(lhs.toString(), rhs.toString());
	}

	bool less<Poco::URI>::operator()(const Poco::URI& lhs, const Poco::URI& rhs ) const
	{
		return less<string>()(lhs.toString(), rhs.toString());
	}
}