#include "XMLDOMSerializer.h"
#include "PimplImpl.h"
#include <string>
#include <xercesc/dom/DOMNode.hpp>
#include <fstream>

namespace xbrlcapi
{
	struct XMLDOMSerializer::Impl
	{
		Impl() {}

		//   static std::string serialize(const xercesc::DOMNode& what) 
		//{
		//       ByteArrayOutputStream baos = new ByteArrayOutputStream();
		//       serialize(what, baos);
		//       return baos.toString();
		//   }

		static void serialize(const xercesc::DOMNode& what, std::ofstream& outputStream)
		{
			// 	try {
			//     	if (what.getNodeType() == xercesc::DOMNode::TEXT_NODE) 
			//{
			//             OutputStreamWriter osw = new OutputStreamWriter(outputStream, "UTF-8");
			//             BufferedWriter bw = new BufferedWriter(osw);
			//             bw.write(what.getTextContent());
			//             bw.flush();
			//             bw.close();
			//         } 
			//else 
			//{    	
			// 	        OutputFormat format = new OutputFormat(what.getOwnerDocument(), "UTF-8", true);
			// 	        format.setOmitXMLDeclaration(true);
			//             XMLSerializer output = new org.apache.xml.serialize.XMLSerializer(outputStream, format);
			//             output.setNamespaces(true);
			// 	        if (what.getNodeType() == Node.DOCUMENT_NODE) 
			//	{
			// 	            output.serialize(((Document) what).getDocumentElement());
			// 	        } 
			//	else if (what.getNodeType() == Node.ELEMENT_NODE) 
			//	{
			// 	            output.serialize((Element) what);
			// 	        }
		}
		//} catch (IOException e) {
		//	throw new XBRLException("The node could not be serialized.",e);
		//}

		/*    	
		DOMImplementation domImplementation = null;
		if (what.getNodeType() == Node.DOCUMENT_NODE) {
		domImplementation = ((Document) what).getImplementation();
		} else {
		domImplementation = what.getOwnerDocument().getImplementation();
		}
		logger.info(domImplementation.getClass().getName());
		if (domImplementation.hasFeature("LS", "3.0") && domImplementation.hasFeature("Core", "2.0")) {
		DOMImplementationLS domImplementationLS = (DOMImplementationLS) domImplementation.getFeature("LS", "3.0");
		LSSerializer lsSerializer = domImplementationLS.createLSSerializer();
		DOMConfiguration domConfiguration = lsSerializer.getDomConfig();

		if (domConfiguration.canSetParameter("format-pretty-print", Boolean.TRUE)) {
		lsSerializer.getDomConfig().setParameter("format-pretty-print", Boolean.TRUE);
		LSOutput lsOutput = domImplementationLS.createLSOutput();
		lsOutput.setEncoding("UTF-8");
		lsOutput.setByteStream(outputStream);
		lsSerializer.write(what, lsOutput);
		} else {
		throw new XBRLException("DOMConfiguration 'format-pretty-print' parameter isn't settable.");
		}
		} else {
		throw new XBRLException("DOM 3.0 LS and/or DOM 2.0 Core not supported.");
		}*/
	};
	XMLDOMSerializer::XMLDOMSerializer() {}
	XMLDOMSerializer::~XMLDOMSerializer() {} 

	XMLDOMSerializer::XMLDOMSerializer(const XMLDOMSerializer& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	XMLDOMSerializer& XMLDOMSerializer::operator=(const XMLDOMSerializer& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	XMLDOMSerializer::XMLDOMSerializer(XMLDOMSerializer&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	XMLDOMSerializer& XMLDOMSerializer::operator=(XMLDOMSerializer&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool XMLDOMSerializer::operator==(const XMLDOMSerializer& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool XMLDOMSerializer::operator!=(const XMLDOMSerializer& rhs)
	{
		return !this->operator==(rhs);
	}

	void XMLDOMSerializer::serialize(const xercesc::DOMNode& what, std::ofstream& outputStream)
	{
		XMLDOMSerializer::Impl::serialize(what, outputStream);
	}
}