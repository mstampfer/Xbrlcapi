/**
* Commandline example showing:
* 1. How to load an XBRL instance document
* 2. How to analyse the presentation networks for that instance
*/

#include "Load.h"
#include "Instance.h"
#include "Item.h"
#include "Loader.h"
#include "CacheFile.h"
#include "XBRLXLinkHandler.h"
#include "XBRLException.h"
#include "CustomLinkRecogniser.h"
#include "XLinkProcessor.h"
#include "EntityResolver.h"
#include "Cache.h"
#include "log4cpp/PropertyConfigurator.hh"
#include <memory>
#include <Poco/Exception.h>
#include <boost/uuid/uuid.hpp>


using Poco::URI;
namespace xbrlcapi
{

	/**
	*  This example loads a set of documents, including one or more XBRL instances,
	*  based on the list of URLs provided on the command line.  The documents
	*  are loaded into a Oracle Berkeley XML Database (but this can easily be modified
	*  by using a different data store) and then the information in the instances
	*  that have been loaded is analysed and reported on, demonstrating how
	*  the XBRLAPI can be used to access information in instances.
	* @author Geoff Shuetrim (geoff@galexy.net)
	*/

	/**
	* Report the information about a concept in the presentation heirarchy
	* @param indent The indent to use for reporting the fragment
	* @param fragment The fragment to report
	* @param linkRole The linkrole of the network to use
	* @throws XBRLExceptions
	*/
	//void Load::reportNode(const std::string& indent, const Fragment& fragment, const std::string& linkRole) 
	//{
	//	Concept concept = dynamic_cast<Concept&>(fragment);
	//	std::cout << indent + concept.getTargetNamespace() + ":" + concept.getName();
	//	//auto children = store.getTargets<Fragment>(concept.getIndex(),linkRole,xbrlcapi::PresentationArcrole);
	//	//if (children.size() > 0) {
	//	//	for (const Fragment& child: children) {
	//	//		reportNode(indent + " ", child,linkRole);
	//	//	}  
	//	//}
	//}

	//void Load::reportInstance(Instance& instance) 
	//{
	//	std::vector<Item> items = instance.getChildItems();
	//	std::cout << "Top level items in the instance." << std::endl;
	//	for (Item item: items) {
	//		//				std::cout << item.getLocalname() + " " + item.getContextId();
	//	}

	//	std::vector<Context> contexts = instance.getContexts();
	//	std::cout << "Contexts in the instance." << std::endl;
	//	for (Context context: contexts) {
	//		std::cout << "Context ID " + context.getId();
	//	}

	//	std::vector<Unit> units = instance.getUnits();
	//	std::cout << "Units in the instance." << std::endl;
	//	for (Unit unit: units) {
	//		std::cout << "Unit ID " + unit.getId();
	//	}

	//	std::vector<ExtendedLink> links = instance.getFootnoteLinks();
	//	std::cout << "Footnote links in the instance." << std::endl;
	//	for (ExtendedLink link: links) {            
	//		std::vector<Resource> resources = link.getResources();
	//		for (Resource resource: resources) {
	//			FootnoteResource fnr = dynamic_cast<FootnoteResource&>(resource);
	//			std::cout << "Footnote resource: " + *fnr.getDataRootElement().getTextContent();
	//		}
	//	}
	//}

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
	Store Load::createStore(const std::string& database, 
		const std::string& container, 
		const std::string& cacheSize
		) 
	{
		if (cacheSize.empty()) 
		{
			std::cout << "Using the default cache size." << std::endl;
			return Store(database,container);
		}
		auto size = std::stoi(cacheSize);
		std::cout << "Using the cache size = " << size << std::endl;
		return Store(database,container,size);
	}


	void initLogger()
	{
		log4cpp::Category &log_root = log4cpp::Category::getRoot();
		log4cpp::Category &log_sub1 = log4cpp::Category::getInstance( std::string("log_sub1") );
		log4cpp::Category &log_sub2 = log4cpp::Category::getInstance( std::string("log_sub1.log_sub2") );

		const char *file_log4cpp_init = "log4cpp.properties";

		try
		{
			log4cpp::PropertyConfigurator::configure( file_log4cpp_init );
		}
		catch( log4cpp::ConfigureFailure &e )
		{
			std::cout 
				<< e.what() 
				<< " [log4cpp::ConfigureFailure catched] while reading " 
				<< file_log4cpp_init 
				<< std::endl;

			exit(1);
		}
	}
	///**
	//* @param store The store to use for the loader.
	//* @param cache The root directory of the document cache.
	//* @return the loader to use for loading the instance and its DTS
	//* @throws XBRLException if the loader cannot be initialised.
	//*/
	std::shared_ptr<Loader> Load::createLoader(Store& store, const std::string& filename) 
	{
		std::unordered_map<Poco::URI,Poco::URI> map;
		initLogger();
		log4cpp::Category &logger = log4cpp::Category::getInstance( std::string("log_sub1") );
		XLinkHandler xlinkHandler;
		CustomLinkRecogniser customLinkRecogniser; 
		XLinkProcessor xlinkProcessor(xlinkHandler,customLinkRecogniser);

		try 
		{
			// Rivet errors in the SEC XBRL data require these URI remappings to prevent discovery process from breaking.
			map.insert(std::make_pair(Poco::URI("http://www.xbrl.org/2003/linkbase/xbrl-instance-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xbrl-instance-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/instance/xbrl-instance-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xbrl-instance-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/linkbase/xbrl-linkbase-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xbrl-linkbase-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/instance/xbrl-linkbase-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xbrl-linkbase-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/instance/xl-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xl-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/linkbase/xl-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xl-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/instance/xlink-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xlink-2003-12-31.xsd")));
			map.insert(std::make_pair( Poco::URI("http://www.xbrl.org/2003/linkbase/xlink-2003-12-31.xsd"),
				Poco::URI("http://www.xbrl.org/2003/xlink-2003-12-31.xsd")));

			Cache cache(CacheFile(filename), map);
			EntityResolver entityResolver(cache);      
			std::shared_ptr<Loader> loader(new Loader(store, xlinkProcessor, entityResolver));
			//			loader->setEntityResolver(entityResolver);
			//			xlinkHandler->setLoader(*loader);
			store.setLoader(loader->tag());
			return loader;
		}
		catch (Poco::SyntaxException) 
		{
			throw std::exception("URI syntax exception");
		}		
		catch (const XBRLException& e)
		{
			logger.error("Error initializing Loader " + e.getMessage());
		}
		catch (...)
		{
			logger.error("Unknown error initializing Loader ");
		}
	}

