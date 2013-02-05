#pragma once
#include "Context.h"

namespace xbrlcapi
{
	class ContextComponent : public Fragment 
	{

		/**
		* Determine the context that contains this component
		*/
		virtual Context getContext();
	};
}