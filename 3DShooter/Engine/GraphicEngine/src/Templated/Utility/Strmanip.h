#pragma once

namespace sm = string_manipulation;

template <typename T>
string_manipulation::Array<T>::Array()
{}

template <typename T>
string_manipulation::Array<T>::Array(T * data, int size) :
	DynamicObject(data, size)
{
	delete [] data;
}

template <typename T>
string_manipulation::Array<T>::~Array()
{}