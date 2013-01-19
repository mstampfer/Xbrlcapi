#include "Networks.h"

namespace xbrlcapi
{

	struct Networks::Impl 
	{
		Impl() {}

		//private HashMap<String,Arc> arcs = new HashMap<String,Arc>();
		//
		//private boolean hasArc(String arcIndex) {
		//    return arcs.containsKey(arcIndex);
		//}
		//
		//private Store store = null;
		//
		//// Map of networks: indexed by the arc role then the link role.
		//private HashMap<String,HashMap<String,Network>> networks = new HashMap<String,HashMap<String,Network>>();
		//
		//public NetworksImpl(Store store) throws XBRLException {
		//	super();
		//	if (store == null) throw new XBRLException("The data store must not be null.");
		//	this.store = store;
		//}

		//public void addNetwork(Network network) throws XBRLException {
		//	String arcrole = network.getArcrole();
		//	String linkRole = network.getLinkRole();
		//	
		//	HashMap<String,Network> map = null;
		//	
		//	if (networks.containsKey(arcrole)) {
		//		map = networks.get(arcrole);
		//		if (map.containsKey(linkRole)) {
		//		    Network existingNetwork = this.getNetwork(linkRole,arcrole);
		//		    existingNetwork.add(network);
		//		}
		//		map.put(linkRole,network);
		//		return;
		//	}
		//	
		//	map = new HashMap<String,Network>();
		//	map.put(linkRole,network);
		//	networks.put(arcrole,map);		
		//	
		//}

		//public Network getNetwork(String linkRole, String arcrole)
		//		throws XBRLException {
		//	if (networks.containsKey(arcrole)) {
		//		Map<String,Network> map = networks.get(arcrole);
		//		if (map.containsKey(linkRole))
		//			return map.get(linkRole);
		//	}
		//	return null;
		//}
		//
		//public Networks getNetworks(String arcrole) throws XBRLException {
		//	
		//    Networks result = new NetworksImpl(this.getStore());
		//	List<Network> selectedNetworks = new LinkedList<Network>();
		//	List<String> linkRoles = getLinkRoles(arcrole);
		//	if (linkRoles.isEmpty()) return result;
		//	for (String linkRole: linkRoles) {
		//		selectedNetworks.add(this.getNetwork(linkRole,arcrole));
		//	}
		//	result.addAll(selectedNetworks);
		//	return result;
		//}
		//
		//public <F extends Fragment> List<F>  getSources(String targetIndex, String arcrole) throws XBRLException {
		//	
		//	List<F> fragments = new Vector<F>();
		//	
		//   	Networks selectedNetworks = this.getNetworks(arcrole);
		//   	for (Network network: selectedNetworks) {
		//   		SortedSet<Relationship> relationships = network.getActiveRelationshipsTo(targetIndex);
		//       	for (Relationship relationship: relationships) {
		//       		fragments.add(relationship.<F>getSource());
		//       	}
		//   	}
		//	return fragments;
		//}
		//
		//public <F extends Fragment> List<F>  getSources(String targetIndex, String linkRole, String arcrole) throws XBRLException {
		//	List<F> fragments = new Vector<F>();
		//	if (! hasNetwork(linkRole,arcrole)) return fragments;
		//   	Network network = this.getNetwork(linkRole,arcrole);
		//	SortedSet<Relationship> relationships = network.getActiveRelationshipsTo(targetIndex);
		//   	for (Relationship relationship: relationships) {
		//   		fragments.add(relationship.<F>getSource());
		//   	}
		//	return fragments;
		//}	
		//
		//public <F extends Fragment> List<F>  getTargets(String sourceIndex, String arcrole) throws XBRLException {
		//	
		//	List<F> fragments = new Vector<F>();
		//	
		//   	Networks selectedNetworks = getNetworks(arcrole);
		//   	for (Network network: selectedNetworks) {
		//   		SortedSet<Relationship> relationships = network.getActiveRelationshipsFrom(sourceIndex);
		//       	for (Relationship relationship: relationships) {
		//       		fragments.add(relationship.<F>getTarget());
		//       	}
		//   	}
		//	return fragments;
		//}
		//
		//public <F extends Fragment> List<F>  getTargets(String sourceIndex, String linkRole, String arcrole) throws XBRLException {
		//	
		//	List<F> fragments = new Vector<F>();
		//	if (! hasNetwork(linkRole, arcrole)) return fragments;
		//   	Network network = this.getNetwork(linkRole, arcrole);
		//	SortedSet<Relationship> relationships = network.getActiveRelationshipsFrom(sourceIndex);
		//   	for (Relationship relationship: relationships) {
		//   		fragments.add(relationship.<F>getTarget());
		//   	}
		//	return fragments;
		//}	

