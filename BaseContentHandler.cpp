#include "BaseContentHandler.h"
#include <list>
#include <Poco/URI.h>
#include "ElementState.h"
#include "Identifier.h"

namespace xbrlcapi
{
	struct BaseContentHandler::Impl 
	{
		ElementState state;
		std::list<std::shared_ptr<Identifier>> identifiers;
		Poco::URI uri;

		Impl() {}
		Impl(const Poco::URI& uri) :
			uri(uri)
		{}

		const Poco::URI getURI() const 
		{
			return uri;
		}

		void setURI(const Poco::URI& uri)
		{
			this->uri = uri;
		}

		void setElementState(const ElementState& state)
		{
			this->state = state;
		}

		ElementState getElementState() 
		{
			return state;
		}    

		std::list<std::shared_ptr<Identifier>> getIdentifiers()  
		{
			return identifiers;
		}    

		void error(const xercesc::SAXParseException& exception)
		{
			/*if (exception.getMessage().contains("Cannot find the declaration of element"))
			if (exception.getMessage().contains("'schema'") || exception.getMessage().contains(":schema'"))
			return;*/
			//		logger.error(":" + exception.getMessage() + ": on line number " + exception.getLineNumber());
		}

		void fatalError(const xercesc::SAXParseException& exception) 
		{
			//	logger.error(exception.getMessage() + ": on line number " + exception.getLineNumber());
		}

		void warning(const xercesc::SAXParseException& exception)
		{
			//logger.warn(exception + "  Carrying on with parsing without doing validation.");
		}

	};

	BaseContentHandler::BaseContentHandler(const Poco::URI& uri) : pImpl(uri)
	{}

	BaseContentHandler::BaseContentHandler() : pImpl()
	{}

	BaseContentHandler::~BaseContentHandler() 
	{} 

	BaseContentHandler::BaseContentHandler(const BaseContentHandler& rhs) : pImpl(rhs.pImpl)
	{}

	BaseContentHandler& BaseContentHandler::operator=(const BaseContentHandler& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			//pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	BaseContentHandler::BaseContentHandler(BaseContentHandler&& rhs) : pImpl(std::move(rhs.pImpl))
	{}

	BaseContentHandler& BaseContentHandler::operator=(BaseContentHandler&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool BaseContentHandler::operator==(const BaseContentHandler& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool BaseContentHandler::operator!=(const BaseContentHandler& rhs)
	{
		return !this->operator==(rhs);
	}

	const Poco::URI BaseContentHandler::getURI() const
	{
		return pImpl->getURI();
	}

	void BaseContentHandler::setURI(const Poco::URI& uri)
	{
		pImpl->setURI(uri);
	}

	void BaseContentHandler::setElementState(ElementState& state)
	{
		pImpl->setElementState(state);
	}

	ElementState BaseContentHandler::getElementState()
	{
		return pImpl->getElementState();
	}

	std::list<std::shared_ptr<Identifier>> BaseContentHandler::getIdentifiers()
	{
		return pImpl->getIdentifiers();
	}

	void BaseContentHandler::error(const xercesc::SAXParseException& exception) 
	{
		pImpl->error(exception);
	}


	void BaseContentHandler::fatalError(const xercesc::SAXParseException& exception) 
	{
		pImpl->fatalError(exception);
	}


	void BaseContentHandler::warning(const xercesc::SAXParseException& exception) 
	{
		pImpl->warning(exception);
	}

}
