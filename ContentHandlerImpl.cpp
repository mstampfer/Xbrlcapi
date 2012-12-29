
#include "ContentHandler.h"
#include <xercesc/sax2/Attributes.hpp>
#include "Identifier.h"
//#include "BaseURISAXResolver.h"
#include "XBRLXLinkIdentifier.h"
#include "BaseURISAXResolver.h"
#include "SchemaIdentifier.h"
#include "XBRLIdentifier.h"
#include "LanguageIdentifier.h"
#include "ReferencePartIdentifier.h"
#include "GenericDocumentRootIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>
#include "Constants.h"
#include "XBRLException.h"
#include <xercesc/sax/SAXException.hpp>
#include "XLinkException.h"
#include "Fragment.h"
#include <iostream>
/**
* SAX content handler used to parse a document into an XBRL API data store.
* 
* The content handler is responsible for identifying 
* XML fragments to be loaded into the data store, 
* as they are parsed and then passing them over to 
* the data loader for creation and storage.
* 
* The content handler needs to be supplied with a variety 
* of helpers to assist with data storage and XLink processing. 
* These are supplied by the loader.
* 

*/
namespace xbrlcapi
{
	struct ContentHandler::Impl
	{
			void ContentHandler::error(const xercesc::SAXParseException &exc)
		{
			std::cout << "error(const xercesc::SAXParseException &exc)" << std::endl;
		}
		void ContentHandler::fatalError(const xercesc::SAXParseException &exc)
		{
			std::cout << "fatalError(const xercesc::SAXParseException &exc)" << std::endl;
		}
		void ContentHandler::resetErrors()
		{
			std::cout << "resetErrors()" << std::endl;
		}
		void ContentHandler::warning(const xercesc::SAXParseException &exc)
		{
			std::cout << "warning(const xercesc::SAXParseException &exc)" << std::endl;
		}

	   void startDocument()
	   {
	       // Set up the base URI resolver for the content handler and the XLink handler.
	       if (getURI().empty()) {
	           throw SAXException("The document URI must not be null when setting up the base URI resolver.");
	       }
	       setBaseURISAXResolver(new BaseURISAXResolverImpl(this.getURI()));
	       getXLinkHandler().setBaseURISAXResolver(this.getBaseURISAXResolver());

	       // Instantiate the fragment identifiers
	       try {
	           addIdentifier(new XBRLXLinkIdentifier(this));
	           addIdentifier(new SchemaIdentifier(this));
	           addIdentifier(new XBRLIdentifier(this));
	           addIdentifier(new LanguageIdentifier(this));
	           addIdentifier(new ReferencePartIdentifier(this));
	           addIdentifier(new GenericDocumentRootIdentifier(this));
	       } catch (XBRLException e) {
	           throw SAXException("One of the fragment identifiers could not be instantiated.",e);
	       }
	       
	   }
	//       
	//   /**
	//    * Sets the element state.
	//    * Increment the fragment children via the loader ????
	//    * Stash xsi:schemaLocation attribute URIs for discovery if required.
	//    * Identifies any new fragment.
	//    * Adds the fragment, if one is found, to the stack of fragments being built by the loader.
	//    * Update the map of defined namespaces.
	//    * Add the element to the current fragment.
	//    * 
	//    * @see org.xml.sax.ContentHandler#startElement(String, String, String, Attributes)
	//    */
	//   public void startElement(
	//           String namespaceURI, 
	//           String lName, 
	//           String qName, 
	//           Attributes attrs)
	//       
	//       Loader loader = getLoader();
	//       
	//       // Update the information about the state of the current element (tracks ancestor attributes)
	//       setElementState(new ElementState(getElementState(),new AttributesImpl( attrs )));

	//       // Stash new URIs in xsi:schemaLocation attributes if desired
	//       if (loader.useSchemaLocationAttributes()) {
	//           String schemaLocations = attrs.getValue(Constants.XMLSchemaInstanceNamespace.toString(),"schemaLocation");
	//           if (schemaLocations != null) {
	//               logger.debug("Processing schema locations: " + schemaLocations);
	//               String[] fields = schemaLocations.trim().split("\\s+");
	//               for (int i=1; i<fields.length; i=i+2) {
	//                   try {
	//                       URI uri = getBaseURISAXResolver().getBaseURI().resolve(new URI(fields[i]));
	//                       logger.debug("Working on: " + uri);
	//                       loader.stashURI(uri);
	//                   } catch (URISyntaxException e) {
	//                       logger.warn("Ignoring malformed XSI schemaLocation URI in: " + schemaLocations);
	//                   } catch (XBRLException e) {
	//                       logger.warn("A problem occurred when stashing the schemaLocation URI: " + fields[i]);
	//                   } catch (XMLBaseException e) {
	//                       logger.warn("A problem occurred when getting the base URI so schemaLocation URIs were not stashed from: " + schemaLocations);
	//                   }
	//               }
	//           }
	//       }

