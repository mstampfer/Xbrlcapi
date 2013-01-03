#pragma once
#include "PimplImpl.h"
#include "Fragment.h"
#include "ElementDeclaration.h"

namespace xbrlcapi
{
	class ReferencePart : public Fragment 
	{
		struct Impl;
		Pimpl<Impl> pImpl;	
	public:
		ReferencePart();
		~ReferencePart();
		ReferencePart(const ReferencePart& rhs);
		ReferencePart& operator=(const ReferencePart& rhs);
		ReferencePart(ReferencePart&& rhs);
		ReferencePart& operator=(ReferencePart&& rhs);
		bool operator==(const ReferencePart& rhs);
		bool operator!=(const ReferencePart& rhs);

		/**
		* Get the value of the reference part. 
		* @return The value of the reference part with spaces 
		* trimmed from the front and end.
		* @throws XBRLException
		*/
		std::string getValue();

		/**
		* Currently implemented by a brute force search of the 
		* reference part declarations with the given local name.
		* @return an XML Schema declaration of the reference part.  If more than
		* one such declaration is in the data store then the declaration returned
		* is application dependent.
		* @throws XBRLException if no declarations can be found in the data store.
		*/
		ElementDeclaration getDeclaration();


	};
}
