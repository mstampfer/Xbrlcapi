
#include "Stdafx.h"
#pragma once


#include <string>
#include "SchemaDeclaration.h"

namespace xbrlcapi
{
	class TypeDeclaration;
/**
 * Base interface for XML Schema element and attribute declarations
 * @author Geoffrey Shuetrim (geoff@galexy.net)
 */

struct SchemaContentDeclaration : public SchemaDeclaration {

    /**
     * @return true iff the element declaration is global rather than
     * part of a complex type declaration.
     * @throws XBRLException
     */
    virtual bool isGlobal();    
    
    /**
     * @return the value of the form attribute if it is on the attribute declaration
     * and returns null otherwise.
     * @throws XBRLException
     */
    virtual std::string getForm();    
    
    /**
     * @return null if there is no default attribute, otherwise return its value.
     * @throws XBRLException
     */
    virtual std::string getDefault();

    /**
     * @return null if there is no fixed attribute, otherwise return its value.
     * @throws XBRLException
     */
    virtual std::string getFixed();
    
    /**
     * @return true iff the element or attribute is fixed and false otherwise.
     * @throws XBRLException
     */
    virtual bool isFixed();    

    /**
     * @return true if the content declaration has a named data type and false otherwise.
     * @throws XBRLException if the datatype is not declared by a type attribute.
     */
    virtual bool hasTypeReference();
    
    /**
     * Retrieve the type namespace.
     * @return the namespace for the data type.
     * @throws XBRLException if the datatype is not declared by a type attribute.
     */
    virtual std::string getTypeNamespace();
    
    /**
     * Retrieve the type namespace alias.
     * @return the namespace alias (prefix) or the empty string if there 
     * is no namespace prefix used in the QName.
     * @throws XBRLException if the datatype is not declared.
     */
    virtual std::string getTypeNamespaceAlias();

    /**
     * Retrieve the type QName.
     * @return the QName used to specify the data type or null
     * if the element has no type attribute.
     * @throws XBRLException if the data root element is not available.
     */
    virtual std::string getTypeQName();

    /**
     * Retrieve the type local name.
     * @return the local name for the datatype.
     * @throws XBRLException if the datatype is not declared.
     */    
    virtual std::string getTypeLocalname();

    /**
     * @return The fragment that is the type declaration referred to by the 
     * schema content declaration or null if there is no type declaration.
     * @throws XBRLException if the fragment cannot be found in the data store.
     */
    virtual TypeDeclaration getTypeDeclaration();
    
    
    /**
     * @return true iff the content declaration has its own local simple or complex type declaration.
     * @throws XBRLException if the content declaration has more than one local type declaration.
     */
    virtual bool hasLocalType();    
    
    /**
     * @return The local type declaration or null if the content 
     * declaration does not have its own local type declaration.
     */
    virtual TypeDeclaration getLocalType();
    
};
}

