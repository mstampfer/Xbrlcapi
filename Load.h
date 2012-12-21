#include "Stdafx.h"
#pragma once
#include "Logger.h"

/**
* Commandline example showing:
* 1. How to load an XBRL instance document
* 2. How to analyse the presentation networks for that instance
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "Store.h"
//#include "LoaderImpl.h"
#include "Store.h"
#include "HashFunctions.h"

using Poco::URI;
namespace xbrlcapi
{
	class Loader;
	struct Instance;
	/**
	*  This example loads a set of documents, including one or more XBRL instances,
	*  based on the list of URLs provided on the command line.  The documents
	*  are loaded into a Oracle Berkeley XML Database (but this can easily be modified
	*  by using a different data store) and then the information in the instances
	*  that have been loaded is analysed and reported on, demonstrating how
	*  the XBRLAPI can be used to access information in instances.
	* @author Geoff Shuetrim (geoff@galexy.net)
	*/
	class Load 
	{

	private:
		Store store;

		/**
		* Report the information about a concept in the presentation heirarchy
		* @param indent The indent to use for reporting the fragment
		* @param fragment The fragment to report
		* @param linkRole The linkrole of the network to use
		* @throws XBRLExceptions
		*/
		static void reportNode(const std::string& indent, const Fragment& fragment, const std::string& linkRole); 
		static void reportInstance(const Instance& instance); 

		/**
		* Report incorrect usage of the command line, with a list of the arguments
		* @param message The error message describing why the command line usage failed.
		*/
		static void xmessage();

	public:
	public:
		/**
		* Create an Oracle Berkeley XML database store and return it
		* cast to an XBRL data store to expose XBRL store enhancements.
		* @param database The location to use for the new store.
		* @param container The name to use for the XML container.
		* @param cacheSize The std::string representation of the number of MB of database
		* cache to use.
		* @return the new store.
		* @throws XBRLException if the store cannot be initialised.
		*/
		static Store createStore(const std::string& database, const std::string& container, const std::string& cacheSize = ""); 

		/**
		* @param store The store to use for the loader.
		* @param cache The root directory of the document cache.
		* @return the loader to use for loading the instance and its DTS
		* @throws XBRLException if the loader cannot be initialised.
		*/
		static std::shared_ptr<Loader> createLoader(Store& store, const std::string& cache);

		/**
		* Helper method to clean up and shut down the data store.
		* @param store the store for the XBRL data.
		* @throws XBRLException if the store cannot be closed. 
		*/
		static void cleanup(Store& store);

		static void badUsage(const std::string& message); 

		/**
		*  This example loads a set of documents, including one or more XBRL instances,
		*  based on the list of URLs provided on the command line.  The documents
		*  are loaded into a Oracle Berkeley XML Database (but this can easily be modified
		*  by using a different data store) and then the information in the instances
		*  that have been loaded is analysed and reported on, demonstrating how
		*  the XBRLAPI can be used to access information in instances.
		* @author Geoff Shuetrim (geoff@galexy.net)
		*/


		void Load::reportInstance(Instance& instance);



	
private:
Logger logger;
};
}