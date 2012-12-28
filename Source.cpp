#include "Builder.h"

namespace xbrlcapi 
{

	struct Builder::Impl
	{


		/**
		* The XML DOM used to build up fragments.
		*/
		private Document dom = null;

		/**
		* The metadata root element.
		*/
		private Element metadata = null;

		/**
		* The element to append new content during construction.
		*/
		private Element insertionPoint = null;

		/**
		* Flag to indicate that a fragment has yet to have any data inserted into it.
		*/
		private boolean isNewFragment = true;
	};
	Builder::Builder() {}
	Builder::Builder(int i) : pImpl(i) {}
	Builder::~Builder() {} 

	Builder::Builder(Builder& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Builder& Builder::operator=(Builder& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Builder::Builder(Builder&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Builder& Builder::operator=(Builder&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Builder::operator==(const Builder& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Builder::operator!=(const Builder& rhs)
	{
		return !this->operator==(rhs);
	}

}