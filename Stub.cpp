#include "Stub.h"
#include <string>
namespace xbrlcapi
{

	struct Stub::Impl 
	{
		Impl() {}

		/**
		* @param id The unique id of the fragment being created,
		* within the scope of the containing data store.
		* @throws XBRLException
		*/

		Impl(const std::string& id, const Poco::URI& uri, const std::string& reason) 
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

		std::string getReason() 
		{
			//return this.getMetaAttribute("reason"); 
			return std::string();
		}

		Poco::URI getResourceURI() 
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
		void setResourceURI(Poco::URI uri) 
		{
			//if (uri == null) throw XBRLException("The stub URI must not be null.");
			//this.setMetaAttribute("resourceURI",uri.toString());
		}

		/**
		* @see org.xbrlapi.Stub#setReason(std::string)
		*/
		void setReason(const std::string& reason) 
		{
			//if (reason == null) throw XBRLException("The reason must not be null.");
			//this.setMetaAttribute("reason",reason);
		}    


	};

	Stub::Stub() {}
	Stub::Stub(const std::string& id, const Poco::URI& uri, const std::string& reason) : 
		pImpl(id, uri, reason)
	{}
	Stub::~Stub() {} 

	Stub::Stub(const Stub& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Stub& Stub::operator=(const Stub& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Stub::Stub(Stub&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Stub& Stub::operator=(Stub&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Stub::operator==(const Stub& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Stub::operator!=(const Stub& rhs)
	{
		return !this->operator==(rhs);
	}			
	
	std::string Stub::getReason()
	{
		return pImpl->getReason();
	}

	Poco::URI Stub::getResourceURI()		
	{
		return pImpl->getResourceURI();
	}

	void Stub::setResourceURI(const Poco::URI& uri)		
	{
		return pImpl->setResourceURI(uri);
	}

	void Stub::setReason(std::string reason)		
	{
		return pImpl->setReason(reason);
	}

}
