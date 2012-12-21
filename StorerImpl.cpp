#include "stdafx.h"
#include "StorerImpl.h"


namespace xbrlcapi
{
	/**
	* @author Geoff Shuetrim (geoff@galexy.net)
	*/
	StorerImpl::StorerImpl(Store& store)
	{
		setStore(store);
	}

	/**
	* @return The data store in which the relationships are
	* to be persisted.
	* @throws XBRLException if the data store is null.
	*/
	Store StorerImpl::getStore() 
	{
		return store;
	}

	/**
	* @param store The data store in which the relationships are
	* to be persisted.
	* @throws XBRLException if the data store is null.
	*/
	void StorerImpl::setStore(Store& s)
	{
//		if (store == null) throw; // new XBRLException("The store must not be null.");
		store = s;
	}

	///**
	//* @see org.xbrlapi.networks.Storer#storeRelationship(Relationship)
	//*/
	//void StorerImpl::storeRelationship(const Relationship& relationship)
	//{
	//	try {
	//		getStore().persist(relationship);
	//	}catch (XBRLException e)
	//{
	//		 std::string arcIndex = relationship.getArcIndex();
	//		URI document = relationship.getArc().getURI();
	//		logger.error("Had problems persisting relationships for arc " + arcIndex);
	//		store.persist(new ErrorImpl(getStore().getId(document.toString() + arcIndex + "_error"), document,arcIndex,"Relationship persistence failed."));
	//	}
	//}

	///**
	//* @see org.xbrlapi.networks.Storer#storeRelationship(Arc, Fragment, Fragment)
	//*/
	//void StorerImpl::storeRelationship(Arc arc, Fragment source, Fragment target)
	//{
	//	try {
	//		Relationship relationship = new RelationshipImpl(arc, source, target);
	//		if (! getStore().hasXMLResource(relationship.getIndex())) getStore().persist(relationship);
	//	}
	//catch (XBRLException e)
	//{
	//		 std::string arcIndex = arc.getIndex();
	//		URI document = arc.getURI();
	//		logger.error("Had problems persisting relationships for arc " + arcIndex);
	//		store.persist(new ErrorImpl(getStore().getId(document.toString() + arcIndex + "_error"), document,arcIndex,"Relationship persistence failed."));
	//	}            
	//}    


	///**
	//* @see org.xbrlapi.networks.Storer#storeRelationships(org.xbrlapi.networks.Network)
	//*/
	//void StorerImpl::storeRelationships(Network network)
	//{
	//	for (const Relationship& relationship: network.getAllRelationships())
	//{            
	//		storeRelationship(relationship);
	//	}
	//}

	///**
	//* @see org.xbrlapi.networks.Storer#storeRelationships(org.xbrlapi.networks.Networks)
	//*/
	//void StorerImpl::storeRelationships(Networks networks)
	//{
	//	for (Network network: networks)
	//{
	//		storeRelationships(network);
	//	}
	//}

	///**+++
	//* @see org.xbrlapi.networks.Storer#storeAllRelationships()
	//*/
	//void StorerImpl::storeAllRelationships()
	//{
	//	this.storeRelationships(getStore().getDocumentURIs());
	//}

	///**
	//* @see Storer#deleteRelationships(URI, URI)
	//*/
	//void StorerImpl::deleteRelationships(URI linkRole, URI arcrole)
	//{
	//	Store store = getStore();
	//	Set<String> indices = store.queryForIndices("#roots#[@type='org.xbrlapi.impl.RelationshipImpl' and @arcRole='"+arcrole+"' and @linkRole='"+linkRole+"']");
	//	for ( std::string index: indices)
	//{
	//		store.remove(index);
	//	}
	//}

	///**
	//* @see Storer#deleteRelationships(URI)
	//*/
	//void StorerImpl::deleteRelationships(URI document)
	//{
	//	Store store = getStore();
	//	Set<String> indices = store.queryForIndices("#roots#[@type='org.xbrlapi.impl.RelationshipImpl' and @arcURI='"+document+"']");
	//	for ( std::string index: indices)
	//{
	//		store.remove(index);
	//	}
	//}

