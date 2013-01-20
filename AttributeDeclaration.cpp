#include "AttributeDeclaration.h"

namespace xbrlcapi
{
	std::string AttributeDeclaration::getUse()
	{
        //if (isGlobal()) return std::string();
        //if (! getDataRootElement().hasAttribute("use")) return "optional";
        //return getDataRootElement().getAttribute("use");
		return std::string();
	}
}
