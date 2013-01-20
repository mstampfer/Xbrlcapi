#pragma once
#include "SchemaContentDeclaration.h"
namespace xbrlcapi
{
	struct AttributeDeclaration : public SchemaContentDeclaration
	{
		std::string getUse();
	};
}