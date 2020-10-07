#pragma once

#define UTILITYDATASTRUCTURES_H_

#include "IncludeAll.h"
#include "Interface.h"

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

		T get_one(GLuint index);
		T * get_all();
		GLuint get_size();

		DynamicObject & operator = (DynamicObject const & data)	// Copy assignment
		{
			if (this == & data)
				return * this;

			delete [] this->data;

			capacity = data.capacity;
			size = data.size;

			this->data = new T[size];
			memcpy(this->data, data.data, size * sizeof(T));

			return * this;
		}

		DynamicObject & operator = (DynamicObject && data)	//Move assignment
		{
			if (this == & data)
				return * this;

			delete [] data;

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
		const GLuint default_capacity = 4;
		GLuint capacity;
		GLuint size = 0;

		T * data;
};

///////////////////////////////////////////////////////////
//===== Class which stores a filename and it's path =====//
///////////////////////////////////////////////////////////

class FileAndPath
{
	//===== Public functions =====//
	public:
		FileAndPath();

		void add(std::string s, std::string p);

		~FileAndPath();

	//===== Protected functions =====//
	protected:
		void resize();

	//===== Public variables =====//
	public:
		const int default_capacity = 4;
		int capacity;

		int size = 0;
		std::string * file;
		std::string * path;
};

#include "../../src/Templated/Utility/UtilityDataStructures.h"