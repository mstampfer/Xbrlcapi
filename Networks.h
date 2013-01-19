#include "PimplImpl.h"

namespace xbrlcapi
{
	class Networks
	{
		struct Impl;
		Pimpl<Impl> pImpl;
	public:
		Networks();
		~Networks();
		Networks(const Networks& rhs);
		Networks& operator=(const Networks& rhs);
		Networks(Networks&& rhs);
		Networks& operator=(Networks&& rhs);
		bool operator==(const Networks& rhs);
		bool operator!=(const Networks& rhs);

		///**
		// * @param store The data store containing the information defining the networks.
		// * @throws XBRLException if the data store is null.
		// */
		//public NetworksImpl(Store store) throws XBRLException {
		//	super();
		//	if (store == null) throw new XBRLException("The data store must not be null.");
		//	this.store = store;
		//}

		///**
		// * @see org.xbrlapi.networks.Networks#addNetwork(Network)
		// */
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

		///**
		// * @see org.xbrlapi.networks.Networks#getNetwork(String, String)
		// */
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
		///**
		// * @see org.xbrlapi.networks.Networks#getNetworks(String)
		// */
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
		///**
		// * @see org.xbrlapi.networks.Networks#getSources(String, String)
		// */
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
		///**
		// * @see org.xbrlapi.networks.Networks#getSources(String, String, String)
		// */
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
		///**
		// * @see org.xbrlapi.networks.Networks#getTargets(String, String)
		// */
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
		///**
		// * @see org.xbrlapi.networks.Networks#getTargets(String, String, String)
		// */
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

		///**
		// * @see org.xbrlapi.networks.Networks#hasNetwork(String, String)
		// */
		//public boolean hasNetwork(String linkRole, String arcrole) {
		//	if (networks.containsKey(arcrole)) {
		//		Map<String,Network> map = networks.get(arcrole);
		//		if (map.containsKey(linkRole)) return true;
		//	}
		//	return false;
		//}
		//
		///**
		// * @see Networks#addRelationship(Relationship)
		// */
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
		//   /**
		//    * @see Networks#addRelationships(String)
		//    */
		//   public void addRelationships(String arcrole) throws XBRLException {

		//       String query = "#roots#[@type='"+ ArcImpl.class.getName() +"' and */*[@xlink:type='arc' and @xlink:arcrole='"+ arcrole +"']]";
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
		///**
		// * @see org.xbrlapi.networks.Networks#getSize()
		// */
		//public int getSize() throws XBRLException {
		//	int size = 0;
		//	for (String arcrole: getArcroles()) {
		//		List<String > linkroles = getLinkRoles(arcrole);
		//		size += linkroles.size();
		//	}
		//	return size;
		//}
		//
		///**
		// * @see org.xbrlapi.networks.Networks#getArcroles()
		// */
		//public List<String> getArcroles() throws XBRLException {
		//	List<String> roles = new Vector<String>();
		//	for (String value: networks.keySet()) {
		//		roles.add(value);
		//	}
		//	return roles;
		//}
		//
		///**
		// * @see org.xbrlapi.networks.Networks#getLinkRoles(String)
		// */
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
		//   /**
		//    * @see java.lang.Iterable#iterator()
		//    */
		//   public Iterator<Network> iterator() {
		//       Set<Network> set = new HashSet<Network>();
		//       for (Map<String,Network> map: networks.values()) {
		//           set.addAll(map.values());
		//       }
		//       return set.iterator();
		//   }

		//   /**
		//    * @see Networks#getStore()
		//    */
		//   public Store getStore() {
		//       return this.store;
		//   }
		//
		//   /**
		//    * @see Networks#addAll(Networks)
		//    */
		//   public void addAll(Networks networks) throws XBRLException {
		//       for (Network network: networks) {
		//           this.addNetwork(network);
		//       }
		//   }
		//   
		//   /**
		//    * @see Networks#addAll(List)
		//    */
		//   public void addAll(List<Network> networks) throws XBRLException {
		//       for (Network network: networks) {
		//           this.addNetwork(network);
		//       }
		//   }

		//   /**
		//    * @see org.xbrlapi.networks.Networks#complete()
		//    */
		//   public void complete() throws XBRLException {
		//       for (Network network: this) {
		//           network.complete();
		//       }
		//   }
		//   
		//   /**
		//    * @see java.lang.Object#hashCode()
		//    */
		//   @Override
		//   public int hashCode() {
		//       final int prime = 31;
		//       int result = 1;
		//       result = prime * result + ((arcs == null) ? 0 : arcs.hashCode());
		//       result = prime * result
		//               + ((networks == null) ? 0 : networks.hashCode());
		//       result = prime * result + ((store == null) ? 0 : store.hashCode());
		//       return result;
		//   }

		//   /**
		//    * @see java.lang.Object#equals(java.lang.Object)
		//    */
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

		//   /**
		//    * @see Networks#addRelationships(Collection)
		//    */
		//   public void addRelationships(Collection<Relationship> relationships) throws XBRLException {
		//       for (Relationship relationship: relationships) 
		//           this.addRelationship(relationship);
		//   }

		//   /**
		//    * @see org.xbrlapi.networks.Networks#getActiveRelationships()
		//    */
		//   public List<Relationship> getActiveRelationships() throws XBRLException {
		//       List<Relationship> result = new Vector<Relationship>();
		//       for (Network network: this) {
		//           result.addAll(network.getAllActiveRelationships());
		//       }
		//       return result;
		//   }

		//   /**
		//    * @see org.xbrlapi.networks.Networks#getActiveRelationshipsFrom(java.lang.String)
		//    */
		//   public SortedSet<Relationship> getActiveRelationshipsFrom(String index)
		//           throws XBRLException {
		//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//       for (Network network: this) {
		//           result.addAll(network.getActiveRelationshipsFrom(index));
		//       }
		//       return result;
		//   }

		//   /**
		//    * @see org.xbrlapi.networks.Networks#getActiveRelationshipsTo(java.lang.String)
		//    */
		//   public SortedSet<Relationship> getActiveRelationshipsTo(String index)
		//           throws XBRLException {
		//       SortedSet<Relationship> result = new TreeSet<Relationship>(new RelationshipOrderComparator());
		//       for (Network network: this) {
		//           result.addAll(network.getActiveRelationshipsTo(index));
		//       }
		//       return result;
		//   }
	};
}