#pragma once
#include <utility>
#include "Pimpl.h"

// default ctor
template<typename T>
Pimpl<T>::Pimpl() : p( new T() ) {}

// ctor of managed object taking multiple parameters
template<typename T>
template<typename ...Args>
Pimpl<T>::Pimpl( Args&& ...args )
	: p( new T( std::forward<Args>(args)... ) ){}

// dtor
template<typename T>
Pimpl<T>::~Pimpl() {}

// dereference operator-> 
template<typename T>
T* Pimpl<T>::operator->() { return p.get(); }


// dereference operator* 
template<typename T>
T& Pimpl<T>::operator*() { return *p.get(); }

// copy ctor
template <typename T>
Pimpl<T>::Pimpl(const Pimpl<T>& rhs) : p(new Pimpl<T>(rhs.p)) {}

// copy assignment operator
template<typename T>
Pimpl<T>& Pimpl<T>::operator=(const Pimpl<T>& rhs) 
{  
	if (p != rhs.p) 
	{
		std::unique_ptr<T> new_p(rhs.p.get());
		p.reset();
		p = std::move(new_p); 
	}
	return *this;
}

// move ctor
template <typename T>
Pimpl<T>::Pimpl(Pimpl<T>&& rhs) : p(std::move(rhs.p)) {}

// move assignment operator
template<typename T>
Pimpl<T>& Pimpl<T>::operator=(Pimpl<T>&& rhs) 
{  
	if (p != rhs.p) 
		p = std::move(rhs.p); 
	return *this;
}

// equality operator
template<typename T>
bool Pimpl<T>::operator==(const Pimpl<T>& rhs) { return (p == rhs.p); }

// inequality operator
template <typename T>
bool Pimpl<T>::operator!=(const Pimpl<T>& rhs) { return !this->operator==(rhs); }