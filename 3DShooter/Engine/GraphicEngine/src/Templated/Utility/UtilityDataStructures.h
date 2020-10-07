#pragma once

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
GLuint DynamicObject<T>::get_size()
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
	
	delete [] data;
	data = aux;

	capacity = capacity + default_capacity;
}

template <class T>
T * DynamicObject<T>::get_all()
{
	return data;
}

template <class T>
T DynamicObject<T>::get_one(GLuint index)
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

	if(!data[index])
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
	delete [] data;
}