#pragma once
#include "PimplImpl.h"
#include "Concept.h"
#include "MixedContentResource.h"
#include <string>
#include <list>

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
* TODO Find out why XPointer metadata does not include the id for label resources.
*/
namespace xbrlcapi
{
	class LabelResource : public MixedContentResource 
	{
		struct Impl;
		Pimpl<Impl> pImpl;	
	public:
		LabelResource();
		~LabelResource();
		LabelResource(const LabelResource& rhs);
		LabelResource& operator=(const LabelResource& rhs);
		LabelResource(LabelResource&& rhs);
		LabelResource& operator=(LabelResource&& rhs);
		bool operator==(const LabelResource& rhs);
		bool operator!=(const LabelResource& rhs);

		/**
		* @see org.xbrlapi.LabelResource#getStringValue()
		*/
		std::string getStringValue();

		/**
		* @return the list of Concepts in the data store that have this label.
		* @throws XBRLException
		*/
		std::list<Concept> getConcepts();

	};
}
