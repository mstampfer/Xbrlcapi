#include "XBRLIdentifier.h"
#include "Constants.h"
#include "XercesString.h"
#include "Instance.h"
#include "Segment.h"
#include "Period.h"
#include "Entity.h"
#include "Fragment.h"
#include "Scenario.h"
#include "Context.h"
#include "Unit.h"
#include "RoleType.h"
#include "ArcroleType.h"
#include "UsedOn.h"
#include "LinkBase.h"
#include "XLinkDocumentation.h"
#include "SimpleNumericItem.h"
#include "NonNumericItem.h"
#include "Tuple.h"
#include "FractionItem.h"
#include "Builder.h"

namespace xbrlcapi 
{


	struct XBRLIdentifier::Impl 
	{
		std::weak_ptr<XBRLIdentifier> outer;
		std::shared_ptr<ContentHandler> contentHandler;
		bool parsingAnXBRLInstance;	
		bool canBeATuple;
		Impl() {}
		Impl(const std::shared_ptr<ContentHandler>& contentHandler) : contentHandler(contentHandler), parsingAnXBRLInstance(false), canBeATuple(false)
		{}

		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{      

			std::shared_ptr<Fragment> xbrlFragment;
			if (namespaceURI == XS(XMLConstants::XBRL21Namespace)) 
			{
				if (lName == L"xbrl") 
				{
					Instance xbrlFragment;
					parsingAnXBRLInstance = true;
					canBeATuple = true;
				} 
				else if (lName == L"period")
				{
					xbrlFragment = std::make_shared<Period>();
				} 
				else if (lName == L"entity") 
				{
					xbrlFragment = std::make_shared<Entity>();
				} 
				else if (lName == L"segment")
				{
					xbrlFragment = std::make_shared<Segment>();
				} 
				else if (lName == L"scenario") 
				{
					xbrlFragment = std::make_shared<Scenario>();
				} 
				else if (lName == L"context") 
				{
					xbrlFragment = std::make_shared<Context>();
					canBeATuple = false;
				} 
				else if (lName == L"unit") 
				{
					xbrlFragment = std::make_shared<Unit>();
					canBeATuple = false;
				}
			}

			if (xbrlFragment) 
			{
				outer.lock()->processFragment(xbrlFragment,attrs);
				return;
			}

			std::shared_ptr<Fragment> xbrlLinkFragment;
			if (namespaceURI == XS(XMLConstants::XBRL21LinkNamespace)) 
			{
				if (lName == L"roleType")
				{
					xbrlLinkFragment = std::make_shared<RoleType>();
				} 
				else if (lName == L"arcroleType") 
				{
					xbrlLinkFragment = std::make_shared<ArcroleType>();
				} 
				else if (lName == L"usedOn") 
				{
					xbrlLinkFragment = std::make_shared<UsedOn>();
				} 
				else if (lName == L"linkbase") 
				{
					xbrlLinkFragment = std::make_shared<Linkbase>();
				} 
				else if (lName == L"documentation") 
				{
					xbrlLinkFragment = std::make_shared<XlinkDocumentation>();
				}

				if (xbrlLinkFragment) 
				{
					outer.lock()->processFragment(xbrlLinkFragment,attrs);
					return;
				}
			}

			if (parsingAnXBRLInstance) 
			{

				std::shared_ptr<Fragment> factFragment;

				// First handle items
				std::string contextRef(to_string(attrs.getValue(L"contextRef")));
				if (!contextRef.empty()) 
				{
					std::string unitRef(to_string(attrs.getValue(L"unitRef")));
					if (!unitRef.empty()) 
					{
						factFragment = std::make_shared<SimpleNumericItem>();
					} 
					else 
					{
						factFragment = std::make_shared<NonNumericItem>();
					}
				}

				// then handle tuples and fraction items
				if (factFragment && canBeATuple) 
				{
					auto currentFragment = outer.lock()->getLoader()->getFragment();

					if (currentFragment.hasMetaAttribute("fact") && 
						 currentFragment.getType() != "Tuple") 
					{
						FractionItem fractionItem;
						fractionItem.setBuilder(currentFragment.getBuilder());
						fractionItem.setMetaAttribute("type","org.xbrlapi.impl.FractionItemImpl");
						outer.lock()->getLoader()->replaceCurrentFragment(fractionItem);
					} 
					else 
					{
						 factFragment = std::make_shared<Tuple>();
					}
				}

				if (factFragment) 
				{
					outer.lock()->processFragment(factFragment,attrs);
					factFragment->setMetaAttribute("fact","true");
					return;
				}

			}

		}

		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs)
		{

			//	if (namespaceURI.equals(Constants.XBRL21Namespace.toString())) {
			//		if (lName.equals("xbrl")) {
			//			this.parsingAnXBRLInstance = false;
			//			this.canBeATuple = false;
			//		} else if (lName.equals("context")) {
			//			this.canBeATuple = true;
			//		} else if (lName.equals("unit")) {
			//			this.canBeATuple = true;
			//		}

			//	} else if (namespaceURI.equals(Constants.XBRL21LinkNamespace.toString())) {
			//		if (lName.equals("footnoteLink")) {
			//			this.canBeATuple = true;
			//		} else if (lName.equals("schemaRef")) {
			//			this.canBeATuple = true;
			//		} else if (lName.equals("linkbaseRef")) {
			//			this.canBeATuple = true;
			//		} else if (lName.equals("arcroleRef")) {
			//			this.canBeATuple = true;
			//		} else if (lName.equals("roleRef")) {
			//			this.canBeATuple = true;
			//		}
			//	}
		}    
		void setOuter(const std::weak_ptr<XBRLIdentifier>& xbrlIdentifier)
		{
			outer = std::weak_ptr<XBRLIdentifier>(xbrlIdentifier);
		}
	};

	XBRLIdentifier::XBRLIdentifier() {}
	XBRLIdentifier::~XBRLIdentifier() {} 
	XBRLIdentifier::XBRLIdentifier(const std::shared_ptr<ContentHandler>& contentHandler) : 
		BaseIdentifier(contentHandler), pImpl(contentHandler) {}

	XBRLIdentifier::XBRLIdentifier(const XBRLIdentifier& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XBRLIdentifier& XBRLIdentifier::operator=(const XBRLIdentifier& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XBRLIdentifier::XBRLIdentifier(XBRLIdentifier&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XBRLIdentifier& XBRLIdentifier::operator=(XBRLIdentifier&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XBRLIdentifier::operator==(const XBRLIdentifier& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XBRLIdentifier::operator!=(const XBRLIdentifier& rhs)
	{
		return !this->operator==(rhs);
	}

	void XBRLIdentifier::startElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{      
		pImpl->startElement(
			namespaceURI, 
			lName, 
			qName,
			attrs);
	}        

	void XBRLIdentifier::endElement(
		const XMLCh* namespaceURI, 
		const XMLCh* lName, 
		const XMLCh* qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(
			namespaceURI, 
			lName, 
			qName,
			attrs);
	}

	std::weak_ptr<XBRLIdentifier> XBRLIdentifier::getPtr()
	{
		return shared_from_this();
	}

	void XBRLIdentifier::initialize()
	{
		pImpl->setOuter(getPtr());
	}

}    




