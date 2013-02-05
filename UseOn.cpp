#include "UsedOn.h"
namespace xbrlcapi
{
	struct UsedOn::Impl 
	{
		Impl() {}


		std::string getUsedOnNamespace()
		{
			//Node rootNode = getDataRootElement();
			//String u = rootNode.getTextContent().trim();
			//if (u.equals("")) throw new XBRLException("The used on declaration does not declare the element that usage is allowed on.");
			//return getNamespaceFromQName(u, rootNode);
			return std::string();
		}

		std::string getUsedOnLocalname()
		{
			//Node rootNode = getDataRootElement();
			//String u = rootNode.getTextContent().trim();
			//if (u.equals("")) throw new XBRLException("The used on declaration does not declare the element that usage is allowed on.");
			//return this.getLocalnameFromQName(u);
			return std::string();
		}    

		bool isUsedOn(const std::string& namespaceURI, const std::string& localname)
		{
			//if (! getUsedOnNamespace().equals(namespaceURI))
			//	return false;
			//if (! getUsedOnLocalname().equals(localname))
			//	return false;
			//return true;
			return false;
		}

	};
	std::string UsedOn::getUsedOnNamespace()
	{
		return pImpl->getUsedOnNamespace();
	}


	std::string UsedOn::getUsedOnLocalname()
	{
		return pImpl->getUsedOnLocalname();
	}    

	bool UsedOn::isUsedOn(const std::string& namespaceURI, const std::string& localname)
	{
		return pImpl->isUsedOn(namespaceURI, localname);
	}

}