	///**
	//* @see org.xbrlapi.networks.Storer#deleteRelationships()
	//*/
	//void StorerImpl::deleteRelationships()
	//{
	//	Store store = getStore();
	//	Set<String> indices = store.queryForIndices("#roots#[@type='org.xbrlapi.impl.RelationshipImpl']");
	//	for ( std::string index: indices)
	//{
	//		store.remove(index);
	//	}
	//}

	///**
	//* @see org.xbrlapi.networks.Storer#storeRelationships(Collection)
	//*/
	//void StorerImpl::storeRelationships(Collection<URI> documents)
	//{
	//	for (URI document: documents)
	//{
	//		storeRelationships(document);
	//		this.getStore().sync();
	//	}
	//}

	///**
	//* This implementation uses just 3 database queries for the document.
	//* @see org.xbrlapi.networks.Storer#storeRelationships(URI)
	//*/
	//void StorerImpl::storeRelationships(URI document)
	//{

	//	Store store = getStore();

	//	try {
	//		// Get indices of all arcs in the document.
	//		Set<String> arcIndices = store.getFragmentIndicesFromDocument(document,"Arc");

	//		if (arcIndices.size() > 0)
	//{
	//			logger.info("Persisting relationships for " + arcIndices.size() + " arcs in " + document);

	//			// Get indices of arc ends in the document.
	//			Map<String,List<String>> endIndices = new HashMap<String,List<String>>();
	//			 std::string query = "for $fragment in #roots#[@uri='" + document + "' and */*[@xlink:type='resource' or @xlink:type='locator']] return concat($fragment/@index,' ',$fragment/@parentIndex,$fragment/*/*/@xlink:label)";
	//			Set<String> pairs = getStore().queryForStrings(query);
	//			for ( std::string pair: pairs)
	//{
	//				int split = pair.indexOf(" ");
	//				 std::string index = pair.substring(0,split);
	//				 std::string parentIndexPlusLabel = pair.substring(split+1);
	//				if (endIndices.containsKey(parentIndexPlusLabel))
	//{
	//					endIndices.get(parentIndexPlusLabel).add(index);
	//				} else {
	//					List<String> list = new Vector<String>();
	//					list.add(index);
	//					endIndices.put(parentIndexPlusLabel,list);
	//				}
	//			}

	//			// Get indices of locator target fragments
	//			Map<String,String> locatorTargets = new HashMap<String,String>();
	//			//query = "for $locator in #roots#[@uri='" + document + "' and */*/@xlink:type='locator'] return concat($locator/@index,' ',#roots#[@uri=$locator/@targetDocumentURI and xbrlapi:xptr/@value=$locator/@targetPointerValue]/@index)";
	//			query = "for $locator in #roots#[@uri='" + document + "' and xbrlapi:data/*/@xlink:type='locator'], $target in #roots# let $uri := $locator/@targetDocumentURI let $pointer := $locator/@targetPointerValue where $target/@uri=$uri and $target/xbrlapi:xptr/@value=$pointer return concat($locator/@index,' ',$target/@index)";                
	//			pairs = getStore().queryForStrings(query);
	//			for ( std::string pair: pairs)
	//{
	//				int split = pair.indexOf(" ");
	//				 std::string locatorIndex = pair.substring(0,split);
	//				 std::string targetIndex = pair.substring(split+1);
	//				locatorTargets.put(locatorIndex,targetIndex);
	//			}

