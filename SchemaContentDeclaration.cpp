#include "SchemaContentDeclaration.h"
#include "TypeDeclaration.h"
#include <string>

/**
/* Base interface for XML Schema element and attribute declaration fragments.
*/

namespace xbrlcapi
{

	struct SchemaContentDeclaration::Impl 
	{
		Impl() {}

		bool isGlobal() 
		{
			//return getSchema().getIndex().equals(this.getParentIndex());
			return false;
		}

		std::string getForm() 
		{
			//if (! getDataRootElement().hasAttribute("form")) return null;
			//return getDataRootElement().getAttribute("form");
			return std::string();
		}    

		std::string getDefault() 
		{
			//Element root = getDataRootElement(); 
			//if (! root.hasAttribute("default")) return null;
			//return root.getAttribute("default");
			return std::string();
		}

		std::string getFixed() 
		{
			//Element root = getDataRootElement(); 
			//if (! root.hasAttribute("fixed")) return null;
			//return root.getAttribute("fixed");      
			return std::string();
		}

		bool isFixed() 
		{
			//return getDataRootElement().hasAttribute("fixed");
			return false;
		}    

		bool hasTypeReference() 
		{
			//return getDataRootElement().hasAttribute("type");
			return false;
		}

		std::string getTypeNamespace() 
		{
			//return getNamespaceFromQName(getTypeQName(), getDataRootElement());
			return std::string();
		}

		std::string getTypeNamespaceAlias() 
		{
			//return getPrefixFromQName(getTypeQName());
			return std::string();
		}

		std::string getTypeQName() 
		{
			//if (! hasTypeReference()) throw XBRLException(this.getIndex() + ": The schema content declaration does not have a named data type.");
			//std::string qname = getDataRootElement().getAttribute("type");
			//if (qname.equals("") || (qname == null)) throw XBRLException("The element declaration does not declare its XML Schema data type via a type attribute.");
			//return qname;
			return std::string();
		}

		std::string getTypeLocalname() 
		{
			//return getLocalnameFromQName(getTypeQName());
			return std::string();
		}

		TypeDeclaration getTypeDeclaration() 
		{
			//TypeDeclaration result = this.getLocalType();
			//if (result != null) return result;
			//if (this.hasTypeReference()) 
			//{

			//	try 
			//	{

			//		result = (TypeDeclaration) getStore().getSchemaContent(this.getTypeNamespace(),this.getTypeLocalname());
			//		if (result == null) throw XBRLException("The type " + this.getTypeQName() + " is not declared in a schema contained in the data store.");
			//	} catch (ClassCastException cce) 
			//	{

			//		throw XBRLException("The XML Schema type declaration is  of the wrong fragment type.",cce);
			//	}
			//}
			//return result;
			return TypeDeclaration();
		}

		std::string localTypeQuery() 
		{
			//return "for $root in #roots#[@parentIndex='"+getIndex()+"'] where $root/@type='org.xbrlapi.impl.SimpleTypeDeclarationImpl' or $root/@type='org.xbrlapi.impl.ComplexTypeDeclarationImpl' return $root";
			return std::string();
		}

		bool hasLocalType() 
		{
			//long localTypes = getStore().queryCount(localTypeQuery());
			//if (localTypes > 1) throw XBRLException("The Schema content declaration has too many local types.");
			//return (localTypes == 1);
			return false;
		}

		TypeDeclaration getLocalType() 
		{
			//List<TypeDeclaration> types = getStore().<TypeDeclaration>queryForXMLResources(localTypeQuery());
			//if (types.size() == 1) return types.get(0);
			//if (types.size() > 1) throw XBRLException("There are too many local type declarations for this content declaration.");
			//return null;
			return TypeDeclaration();
		}    
	};

	SchemaContentDeclaration::SchemaContentDeclaration() {}
	SchemaContentDeclaration::~SchemaContentDeclaration() {} 

	SchemaContentDeclaration::SchemaContentDeclaration(const SchemaContentDeclaration& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	SchemaContentDeclaration& SchemaContentDeclaration::operator=(const SchemaContentDeclaration& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	SchemaContentDeclaration::SchemaContentDeclaration(SchemaContentDeclaration&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	SchemaContentDeclaration& SchemaContentDeclaration::operator=(SchemaContentDeclaration&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool SchemaContentDeclaration::operator==(const SchemaContentDeclaration& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool SchemaContentDeclaration::operator!=(const SchemaContentDeclaration& rhs)
	{
		return !this->operator==(rhs);
	}

	bool SchemaContentDeclaration::isGlobal() 
	{
		return pImpl->isGlobal();
	}

	std::string SchemaContentDeclaration::getForm() 
	{
		return pImpl->getForm();
	}    

	std::string SchemaContentDeclaration::getDefault() 
	{
		return pImpl->getDefault();
	}

	std::string SchemaContentDeclaration::getFixed() 
	{
		return pImpl->getFixed();
	}

	bool SchemaContentDeclaration::isFixed() 
	{
		return pImpl->isFixed();
	}    

	bool SchemaContentDeclaration::hasTypeReference() 
	{
		return pImpl->hasTypeReference();
	}

	std::string SchemaContentDeclaration::getTypeNamespace() 
	{
		return pImpl->getTypeNamespace();
	}

	std::string SchemaContentDeclaration::getTypeNamespaceAlias() 
	{
		return pImpl->getTypeNamespaceAlias();
	}

	std::string SchemaContentDeclaration::getTypeQName() 
	{
		return pImpl->getTypeQName();
	}

	std::string SchemaContentDeclaration::getTypeLocalname() 
	{
		return pImpl->getTypeLocalname();
	}

	TypeDeclaration SchemaContentDeclaration::getTypeDeclaration() 
	{
		return pImpl->getTypeDeclaration();
	}

	bool SchemaContentDeclaration::hasLocalType() 
	{
		return pImpl->hasLocalType();
	}

	TypeDeclaration SchemaContentDeclaration::getLocalType() 
	{
		return pImpl->getLocalType();
	} 

}