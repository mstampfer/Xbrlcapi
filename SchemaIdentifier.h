#pragma once
#include "PimplImpl.h"
#include "ContentHandler.h"
#include "BaseIdentifier.h"
#include <xercesc/sax2/Attributes.hpp>

namespace xbrlcapi 
{
	/**
	* Identifies XML Schema fragments.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
	class SchemaIdentifier :  
		public BaseIdentifier, 
		public std::enable_shared_from_this<SchemaIdentifier>   
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		SchemaIdentifier();
		~SchemaIdentifier();
		SchemaIdentifier(SchemaIdentifier& rhs);
		SchemaIdentifier& operator=(SchemaIdentifier& rhs);
		SchemaIdentifier(SchemaIdentifier&& rhs);
		SchemaIdentifier& operator=(SchemaIdentifier&& rhs);
		bool operator==(const SchemaIdentifier& rhs);
		bool operator!=(const SchemaIdentifier& rhs);

		/**
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#BaseIdentifier(ContentHandler)
		*/
		SchemaIdentifier(const std::shared_ptr<ContentHandler>& contentHandler);
		std::weak_ptr<SchemaIdentifier> getPtr();
		void initialize();

		/**
		* Find fragments with root elements in the XML Schema namespace.
		* @see org.xbrlapi.sax.identifiers.BaseIdentifier#startElement(const std::string&,const std::string&,const std::string&,Attributes)
		*/
		void startElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs);

		/**
		* The implementation assumes that XML schemas do not nest XML schemas.
		* 
		* Set the target namespace to null once the schema element is ended.
		* 
		* @see Identifier#endElement(const XMLCh*, const XMLCh*, const XMLCh*, Attributes)
		*/
		void endElement(
			const XMLCh* namespaceURI, 
			const XMLCh* lName, 
			const XMLCh* qName,
			const xercesc::Attributes& attrs);

	protected:
		/**
		* @return the XML Schema grammar model.
		*/
//		XSModel getXSModel();

		/**
		* @param model The XML Schema grammar model.
		* @throws XBRLException if the model is null.
		*/
//		void setXSModel(XSModel model);

		/**
		* @return the target namespace.
		*/
		std::string getTargetNamespace();

		/**
		* @param targetNamespace The target namespace of the schema.
		*/
		void setTargetNamespace(const std::string& targetNamespace); 

		/**
		* (Commented out!) Modified on 13 February, 2007 by Howard Ungar to use the static grammar pool provided by the GrammarCache implementation.
		* TODO Determine why a static grammar pool is needed to use included anonymous schemas.
		* @return the XML Schema grammar model for the XML Schema being parsed.
		* @throws XBRLException
		*/
		//XSModel constructXSModel();

	};
}
