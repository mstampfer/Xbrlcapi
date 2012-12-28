
#pragma once
#include <xercesc/dom/DOMLSInput.hpp>
#include <xercesc/dom/DOMLSResourceResolver.hpp>
#include <dbxml/XmlInputStream.hpp>
#include "Constants.h"
namespace xbrlcapi
{
	class XmlInputStreamWrap : public xercesc::DOMLSInput, public DbXml::XmlInputStream
{
private:

public:
	XmlInputStreamWrap()  {}

	xercesc::DOMLSInput* getSource(DbXml::XmlInputStream& xis)
	{
				/*xercesc::DOMLSResourceResolver resolver;
					return resolver.resolveResource	(XMLConstants::XML_DTD_NS_URI,
															namespaceUri,
															NULL,
															NULL,
															NULL);*/
	}


private:
};
}