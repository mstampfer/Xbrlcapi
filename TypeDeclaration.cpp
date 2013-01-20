#include "TypeDeclaration.h"	

namespace xbrlcapi
{
	std::shared_ptr<xercesc::DOMElement> TypeDeclaration::getDerivation() 
	{
		//	Element data = this.getDataRootElement();
		//	NodeList contents = data.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"restriction");
		//	if (contents.getLength() != 0) return (Element) contents.item(0);
		//	contents = data.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"extension");
		//	if (contents.getLength() != 0) return (Element) contents.item(0);
		//	contents = data.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"complexContent");
		//	if (contents.getLength() == 0) 
		//		contents = data.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"simpleContent");
		//	if (contents.getLength() == 0) 
		//	{
		//
		//		return null;
		//	}
		//	Element content = (Element) contents.item(0);
		//	NodeList derivations = content.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"extension");
		//	if (derivations.getLength() == 0) derivations = data.getElementsByTagNameNS(Constants.XMLSchemaNamespace.tostd::string(),"restriction");
		//	if (derivations.getLength() == 0) 
		//	{
		//
		//		return null;
		//	}
		//
		//	return (Element) derivations.item(0);
		return std::shared_ptr<xercesc::DOMElement>();
	}

	std::string TypeDeclaration::getFinal() 
	{
		//		return getDataRootElement().getAttributeNS(Constants.XMLSchemaNamespace.tostd::string(),"final");
		return "";
	}

	bool TypeDeclaration::isFinal() 
	{
		//return (isFinalForExtension() && isFinalForRestriction());
		return false;
	}

	bool TypeDeclaration::isFinalForExtension() 
	{
		//std::string f = getFinal();
		//if (f.contains("#all")) return true;
		//if (f.contains("extension")) return true;
		return false;
	}

	bool TypeDeclaration::isFinalForRestriction() 
	{
		//std::string f = getFinal();
		//if (f.contains("#all")) return true;
		//if (f.contains("restriction")) return true;
		return false;
	}

	bool TypeDeclaration::isDerivedFrom(TypeDeclaration candidate) 
	{
		//if (this.equals(candidate)) return true;
		//std::string parentNamespace = getParentTypeNamespace();
		//if (parentNamespace.equals(Constants.XMLSchemaNamespace)) return false;
		//TypeDeclaration parentType = this.getParentType();
		//if (parentType == null) return false;
		//if (parentType.equals(candidate)) return true;
		//return parentType.isDerivedFrom(candidate);
		return false;
	}

	bool TypeDeclaration::isDerivedFrom(const std::string& Namespace, const std::string& name)
	{
		//if (this.getTargetNamespace().equals(namespace) && (this.getName() != null) && this.getName().equals(name)) return true;
		//std::string parentNamespace = getParentTypeNamespace();
		//std::string parentName = this.getParentTypeLocalname();
		//if (parentNamespace.equals(namespace) && parentName.equals(name)) return true;
		//TypeDeclaration parentType = this.getParentType();
		//if (parentType == null) return false;
		//return parentType.isDerivedFrom(namespace,name);
		return false;
	}

	TypeDeclaration TypeDeclaration::getParentType() 
	{
		//std::string parentNamespace = this.getParentTypeNamespace();
		//if (parentNamespace.equals(Constants.XMLSchemaNamespace)) return null;
		//std::string parentName = this.getParentTypeLocalname();
		//TypeDeclaration parent = getStore().getGlobalDeclaration(parentNamespace,parentName);
		//if (parent != null) return parent;
		//throw new XBRLException("There is no parent type ( "+parentNamespace + ":" + parentName +" ) in the data store.");
		return TypeDeclaration();
	}

	std::string TypeDeclaration::getParentTypeLocalname() 
	{
		//Element derivation = this.getDerivation();
		//if (derivation.hasAttribute("base")) 
		//{

		//	std::string qname = derivation.getAttribute("base");
		//	return this.getLocalnameFromQName(qname);
		//}
		//throw new XBRLException("There is no parent type in the data store.");
		return "";
	}

	std::string TypeDeclaration::getParentTypeNamespace() 
	{
		//Element derivation = this.getDerivation();
		//if (derivation == null) throw new XBRLException("Type " + getIndex() + " is not derived from another. It is in " + getTargetNamespace());
		//if (derivation.hasAttribute("base")) 
		//{

		//	std::string qname = derivation.getAttribute("base");
		//	std::string namespace = this.getNamespaceFromQName(qname,derivation);
		//	return namespace;
		//}
		//throw new XBRLException("This type is not derived from another.");
		return "";
	}

	bool TypeDeclaration::isNumericItemType() 
	{
		/*		TypeDeclaration parentType = this.getParentType();
		if (parentType != null) 
		if (parentType.isa(ComplexTypeDeclarationImpl.class))
		return parentType.isNumericItemType();

		std::string namespace = this.getTargetNamespace();
		if (namespace == null) return false;
		if (namespace.equals(Constants.XBRL21Namespace)) 
		{

		List<AttributeGroupDeclaration> agds = this.<AttributeGroupDeclaration>getChildren(AttributeGroupDeclarationImpl.class);
		for (AttributeGroupDeclaration agd: agds) 
		{

		if (agd.hasReference()) 
		{

		if (agd.getReferenceLocalname().equals("numericItemAttrs")) return true;
		if (agd.getReferenceLocalname().equals("essentialNumericItemAttrs")) return true;
		}
		}
		}
		return false;       */ 
		return false;
	}	
}