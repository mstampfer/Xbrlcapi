#include "Period.h"

namespace xbrlcapi
{
	struct Period::Impl 
	{
		Impl() {}

		/**
		* @see #isFiniteDurationPeriod()
		*/
		bool isFiniteDurationPeriod() 
		{
			//if (this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"instant").getLength() == 1) return false;
			//if (this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"forever").getLength() == 1) return false;
			return true;
		}

		/**
		* @see #isInstantPeriod()
		*/
		bool isInstantPeriod() 
		{
			//if (this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"instant").getLength() > 0) return true;
			return false;
		}

		/**
		* @see #isForeverPeriod()
		*/
		bool isForeverPeriod() 
		{
			//return (this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"forever").getLength() == 1);
			return false;
		}

		/**
		* @see #getInstant()
		*/
		std::string getInstant() 
		{
			//if (! isInstantPeriod()) throw new XBRLException("The period is not an instant.");
			//return this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"instant").item(0).getTextContent().trim();
			return std::string();
		}

		/**
		* @see #getStart()
		*/
		std::string getStart() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"startDate").item(0).getTextContent().trim();
			return std::string();
		}

		/**
		* @see #getEnd()
		*/
		std::string getEnd() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return this.getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.tostd::string(),"endDate").item(0).getTextContent().trim();
			return std::string();
		}

		/**
		* @see Period#getEndCalendar()
		*/
		xercesc::XMLDateTime getEndCalendar() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//xercesc::XMLDateTime date = this.getxercesc::XMLDateTime(getEnd());
			//if (date.getXMLSchemaType().getLocalPart().equals("date")) {
			//	date = roll(date);
			//	date = addTime(date);
			//}
			//return date;
			return xercesc::XMLDateTime();
		}

		/**
		* @see Period#getInstantCalendar()
		*/
		xercesc::XMLDateTime getInstantCalendar() 
		{
			//if (! isInstantPeriod()) throw new XBRLException("The period is not an instant.");
			//xercesc::XMLDateTime date = this.getxercesc::XMLDateTime(getInstant());
			//if (date.getXMLSchemaType().getLocalPart().equals("date")) {
			//	date = roll(date);
			//	date = addTime(date);
			//}
			//return date;
			return xercesc::XMLDateTime();
		}

		/**
		* @see Period#getStartCalendar()
		*/
		xercesc::XMLDateTime getStartCalendar() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//xercesc::XMLDateTime date = this.getxercesc::XMLDateTime(getStart());
			//if (date.getXMLSchemaType().getLocalPart().equals("date")) date = addTime(date);
			//return date;
			return xercesc::XMLDateTime();
		}

		/**
		* @param value The XML date or dateTime std::string value
		* @return the XML Gregorian Calendar as a construct obtained from
		* a lexical representation of an XML Schema date or dateTime value value.
		*/
		xercesc::XMLDateTime getXMLGregorianCalendar(const std::string& value) 
		{
			//try {
			//	DatatypeFactory factory = DatatypeFactory.newInstance();
			//	xercesc::XMLDateTime calendar = factory.newxercesc::XMLDateTime(value);
			//	return calendar;
			//} catch (DatatypeConfigurationException e) {
			//	throw new XBRLException("The data type conversion factory could not be instantiated.",e);
			//}
			return xercesc::XMLDateTime();
		}

		/**
		* @param date The date to convert to a dateTime.
		* @return the date time equivalent to the date, obtained by 
		* adding T00:00:00 to the lexical representation as per the XBRL Specification.
		*/
		xercesc::XMLDateTime addTime(const xercesc::XMLDateTime& date) 
		{
			//try {
			//	DatatypeFactory factory = DatatypeFactory.newInstance();
			//	return factory.newxercesc::XMLDateTime(date.toXMLFormat() + "T00:00:00");
			//} catch (DatatypeConfigurationException e) {
			//	throw new XBRLException("The data type conversion factory could not be instantiated.",e);
			//}
			return xercesc::XMLDateTime();
		}

		/**
		* @param date The date to roll forward by 1 day.
		* @return the XML Gregorian Calendar rolled forward by one day.
		*/
		xercesc::XMLDateTime roll(const xercesc::XMLDateTime& date)  
		{
			//try {
			//	DatatypeFactory factory = DatatypeFactory.newInstance();
			//	date.add(factory.newDuration("P1D"));
			//	return date;
			//} catch (DatatypeConfigurationException e) {
			//	throw new XBRLException("The data type conversion factory could not be instantiated.",e);
			//}
			return xercesc::XMLDateTime();
		}

		/**
		* @see #endHasTimezone()
		*/
		bool endHasTimezone() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return getxercesc::XMLDateTime(getEnd()).getTimezone() != DatatypeConstants.FIELD_UNDEFINED;
			return false;
		}

		/**
		* @see #endIsDateOnly()
		*/
		bool endIsDateOnly() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return getxercesc::XMLDateTime(getEnd()).getXMLSchemaType().getLocalPart().equals("date");
			return false;
		}

		/**
		* @see #instantHasTimezone()
		*/
		bool instantHasTimezone() 
		{
			//if (! isInstantPeriod()) throw new XBRLException("The period is not an instant.");
			//return getxercesc::XMLDateTime(getInstant()).getTimezone() != DatatypeConstants.FIELD_UNDEFINED;
			return false;
		}

		/**
		* @see #instantIsDateOnly()
		*/
		bool instantIsDateOnly() 
		{
			//if (! isInstantPeriod()) throw new XBRLException("The period is not an instant.");
			//return getxercesc::XMLDateTime(getInstant()).getXMLSchemaType().getLocalPart().equals("date");
			return false;
		}

		/**
		* @see #startHasTimezone()
		*/
		bool startHasTimezone() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return getxercesc::XMLDateTime(getStart()).getTimezone() != DatatypeConstants.FIELD_UNDEFINED;
			return false;
		}

		/**
		* @see #startIsDateOnly()
		*/
		bool startIsDateOnly() 
		{
			//if (! isFiniteDurationPeriod()) throw new XBRLException("The period is not a finite duration.");
			//return getxercesc::XMLDateTime(getStart()).getXMLSchemaType().getLocalPart().equals("date");
			return false;
		}

	};

	Period::Period() {}
	Period::~Period() {} 

	Period::Period(const Period& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Period& Period::operator=(const Period& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Period::Period(Period&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Period& Period::operator=(Period&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Period::operator==(const Period& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Period::operator!=(const Period& rhs)
	{
		return !this->operator==(rhs);
	}

	bool Period::isFiniteDurationPeriod() 
	{
		return pImpl->isFiniteDurationPeriod();
	}

	bool Period::isInstantPeriod() 
	{
		return pImpl->isInstantPeriod();
	}

	bool Period::isForeverPeriod() 
	{
		return pImpl->isForeverPeriod();
	}

	std::string Period::getInstant() 
	{
		return pImpl->getInstant();
	}

	std::string Period::getStart() 
	{
		return pImpl->getStart();
	}

	std::string Period::getEnd() 
	{
		return pImpl->getEnd();
	}

	xercesc::XMLDateTime Period::getEndCalendar() 
	{
		return pImpl->getEndCalendar();
	}

	xercesc::XMLDateTime Period::getInstantCalendar() 
	{
		return pImpl->getInstantCalendar();
	}

	xercesc::XMLDateTime Period::getStartCalendar() 
	{
		return pImpl->getStartCalendar();
	}

	bool Period::endHasTimezone() 
	{
		return pImpl->endHasTimezone();
	}

	bool Period::endIsDateOnly() 
	{
		return pImpl->endIsDateOnly();
	}

	bool Period::instantHasTimezone() 
	{
		return pImpl->instantHasTimezone();
	}

	bool Period::instantIsDateOnly() 
	{
		return pImpl->instantIsDateOnly();
	}

	bool Period::startHasTimezone() 
	{
		return pImpl->startHasTimezone();
	}

	bool Period::startIsDateOnly() 
	{
		return pImpl->startIsDateOnly();
	}

}