	//       // Identify the fragments
	//       for (Identifier identifier: getIdentifiers()) {
	//           try {
	//               identifier.startElement(namespaceURI,lName,qName,attrs);
	//               if (loader.isBuildingAFragment()) {
	//                   if (loader.getFragment().isNewFragment()) {
	//                       break;
	//                   }
	//               }
	//           } catch (XBRLException e) {
	//               logger.error(this.getURI() + " : " + e.getMessage());
	//               throw SAXException("Fragment identification failed.",e);
	//           }
	//       }

	//       if (! loader.isBuildingAFragment()) {
	//           throw SAXException("Some element has not been placed in a fragment.");
	//       }      
	//       
	//       // Insert the current element into the fragment being built
	//       try {
	//           Fragment fragment = getLoader().getFragment();
	//           if (fragment == null) throw SAXException("A fragment should be being built.");
	//           Builder builder = fragment.getBuilder();
	//           if (builder == null) throw SAXException("A fragment that is being built needs a builder.");
	//           builder.appendElement(namespaceURI, lName, qName, attrs);
	//           
	//           // Hardwire XLink resource language code inheritance to
	//           // improve query performance based on language selections.
	//           if (attrs.getIndex(Constants.XLinkNamespace.toString(),"type") > -1) {
	//               try {
	//                   Element element = fragment.getDataRootElement();
	//                   if (!element.hasAttributeNS(Constants.XMLNamespace,"lang")) {
	//                       String code = getElementState().getLanguageCode();
	//                       if (code != null) {
	//                               element.setAttribute("xml:lang",code);
	//                       }
	//                   }
	//               } catch (Throwable t) {
	//                   logger.info("bugger");
	//               }
	//           }
	//           
	//       } catch (XBRLException e) {
	//           logger.error(this.getURI() + " : " + e.getMessage());
	//           throw SAXException("The element could not be appended to the fragment.",e);
	//       }
	//       
	//   }
	//   
	   void endElement(
	           String namespaceURI, 
	           String lName, 
	           String qName)

	       // Get the attributes of the element being ended.
	       Attributes attrs = getElementState().getAttributes();

	       // Handle the ending of an element in the fragment builder
	       try {
	           getLoader().getFragment().getBuilder().endElement(namespaceURI, lName, qName);
	       } catch (XBRLException e) {
	           throw SAXException("The XBRLAPI fragment endElement failed.",e);
	       }

	       // Handle the ending of an element in the XLink processor
	       try {
	           getLoader().getXlinkProcessor().endElement(namespaceURI, lName, qName, attrs);
	       } catch (XLinkException e) {
	           throw SAXException("The XLink processor endElement failed.",e);
	       }

	       // Update the states of the fragment identifiers
	       for (Identifier identifier: this.getIdentifiers()) {
	           try {
	               identifier.endElement(namespaceURI,lName,qName,attrs);
	           } catch (XBRLException e) {
	               throw SAXException("Fragment identifier state update failed at the end of an element failed.",e);
	           }
	       }

	       // Update the state of the loader.
	       try {
	           getLoader().updateState(getElementState());
	       } catch (XBRLException e) {
	           throw SAXException("The state of the loader could not be updated at the end of element " + namespaceURI + ":" + lName + "." + e.getMessage(),e);
	       }
	               
	       // Update the information about the state of the current element
	       setElementState(getElementState().getParent());

	//   }    
	//   
	//   /**
	//    * Ignore ignorable whitespace
	//    */
	//   public void ignorableWhitespace(char buf[], int offset, int len)
	//  
	//       try {
	//           String s = String(buf, offset, len);
	//           if (!s.trim().equals(""))
	//               getLoader().getFragment().getBuilder().appendText(s);
	//       } catch (XBRLException e) {
	//           throw SAXException("Failed to handle ignorable white space." + getInputErrorInformation());
	//       }
	//   }    

	//   /**
	//    * Copy across processing instructions to the DTSImpl
	//    */
	//   public void processingInstruction(String target, String data)
	//  
	//   {
	//       try {
	//           Fragment fragment = getLoader().getFragment();
	//           if (fragment != null) {
	//               fragment.getBuilder().appendProcessingInstruction(target,data);
	//           }
	//       } catch (XBRLException e) {
	//           // Need to store processing instructions for incorporation into the fragment being created.
	//       }
	//   }    
	//   
	//   /**
	//    * Copy characters (trimming white space as required) to the DTSImpl.
	//    */
	//   public void characters(char buf[], int offset, int len) 
	//      
	//   {
	//       try {
	//           String s = String(buf, offset, len);
	//           getLoader().getFragment().getBuilder().appendText(s);
	//       } catch (XBRLException e) {
	//           throw SAXException("The characters could not be appended to the fragment." + getInputErrorInformation());
	//       }
	//   }    
	//   
	//   /**
	//    * SAX parsing locator - provides information for use in
	//    * error reporting.
	//    */
	//   private xercesc::Locator locator = null;

