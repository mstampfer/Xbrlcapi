#pragma once

#include <memory>
#include <type_traits>

template<typename T>
class Pimpl 
{
private:
	std::unique_ptr<T> p;
public:
	Pimpl();
	template<typename ...Args> Pimpl( Args&& ... );
	~Pimpl();
	T* operator->();
	T& operator*();
	Pimpl(const Pimpl<T>&);
	Pimpl<T>& operator=(const Pimpl<T>&);
	Pimpl(Pimpl<T>&&);
	Pimpl<T>& operator=(Pimpl<T>&&);
	bool operator==(const Pimpl<T>&);
	bool operator!=(const Pimpl<T>&);
};
