#pragma once
#include "PimplImpl.h"
#include "ContextComponent.h"
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMElement.hpp>

namespace xbrlcapi
{
	class OpenContextComponent : public ContextComponent 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		OpenContextComponent();
		virtual ~OpenContextComponent();
		OpenContextComponent(const OpenContextComponent& rhs);
		OpenContextComponent& operator=(const OpenContextComponent& rhs);
		OpenContextComponent(OpenContextComponent&& rhs);
		OpenContextComponent& operator=(OpenContextComponent&& rhs);
		bool operator==(const OpenContextComponent& rhs);
		bool operator!=(const OpenContextComponent& rhs);
		/**
		* Gets the complex content
		*
		* @return the complex content contained by the open
		* context component as a linked list of complex content
		* XML nodes
		* @throws XBRLException
		*/
		virtual std::shared_ptr<xercesc::DOMNodeList> getComplexContent();

		/**
		* @return the list of child elements.
		* @throws XBRLException
		*/
		virtual std::list<xercesc::DOMElement> getChildElements();

		/**
		* Test c-equality of this open context component and another.
		* @param other the other open context component.
		* @return true if the two components are c-equal and false otherwise.
		*/
		virtual bool equals(const OpenContextComponent& other);    
	};
}