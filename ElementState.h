#pragma once
#include "PimplImpl.h"
#include <string>
#include <vector>
#include <xercesc/sax2/Attributes.hpp>


/**
* Assists in the tracking of document state information
* during SAX parsing, retaining the necessary information
* to construct all element scheme XPointer expressions
* that can be used to identify each element in a document.
* 
* The state is started again when a new document is started.
* As each new element is parsed in, a new element state is created,
* wrapping the parent element's state as a property.
* 
* The state keeps track of ancestor element states, the id of the current
* element, if any, and the order which is set equal to the number of children 
* so far for the parent element state.
*
* @author Geoff Shuetrim (geoff@galexy.net)
*/
namespace xbrlcapi
{
	class ElementState 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:

		ElementState();
		~ElementState();
		ElementState(ElementState& rhs);
		ElementState& operator=(ElementState& rhs);
		ElementState(ElementState&& rhs);
		ElementState& operator=(ElementState&& rhs);
		bool operator==(const ElementState& rhs);
		bool operator!=(const ElementState& rhs);

		/**
		* @return the attributes of the element.
		*/
		std::shared_ptr<xercesc::Attributes> getAttributes(); 

		/**
		* @param parent The state of the parent element
		* @param attrs The attributes of the element (make sure that these are a clone of the
		* originals received by the SAX parser or the state will get really messed up 
		* and confusing.  
		* Use the org.xml.sax.helpers.AttributesImpl(Attributes); constructor to clone the
		* originals.
		*/
		ElementState(const ElementState& parent, const xercesc::Attributes& attrs); 

		bool hasParent(); 

		ElementState getParent(); 

		void addChild(); 

		long getChildrenSoFar(); 

		std::string getId(); 

		void setId(const std::string& id); 

		bool hasId(); 

		std::vector<std::string> getElementSchemePointers(); 

		/**
		* @return the inherited XML lang attribute value based upon the
		* current element state or returns null if there is no inherited XML lang 
		* attribute value.
		* @throws XBRLException
		*/
		std::string getLanguageCode();

	};
}
