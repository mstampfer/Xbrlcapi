#include "ElementState.h"
#include "Constants.h"


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

		std::shared_ptr<ElementState> parent;

		std::shared_ptr<const xercesc::Attributes> attributes;

		long order;// = 1;

		long childrenSoFar;// = 0;

		std::string id;;

		Impl(){}

		Impl(ElementState& p, const xercesc::Attributes& attrs) :
			parent(std::shared_ptr<ElementState>(&p)),
			attributes(std::shared_ptr<const xercesc::Attributes>(&attrs))
		{
			if (hasParent()) 
			{
				parent->addChild();
				this->order = parent->getChildrenSoFar();
			}
		}

		std::shared_ptr<const xercesc::Attributes> getAttributes() 
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

		std::string getLanguageCode()
		{
		//	XMLCh * xch = XercesString(XMLConstants::XMLNamespace).c_str();
		//	int index = attributes->getIndex(,L"lang");
		//	if (index > -1) 
		//	{
		//		return attributes->getValue(index);
		//	}

		//	if (parent.get() == Null) 
		//	{
		//		return Null;
		//	}

		//	return xerces_util::to_native(parent->getLanguageCode());
			return std::string();
		}

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
			//pImpl->~Impl();
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

	std::shared_ptr<const xercesc::Attributes> ElementState::getAttributes() 
	{
		return pImpl->getAttributes();
	}

	ElementState::ElementState(ElementState& parent, 
		const xercesc::Attributes& attrs) : pImpl(parent,attrs)
	{}

	bool ElementState::hasParent() 
	{
		return pImpl->hasParent();
	}

	std::shared_ptr<ElementState> ElementState::getParent() 
	{
		return pImpl->getParent();
	}

	void ElementState::addChild() 
	{
		pImpl->addChild();
	}

	long ElementState::getChildrenSoFar() 
	{
		return pImpl->getChildrenSoFar();
	}

	std::string ElementState::getId() 
	{
		return pImpl->getId();
	}

	void ElementState::setId(const std::string& id) 
	{
		pImpl->setId(id);
	}

	bool ElementState::hasId() 
	{
		return pImpl->hasId();
	}

	std::vector<std::string> ElementState::getElementSchemePointers() 
	{
		return pImpl->getElementSchemePointers();
	}

	std::string ElementState::getLanguageCode()
	{
		return pImpl->getLanguageCode();
	}

}
