
#include "Stdafx.h"
#pragma once

#include <memory>

#include "XLinkHandlerDefaultImpl.h"
#include "Loader.h"
#include "XBRLXLinkHandlerImpl.h"

namespace xbrlcapi
{

	/**
	* XBRL XLink Handler
	* This class provides a real world example of an XLink handler for XBRL.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
		XBRLXLinkHandlerImpl::XBRLXLinkHandlerImpl() // Todo: use delegating ctor here when available 
		{
			XLinkHandlerDefaultImpl();
		}

		/**
		 * Set the XBRL DTS loader
		 * @param loader The XBRL DTS loader
		 */
		void XBRLXLinkHandlerImpl::setLoader(std::shared_ptr<Loader>& rhs) 
		{
			loader = rhs;
		}
		//
		///**
		// * Set the base URI resolver for the XBRL XLink handler.
		// * @param resolver the base URI resolver used by the XLink handler.
		// */
		//public void setBaseURISAXResolver(BaseURISAXResolver resolver) {
		//	baseURIResolver = resolver;
		//}

		///**
		// * Handle the XML Base attribute discovery
		// * @param value the Value of the XML Base attribute
		// */
		//public void xmlBaseStart( std::string value) throws XLinkException {
		//	try {
		//		baseURIResolver.addBaseURI(value);
		//	} catch (XMLBaseException e) {
		//		throw new XLinkException("The Base URI Resolver could not update the base URI",e);
		//	}
		//}

		///**
		// * Creates and stores an XLink title fragment.
		// */
		//public void startTitle( std::string namespaceURI,  std::string lName,  std::string qName,
		//		Attributes attrs) throws XLinkException {
		//	try {
		//		processFragment(new TitleImpl(),attrs);
		//	} catch (XBRLException e) {
		//		throw new XLinkException("The title could not be created and stored.",e);
		//	}
		//}

		///**
		// * Handle the change of XML Base scope as you step back up the tree
		// */
		//public void xmlBaseEnd() throws XLinkException {
		//		try {
		//			 baseURIResolver.removeBaseURI();
		//		} catch (XMLBaseException e) {
		//			throw new XLinkException("The Base URI Resolver could not revert to the previous base URI",e);
		//		}
		//}

		///**
		// * The extended link processing algorithm, central to this implementation, 
		// * operates as follows:
		// * <ul>
		// * <li>Store all locators and resources that are found in the extended link 
		// * in a map of lists where the map is indexed by XLink label attribute values
		// * and each list is made up of the locators and resources that have been found
		// * in the extended link that carry the same XLink label.
		// * </li>
		// * <li> 
		// * Preprocess the XLink href attribute values on locators to determine those
		// * locators linking to XML resources that have already been discovered and 
		// * parsed and those linking to XML resources that are yet to be parsed.  For 
		// * locators linking to parsed XML resources, add a relationship element to the
		// * locator containing the DTS index of the resource and add a relationship
		// * element to the resource containing the DTS index of the locator (The DTS
		// * index is the index attribute value unique within the DTS that is given to 
		// * various elements during the discovery process.)  For locators linked to 
		// * unparsed XML resources, place them in map of unprocessed locators, indexed
		// * by the href attribute value of the locator so that a resource can quickly 
		// * find all locators that point to them using the map and knowing their location.
		// * </li>
		// * <li>
		// * Store all arcs that are found in the extended link in a stack ready for 
		// * processing once the end of the extended link has been found.
		// * </li>
		// * </ul>
		// */
		//public void startExtendedLink(
		//		 std::string namespaceURI, 
		//		 std::string lName,
		//		 std::string qName, 
		//		Attributes attrs, 
		//		 std::string role, 
		//		 std::string title)
		//		throws XLinkException {
		//	
		//	try {
		//           processFragment(new ExtendedLinkImpl(),attrs);
		//	} catch (XBRLException e) {
		//		throw new XLinkException("The extended link could not be created.",e);
		//	}
		//}

		///**
		// * Nothing needs to be done at the end of the extended link discovery.
		// */
		//public void endExtendedLink( std::string namespaceURI,  std::string sName,  std::string qName)
		//		throws XLinkException {
		//	;
		//}
		//
		///**
		// * @see XLinkHandler#startResource(String, String, String, Attributes, String, String, String)
		// */
		//public void startResource(
		//		 std::string namespaceURI, 
		//		 std::string lName, 
		//		 std::string qName,
		//		Attributes attrs, 
		//		 std::string role, 
		//		 std::string title, 
		//		 std::string label)
		//		throws XLinkException {
		//	try {

