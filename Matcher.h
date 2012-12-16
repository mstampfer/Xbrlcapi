#include "stdafx.h"
#pragma once
#include "Logger.h"
#include <Poco/URI.h>
#include <vector>

/**
* The resource matcher interface, defining all methods that need to be 
* implemented by a resource matcher to support XBRLAPI data stores.
* @author Geoffrey Shuetrim (geoff@galexy.net)
*/

namespace xbrlcapi
{
	struct Signer;

	struct Matcher //extends Serializable 
	{
		virtual ~Matcher(){}
		/**
		* Call this method if you need to use a different signature
		* generator for the resources you are working with.
		* @param signer The object used to generate signatures.
		*/
		virtual void setSigner(const Signer& signer) = 0;

		/**
		* @param uri The URI of the resource to obtain the signature for.
		* @return the signature for the resource specified by the URI or null
		* if the resource could not be accessed.
		* @throws XBRLException if the signature cannot be constructed.
		*/
		virtual std::string getSignature(const Poco::URI& uri) = 0;

		/**
		* As a side effect, this method adds the specified
		* URI to the matcher.
		* @param uri The URI of the resource to be tested for a match.
		* @return the URI of the matching resource in the data store if one
		* exists and the original URI otherwise (because it becomes the
		* matching URI in the data store).
		* @throws XBRLException
		*/
		virtual Poco::URI getMatch(const Poco::URI& uri) = 0;

		/**
		* @param uri The URI to test.
		* @return true if the matcher has a URI that is a match for the 
		* given URI (this match may be the URI itself).
		* @throws XBRLException
		*/
		virtual bool hasURI(const Poco::URI&  uri) = 0;


		/**
		* @param uri The URI of the resource to be tested for a match.
		* @return a list of all URIs that match the given URI, including the given URI.
		* @throws XBRLException
		*/
		virtual std::vector<Poco::URI> getAllMatchingURIs(const Poco::URI&  uri) = 0;

		/**
		* Deletes the given URI from the matcher.
		* @param uri The URI to delete.
		* @return the new match URI for documents that used to 
		* match the given URI or null if there is none.
		* @throws XBRLException if the URI is null.
		*/
		virtual Poco::URI del(const Poco::URI&  uri) = 0;

	private:
Logger logger;
};
}
