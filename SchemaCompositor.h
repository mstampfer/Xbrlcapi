#pragma once
#include "SchemaContent.h"
#include "ElementDeclaration.h"
#include <list>
namespace xbrlcapi
{
	struct SchemaCompositor : public SchemaContent
	{
		std::list<ElementDeclaration> getMembers();
	};
}