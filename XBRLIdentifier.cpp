#include "XBRLIdentifier.h"

namespace xbrlcapi 
{


	struct XBRLIdentifier::Impl : public BaseIdentifier
	{
		Impl() {}
		Impl(const ContentHandler& contentHandler) : BaseIdentifier(contentHandler)
		{}

		void startElement(
			const std::string& namespaceURI, 
			const std::string& lName, 
			const std::string& qName,
			const xercesc::Attributes& attrs)
		{      

			//		Fragment xbrlFragment = null;
			//		if (namespaceURI.equals(Constants.XBRL21Namespace.toString())) {
			//			if (lName.equals("xbrl")) {
			//				xbrlFragment = new InstanceImpl();
			//				this.parsingAnXBRLInstance = true;
			//				this.canBeATuple = true;
			//			} else if (lName.equals("period")) {
			//				xbrlFragment = new PeriodImpl();
			//			} else if (lName.equals("entity")) {
			//				xbrlFragment = new EntityImpl();
			//			} else if (lName.equals("segment")) {
			//				xbrlFragment = new SegmentImpl();
			//			} else if (lName.equals("scenario")) {
			//				xbrlFragment = new ScenarioImpl();
			//			} else if (lName.equals("context")) {
			//				xbrlFragment = new ContextImpl();
			//				this.canBeATuple = false;
			//			} else if (lName.equals("unit")) {
			//				xbrlFragment = new UnitImpl();
			//				this.canBeATuple = false;
			//			}
			//		}

			//		if (xbrlFragment != null) {
			//			this.processFragment(xbrlFragment,attrs);
			//			return;
			//		}

			//		Fragment xbrlLinkFragment = null;
			//		if (namespaceURI.equals(Constants.XBRL21LinkNamespace.toString())) {
			//			if (lName.equals("roleType")) {
			//				xbrlLinkFragment = new RoleTypeImpl();
			//			} else if (lName.equals("arcroleType")) {
			//				xbrlLinkFragment = new ArcroleTypeImpl();
			//			} else if (lName.equals("usedOn")) {
			//				xbrlLinkFragment = new UsedOnImpl();
			//			} else if (lName.equals("linkbase")) {
			//				xbrlLinkFragment = new LinkbaseImpl();
			//			} else if (lName.equals("documentation")) {
			//				xbrlLinkFragment = new XlinkDocumentationImpl();
			//			}

			//			if (xbrlLinkFragment != null) {
			//				this.processFragment(xbrlLinkFragment,attrs);
			//				return;
			//			}
			//		}

			//		if (parsingAnXBRLInstance) {

			//			Fragment factFragment = null;

			//			// First handle items
			//			std::string contextRef = attrs.getValue("contextRef");
			//			if (contextRef != null) {
			//				std::string unitRef = attrs.getValue("unitRef");
			//				if (unitRef != null) {
			//					factFragment = new SimpleNumericItemImpl();
			//				} else {
			//					factFragment = new NonNumericItemImpl();
			//				}
			//			}

			//			// then handle tuples and fraction items
			//			if ((factFragment == null) && this.canBeATuple) {
			//				Fragment currentFragment = this.getLoader().getFragment();

			//				if (currentFragment.hasMetaAttribute("fact") && ! currentFragment.getType().equals(TupleImpl.class.getName())) {
			//					Fragment fractionItem = new FractionItemImpl();
			//					fractionItem.setBuilder(currentFragment.getBuilder());
			//					fractionItem.setMetaAttribute("type","org.xbrlapi.impl.FractionItemImpl");
			//					getLoader().replaceCurrentFragment(fractionItem);
			//				} else {
			//					factFragment = new TupleImpl();
			//				}
			//			}

			//			if (factFragment != null) {
			//				processFragment(factFragment,attrs);
			//				factFragment.setMetaAttribute("fact","true");
			//				return;
			//			}

			//		}

		}

		//void endElement(
		//	const std::string& namespaceURI, 
		//	const std::string& lName, 
		//	const std::string& qName,
		//	const xercesc::Attributes& attrs)
		//{

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

		//}    
	};

	XBRLIdentifier::XBRLIdentifier() {}
	XBRLIdentifier::~XBRLIdentifier() {} 
	XBRLIdentifier::XBRLIdentifier(const ContentHandler& contentHandler) : 
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
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{      
		pImpl->startElement(
			namespaceURI, 
			lName, 
			qName,
			attrs);
	}        

	void XBRLIdentifier::endElement(
		const std::string& namespaceURI, 
		const std::string& lName, 
		const std::string& qName,
		const xercesc::Attributes& attrs)
	{
		pImpl->endElement(
			namespaceURI, 
			lName, 
			qName,
			attrs);
	}

}    