		//	    Resource fragment = null;
		//	    
		//		if (namespaceURI.equals(Constants.XBRL21LinkNamespace.toString())) {
		//			if (lName.equals("label")) {
		//				fragment = new LabelResourceImpl();
		//			} else if (lName.equals("reference")) {
		//				fragment = new ReferenceResourceImpl();
		//			} else if (lName.equals("footnote")) {
		//				fragment = new FootnoteResourceImpl();
		//			}
		//		} else if (namespaceURI.equals(Constants.GenericLabelNamespace.toString())) {
		//			if (lName.equals("label")) {
		//				fragment = new LabelResourceImpl();			
		//			}
		//		} else if (namespaceURI.equals(Constants.GenericReferenceNamespace.toString())) {
		//			if (lName.equals("reference")) {
		//				fragment = new ReferenceResourceImpl();				
		//			}
		//           } else if (namespaceURI.equals(Constants.XBRLAPIEntitiesNamespace.toString())) {
		//               if (lName.equals("identifier")) {
		//                   fragment = new EntityResourceImpl();             
		//               }
		//           } else if (namespaceURI.equals(Constants.XBRLAPIMeasuresNamespace.toString())) {
		//               if (lName.equals("measure")) {
		//                   fragment = new MeasureResourceImpl();    
		//               }
		//           }			
		//		if (fragment == null) {
		//			fragment = new ResourceImpl();
		//		}
		//		
		//		processFragment(fragment,attrs);
		//           
		//	} catch (XBRLException e) {
		//		throw new XLinkException("The resource could not be created.",e);
		//	}
		//}

		///**
		// * Handle the end of the resource.
		// */
		//public void endResource( std::string namespaceURI,  std::string sName,  std::string qName) throws XLinkException {
		//	;
		//}
		//
		///**
		// * Create the locator fragment and then add it to the map of arc anchors.
		// * Finally queue up the locator href value in the exploration queue.
		// */
		//public void startLocator(
		//		 std::string namespaceURI, 
		//		 std::string lName, 
		//		 std::string qName,
		//		Attributes attrs, 
		//		 std::string href, 
		//		 std::string role, 
		//		 std::string title,
		//		 std::string label) 
		//throws XLinkException {
		//    try {
		//        try {
		//            Locator fragment = new LocatorImpl();
		//            processFragment(fragment,attrs);            

		//            Loader loader = getLoader();
		//            URI uri = baseURIResolver.getBaseURI().resolve(new URI(href));
		//            fragment.setTarget(uri);
		//            loader.stashURI(uri);

		//        } catch (URISyntaxException e) {
		//               logger.error("Problem encountered starting a locator for " + this.getLoader().getDocumentURI());
		//               throw new XLinkException("The locator href value," + href + ", is a malformed URI.",e);
		//        } catch (XMLBaseException e) {
		//               logger.error("Problem encountered starting a locator for " + this.getLoader().getDocumentURI());
		//            throw new XLinkException("Base URI problems prevented the locator href from being queued up for processing.",e);
		//        }
		//    } catch (XBRLException xbrlException) {
		//           throw new XLinkException("An XBRL Exception prevented the locator href from being queued up for processing.",xbrlException);
		//       }           
		//}


		///**
		// * Handle the end of the locator.
		// */
		//public void endLocator( std::string namespaceURI,  std::string sName,  std::string qName) throws XLinkException {
		//	;
		//}
		//
		///**
		// * Create the arc fragment first. Then add the arc to the 
		// * stack of arcs to be processed.
		// */
		//public void startArc(
		//		 std::string namespaceURI, 
		//		 std::string lName, 
		//		 std::string qName,
		//		Attributes attrs, 
		//		 std::string from, 
		//		 std::string to, 
		//		 std::string arcrole,
		//		 std::string title, 
		//		 std::string show, 
		//		 std::string actuate) throws XLinkException {
		//	try {
		//	    if (from == null || to == null) {
		//            throw new XLinkException("The XBRL XLink arc must have a 'from' and a 'to' label.");
		//	    }
		//	    processFragment(new ArcImpl(),attrs);
		//	} catch (XBRLException e) {
		//		throw new XLinkException("The arc could not be created.",e);
		//	}
		//}
		//
		///**
		// * Handle the end of the arc.
		// */
		//public void endArc( std::string namespaceURI,  std::string sName,  std::string qName) throws XLinkException {
		//	;
		//}
		//
		///**
		// * Add the href to the set of XML documents to be explored and 
		// * create the fragment for the simple link.
		// * TODO Should simple links generate relationship metadata?
		// */
		//public void startSimpleLink(
		//		 std::string namespaceURI, 
		//		 std::string lName,
		//		 std::string qName, 
		//		Attributes attrs, 
		//		 std::string href, 
		//		 std::string role,
		//		 std::string arcrole, 
		//		 std::string title, 
		//		 std::string show, 
		//		 std::string actuate)
		//		throws XLinkException {
		//	
		//       SimpleLink fragment = new SimpleLinkImpl();
		//	try {
		//           processFragment(fragment,attrs);
		//       } catch (XBRLException e) {
		//           throw new XLinkException("The simple link fragment could not be processed.",e);
		//       }

		//       URI uri = null;
		//       try {
		//           uri = new URI(href);
		//       } catch (URISyntaxException e) {
		//               throw new XLinkException("The simple link URI could not be queued up for exploration in DTS discovery.",e);
		//       }

