#include "Segment.h"		

namespace xbrlcapi
{

	struct Segment::Impl 
	{

		Impl() {}

		Entity getEntity()
		{
			//	return (Entity) this.getAncestorOrSelf("org.xbrlapi.Impl.EntityImpl");
			return Entity();
		}

	};

	Segment::Segment() {}
	Segment::~Segment() {} 

	Segment::Segment(const Segment& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Segment& Segment::operator=(const Segment& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Segment::Segment(Segment&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Segment& Segment::operator=(Segment&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Segment::operator==(const Segment& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Segment::operator!=(const Segment& rhs)
	{
		return !this->operator==(rhs);
	}
}