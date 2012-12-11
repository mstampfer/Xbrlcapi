#include "stdafx.h"
#include "Poco/URI.h"
#include "Stub.h"

namespace xbrlcapi
{
	class StubImpl : public Stub 
	{
	private:
		static const long long serialVersionUID = 4672320267418877015L;

		/**
		* No argument constructor.
		* @throws XBRLException
		*/
	public:
		StubImpl();

		/**
		* @param id The unique id of the fragment being created,
		* within the scope of the containing data store.
		* @throws XBRLException
		*/
		StubImpl(const std::string& id, const Poco::URI& uri, const std::string& reason);

		/**
		* @see org.xbrlapi.Stub#getReason()
		*/
		std::string getReason();

		/**
		* @see org.xbrlapi.Stub#getResourceURI()
		*/
		Poco::URI getResourceURI();

		/**
		* @see org.xbrlapi.Stub#setResourceURI(URI)
		*/
		void setResourceURI(Poco::URI uri);

		/**
		* @see org.xbrlapi.Stub#setReason(std::string)
		*/
		void setReason(const std::string& reason);
	};
}
