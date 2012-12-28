#pragma once
#include "XML.h"

namespace xbrlcapi
{

	class NonFragmentXMLImpl : public XMLImpl  
	{

	public:
		NonFragmentXML() : XML()
		{}


	protected:
		/**
		* Used to eliminate the builder once the XML resource has been constructed.
		* Call this method at the end of constructors for XML resources that 
		* extend this class.
		* @throws XBRLException
		*/
		void finalizeBuilder()
		{
			setResource(getBuilder().getMetadata());
			setBuilder(NULL);
		}
	};
}