		//public boolean hasNetwork(String linkRole, String arcrole) {
		//	if (networks.containsKey(arcrole)) {
		//		Map<String,Network> map = networks.get(arcrole);
		//		if (map.containsKey(linkRole)) return true;
		//	}
		//	return false;
		//}
		//
		//public void addRelationship(Relationship relationship) throws XBRLException {
		//	String arcrole = relationship.getArcrole();
		//	String linkRole = relationship.getLinkRole();
		//	
		//	if (hasNetwork(linkRole,arcrole)) {
		//		getNetwork(linkRole,arcrole).addRelationship(relationship);
		//		return;
		//	}
		//	Network network = new NetworkImpl(getStore(),linkRole,arcrole);
		//	network.addRelationship(relationship);
		//	addNetwork(network);
		//}
		//
		//   public void addRelationships(String arcrole) throws XBRLException {

		//       List<Arc> arcs = this.getStore().<Arc>queryForXMLResources(query);
		//       for (Arc arc: arcs) {
		//           List<ArcEnd> sources = arc.getSourceFragments();
		//           List<ArcEnd> targets = arc.getTargetFragments();
		//           for (Fragment source: sources) {
		//               Fragment s = source;
		//               if (source.isa(LocatorImpl.class)) s = ((Locator) source).getTarget();
		//               for (Fragment target: targets) {
		//                   Fragment t = target;
		//                   if (target.isa(LocatorImpl.class)) t = ((Locator) target).getTarget();
		//                   this.addRelationship(new RelationshipImpl(arc,s,t));
		//               }
		//           }
		//       }

		//   }
		//
		//public int getSize() throws XBRLException {
		//	int size = 0;
		//	for (String arcrole: getArcroles()) {
		//		List<String > linkroles = getLinkRoles(arcrole);
		//		size += linkroles.size();
		//	}
		//	return size;
		//}
		//
		//public List<String> getArcroles() throws XBRLException {
		//	List<String> roles = new Vector<String>();
		//	for (String value: networks.keySet()) {
		//		roles.add(value);
		//	}
		//	return roles;
		//}
		//
		//public List<String> getLinkRoles(String arcrole) throws XBRLException {
		//	List<String> roles = new Vector<String>();

		//	if (networks.containsKey(arcrole)) {
		//		Map<String,Network> map = networks.get(arcrole);
		//		if (map == null) return roles;
		//		for (String value: map.keySet()) {
		//			roles.add(value);
		//		}
		//	}
		//	return roles;
		//}
		//
		//   public Iterator<Network> iterator() {
		//       Set<Network> set = new HashSet<Network>();
		//       for (Map<String,Network> map: networks.values()) {
		//           set.addAll(map.values());
		//       }
		//       return set.iterator();
		//   }

		//   public Store getStore() {
		//       return this.store;
		//   }
		//
		//   public void addAll(Networks networks) throws XBRLException {
		//       for (Network network: networks) {
		//           this.addNetwork(network);
		//       }
		//   }
		//   
		//   public void addAll(List<Network> networks) throws XBRLException {
		//       for (Network network: networks) {
		//           this.addNetwork(network);
		//       }
		//   }

		//   public void complete() throws XBRLException {
		//       for (Network network: this) {
		//           network.complete();
		//       }
		//   }
		//   
		//   @Override
		//   public int hashCode() {
		//       final int prime = 31;
		//       int result = 1;
		//               + ((networks == null) ? 0 : networks.hashCode());
		//       return result;
		//   }

