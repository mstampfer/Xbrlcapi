#include "ReferenceResource.h"

namespace xbrlcapi
{
	struct ReferenceResource::Impl : public MixedContentResource
	{
		Impl() {}
		///**
		// * Get a list of reference part fragments.
		// * @return the list of reference part fragments that are children of the reference.
		// * @throws XBRLException
		// * @see org.xbrlapi.ReferenceResource#getReferenceParts()
		// */
		//public List<ReferencePart> getReferenceParts() throws XBRLException {
		//	return this.getChildren("org.xbrlapi.impl.ReferencePartImpl");
		//}

		///**
		// * Get a specific reference part from a reference.
		// * TODO How to handle a referencePart used more than once in a reference?
		// * @param namespace The namespace in which the reference part has been defined
		// * @param localname The local name of the reference part
		// * @return the first matching reference part or null if no such reference part exists.
		// * @throws XBRLException
		// * @see org.xbrlapi.ReferenceResource#getReferencePart(String,String)
		// */
		//public ReferencePart getReferencePart(String namespace, String localname) throws XBRLException {
		//	List<ReferencePart> candidates = getReferenceParts();
		//	for (int i=0; i<candidates.size(); i++) {
		//		ReferencePart part = candidates.get(i);
		//		if (part.getNamespace().equals(namespace) & part.getLocalname().equals(localname)) {
		//			return part;
		//		}
		//	}
		//	return null;
		//}

	};



	ReferenceResource::ReferenceResource() {}
	ReferenceResource::~ReferenceResource() {} 

	ReferenceResource::ReferenceResource(const ReferenceResource& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ReferenceResource& ReferenceResource::operator=(const ReferenceResource& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ReferenceResource::ReferenceResource(ReferenceResource&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ReferenceResource& ReferenceResource::operator=(ReferenceResource&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ReferenceResource::operator==(const ReferenceResource& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ReferenceResource::operator!=(const ReferenceResource& rhs)
	{
		return !this->operator==(rhs);
	}

	//std::list<ReferencePart> getReferenceParts()
	//{
	//	//TODO not implemented
	//	return std::list<ReferencePart>();
	//}

	///**
	//* Get a specific reference part from a reference.
	//* TODO How to handle a referencePart used more than once in a reference?
	//* @param namespace The namespace in which the reference part has been defined
	//* @param localname The local name of the reference part
	//* @return the first matching reference part or null if no such reference part exists.
	//* @throws XBRLException
	//* @see org.xbrlapi.ReferenceResource#getReferencePart(String,String)
	//*/
	//ReferencePart getReferencePart(const std::string& Namespace, const std::string& localname)
	//{
	//	//TODO not implemented
	//	return ReferencePart();
	//}
}

