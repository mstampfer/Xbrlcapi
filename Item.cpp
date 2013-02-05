#include "Item.h"
#include "Context.h"

namespace xbrlcapi
{
	struct Item::Impl 
	{
		Impl() {}

		Context getContext()
		{
			/*	String query = "for $root in #roots#[@uri='"+this.getURI()+"' and @type='"+ContextImpl.class.getName()+"' and xbrlapi:data/xbrli:context/@id='"+this.getContextId()+"'] return $root";
			List<Context> contexts = getStore().<Context>queryForXMLResources(query);
			if (contexts.size() == 1) return contexts.get(0);
			throw new XBRLException("There is not a unique matching context with ID "+this.getContextId()+" for this fact in instance " + this.getURI());*/
			return Context();
		}


		std::string getContextId()
		{
			//Element root = getDataRootElement();
			//if (root.hasAttribute("contextRef")) {
			//	return root.getAttribute("contextRef");
			//}
			//throw new XBRLException("The contextRef is missing on an item.");
			return std::string();
		}

	};

	Item::Item() {}
	Item::~Item() {} 

	Item::Item(const Item& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Item& Item::operator=(const Item& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Item::Item(Item&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Item& Item::operator=(Item&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Item::operator==(const Item& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Item::operator!=(const Item& rhs)
	{
		return !this->operator==(rhs);
	}

	Context Item::getContext()
	{
		return pImpl->getContext();
	}


	std::string Item::getContextId()
	{
		return pImpl->getContextId();
	}

}