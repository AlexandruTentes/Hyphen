#pragma once

#include "../CompiledHeaders.h"

#define UTILITYDATASTRUCTURES_H_

///////////////////////////////////////////////////////////////////////////////////
//===== Class which creates and maintains a dynamic array of any class type =====//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
class DynamicObject
{
	//===== Public functions =====//
public:
	DynamicObject(DynamicObject const & data)	//Copy constructor which makes a clone
	{
		capacity = data.capacity;
		size = data.size;

		this->data = new T[size];
		memcpy(this->data, data.data, size * sizeof(T));
	}

	DynamicObject(DynamicObject && data)	//Move constructor which steals data 
	{
		capacity = data.capacity;
		size = data.size;

		this->data = data.data;
		data.data = nullptr;
	}

	DynamicObject();
	DynamicObject(int size);
	DynamicObject(T * data, int size);	// Create an array object with the given size and data at once (uses memcpy)

	void push(T * item);	// Pushes items to the array object one at a time with resize check at each item
	void push(T item);	// Pushes an item at the end of the array, always
	void push(T item, int index);	// Pushes one item by index at a time, if the item is already on the index, override

	T get_one(unsigned int index);
	T * get_all();
	unsigned int get_size();

	DynamicObject & operator = (DynamicObject const & data)	// Copy assignment
	{
		if (this == &data)
			return *this;

		delete[] this->data;

		capacity = data.capacity;
		size = data.size;

		this->data = new T[size];
		memcpy(this->data, data.data, size * sizeof(T));

		return *this;
	}

	DynamicObject & operator = (DynamicObject && data)	//Move assignment
	{
		if (this == &data)
			return *this;

		delete[] data;

		capacity = data.capacity;
		size = data.size;

		this->data = data.data;
		data.data = nullptr;
	}

	~DynamicObject();

	//===== Protected functions =====//
protected:
	void resize();

	//===== Private variables =====//
private:
	const unsigned int default_capacity = 4;
	unsigned int capacity;
	unsigned int size = 0;

	T * data;
};

///////////////////////////////////////////////////
//===== Dynamic Object class implementation =====//
///////////////////////////////////////////////////

template <class T>
DynamicObject<T>::DynamicObject()
{
	capacity = default_capacity;
	data = new T[capacity];
}

template <class T>
DynamicObject<T>::DynamicObject(int size)
{
	capacity = size;
	data = new T[capacity];
}

template <class T>
DynamicObject<T>::DynamicObject(T * data, int size)
{
	capacity = size;
	this->data = new T[capacity];

	memcpy(this->data, data, size * sizeof(data[0]));
}

template <class T>
unsigned int DynamicObject<T>::get_size()
{
	return size;
}

template <class T>
void DynamicObject<T>::resize()
{
	if (size < capacity)
		return;

	T * aux = new T[capacity + default_capacity];
	memcpy(aux, data, size * sizeof(T));

	delete[] data;
	data = aux;

	capacity = capacity + default_capacity;
}

template <class T>
T * DynamicObject<T>::get_all()
{
	return data;
}

template <class T>
T DynamicObject<T>::get_one(unsigned int index)
{
	return data[index];
}

template <class T>
void DynamicObject<T>::push(T item)
{
	resize();

	data[size] = item;

	size++;
}

template <class T>
void DynamicObject<T>::push(T item, int index)
{
	resize();

	data[index] = item;

	if (!data[index])
		size++;
}

template <class T>
void DynamicObject<T>::push(T * item)
{
	for (int i = 0; i < sizeof(*item) / sizeof(item[0]); i++)
		push(item[i]);
}

template <class T>
DynamicObject<T>::~DynamicObject()
{
	delete[] data;
}