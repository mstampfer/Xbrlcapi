#include "LabelResource.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include "XercesStrings.h"
#include "Matcher.h"

/**
* @author Geoffrey Shuetrim (geoff@galexy.net)
* TODO Find out why XPointer metadata does not include the id for label resources.
*/
namespace xbrlcapi
{
	struct LabelResource::Impl : public MixedContentResource
	{
		Impl() {}
		///**
		//* @see org.xbrlapi.LabelResource#getStringValue()
		//*/
		//std::string getStringValue()
		//{
		//	//std::string value = "";
		//	//std::shared_ptr<xercesc::DOMNodeList> nodes = std::shared_ptr<xercesc::DOMNodeList>(getContentAsNodeList());
		//	//for (int i=0; i<nodes->getLength(); i++) 
		//	//{
		//	//	std::shared_ptr<xercesc::DOMNode> node = std::shared_ptr<xercesc::DOMNode>(nodes->item(i));
		//	//	if (node->getNodeType() == xercesc::DOMNode::TEXT_NODE) value = value + " " + xerces_util::toNative(node->getTextContent()).trim() + " ";
		//	//	if (node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) value = value + getStringValue((Element) node);			
		//	//}

		//	//Pattern pattern = Pattern.compile("\\s+");
		//	//std::shared_ptr<Matcher> matcher = std::shared_ptr(pattern.matcher(value));
		//	//return matcher->replaceAll(" ").trim();
		//	return std::string();
		//}


		///**
		//* @return the list of Concepts in the data store that have this label.
		//* @throws XBRLException
		//*/
		//std::list<Concept> getConcepts()
		//{

		//	//Set<std::string> indices;
		//	//if (this.getNamespace().equals(Constants.GenericLabelNamespace))
		//	//	indices = getStore().getSourceIndices(getIndex(),null,Constants.GenericLabelArcrole);
		//	//else 
		//	//	indices = getStore().getSourceIndices(getIndex(),null,Constants.LabelArcrole);

		//	//Set<Concept> concepts = new HashSet<Concept>();
		//	//for (std::string index: indices) 
		//	//{
		//	//	try 
		//	//	{
		//	//		Concept c = getStore().<Concept>getXMLResource(index);
		//	//		concepts.add(c);
		//	//	} catch (Exception e) 
		//	//	{
		//	//		;// Not a concept so ignore it.
		//	//	}
		//	//}

		//	//return std::list<Concept>(concepts);
		//	return std::list<Concept>();
		//}

		///**
		//* @param element The element at the top of the markup to be converted to a string.
		//* @return the string value from an element contained in the XHTML markup content,
		//* eliminating the markup itself.
		//* @throws XBRLException
		//*/
		//std::string getStringValue(const xercesc::DOMElement& element)
		//{
		//	//std::string value = "";
		//	//xercesc::DOMNodeList nodes = element.getChildNodes();
		//	//for (int i=0; i<nodes->getLength(); i++) 
		//	//{
		//	//	Node node = nodes->item(i);
		//	//	if (node->getNodeType() == xercesc::DOMNode::TEXT_NODE) value = value + node->getTextContent();
		//	//	else if (node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) value = value + getStringValue((Element) node);
		//	//}
		//	//return " " + value.trim() + " ";
		//	return std::string();
		//}	
	};


	LabelResource::LabelResource() {}
	LabelResource::~LabelResource() {} 

	LabelResource::LabelResource(const LabelResource& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	LabelResource& LabelResource::operator=(const LabelResource& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	LabelResource::LabelResource(LabelResource&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	LabelResource& LabelResource::operator=(LabelResource&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool LabelResource::operator==(const LabelResource& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool LabelResource::operator!=(const LabelResource& rhs)
	{
		return !this->operator==(rhs);
	}

	//std::string LabelResource::getStringValue()
	//{
	//	return pImpl->getStringValue();
	//}

	//std::list<Concept> LabelResource::getConcepts()
	//{
	//	return pImpl->getConcepts();
	//}

}
