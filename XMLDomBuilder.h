
#pragma once
#include "XBRLException.h"

#include <exception>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>


/**
* Utility methods for constructing XML DOM objects.

*/
namespace xbrlcapi

{
	class XMLDomBuilder 
	{


	private:
		std::shared_ptr<xercesc::SAX2XMLReader> builder;

		/**
		* Initialise the document builder.
		* @throws XBRLException if the builder cannot be initialised.
		*/
		void initialise()
		{
			try 
			{
				if (builder == nullptr)

					builder = std::shared_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader());
			} catch (const std::exception& e) 
			{
				logger.error("The fragment builder could not be constructed.");
				throw XBRLException("The DOM builder could not be initialised.",e);
			}
		}

	public:
		XMLDOMBuilder()
		{
			initialise();
		}


		/**
		* Create an XML DOM document object that will contain the fragment content.
		* The DOM is always namespace aware and non-validating
		*/
		//	xercesc::DOMDocument newDocument() 
		//{
		//	return builder.newDocument();
		//}

		/**
		* @param inputStream The input stream to parse.
		* @return An XML DOM object for the given input stream.
		* @throws XBRLException if an IO or SAX exception occurs.
		*/
		std::shared_ptr<xercesc::SAX2XMLReader> newDocument(const xercesc::InputSource& inputStream)
		{
			try 
			{
				return builder->parse(inputStream);
			} 
			/*			catch (IOException e) 
			{
			throw XBRLException("IO exception building an XML DOM.",e);
			}*/ 
			catch (const xercesc::SAXException& e) 
			{
				throw XBRLException("SAX exception building an XML DOM.",to_string(e.getMessage()));
			}
		}

		/**
		* @param uri The URI of a document to parse into a DOM object.
		* @return An XML DOM object for the given URI.
		* @throws XBRLException if the URI corresponds to a malformed URL.
		*/
		//xercesc::DOMDocument newDocument(const Poco::URI& uri)
		//{
		//	try 
		//	{
		//		return newDocument(uri.toURL().openStream());
		//	} catch (MalformedURLException e) 
		//	{ 
		//		throw XBRLException(uri + " is a malformed URL.");
		//	} catch (IOException e) 
		//	{ 
		//		throw XBRLException(uri + " caused an IO exception.");
		//	}
		//}	

		/**
		* @param xml is the XML in its string representation.
		* @return The DOM document corresponding to the supplied XML.
		* @throws XBRLException if problems occur constructing the DOM.
		*/
		//xercesc::DOMDocument newDocument(const std::string& xml)
		//{
		//	try 
		//	{
		//		return builder.parse(new InputSource(new std::stringReader(xml)));			
		//	} catch (IOException e) 
		//	{
		//		logger.error("The problematic XML is");
		//		logger.error(xml);
		//		throw XBRLException("An IO exception is causing problems.",e);
		//	} catch (SAXException e) 
		//	{
		//		logger.error("The problematic XML is");
		//		logger.error(xml);
		//		throw XBRLException("A SAX exception is causing problems.",e);
		//	}
		//}
	private:
};
}