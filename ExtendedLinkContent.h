

#pragma once
#include "Logger.h"

//#include "ExtendedLink.h"
#include "Xlink.h"

/**

*/
namespace xbrlcapi
{
	struct ExtendedLink;
	struct ExtendedLinkContent : public Xlink {

		/**
		* Get the extended link containing the extended link xlink content.
		* @return the extended link fragment containing the extended link xlink content.
		* @throws XBRLException
		*/
		virtual ExtendedLink getExtendedLink();

		private:
Logger logger;
};
}