		//   @Override
		//   public boolean equals(Object obj) {
		//       if (this == obj)
		//           return true;
		//       if (obj == null)
		//           return false;
		//       if (getClass() != obj.getClass())
		//           return false;
		//       NetworksImpl other = (NetworksImpl) obj;
		//       if (arcs == null) {
		//           if (other.arcs != null)
		//               return false;
		//       } else if (!arcs.equals(other.arcs))
		//           return false;
		//       if (networks == null) {
		//           if (other.networks != null)
		//               return false;
		//       } else if (!networks.equals(other.networks))
		//           return false;
		//       if (store == null) {
		//           if (other.store != null)
		//               return false;
		//       } else if (!store.equals(other.store))
		//           return false;
		//       return true;
		//   }

		//   public void addRelationships(Collection<Relationship> relationships) throws XBRLException {
		//       for (Relationship relationship: relationships) 
		//           this.addRelationship(relationship);
		//   }

		//   public List<Relationship> getActiveRelationships() throws XBRLException {
		//       List<Relationship> result = new Vector<Relationship>();
		//       for (Network network: this) {
		//           result.addAll(network.getAllActiveRelationships());
		//       }
		//       return result;
		//   }

		//   public SortedSet<Relationship> getActiveRelationshipsFrom(String index)
		//           throws XBRLException {
		//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//       for (Network network: this) {
		//           result.addAll(network.getActiveRelationshipsFrom(index));
		//       }
		//       return result;
		//   }

		//   public SortedSet<Relationship> getActiveRelationshipsTo(String index)
		//           throws XBRLException {
		//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//       for (Network network: this) {
		//           result.addAll(network.getActiveRelationshipsTo(index));
		//       }
		//       return result;
		//   }

	};

	Networks::Networks() {}
	Networks::~Networks() {} 

	Networks::Networks(const Networks& rhs) 
	{ 
		pImpl = rhs.pImpl; 
	}

	Networks& Networks::operator=(const Networks& rhs)
	{
		if (pImpl != rhs.pImpl)
		{
			pImpl->~Impl();
			pImpl = rhs.pImpl;
		}
		return *this;
	}

	Networks::Networks(Networks&& rhs) 
	{ 
		pImpl = std::move(rhs.pImpl); 
	}

	Networks& Networks::operator=(Networks&& rhs)
	{
		if (pImpl != rhs.pImpl)
			pImpl = std::move(rhs.pImpl);
		return *this;
	}

	bool Networks::operator==(const Networks& rhs)
	{
		return (pImpl == rhs.pImpl);
	}

	bool Networks::operator!=(const Networks& rhs)
	{
		return !this->operator==(rhs);
	}

	//public NetworksImpl(Store store) throws XBRLException //
	//{
	//	super();
	//	if (store == null) throw new XBRLException("The data store must not be null.");
	//	this.store = store;
	//}

	//public void addNetwork(Network network) throws XBRLException //
	//{
	//	String arcrole = network.getArcrole();
	//	String linkRole = network.getLinkRole();
	//	
	//	HashMap<String,Network> map = null;
	//	
	//	if (networks.containsKey(arcrole)) //
	//{
	//		map = networks.get(arcrole);
	//		if (map.containsKey(linkRole)) //
	//{
	//		    Network existingNetwork = this.getNetwork(linkRole,arcrole);
	//		    existingNetwork.add(network);
	//		}
	//		map.put(linkRole,network);
	//		return;
	//	}
	//	
	//	map = new HashMap<String,Network>();
	//	map.put(linkRole,network);
	//	networks.put(arcrole,map);		
	//	
	//}

