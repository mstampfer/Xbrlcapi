#pragma once
#include "PimplImpl.h"
#include "ContextComponent.h"
#include <string>

namespace xbrlcapi
{
	class EntityResource;
	class Segment;

	class Entity : public ContextComponent
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Entity();
		~Entity();
		Entity(const Entity& rhs);
		Entity& operator=(const Entity& rhs);
		Entity(Entity&& rhs);
		Entity& operator=(Entity&& rhs);
		bool operator==(const Entity& rhs);
		bool operator!=(const Entity& rhs);
		/**
		* @see org.xbrlapi.Entity#getIdentifierScheme()
		*/
		std::string getIdentifierScheme();

		/**
		* @see org.xbrlapi.Entity#getIdentifierValue()
		*/
		std::string getIdentifierValue();

		/**
		* @see org.xbrlapi.Entity#getSegment()
		*/
		std::shared_ptr<Segment> getSegment();

		/**
		* @see org.xbrlapi.Entity#hasSegment()
		*/
		bool hasSegment();

		/**
		* @see org.xbrlapi.Entity#getEntityResources()
		*/
		std::list<EntityResource> getEntityResources();


		/**
		* @see org.xbrlapi.Entity#getEntityLabels()
		*/
		std::list<LabelResource> getEntityLabels();

		/**
		* @see org.xbrlapi.Entity#getAllEntityLabels()
		*/
		std::list<LabelResource> getAllEntityLabels();

	};
}
