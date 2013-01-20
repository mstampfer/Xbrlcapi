#include "SchemaCompositor.h"
namespace xbrlcapi
{
	std::list<ElementDeclaration> SchemaCompositor::getMembers()
	{
		std::list<ElementDeclaration> result;
		for (const Fragment& child : getAllChildren()) 
		{
//			result.push_back((ElementDeclaration) child);
		}
		return result;
	}
}

