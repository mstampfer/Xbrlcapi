#pragma once
#include "PimplImpl.h"
#include "OpenContextComponent.h"
#include "Entity.h"


namespace xbrlcapi
{
	class Segment :  public OpenContextComponent
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Segment();
		~Segment();
		Segment(const Segment& rhs);
		Segment& operator=(const Segment& rhs);
		Segment(Segment&& rhs);
		Segment& operator=(Segment&& rhs);
		bool operator==(const Segment& rhs);
		bool operator!=(const Segment& rhs);

		/**
		* Gets the containing entity
		*
		* @return the entity that contains this segment
		* @throws XBRLException
		* @see org.xbrlapi.Segment#getEntity()
		*/
		Entity getEntity();
	};
}