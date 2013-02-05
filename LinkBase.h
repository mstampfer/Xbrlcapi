#pragma once
#include "PimplImpl.h"
#include <string>
#include <list>
#include <xercesc/util/QName.hpp>
#include "Fragment.h"

namespace xbrlcapi
{

	class SimpleLink;
	class ExtendedLink;
	class XlinkDocumentation;

	class Linkbase : public Fragment 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Linkbase();
		~Linkbase();
		Linkbase(const Linkbase& rhs);
		Linkbase& operator=(const Linkbase& rhs);
		Linkbase(Linkbase&& rhs);
		Linkbase& operator=(Linkbase&& rhs);
		bool operator==(const Linkbase& rhs);
		bool operator!=(const Linkbase& rhs);

		/**
		* Retrieve an arcroleRef from a linkbase.
		* @param uri The arcroleRef URI
		* @return the required arcroleRef 
		* @throws XBRLException if the arcroleRef is not part of the linkbase
		* @see org.xbrlapi.Linkbase#getArcroleRef(String)
		*/
		SimpleLink getArcroleRef(const std::string& uri);

		/**
		* Gets the list of arcroleRefs in a linkbase.
		* @return list of arcroleRef fragments that are children of the linkbase.
		* The list can be empty.
		* @throws XBRLException
		* @see org.xbrlapi.Linkbase#getArcroleRefs()
		*/
		std::list<SimpleLink> getArcroleRefs();

		/**
		* Retrieve an roleRef from a linkbase.
		* @param uri The roleRef URI
		* @throws XBRLException if the roleRef is not part of the linkbase
		* @see org.xbrlapi.Linkbase#getRoleRef(String)
		*/
		SimpleLink getRoleRef(const std::string& uri);

		/**
		* Gets the list of roleRefs in a linkbase.
		* @return list of roleRef fragments that are children of the linkbase.
		* The list can be empty.
		* @throws XBRLException
		* @see org.xbrlapi.Linkbase#getRoleRefs()
		*/
		std::list<SimpleLink> getRoleRefs();

		/**
		* @see org.xbrlapi.Linkbase#getExtendedLinks()
		*/
		std::list<ExtendedLink> getExtendedLinks();

		/**
		* @see org.xbrlapi.Linkbase#getExtendedLinks(QName)
		*/
		std::list<ExtendedLink> getExtendedLinks(const xercesc::QName& qname);

		/**
		* Get the list of documentation fragments that are children of the linkbase.
		* Returns the list of documentation fragments in the linkbase.
		* @throws XBRLException
		* @see org.xbrlapi.Linkbase#getDocumentations()
		*/
		std::list<XlinkDocumentation> getDocumentations();

		/**
		* Remove a link documentation child fragment from the linkbase.
		* @param documentation The documentation fragment to be removed.
		* @throws XBRLException
		* @see org.xbrlapi.Linkbase#removeDocumentation(Fragment)
		*/
		void removeDocumentation(const Fragment& documentation);

		/**
		* @see Linkbase#getExtendedLinkQNames()
		*/
		//std::unordered_set<xercesc::QName> getExtendedLinkQNames();
	};
}
