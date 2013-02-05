#include "SchemaDeclaration.h"

namespace xbrlcapi
{
	struct SchemaDeclaration::Impl 
	{
		Impl() {}

		std::string getName() 
		{
			//Element element = getDataRootElement();
			//if (element.hasAttribute("name")) return element.getAttribute("name");
			//return null;
			return std::string();
		}

		bool hasReference() 
		{
			//return getDataRootElement().hasAttribute("ref");
			return false;
		}

		std::string getReferenceNamespace() 
		{
			//return getNamespaceFromQName(getReferenceQName(), getDataRootElement());
			return std::string();
		}

		std::string getReferenceNamespaceAlias() 
		{
			//return getPrefixFromQName(getReferenceQName());
			return std::string();
		}

		std::string getReferenceQName() 
		{
			//if (! hasReference()) throw XBRLException("The content declaration does not use a reference to another XML Schema declaration.");
			//std::string qname = getDataRootElement().getAttribute("ref");
			//if (qname.equals("") || (qname == null)) throw XBRLException("The element declaration does not use a reference to another XML Schema declaration.");
			//return qname;
			return std::string();
		}

		std::string getReferenceLocalname() 
		{
			//return getLocalnameFromQName(getReferenceQName());
			return std::string();
		}

		template <typename T> T getReferencedSchemaDeclaration()
		{
			//try {
			//    F sd = (F) getStore().getSchemaContent(this.getReferenceNamespace(),this.getReferenceLocalname());
			//    if (sd == null) throw XBRLException("The schema declaration is not in a schema contained in the data store.");
			//    return sd;
			//} catch (ClassCastException e) {
			//    throw XBRLException("The XML Schema declaration is  of the wrong fragment type.",e);
			//}
			return T();
		}
	};

	SchemaDeclaration::SchemaDeclaration() {}
	SchemaDeclaration::~SchemaDeclaration() {} 

	SchemaDeclaration::SchemaDeclaration(const SchemaDeclaration& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	SchemaDeclaration& SchemaDeclaration::operator=(const SchemaDeclaration& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	SchemaDeclaration::SchemaDeclaration(SchemaDeclaration&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	SchemaDeclaration& SchemaDeclaration::operator=(SchemaDeclaration&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool SchemaDeclaration::operator==(const SchemaDeclaration& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool SchemaDeclaration::operator!=(const SchemaDeclaration& rhs)
	{
		return !this->operator==(rhs);
	}

	std::string SchemaDeclaration::getName() 
	{
		//Element element = getDataRootElement();
		//if (element.hasAttribute("name")) return element.getAttribute("name");
		//return null;
		return std::string();
	}

	bool SchemaDeclaration::hasReference() 
	{
		//return getDataRootElement().hasAttribute("ref");
		return false;
	}

	std::string SchemaDeclaration::getReferenceNamespace() 
	{
		//return getNamespaceFromQName(getReferenceQName(), getDataRootElement());
		return std::string();
	}

	std::string SchemaDeclaration::getReferenceNamespaceAlias() 
	{
		//return getPrefixFromQName(getReferenceQName());
		return std::string();
	}

	std::string SchemaDeclaration::getReferenceQName() 
	{
		//if (! hasReference()) throw XBRLException("The content declaration does not use a reference to another XML Schema declaration.");
		//std::string qname = getDataRootElement().getAttribute("ref");
		//if (qname.equals("") || (qname == null)) throw XBRLException("The element declaration does not use a reference to another XML Schema declaration.");
		//return qname;
		return std::string();
	}

	std::string SchemaDeclaration::getReferenceLocalname() 
	{
		//return getLocalnameFromQName(getReferenceQName());
		return std::string();
	}

	template <typename T> T SchemaDeclaration::getReferencedSchemaDeclaration()
	{
		//try {
		//    F sd = (F) getStore().getSchemaContent(this.getReferenceNamespace(),this.getReferenceLocalname());
		//    if (sd == null) throw XBRLException("The schema declaration is not in a schema contained in the data store.");
		//    return sd;
		//} catch (ClassCastException e) {
		//    throw XBRLException("The XML Schema declaration is  of the wrong fragment type.",e);
		//}
		return T();
	}

}