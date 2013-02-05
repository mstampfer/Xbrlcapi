#include "Entity.h"
#include "Segment.h"
//#include "EntityResource.h"
#include "LabelResource.h"

namespace xbrlcapi
{

	struct Entity::Impl 
	{
		Impl() {}
		std::string getIdentifierScheme()
		{
			//NodeList identifiers = getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.toString(),"identifier");
			//if (identifiers.getLength() == 0) throw new XBRLException("An entity identifier is missing from the entity.");
			//if (identifiers.getLength() > 1) throw new XBRLException("There are too many entity identifiers in the entity.");
			//Element identifier = (Element) identifiers.item(0);
			//if (! identifier.hasAttribute("scheme")) throw new XBRLException("The entity identifier scheme is not specified.");
			//return identifier.getAttribute("scheme");
			return std::string();
		}

		std::string getIdentifierValue()
		{
			//NodeList identifiers = getDataRootElement().getElementsByTagNameNS(Constants.XBRL21Namespace.toString(),"identifier");
			//if (identifiers.getLength() == 0) throw new XBRLException("An entity identifier is missing from entity " + this.getIndex());
			//if (identifiers.getLength() > 1) throw new XBRLException("There are too many entity identifiers in entity " + this.getIndex());
			//Element identifier = (Element) identifiers.item(0);
			//return identifier.getTextContent();
			return std::string();
		}

		std::shared_ptr<Segment> getSegment()
		{
			//std::list<Segment> candidates = this.<Segment>getChildren("org.xbrlapi.Impl.SegmentImpl");
			//if (candidates.size()==1) return candidates.get(0);
			//if (candidates.size()==0) return null;
			//throw new XBRLException("Entity identifier " + this.getIndex() + " contains more than one segment.");
			return std::shared_ptr<Segment>();
		}

		bool hasSegment()
		{
			//long count = getStore().queryCount("for $root in #roots#[@parentIndex='" + this.getIndex() + "' and @type='" + SegmentImpl.class.getName() + "'] return $root");
			//if (count == 1) return true;
			//if (count == 0) return false;
			//throw new XBRLException("Entity " + this.getIndex() + " has more than one child segment.  That is not valid XBRL.");
			return false;
		}    

		//std::list<EntityResource> getEntityResources()
		//{
		//	//std::string query = "";
		//	//std::string value = this.getIdentifierValue().trim();
		//	//query = "#roots#[@type='org.xbrlapi.Impl.EntityResourceImpl' and */*/@scheme='"+ this.getIdentifierScheme() +"' and */*/@value='" + value + "']";
		//	//return getStore().<EntityResource>queryForXMLResources(query);
		//}


		std::list<LabelResource> getEntityLabels()
		{
			//std::list<EntityResource> resources = this.getEntityResources();
			//std::list<LabelResource> labels = new Vector<LabelResource>();
			//for (EntityResource resource: resources) {
			//	labels.addAll(resource.getLabels());
			//}
			//return labels;
			return std::list<LabelResource>();
		}

		std::list<LabelResource> getAllEntityLabels()
		{
			//std::list<EntityResource> resources = this.getEntityResources();
			//std::list<LabelResource> labels = new Vector<LabelResource>();
			//for (EntityResource resource: resources) {
			//	Set<EntityResource> equivalents = resource.getEquivalents();
			//	for (EntityResource equivalent: equivalents) {
			//		labels.addAll(equivalent.getLabels());
			//	}
			//}

			//// Find unique labels
			//HashMap<std::string,LabelResource> map = new HashMap<std::string,LabelResource>();
			//for (LabelResource label: labels) {
			//	if (!map.containsKey(label.getIndex())) {
			//		map.put(label.getIndex(), label);
			//	}
			//}

			//// Convert map to a fragment list
			//std::list<LabelResource> result = new Vector<LabelResource>();
			//for (LabelResource label: map.values()) {
			//	result.add(label);
			//}

			//return result;
			//}
			return std::list<LabelResource>();
		}
	};

	Entity::Entity() {}
	Entity::~Entity() {} 

	Entity::Entity(const Entity& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Entity& Entity::operator=(const Entity& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Entity::Entity(Entity&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Entity& Entity::operator=(Entity&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Entity::operator==(const Entity& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Entity::operator!=(const Entity& rhs)
	{
		return !this->operator==(rhs);
	}

	std::string Entity::getIdentifierScheme()
	{
		return pImpl->getIdentifierScheme();
	}

	std::string Entity::getIdentifierValue()
	{
		return pImpl->getIdentifierValue();
	}

	std::shared_ptr<Segment> Entity::getSegment()
	{
		return pImpl->getSegment();
	}

	bool Entity::hasSegment()
	{
		return pImpl->hasSegment();
	}

	//std::list<EntityResource> Entity::getEntityResources()
	//{
	//	return pImpl->getEntityResources();
	//}

	std::list<LabelResource> Entity::getEntityLabels()
	{
		return pImpl->getEntityLabels();
	}

	std::list<LabelResource> Entity::getAllEntityLabels()
	{
		return pImpl->getAllEntityLabels();
	}

}
