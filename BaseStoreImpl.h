#include "Stdafx.h"
#pragma once
#include "DefaultMatcherImpl.h"
#include "HashFunctions.h"
#include "Fragment.h"
#include "Stub.h"
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <map>
///**
// * Abstract base implementation of the data store
// * providing all methods of the store interface that
// * do not depend on the nature of the underlying data store
// * implementation.
// * 
// * @author Geoffrey Shuetrim (geoff@galexy.net)
// */

namespace xbrlcapi
{
	class LoaderImpl;
	class BaseStoreImpl 
	{

	private:
		     static const long long serialversionuid = -3709078033252193797l;
//		     xercesc::DOMImplementationRegistry domimplementationregistry;
//			 static const logger logger = logger.getlogger(basestoreimpl.class);
			int loadingStatus;
//			std::map<Poco::URI,Loader> loadingRights;
			BaseStoreImpl& operator=(const BaseStoreImpl& rhs);
			BaseStoreImpl(const BaseStoreImpl& rhs);
			std::unordered_set<Poco::URI> uris;
		    protected:
			std::shared_ptr<xercesc::DOMDocument> storedom;
		    std::shared_ptr<xercesc::DOMImplementationLS> domimplementation;
	//    /**
	//     * This property is used to co-ordinate the document
	//     * loading activities of loaders that are operating in
	//     * parallel on the one data store.  It is used to 
	//     * prevent the same document from being simultaneously
	//     * loaded by several of the loaders.
	//     */
	//    transient private 
			std::unordered_map<Poco::URI,std::shared_ptr<LoaderImpl>> loadingRights;		    	    
		    /**
		     * resource matcher
		     */
		protected:
		DefaultMatcherImpl matcher;
			    /**
	     * Namespace bindings map from prefix to namespace.
	     */
	    std::unordered_map<std::string,std::string> namespaceBindings;   
		//
	public:
		BaseStoreImpl();
		BaseStoreImpl(BaseStoreImpl&& rhs);
		BaseStoreImpl& operator=(BaseStoreImpl&& rhs);
		DefaultMatcherImpl getMatcher();  		
		bool hasDocument(const Poco::URI& uri);
		void startLoading();		
		void stopLoading();
		std::vector<Poco::URI> getDocumentsToDiscover();
		std::vector<Stub> getXMLResources(const std::string& interfaceName);
		std::string getId(const std::string& input);
		bool requestLoadingRightsFor(LoaderImpl& loader, const Poco::URI& document);
		void recindLoadingRightsFor(LoaderImpl& loader, const Poco::URI& document);
		std::unordered_set<Poco::URI> getFilteringURIs();
		bool isFilteringByURIs();
		std::string getURIFilteringPredicate();
		std::vector<Stub> getStubs();
	};
}