	//			// Iterate arcs, storing relationships defined by each
	//			for ( std::string arcIndex: arcIndices)
	//{
	//				Arc arc = getStore().<Arc>getXMLResource(arcIndex);
	//				 std::string parentIndex = arc.getParentIndex();
	//				 std::string fromKey = parentIndex + arc.getFrom();
	//				 std::string toKey = parentIndex + arc.getTo();
	//				if (endIndices.containsKey(fromKey) && endIndices.containsKey(toKey))
	//{
	//					for ( std::string sourceIndex: endIndices.get(fromKey))
	//{
	//						for ( std::string targetIndex: endIndices.get(toKey))
	//{
	//							try {
	//								boolean storeThisRelationship = true;
	//								Fragment source = null;
	//								if (locatorTargets.containsKey(sourceIndex))
	//{
	//									source = store.getXMLResource(locatorTargets.get(sourceIndex));
	//								} else {
	//									source = store.getXMLResource(sourceIndex);
	//									if (source.isa(LocatorImpl.class))
	//{
	//										storeThisRelationship = false;
	//										store.persist(new ErrorImpl(getStore().getId(document.toString() + "_error"), document,"Locator " + sourceIndex + " does not reference an external resource.  Check its href attribute."));
	//									}
	//								}
	//								Fragment target = null;
	//								if (locatorTargets.containsKey(targetIndex))
	//{
	//									target = store.getXMLResource(locatorTargets.get(targetIndex));
	//								} else {
	//									target = store.getXMLResource(targetIndex);
	//									if (target.isa(LocatorImpl.class))
	//{
	//										storeThisRelationship = false;
	//										store.persist(new ErrorImpl(getStore().getId(document.toString() + "_error"), document,"Locator " + targetIndex + " does not reference an external resource.  Check its href attribute."));
	//									}
	//								}
	//								if (storeThisRelationship)
	//{
	//									this.storeRelationship(arc,source,target);
	//								}
	//							}
	//catch (XBRLException e)
	//{
	//								logger.error("Had problems persisting relationships for arc " + arcIndex);
	//								store.persist(new ErrorImpl(getStore().getId(document.toString() + arcIndex + "_error"), document,arcIndex,"Relationship persistence failed because of trouble finding sources/targets."));
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//catch (XBRLException e)
	//{
	//		logger.error("Had problems persisting relationships for " + document);
	//		e.printStackTrace();
	//		store.persist(new ErrorImpl(getStore().getId(document.toString() + "_error"), document,"Relationship persistence failed."));
	//	}

	//	getStore().sync();

	//}    

	///**
	//* @param arc The arc to store relationships for.
	//* @throws XBRLException
	//*/
	//void StorerImpl::storeRelationships(const Arc& arc)
	//{

	//	long start = System.currentTimeMillis();

	//	try {
	//		List<ArcEnd> sources = arc.getSourceFragments();
	//		List<ArcEnd> targets = arc.getTargetFragments();
	//		for (ArcEnd source: sources)
	//{
	//			for (ArcEnd target: targets)
	//{
	//				Fragment s = source;
	//				Fragment t = target;
	//				if (source.getType().equals("org.xbrlapi.impl.LocatorImpl")) s = ((Locator) source).getTarget();
	//				if (target.getType().equals("org.xbrlapi.impl.LocatorImpl")) t = ((Locator) target).getTarget();
	//				storeRelationship(arc,s,t);
	//			}
	//		}

	//		logger.debug("" + (System.currentTimeMillis() - start) + " ms to store relationships for arc " + arc.getIndex());

	//	}
	//catch (XBRLException e)
	//{
	//		logger.error("The relationship expressed by arc " + arc.getIndex() + " could not be persisted. " + e.getMessage());
	//	}


	//}

	///**
	//* @see Storer#deleteInactiveRelationships()
	//*/
	//void StorerImpl::deleteInactiveRelationships()
	//{

	//	logger.info("Deleting inactive persisted relationships.");
	//	Analyser analyser = new AnalyserImpl(getStore());

	//	Set<String> arcroles = analyser.getArcroles();
	//	for ( std::string arcrole: arcroles)
	//{
	//		Set<String> linkRoles = analyser.getLinkRoles(arcrole);
	//		for ( std::string linkRole: linkRoles)
	//{
	//			this.deleteInactiveRelationships(linkRole,arcrole);
	//		}
	//	}
	//}

	///**
	//* @see Storer#deleteInactiveRelationships(String, String)
	//*/
	//void StorerImpl::deleteInactiveRelationships( std::string linkRole,  std::string arcrole)

