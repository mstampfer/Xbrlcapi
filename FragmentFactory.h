#pragma once
#include "Fact.h"
#include "XBRLException.h"
#include <xercesc/dom/DOMDocument.hpp>
#include <memory>
#include "Store.h"
namespace xbrlcapi
{
	/**
	* Fragment instantiation factory used to create new fragments
	* of the correct fragment type from data in the data store.
	
	*/

	class FragmentFactory
	{
		class Store;

		/**
		* Get the class for the specified class name.
		* @param className The full name of the class to get.
		* @return The class that has been named.
		* @throws XBRLException if the class cannot be obtained.
		*/
	public:
		//static Class getClass(String className) throws XBRLException {
		//       try {
		//           ClassLoader loader = Thread.currentThread().getContextClassLoader();
		//           if (loader != null) {
		//               try {
		//                   return loader.loadClass(className);
		//               } catch (Exception e) {
		//                   return Class.forName(className);
		//               }
		//           }
		//           return Class.forName(className);
		//       }
		//       catch (Exception e) {
		//           throw XBRLException("Failed to load fragment class " + className,e);
		//       }
		//}

		/**
		* Instantiate a fragment using its type.
		* @param <F> The subclass of XML being returned.
		* @param store The data store that contains the fragment.
		* @param root The root element of the fragment.
		* @return an instance of the fragment or null if it is not loadable.
		* @throws XBRLException if the class cannot be loaded.
		*/
		template<typename T>
		static std::shared_ptr<T> newFragment(const Store& store, const xercesc::DOMElement& root)  
		{
			try 
			{

				if (! root.hasAttribute(L"type")) 
				{
					throw XBRLException("The data does not identify the fragment type.");
				}

				//std::wstring className = root.getAttribute(L"type");
				//  	auto fragmentClass = getClass(className);

				//Constructor<?> constructor = fragmentClass.getConstructor();
				//  	XML xml = (XML) constructor.newInstance();
				//         xml.setStore(store);
				//         xml.setResource(root);
				//         return (F) xml;

			} 
			catch (const XBRLException& e)
			{
				//TODO
			}
			//catch (InvocationTargetException e) 
			//{
			//          throw XBRLException("Failed to instantiate the correct type of fragment because the constructor could not be invoked.",e);
			//      } 
			//catch (IllegalAccessException e) 
			//{
			//          throw XBRLException("Attempted to access an inaccessible fragment constructor.",e);
			//      } 
			//catch (NoSuchMethodException e) 
			//{
			//          throw XBRLException("Attempted to access a constructor that does not exist.  There was no such method.",e);
			//      } 
			//catch (InstantiationException e) 
			//{
			//          throw XBRLException("Attempted to access a constructor that does not exist.Instantiation failed.",e);
			//      }
		}
	private:
};
}