
#include "StubImpl.h"
namespace xbrlcapi
{
	StubImpl::StubImpl()
	{
	}
	/**
	* @param id The unique id of the fragment being created,
	* within the scope of the containing data store.
	* @throws XBRLException
	*/
	StubImpl::StubImpl(const std::string& id, const Poco::URI& uri, const std::string& reason) 
	{
		//this();
		//setBuilder(new BuilderImpl());
		//if (id == null) throw XBRLException("The stub index must not be null.");
		//this.setIndex(id);
		//if (uri == null) throw XBRLException("The stub URI must not be null.");
		//this.setResourceURI(uri);
		//if (reason == null) throw XBRLException("The reason must not be null.");		
		//this.setReason(reason);

		//// Up to here all of the properties have been stored in an XML DOM being
		//// put together by the builder.

		//this.finalizeBuilder();
	}

	/**
	* @see org.xbrlapi.Stub#getReason()
	*/
	std::string StubImpl::getReason() 
	{
		//return this.getMetaAttribute("reason"); 
		return std::string();
	}

	/**
	* @see org.xbrlapi.Stub#getResourceURI()
	*/
	Poco::URI StubImpl::getResourceURI() 
	{
		//std::string uri = "";
		//try 
		//{
		//	uri  = this.getMetaAttribute("resourceURI");
		//	return new Poco::URI(uri);
		//} catch (URISyntaxException e) 
		//{
		//	throw XBRLException(" URI: " + uri + " has incorrect syntax .", e);
		//}
		return Poco::URI();
	}

	/**
	* @see org.xbrlapi.Stub#setResourceURI(URI)
	*/
	void StubImpl::setResourceURI(Poco::URI uri) 
	{
		//if (uri == null) throw XBRLException("The stub URI must not be null.");
		//this.setMetaAttribute("resourceURI",uri.toString());
	}

	/**
	* @see org.xbrlapi.Stub#setReason(std::string)
	*/
	void StubImpl::setReason(const std::string& reason) 
	{
		//if (reason == null) throw XBRLException("The reason must not be null.");
		//this.setMetaAttribute("reason",reason);
	}    
}