	//public Network getNetwork(String linkRole, String arcrole)
	//		throws XBRLException //
	//{
	//	if (networks.containsKey(arcrole)) //
	//{
	//		Map<String,Network> map = networks.get(arcrole);
	//		if (map.containsKey(linkRole))
	//			return map.get(linkRole);
	//	}
	//	return null;
	//}
	//
	//public Networks getNetworks(String arcrole) throws XBRLException //
	//{
	//	
	//    Networks result = new NetworksImpl(this.getStore());
	//	List<Network> selectedNetworks = new LinkedList<Network>();
	//	List<String> linkRoles = getLinkRoles(arcrole);
	//	if (linkRoles.isEmpty()) return result;
	//	for (String linkRole: linkRoles) //
	//{
	//		selectedNetworks.add(this.getNetwork(linkRole,arcrole));
	//	}
	//	result.addAll(selectedNetworks);
	//	return result;
	//}
	//
	//public <F extends Fragment> List<F>  getSources(String targetIndex, String arcrole) throws XBRLException //
	//{
	//	
	//	List<F> fragments = new Vector<F>();
	//	
	//   	Networks selectedNetworks = this.getNetworks(arcrole);
	//   	for (Network network: selectedNetworks) //
	//{
	//   		SortedSet<Relationship> relationships = network.getActiveRelationshipsTo(targetIndex);
	//       	for (Relationship relationship: relationships) //
	//{
	//       		fragments.add(relationship.<F>getSource());
	//       	}
	//   	}
	//	return fragments;
	//}
	//
	//public <F extends Fragment> List<F>  getSources(String targetIndex, String linkRole, String arcrole) throws XBRLException //
	//{
	//	List<F> fragments = new Vector<F>();
	//	if (! hasNetwork(linkRole,arcrole)) return fragments;
	//   	Network network = this.getNetwork(linkRole,arcrole);
	//	SortedSet<Relationship> relationships = network.getActiveRelationshipsTo(targetIndex);
	//   	for (Relationship relationship: relationships) //
	//{
	//   		fragments.add(relationship.<F>getSource());
	//   	}
	//	return fragments;
	//}	
	//
	//public <F extends Fragment> List<F>  getTargets(String sourceIndex, String arcrole) throws XBRLException //
	//{
	//	
	//	List<F> fragments = new Vector<F>();
	//	
	//   	Networks selectedNetworks = getNetworks(arcrole);
	//   	for (Network network: selectedNetworks) //
	//{
	//   		SortedSet<Relationship> relationships = network.getActiveRelationshipsFrom(sourceIndex);
	//       	for (Relationship relationship: relationships) //
	//{
	//       		fragments.add(relationship.<F>getTarget());
	//       	}
	//   	}
	//	return fragments;
	//}
	//
	//public <F extends Fragment> List<F>  getTargets(String sourceIndex, String linkRole, String arcrole) throws XBRLException //
	//{
	//	
	//	List<F> fragments = new Vector<F>();
	//	if (! hasNetwork(linkRole, arcrole)) return fragments;
	//   	Network network = this.getNetwork(linkRole, arcrole);
	//	SortedSet<Relationship> relationships = network.getActiveRelationshipsFrom(sourceIndex);
	//   	for (Relationship relationship: relationships) //
	//{
	//   		fragments.add(relationship.<F>getTarget());
	//   	}
	//	return fragments;
	//}	

	//public boolean hasNetwork(String linkRole, String arcrole) //
	//{
	//	if (networks.containsKey(arcrole)) //
	//{
	//		Map<String,Network> map = networks.get(arcrole);
	//		if (map.containsKey(linkRole)) return true;
	//	}
	//	return false;
	//}
	//
	//public void addRelationship(Relationship relationship) throws XBRLException //
	//{
	//	String arcrole = relationship.getArcrole();
	//	String linkRole = relationship.getLinkRole();
	//	
	//	if (hasNetwork(linkRole,arcrole)) //
	//{
	//		getNetwork(linkRole,arcrole).addRelationship(relationship);
	//		return;
	//	}
	//	Network network = new NetworkImpl(getStore(),linkRole,arcrole);
	//	network.addRelationship(relationship);
	//	addNetwork(network);
	//}
	//
	//   public void addRelationships(String arcrole) throws XBRLException //
	//{

	//       List<Arc> arcs = this.getStore().<Arc>queryForXMLResources(query);
	//       for (Arc arc: arcs) //
	//{
	//           List<ArcEnd> sources = arc.getSourceFragments();
	//           List<ArcEnd> targets = arc.getTargetFragments();
	//           for (Fragment source: sources) //
	//{
	//               Fragment s = source;
	//               if (source.isa(LocatorImpl.class)) s = ((Locator) source).getTarget();
	//               for (Fragment target: targets) //
	//{
	//                   Fragment t = target;
	//                   if (target.isa(LocatorImpl.class)) t = ((Locator) target).getTarget();
	//                   this.addRelationship(new RelationshipImpl(arc,s,t));
	//               }
	//           }
	//       }

