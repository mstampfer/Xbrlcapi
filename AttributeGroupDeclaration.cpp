#include "AttributeGroupDeclaration.h"

namespace xbrlcapi
{
	std::list<SchemaDeclaration> AttributeGroupDeclaration::getMembers()
	{
		//std::string query = "for $root in #roots#[@parentIndex='" + 
		//	getIndex() + 
		//	"' and (@type='org.xbrlapi.impl.AttributeImpl' or @type='org.xbrlapi.impl.AttributeGroupImpl')] order by $root/@index return $root";
		//return getStore().<SchemaDeclaration>queryForXMLResources(query);
		return std::list<SchemaDeclaration>();
	}
}
