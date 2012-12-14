#include "stdafx.h"
#include "HistoryImpl.h"

namespace xbrlcapi
{

		/**
		* @see History#addRecord(Poco::URI, String)
		*/
		void HistoryImpl::addRecord(const Poco::URI& uri, const std::string& identifier) 
		{
			//logger.debug(uri + " has identifier: " + identifier);
		}

		/**
		* @see History#getIdentifier(Poco::URI)
		*/
		std::string HistoryImpl::getIdentifier(const Poco::URI& uri) 
		{
			return "";
		}    

		std::unordered_set<Poco::URI> HistoryImpl::getURIs() 
		{
			return std::unordered_set<Poco::URI>();
		}

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
		//bool HistoryImpl::equals(Object obj) {
		//        if (this == obj)
		//            return true;
		//        if (obj == NULL)
		//            return false;
		//        if (getClass() != obj.getClass())
		//            return false;
		//        return true;
		//    }

}