	//   }
	//
	//public int getSize() throws XBRLException //
	//{
	//	int size = 0;
	//	for (String arcrole: getArcroles()) //
	//{
	//		List<String > linkroles = getLinkRoles(arcrole);
	//		size += linkroles.size();
	//	}
	//	return size;
	//}
	//
	//public List<String> getArcroles() throws XBRLException //
	//{
	//	List<String> roles = new Vector<String>();
	//	for (String value: networks.keySet()) //
	//{
	//		roles.add(value);
	//	}
	//	return roles;
	//}
	//
	//public List<String> getLinkRoles(String arcrole) throws XBRLException //
	//{
	//	List<String> roles = new Vector<String>();

	//	if (networks.containsKey(arcrole)) //
	//{
	//		Map<String,Network> map = networks.get(arcrole);
	//		if (map == null) return roles;
	//		for (String value: map.keySet()) //
	//{
	//			roles.add(value);
	//		}
	//	}
	//	return roles;
	//}
	//
	//   public Iterator<Network> iterator() //
	//{
	//       Set<Network> set = new HashSet<Network>();
	//       for (Map<String,Network> map: networks.values()) //
	//{
	//           set.addAll(map.values());
	//       }
	//       return set.iterator();
	//   }

	//   public Store getStore() //
	//{
	//       return this.store;
	//   }
	//
	//   public void addAll(Networks networks) throws XBRLException //
	//{
	//       for (Network network: networks) //
	//{
	//           this.addNetwork(network);
	//       }
	//   }
	//   
	//   public void addAll(List<Network> networks) throws XBRLException //
	//{
	//       for (Network network: networks) //
	//{
	//           this.addNetwork(network);
	//       }
	//   }

	//   public void complete() throws XBRLException //
	//{
	//       for (Network network: this) //
	//{
	//           network.complete();
	//       }
	//   }
	//   
	//   @Override
	//   public int hashCode() //
	//{
	//       final int prime = 31;
	//       int result = 1;
	//               + ((networks == null) ? 0 : networks.hashCode());
	//       return result;
	//   }

	//   @Override
	//   public boolean equals(Object obj) //
	//{
	//       if (this == obj)
	//           return true;
	//       if (obj == null)
	//           return false;
	//       if (getClass() != obj.getClass())
	//           return false;
	//       NetworksImpl other = (NetworksImpl) obj;
	//       if (arcs == null) //
	//{
	//           if (other.arcs != null)
	//               return false;
	//       } else if (!arcs.equals(other.arcs))
	//           return false;
	//       if (networks == null) //
	//{
	//           if (other.networks != null)
	//               return false;
	//       } else if (!networks.equals(other.networks))
	//           return false;
	//       if (store == null) //
	//{
	//           if (other.store != null)
	//               return false;
	//       } else if (!store.equals(other.store))
	//           return false;
	//       return true;
	//   }

	//   public void addRelationships(Collection<Relationship> relationships) throws XBRLException //
	//{
	//       for (Relationship relationship: relationships) 
	//           this.addRelationship(relationship);
	//   }

	//   public List<Relationship> getActiveRelationships() throws XBRLException //
	//{
	//       List<Relationship> result = new Vector<Relationship>();
	//       for (Network network: this) //
	//{
	//           result.addAll(network.getAllActiveRelationships());
	//       }
	//       return result;
	//   }

	//   public SortedSet<Relationship> getActiveRelationshipsFrom(String index)
	//           throws XBRLException //
	//{
	//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
	//       for (Network network: this) //
	//{
	//           result.addAll(network.getActiveRelationshipsFrom(index));
	//       }
	//       return result;
	//   }

	//   public SortedSet<Relationship> getActiveRelationshipsTo(String index)
	//           throws XBRLException //
	//{
	//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
	//       for (Network network: this) //
	//{
	//           result.addAll(network.getActiveRelationshipsTo(index));
	//       }
	//       return result;
	//   }
}