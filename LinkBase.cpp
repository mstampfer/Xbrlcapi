#include "LinkBase.h"
#include "SimpleLink.h"
#include "ExtendedLink.h"
#include "XlinkDocumentation.h"

namespace xbrlcapi
{
	struct Linkbase::Impl 
	{
		Impl() {}

		SimpleLink getArcroleRef(const std::string& uri)
		{
			//List<SimpleLink> refs = getArcroleRefs();
			//for (SimpleLink ref: refs) {
			//	if (ref.getDataRootElement().getAttribute("arcroleURI").equals(uri))
			//		return ref;
			//}
			//throw new XBRLException("The required arcroleRef is not part of the linkbase.");
			return SimpleLink();
		}

		std::list<SimpleLink> getArcroleRefs()
		{
			//String query = "for $root in #roots#[@type='" + SimpleLinkImpl.class.getName() + "' and @parentIndex='" + this.getIndex() + "'] where $root/xbrlapi:data/link:arcroleRef return $root";
			//return this.getStore().<SimpleLink>queryForXMLResources(query);
			return std::list<SimpleLink>();
		}

		SimpleLink getRoleRef(const std::string& uri)
		{
			//List<SimpleLink> refs = getRoleRefs();
			//for (SimpleLink ref: refs) {
			//	if (ref.getDataRootElement().getAttribute("roleURI").equals(uri))
			//		return ref;
			//}
			//throw new XBRLException("The required roleRef is not part of the linkbase.");
			return SimpleLink();
		}

		std::list<SimpleLink> getRoleRefs()
		{
			//String query = "for $root in #roots#[@type='" + SimpleLinkImpl.class.getName() + "' and @parentIndex='" + this.getIndex() + "'] where $root/xbrlapi:data/link:roleRef return $root";
			//return this.getStore().<SimpleLink>queryForXMLResources(query);
			return std::list<SimpleLink>();
		}

		std::list<ExtendedLink> getExtendedLinks()
		{
			//String xpath = "for $root in #roots#[@parentIndex='" + getIndex() + "'] let $data := $root/xbrlapi:data/* where $data/@xlink:type='extended' order by namespace-uri($data), local-name($data), $data/@xlink:role return $root";
			//List<ExtendedLink> fragments = getStore().<ExtendedLink>queryForXMLResources(xpath);
			//return fragments;
			return std::list<ExtendedLink>();
		}

		std::list<ExtendedLink> getExtendedLinks(const xercesc::QName& qname)
		{
			//List<ExtendedLink> fragments = getExtendedLinks();
			//List<ExtendedLink> result = new Vector<ExtendedLink>();
			//for (ExtendedLink link: fragments) {
			//	if (link.getNamespace().toString().equals(qname.getNamespaceURI()))
			//		if (link.getLocalname().equals(qname.getLocalPart())) {
			//			result.add(link);
			//		}
			//}

			//return result;
			return std::list<ExtendedLink>();
		}    

		std::list<XlinkDocumentation> getDocumentations()
		{
			//return this.<XlinkDocumentation>getChildren("org.xbrlapi.impl.XlinkDocumentationImpl");
			return std::list<XlinkDocumentation>();
		}

		void removeDocumentation(const Fragment& documentation)
		{
			//throw new XBRLException("Data update methods are not yet implemented.");
		}

		//std::unordered_set<xercesc::QName> getExtendedLinkQNames()
		//{
		//	//Set<QName> result = new HashSet<QName>();
		//	//for (ExtendedLink link: this.getExtendedLinks()) {
		//	//	QName qname = new QName(link.getNamespace().toString(), link.getLocalname());
		//	//	result.add(qname);
		//	//}
		//	//return result;
		//	return std::unordered_set<xercesc::QName>();
		//}

	};

	Linkbase::Linkbase() {}
	Linkbase::~Linkbase() {} 

	Linkbase::Linkbase(const Linkbase& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Linkbase& Linkbase::operator=(const Linkbase& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Linkbase::Linkbase(Linkbase&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Linkbase& Linkbase::operator=(Linkbase&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Linkbase::operator==(const Linkbase& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Linkbase::operator!=(const Linkbase& rhs)
	{
		return !this->operator==(rhs);
	}


	SimpleLink Linkbase::getArcroleRef(const std::string& uri)
	{
		return pImpl->getArcroleRef(uri);
	}

	std::list<SimpleLink> Linkbase::getArcroleRefs()
	{
		return pImpl->getArcroleRefs();
	}

	SimpleLink Linkbase::getRoleRef(const std::string& uri)
	{
		return pImpl->getRoleRef(uri);
	}

	std::list<SimpleLink> Linkbase::getRoleRefs()
	{
		return pImpl->getRoleRefs();
	}

	std::list<ExtendedLink> Linkbase::getExtendedLinks()
	{
		return pImpl->getExtendedLinks();
	}

	std::list<ExtendedLink> Linkbase::getExtendedLinks(const xercesc::QName& qname)
	{
		return pImpl->getExtendedLinks(qname);
	}    

	std::list<XlinkDocumentation> Linkbase::getDocumentations()
	{
		return pImpl->getDocumentations();
	}

	void Linkbase::removeDocumentation(const Fragment& documentation)
	{
		return pImpl->removeDocumentation(documentation);
	}

	//std::unordered_set<xercesc::QName> Linkbase::getExtendedLinkQNames()
	//{
	//	return pImpl->getExtendedLinkQNames();
	//}

}