	//{

	//	logger.info("Deleting inactive persisted relationships for linkRole: " + linkRole + " and arcrole " + arcrole);

	//	 std::string query = "#roots#[@linkRole='"+linkRole+"' and @arcRole='"+arcrole+"']/@sourceIndex";
	//	Set<String> sourceIndices = getStore().queryForStrings(query);
	//	logger.info("# sources = " + sourceIndices.size());
	//	for ( std::string sourceIndex: sourceIndices)
	//{
	//		query = "#roots#[@linkRole='"+linkRole+"' and @arcRole='"+arcrole+"' and @sourceIndex='"+sourceIndex+"']/@targetIndex";
	//		Set<String> targetIndices = getStore().queryForStrings(query);
	//		for ( std::string targetIndex: targetIndices)
	//{
	//			Map<String,SortedSet<Relationship>> map = getEquivalentRelationships(linkRole,arcrole,sourceIndex,targetIndex);
	//			for ( std::string key: map.keySet())
	//{
	//				SortedSet<Relationship> equivalents = map.get(key);
	//				Relationship active = equivalents.first();
	//				for (const Relationship& equivalent: equivalents)
	//{
	//					if (equivalent != active)
	//{
	//						logger.info("removing " + equivalent.getArc().getURI() + " " + equivalent.getIndex());
	//					}
	//				}
	//			}
	//		}
	//	}

	//}    

	///**
	//* @param linkRole The link role of the relationships to mark.
	//* @param arcrole the arcrole  of the relationships to mark.
	//* @throws XBRLException
	//*/
	//void StorerImpl::markActiveRelationships( std::string linkRole,  std::string arcrole)

	//{

	//	 std::string query = "#roots#[@linkRole='"+linkRole+"' and @arcRole='"+arcrole+"']/@sourceIndex";
	//	Set<String> sourceIndices = getStore().queryForStrings(query);
	//	logger.info("# sources = " + sourceIndices.size());
	//	for ( std::string sourceIndex: sourceIndices)
	//{
	//		query = "#roots#[@linkRole='"+linkRole+"' and @arcRole='"+arcrole+"' and @sourceIndex='"+sourceIndex+"']/@targetIndex";
	//		Set<String> targetIndices = getStore().queryForStrings(query);
	//		for ( std::string targetIndex: targetIndices)
	//{
	//			Map<String,SortedSet<Relationship>> map = getEquivalentRelationships(linkRole,arcrole,sourceIndex,targetIndex);
	//			for ( std::string key: map.keySet())
	//{
	//				map.get(key).first().setMetaAttribute("active","");
	//			}
	//		}
	//	}

	//}

	///**
	//* @param linkRole The network link role
	//* @param arcrole The network arcrole
	//* @return a map of sorted sets of equivalent relationships in the network.
	//* @throws XBRLException
	//*/
	//Map<String,SortedSet<Relationship>> StorerImpl::getEquivalentRelationships( std::string linkRole,  std::string arcrole,  std::string sourceIndex,  std::string targetIndex)

	//{

	//	Map<String,SortedSet<Relationship>> map = new HashMap<String,SortedSet<Relationship>>();
	//	 std::string query = "#roots#[@linkRole='"+linkRole+"' and @arcRole='"+arcrole+"' and @sourceIndex='"+sourceIndex+"' and @targetIndex='"+targetIndex+"']";
	//	List<Relationship> relationships = this.getStore().<Relationship>queryForXMLResources(query);
	//	for (const Relationship& relationship: relationships)
	//{
	//		 std::string key = relationship.getSourceIndex() + relationship.getTargetIndex() + relationship.getLinkRole() + relationship.getArcrole() + relationship.getSignature();
	//		if (map.containsKey(key))
	//{
	//			map.get(key).add(relationship);
	//		} else {
	//			SortedSet<Relationship> set = new TreeSet<Relationship>(new RelationshipPriorityComparator());
	//			set.add(relationship);
	//			map.put(key,set);
	//		}
	//	}

	//	return map;
	//}

}