	//   /**
	//    * @return the locator of the current document position.
	//    */
	//   private xercesc::Locator getLocator() {
	//       return this.locator;
	//   }
	//   
	//   /**
	//    * The locator for a document is stored to facilitate resolution 
	//    * of CacheURIImpl's relative to that location.
	//    */
	//   public void setDocumentLocator(xercesc::Locator locator) {
	//       this.locator = locator;
	//   }
	//   
	//   /**
	//    * @return The public ID of the document.
	//    */
	//   private String getPublicId() {
	//       return getLocator().getPublicId();
	//   }

	//   /**
	//    * @return the system ID of the document being parsed.
	//    */
	//   private String getSystemId() {
	//       return getLocator().getSystemId();
	//   }
	//   
	//   /**
	//    * @return the line that the parser has reached.
	//    */
	//   private int getLineNumber() {
	//       return getLocator().getLineNumber();
	//   }

	//   /**
	//    * @return the column that the parser has reached.
	//    */
	//   private int getColumnNumber() {
	//       return getLocator().getColumnNumber();
	//   }
	//   
	//   /**
	//    * @return the information about the input error.
	//    */
	//   private String getInputErrorInformation() {
	//       StringBuffer s = StringBuffer("  The problem occurred in ");
	//       if (!(getSystemId() == null))
	//           s.append(getSystemId() + ".  ");
	//       else
	//           s.append("a document without a URI.  All DTS documents must have a URI but one being parsed into the DTS does not.");
	//       s.append("The problem seems to be on line" + getLineNumber() + " at column " + getColumnNumber() + ".");
	//       return s.toString();
	//   }    

	//   /**
	//    * Creates the content handler, starting out by
	//    * identifying the DTS structure that the content
	//    * handler is discovering.
	//    * @param loader The DTS loader that is using this content handler.
	//    * @param uri The URI of the document being parsed.
	//    * @throws XBRLException if any of the parameters
	//    * are null.
	//    */
	//public ContentHandler(Loader loader, URI uri)
	//	super(loader, uri);
	//   }
	//
	//   /**
	//    * Creates the content handler, starting out by
	//    * identifying the data structure that the content
	//    * handler is discovering.
	//    * @param loader The data loader that is using this content handler.
	//    * @param uri The URI of the document being parsed.
	//    * @param xml The string representation of the XML document being parsed.
	//    * @throws XBRLException if any of the parameters
	//    * are null.
	//    */
	//public ContentHandler(Loader loader, URI uri, String xml)
	//	this(loader, uri);
	//	setXML(xml);
	//}	
	//   
	    XBRLXLinkHandlerImpl getXLinkHandler()
	   	try {
	   		return (XBRLXLinkHandlerImpl) this.getLoader().getXlinkProcessor().getXLinkHandler();
	   	} catch (ClassCastException e) {
	   		throw SAXException("The XBRL API is not using the XBRL XLink Handler implementation.");
	   	}
	   }
	//   
	//   /**
	//    * The  resolver that is used to resolve URIs against
	//    * the appropriate base URI during SAX parsing.
	//    */
	//   private BaseURISAXResolver baseURISAXResolver = null;
	//   
void setBaseURISAXResolver(BaseURISAXResolver resolver)
{
	       if (resolver == null) throw SAXException("The base URI SAX resolver must not be null.");
	       this.baseURISAXResolver = resolver;
	   }
	//   
	//   /**
	//    * @return the base URI resolver for SAX parsing.
	//    */
	 BaseURISAXResolver getBaseURISAXResolver() 
	{
	       return baseURISAXResolver;
	   }
	   
	//   /**
	//    * String representation of the XML document - for documents supplied as such.
	//    */
	//   private String xml = null;
	//   
	//   /**
	//    * The list of fragment identifiers
	//    */
	//   protected List<Identifier> identifiers = this.getIdentifiers();
	//   
	//   /**
	//    * @param identifier The identifier to add to the list of
	//    * fragment identifiers used by the content handler.
	//    */
	//   protected void addIdentifier(Identifier identifier) {
	//       identifiers.add(identifier);
	//   }
	//   
		   void addIdentifier(int index, Identifier identifier) {
	       identifiers.add(index,identifier);
	   }
	//   
	//   /**
	//    * @param index The index of the identifier to remove from the list of
	//    * fragment identifiers used by the content handler.
	//    */
	//   protected void removeIdentifier(int index)
	//       if (index > identifiers.size()-1) throw XBRLException("The identifier index was too large.");
	//       if (index < 0) throw XBRLException("The identifier index was too low.");
	//       if (identifiers.size() == 0) throw XBRLException("There are no identifiers to remove.");
	//       identifiers.remove(index);
	//   }    
	//   
	//   /**
	//    * @param xml The XML stored as a string, that is to be parsed.
	//    * @throws XBRLException if the XML string is null.
	//    */
	//   private void setXML(String xml)
	//       if (xml == null) throw XBRLException("The string of XML to be parsed must not be null.");  
	//       this.xml = xml;    
	//   }    
}
