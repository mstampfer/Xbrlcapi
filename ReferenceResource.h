#pragma once
#include "PimplImpl.h"
#include "ReferencePart.h"
#include "MixedContentResource.h"
#include <string>
#include <list>

namespace xbrlcapi
{
	class ReferenceResource : public MixedContentResource 
	{
		struct Impl;
		Pimpl<Impl> pImpl;	
	public:
		ReferenceResource();
		~ReferenceResource();
		ReferenceResource(const ReferenceResource& rhs);
		ReferenceResource& operator=(const ReferenceResource& rhs);
		ReferenceResource(ReferenceResource&& rhs);
		ReferenceResource& operator=(ReferenceResource&& rhs);
		bool operator==(const ReferenceResource& rhs);
		bool operator!=(const ReferenceResource& rhs);

		/**
		* Get a list of reference part fragments.
		* @return the list of reference part fragments that are children of the reference.
		* @throws XBRLException
		* @see org.xbrlapi.ReferenceResource#getReferenceParts()
		//*/
		//std::list<ReferencePart> getReferenceParts();

		///**
		//* Get a specific reference part from a reference.
		//* TODO How to handle a referencePart used more than once in a reference?
		//* @param namespace The namespace in which the reference part has been defined
		//* @param localname The local name of the reference part
		//* @return the first matching reference part or null if no such reference part exists.
		//* @throws XBRLException
		//* @see org.xbrlapi.ReferenceResource#getReferencePart(String,String)
		//*/
		//ReferencePart getReferencePart(const std::string& Namespace, const std::string& localname);


	};
}
