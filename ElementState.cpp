#include "ElementState.h"
#include "Constants.h"
#include "XercesStrings.h"

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
	struct ElementState::Impl
	{

		const std::shared_ptr<ElementState> parent;

		const std::shared_ptr<xercesc::Attributes> attributes;

		long order;// = 1;

		long childrenSoFar;// = 0;

		std::string id;;

		Impl(){}

		Impl(const ElementState& p, const xercesc::Attributes& attrs) :
			parent(std::make_shared<ElementState>(p)), 
			attributes(std::make_shared<xercesc::Attributes>(attrs))
		{
			if (hasParent()) 
			{
				parent->addChild();
				this->order = parent->getChildrenSoFar();
			}
		}

		std::shared_ptr<xercesc::Attributes> getAttributes() 
		{
			return attributes;
		}

		bool hasParent() 
		{
			if (parent.get() == NULL) return false;
			return true;
		}

		std::shared_ptr<ElementState> getParent() 
		{
			return parent;
		}

		void addChild() 
		{
			childrenSoFar++;
		}

		long getChildrenSoFar() 
		{
			return childrenSoFar;
		}

		std::string getId() 
		{
			return id;
		}

		void setId(const std::string& id) 
		{
			this->id = id;
		}

		bool hasId() 
		{
			if (id.empty()) return false;
			return true;
		}

		std::vector<std::string> getElementSchemePointers() 
		{

			std::vector<std::string> pointers;

			if (hasParent()) 
			{
				pointers = parent->getElementSchemePointers();
				for (size_t i=0; i<pointers.size(); i++) 
				{
					std::string pointer = pointers[i];
					pointers[i] += "/" + std::to_string(order);
				}
			} else 
			{
				std::vector<std::string> pointers;
				pointers.push_back("/" + std::to_string(order));
			}

			if (hasId()) 
			{
				pointers.push_back(getId());
			}
			return pointers;
		}

		//std::wstring getLanguageCode()
		//{
		//	XMLCh * xch = xerces_util::fromNative(XMLConstants::XMLNamespace).c_str();
		//	int index = attributes->getIndex(,L"lang");
		//	if (index > -1) 
		//	{
		//		return attributes->getValue(index);
		//	}

		//	if (parent.get() == Null) 
		//	{
		//		return Null;
		//	}

		//	return parent->getLanguageCode();
		//}

	};

	ElementState::ElementState() {}
	ElementState::~ElementState() {} 

	ElementState::ElementState(const ElementState& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	ElementState& ElementState::operator=(const ElementState& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	ElementState::ElementState(ElementState&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	ElementState& ElementState::operator=(ElementState&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool ElementState::operator==(const ElementState& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool ElementState::operator!=(const ElementState& rhs)
	{
		return !this->operator==(rhs);
	}

	std::shared_ptr<xercesc::Attributes> ElementState::getAttributes() 
	{
		pImpl->getAttributes();
	}

	ElementState::ElementState(const ElementState& parent, const xercesc::Attributes& attrs) :
		pImpl(parent,attrs)
	{}

	bool ElementState::hasParent() 
	{
		pImpl->hasParent();
	}

	ElementState ElementState::getParent() 
	{
		pImpl->getParent();
	}

	void ElementState::addChild() 
	{
		pImpl->addChild();
	}

	long ElementState::getChildrenSoFar() 
	{
		pImpl->getChildrenSoFar();
	}

	std::string ElementState::getId() 
	{
		pImpl->getId();
	}

	void ElementState::setId(const std::string& id) 
	{
		pImpl->setId(id);
	}

	bool ElementState::hasId() 
	{
		pImpl->hasId();
	}

	std::vector<std::string> ElementState::getElementSchemePointers() 
	{
		pImpl->getElementSchemePointers();
	}

	std::string ElementState::getLanguageCode()
	{
	//	pImpl->getLanguageCode();
	}

}
