#include "stdafx.h"
#pragma once
#include <string>
#include <unordered_set>
#include "Poco/URI.h"
#include "History.h"

namespace xbrlcapi
{
	class HistoryImpl : public History 
	{

	private:
		static const long long serialVersionUID = -4599201126216530103L;

		//private static const Logger logger = Logger.getLogger(HistoryImpl.class);

		/**
		* @see History#addRecord(URI, String)
		*/
	public:
		void addRecord(const Poco::URI& uri, const std::string& identifier);

		/**
		* @see History#getIdentifier(URI)
		*/
		std::string getIdentifier(const Poco::URI& uri);

		std::unordered_set<Poco::URI> getURIs();

		/**
		* @see java.lang.Object#equals(java.lang.Object)
		*/
		//bool equals(Object obj);

	};
}