	/**
	* Helper method to clean up and shut down the data store.
	* @param store the store for the XBRL data.
	* @throws XBRLException if the store cannot be closed. 
	*/
	void Load::cleanup(Store& store) 
	{
		store.close();
	}    
	/**
	/* Report incorrect usage of the command line, with a list of the arguments
	/* @param message The error message describing why the command line usage failed.
	*/
	void Load::xmessage()
	{
		std::cout << "Command line usage: xbrlcapi -database VALUE -container VALUE -cache VALUE URI1 URI2 ..." << std::endl;
		std::cout << "Mandatory arguments: " << std::endl;
		std::cout << " -database VALUE   directory containing the Oracle BDB XML database" << std::endl;
		std::cout << " -container VALUE  name of the data container" << std::endl;
		std::cout << " -cache VALUE      directory that is the root of the document cache" << std::endl;
		std::cout << "Optional arguments: " << std::endl;
		std::cout << " -dbCacheSize VALUE    Size of the cache (in MB) to use for the Oracle BDB XML database" << std::endl;        
		std::cout << "EG: To load the XBRL instance schema." << std::endl;
		std::cout << "xbrlcapi -dbCacheSize 250 -database /home/geoff/container -container test -cache /home/geoff/cache http://www.xbrl.org/2003/xbrl-instance-2003-12-31.xsd" << std::endl;        
	}

	void Load::badUsage(const std::string& message) 
	{
		if (!("" == (message))) 
		{
			std::cout << message;
		}
		xmessage();
	}
}


int main(int argv, char * args[]) 
{ 

	log4cpp::Category& logger = log4cpp::Category::getInstance( std::string("log_sub1") );

	try 
	{
		xercesc::XMLPlatformUtils::Initialize();
	}
	catch (const xercesc::XMLException& ) 
	{
		std::cout << "Unable to initialize xerces subsystem." << std::endl;
	}

	try 
	{
		// Process command line arguments
		std::vector<Poco::URI> inputs;
		std::unordered_map<std::string, const std::string> arguments;
		size_t i = 1;
		if (i >= argv-1)
			xbrlcapi::Load::badUsage("No map of taxonomies has been specified");
		while (true) 
		{
			if (i == argv)
				break;

			std::cout << args[i] << std::endl;
			if (args[i][0] == '-')
			{
				if (strcmp(args[i], "-database") == 0) 
				{
					i++;
					arguments.insert(std::make_pair("database", args[i]));
				} 
				else if (strcmp(args[i], "-container") == 0)
				{
					i++;
					arguments.insert(std::make_pair("container", args[i]));
				} 
				else if (strcmp(args[i], "-cache") == 0)
				{
					i++;
					arguments.insert(std::make_pair("cache", args[i]));
				} 
				else if (strcmp(args[i], "-dbCacheSize") == 0)
				{
					i++;
					arguments.insert(std::make_pair("dbCacheSize", args[i]));

				} else
					xbrlcapi::Load::badUsage("Unknown argument: " + std::string(args[i]));
			} 
			else 
			{
				try 
				{
					inputs.push_back(Poco::URI(args[i]));
				} 
				catch (...) 
				{
					xbrlcapi::Load::badUsage("Malformed discovery starting point URI: " + std::string(args[i]));
				}
			}
			i++;
		}

		if (arguments.find("database") == arguments.end()) 
			xbrlcapi::Load::badUsage("You need to specify the database directory.");
		if (arguments.find("container") == arguments.end()) 
			xbrlcapi::Load::badUsage("You need to specify the database container name.");
		if (arguments.find("cache")  == arguments.end()) 
			xbrlcapi::Load::badUsage("You need to specify the root of the document cache.");
		if (inputs.size() < 1) xbrlcapi::Load::badUsage("You need to specify at least one starting point for discovery.");

		// Make sure that the taxonomy cache exists
		try 
		{
			xbrlcapi::CacheFile cache(arguments["cache"]);
			if (!cache) 
				xbrlcapi::Load::badUsage("The document cache directory does not exist. " + arguments["cache"]);
		} catch (...) 
		{
			xbrlcapi::Load::badUsage("There are problems with the cache location: " + arguments["cache"]);
		}

		// Set up the cache size if that has been specified.


		// Set up the data store to load the data
		auto store = xbrlcapi::Load::createStore(arguments["database"],arguments["container"], arguments["dbCacheSize"]);

		// Set up the data loader (does the parsing and data discovery)
		auto loader = xbrlcapi::Load::createLoader(store,arguments["cache"]);

		// Load the instance data
		loader->discover(inputs);

		// Clean up the data store and exit
		xbrlcapi::Load::cleanup(store);

		xercesc::XMLPlatformUtils::Terminate();
	}
	catch (const xbrlcapi::XBRLException& e)
	{
		logger.error(e.getMessage());
	}
	catch (std::exception& e) 
	{
		xbrlcapi::Load::badUsage(e.what());
	}

}


