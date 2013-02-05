#pragma once
#include "PimplImpl.h"
#include "ContextComponent.h"
#include <string>
#include <xercesc/util/XMLDateTime.hpp>

namespace xbrlcapi 
{

	/**
	* Implementation of context period fragments for instants and durations.
	* @author Geoffrey Shuetrim (geoff@galexy.net)
	*/
	class Period : public ContextComponent 
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Period();
		~Period();
		Period(const Period& rhs);
		Period& operator=(const Period& rhs);
		Period(Period&& rhs);
		Period& operator=(Period&& rhs);
		bool operator==(const Period& rhs);
		bool operator!=(const Period& rhs);

		/**
		* @see #isFiniteDurationPeriod()
		*/
		bool isFiniteDurationPeriod();

		/**
		* @see #isInstantPeriod()
		*/
		bool isInstantPeriod();

		/**
		* @see #isForeverPeriod()
		*/
		bool isForeverPeriod();

		/**
		* @see #getInstant()
		*/
		std::string getInstant();

		/**
		* @see #getStart()
		*/
		std::string getStart();

		/**
		* @see #getEnd()
		*/
		std::string getEnd();

		/**
		* @see Period#getEndCalendar()
		*/
		xercesc::XMLDateTime getEndCalendar();

		/**
		* @see Period#getInstantCalendar()
		*/
		xercesc::XMLDateTime getInstantCalendar();

		/**
		* @see Period#getStartCalendar()
		*/
		xercesc::XMLDateTime getStartCalendar();

		/**
		* @see #endHasTimezone()
		*/
		bool endHasTimezone();

		/**
		* @see #endIsDateOnly()
		*/
		bool endIsDateOnly();

		/**
		* @see #instantHasTimezone()
		*/
		bool instantHasTimezone();

		/**
		* @see #instantIsDateOnly()
		*/
		bool instantIsDateOnly();

		/**
		* @see #startHasTimezone()
		*/
		bool startHasTimezone();

		/**
		* @see #startIsDateOnly()
		*/
		bool startIsDateOnly();
	};
}