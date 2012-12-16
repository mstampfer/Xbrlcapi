
#include "Stdafx.h"
#pragma once
#include "Logger.h"


#include <string>
#include "Fact.h"
//#include "Context.h"
/**
 * @author Geoffrey Shuetrim (geoff@galexy.net)
 */

namespace xbrlcapi
{
	struct Context;
	struct Item : public Fact 
	{

	/** 
	 * Get the context for this item.
	 * Presumes that there is at most one XBRL instance in each document in the data store.
	 * @return the context fragment associated with this item
	 * @throws XBRLException if the context reference is missing or the context is unavailable.
	 */
	Context getContext();
	
    /** 
     * @return the ID of the context referenced by this item.
     * @throws XBRLException if the context reference is missing.
     */
    std::string getContextId();	

private:
Logger logger;
};
}

