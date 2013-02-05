#include "SchemaContent.h"
#include "ElementDeclaration.h"
#include "Schema.h"

namespace xbrlcapi
{
	struct SchemaContent::Impl 
	{
		Impl() {}
		SchemaContent getSchema()
		{
			//return (Schema) getAncestorOrSelf("org.xbrlapi.impl.SchemaImpl");
			return Schema();
		}

		std::string getTargetNamespace()
		{
			//Schema s = getSchema();
			//Element e = s.getDataRootElement();
			//if (e.hasAttribute("targetNamespace")) return e.getAttribute("targetNamespace");
			//return null;
			return std::string();
		}

		std::vector<std::shared_ptr<xercesc::DOMElement>> getAnnotations()
		{
			//	List<Element> result = new Vector<Element>();
			//	NodeList nodes = this.getDataRootElement().getElementsByTagNameNS(Constants.XMLSchemaNamespace.toString(),"annotation");
			//	for (int i=0; i<nodes.getLength(); i++)
			//{
			//		result.add((Element) nodes.item(i));
			//	}
			//	return result;
			return std::vector<std::shared_ptr<xercesc::DOMElement>>();
		}    

		bool hasOtherAttribute(const std::string& Namespace, const std::string& localname)
		{
			//return getDataRootElement().hasAttributeNS(namespace.toString(), localname);
			return false;
		}

		std::vector<std::shared_ptr<xercesc::DOMNode>> getOtherAttributes()
		{
			//	NamedNodeMap attributes = getDataRootElement().getAttributes();
			//	LinkedList<Node> otherAttributes = new LinkedList<Node>();
			//	for (int i=0; i<attributes.getLength(); i++)
			//{
			//		std::string ns = attributes.item(i).getNamespaceURI();
			//		if (! ns.equals(Constants.XMLSchemaNamespace.toString()) && ! ns.equals(Constants.XBRL21Namespace.toString()))
			//{
			//			otherAttributes.add(attributes.item(i));
			//		}
			//	}
			//	return otherAttributes;
			return std::vector<std::shared_ptr<xercesc::DOMNode>>();
		}    

		std::string getOtherAttribute(const std::string& Namespace, const std::string& localname)
		{
			//if (this.hasOtherAttribute(namespace, localname)) 
			//	return getDataRootElement().getAttributeNS(namespace.toString(), localname);
			//return null;
			return std::string();
		}

		std::string getSchemaId()
		{
			//if (! getDataRootElement().hasAttributeNS(Constants.XMLSchemaNamespace.toString(),"id")) return null;
			//return getDataRootElement().getAttributeNS(Constants.XMLSchemaNamespace.toString(),"id");
			return std::string();
		}    


	};

	SchemaContent::SchemaContent() {}
	SchemaContent::~SchemaContent() {} 

	SchemaContent::SchemaContent(const SchemaContent& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	SchemaContent& SchemaContent::operator=(const SchemaContent& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	SchemaContent::SchemaContent(SchemaContent&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	SchemaContent& SchemaContent::operator=(SchemaContent&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool SchemaContent::operator==(const SchemaContent& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool SchemaContent::operator!=(const SchemaContent& rhs)
	{
		return !this->operator==(rhs);
	}

	SchemaContent SchemaContent::getSchema()
	{
		return pImpl->getSchema();
	}

	std::string SchemaContent::getTargetNamespace()
	{
		return pImpl->getTargetNamespace();
	}

	std::vector<std::shared_ptr<xercesc::DOMElement>> SchemaContent::getAnnotations()
	{
		return pImpl->getAnnotations();
	}    

	std::vector<std::shared_ptr<xercesc::DOMNode>> SchemaContent::getOtherAttributes()
	{
		return pImpl->getOtherAttributes();
	}

	std::string SchemaContent::getOtherAttribute(const std::string& Namespace, const std::string& localname)
	{
		return pImpl->getOtherAttribute(Namespace, localname);
	}

	bool SchemaContent::hasOtherAttribute(const std::string& Namespace, const std::string& localname)
	{
		return pImpl->hasOtherAttribute(Namespace,localname);
	}

	std::string SchemaContent::getSchemaId()
	{
		return pImpl->getSchemaId();
	}    


}