#pragma once
#include "SchemaDeclaration.h"
#include <list>
namespace xbrlcapi
{
	struct AttributeGroupDeclaration : public SchemaDeclaration
	{
		std::list<SchemaDeclaration> getMembers();
	};
}