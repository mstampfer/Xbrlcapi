#pragma once
#include "PimplImpl.h"
#include <Poco/URI.h>
#include <string>
#include "BaseURIResolver.h"

namespace xbrlcapi
{
	class BaseURISAXResolver : public BaseURIResolver
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		/**
		* Constructor for processing documents without a 
		* base URI.  Sets the documentURI to null.
		*/
		BaseURISAXResolver();

		/**
		* Constructor takes the absolute URI of the
		* document to be processed using this BaseURISAXResolver
		* Implementation as an input.  This is then used
		* as part of the Base URI resolution.
		* @param documentURI The absolute URI of
		* the base document.  If the base document does not
		* have a base URI then this parameter must be null if
		* this constructor is being used.
		*/
		BaseURISAXResolver(const Poco::URI& documentURI);
		~BaseURISAXResolver();
		BaseURISAXResolver(const BaseURISAXResolver& rhs);
		BaseURISAXResolver& operator=(const BaseURISAXResolver& rhs);
		BaseURISAXResolver(BaseURISAXResolver&& rhs);
		BaseURISAXResolver& operator=(BaseURISAXResolver&& rhs);
		bool operator==(const BaseURISAXResolver& rhs);
		bool operator!=(const BaseURISAXResolver& rhs);

		Poco::URI getBaseURI();

		/**
		* Updates the XML Base given new base information
		* Used on the start of element XML base event.
		* @param xmlBase the value of the xmlBase attribute if supplied.
		*/
		void addBaseURI(const std::string& xmlBase);

		/**
		* Reverts to the previous Base URI - used on the end of 
		* element XML base event.
		*/
		void removeBaseURI();
	};
}