		//       if (! uri.isAbsolute()) {
		//           URI baseUri = null;
		//           try {
		//               baseUri = baseURIResolver.getBaseURI();
		//           } catch (XMLBaseException e) {
		//               throw new XLinkException("The base URI to use for URI resolution cannot be accessed.",e);
		//           }
		//           uri = baseUri.resolve(uri);
		//       }

		//       logger.debug("Got a simple link to " + uri);
		//       
		//       Loader loader = null;
		//       try {
		//           loader = getLoader();
		//       } catch (XBRLException e) {
		//           throw new XLinkException("The loader could not be accessed so the simple link URI cannot be stashed for discovery.",e);
		//       }

		//       try {
		//           fragment.setTarget(uri);
		//       } catch (XBRLException e) {
		//           throw new XLinkException("The simple link fragment target could not be set to " + uri,e);
		//       }

		//       try {
		//           loader.stashURI(uri);
		//       } catch (XBRLException e) {
		//           throw new XLinkException("The simple link URI could not be stashed for future discovery: " + href,e);
		//       }

		//}
		//
		///**
		// * Handle the end of the simple link
		// */
		//public void endSimpleLink( std::string namespaceURI,  std::string sName,  std::string qName) throws XLinkException {
		//	;
		//}
		//	
		///**
		// * @return The XBRL DTS loader that is using this XLink handler.
		// * @throws XBRLException if the XLink handler has no loader to work with.
		// */
		//private Loader getLoader() {
		//	if (loader == null) throw new XBRLException("The XLink Handler has no XBRL DTS loader to work with.");
		//	return loader;
		//}

		///**
		// * @param elementState The state for the current element.
		// */
		//public void setElementState(ElementState elementState) {
		//	this.elementState = elementState; 
		//}
		//
		//private ElementState getElementState() {
		//	return elementState; 
		//}	
		//
		//   /**
		//    * Walter Hamscher has identified documents in the XBRL community that violate the constraint
		//    * that attributes not defined in the XLink specification must not be in the XLink namespace.
		//    * To accommodate this imperfection, we catch that kind of error and make it a warning.
		//    * 
		//    * @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		//    */
		//   public void error( std::string namespaceURI,  std::string lName,  std::string qName,
		//           Attributes attrs, std::string message) throws XLinkException {

		//       if (message.endsWith(" is not defined in the XLink namespace.")) {
		//           this.warning(namespaceURI, lName, qName, attrs, message);
		//           return;
		//       }

		//       throw new XLinkException(message);
		//   }
		//   
		//   /**
		//    * Log a warning message
		//    * @see org.xbrlapi.xlink.XLinkHandler#warning(java.lang.String,java.lang.String, java.lang.String, org.xml.sax.Attributes, java.lang.String)
		//    */
		//   public void warning( std::string namespaceURI,  std::string lName,  std::string qName,
		//           Attributes attrs, std::string message) throws XLinkException {
		//       logger.warn(message);
		//   }
		//   
		//   /**
		//    * Set up the fragment and add it to the loader.
		//    * @param fragment The newly identified fragment.
		//    * @param attrs The attributes of the root element of the fragment.
		//    * @throws XBRLException
		//    */
		//   private void processFragment(const Fragment& fragment,Attributes attrs) {
		//       Loader loader = this.getLoader();
		//       fragment.setBuilder(new BuilderImpl(loader.getBuilderDOM()));
		//        std::string index = getLoader().getNextFragmentId();
		//       if (index == null) throw new XBRLException(getLoader().getDocumentURI() + ": The fragment index MUST not be null.");
		//       if (index.equals("")) throw new XBRLException(getLoader().getDocumentURI() + ": The fragment index MUST not be the empty string.");
		//       fragment.setIndex(index);
		//       if (attrs.getValue("id") != null) {
		//           fragment.appendID(attrs.getValue("id"));
		//           this.getElementState().setId(attrs.getValue("id"));
		//       }
		//       loader.add(fragment,getElementState());
		//   }

		//   /**
		//    * @see java.lang.Object#hashCode()
		//    */
		//   @Override
		//   public int hashCode() {
		//       final int prime = 31;
		//       int result = super.hashCode();
		//       result = prime * result + ((baseURIResolver == null) ? 0 : baseURIResolver.hashCode());
		//       return result;
		//   }

		//   /**
		//    * @see java.lang.Object#equals(java.lang.Object)
		//    */
		//   @Override
		//   public bool equals(Object obj) {
		//       if (this == obj)
		//           return true;
		//       if (!super.equals(obj))
		//           return false;
		//       if (getClass() != obj.getClass())
		//           return false;
		//       XBRLXLinkHandlerImpl other = (XBRLXLinkHandlerImpl) obj;
		//       if (baseURIResolver == null) {
		//           if (other.baseURIResolver != null)
		//               return false;
		//       } else if (!baseURIResolver.equals(other.baseURIResolver))
		//           return false;
		//       return true;
		//   }
		//   
	};

