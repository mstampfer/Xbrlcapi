
#pragma once
#include "Logger.h"
#include "SchemaDeclaration.h"
#include "SchemaContentImpl.h"
#include <string>
namespace xbrlcapi
{
/**
 
 */

class SchemaDeclarationImpl : public  SchemaContentImpl, public SchemaDeclaration 
{
public:
    /**
     * Get the name of structure being declared.
     * @return the name of the structure being declared.
     * @throws XBRLException
     * @see org.xbrlapi.SchemaDeclaration#getName()
     */
    std::string getName();

    /**
     * @see org.xbrlapi.SchemaDeclaration#hasReference()
     */
    bool hasReference();

    /**
     * @see org.xbrlapi.SchemaDeclaration#getReferenceNamespace()
     */
    std::string getReferenceNamespace();
    
    /**
     * @see org.xbrlapi.SchemaDeclaration#getReferenceNamespaceAlias()
     */
    std::string getReferenceNamespaceAlias();

    /**
     * @see org.xbrlapi.SchemaDeclaration#getReferenceQName()
     */
    std::string getReferenceQName();

    /**
     * @see org.xbrlapi.SchemaDeclaration#getReferenceLocalname()
     */  
    std::string getReferenceLocalname();

    /**
     * @see org.xbrlapi.SchemaDeclaration#getReferencedSchemaDeclaration()
     */  
	 template <typename F> F getReferencedSchemaDeclaration();
    
private:
Logger logger;
};
    
}