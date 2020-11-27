#pragma once

#include "../CompiledHeaders.h"
#include "../Platform.h"

#define UTILITYDATASTRUCTURES_H_

namespace Hyphen
{
	///////////////////////////////////////////////////////////////////////////////////
	//===== Class which creates and maintains a dynamic array of any class type =====//
	///////////////////////////////////////////////////////////////////////////////////

	template <class T>
	class API DynamicObject
	{
		//===== Public functions =====//
	public:
		DynamicObject(DynamicObject const & data)	//Copy constructor which makes a clone
		{
			max_capacity = data.max_capacity;
			capacity = data.capacity;
			size = data.size;

			this->data = new T[size];
			memcpy(this->data, data.data, size * sizeof(T));
		}
		DynamicObject(DynamicObject && data)	//Move constructor which steals data 
		{
			max_capacity = data.max_capacity;
			capacity = data.capacity;
			size = data.size;

			this->data = data.data;
			data.data = nullptr;
		}

		DynamicObject()
		{
			capacity = default_capacity;
			data = new T[capacity];
		};
		DynamicObject(unsigned int const & size)
		{
			capacity = size;
			data = new T[capacity];
		};
		DynamicObject(T * data, unsigned int const & size) // Create an array object with the given size and data at once (uses memcpy)
		{
			capacity = size;
			this->data = new T[capacity];
			memcpy(this->data, data, size * sizeof(data[0]));
		};

		void push(T const & item) // Pushes an item at the end of the array, always
		{
			if (is_full())
				return;

			resize();
			data[size] = item;

			size++;
		};

		void remove(unsigned int const & index)
		{
			if (index >= size)
				return;

			if (index == size - 1)
			{
				size = size - 1;
				return;
			}

			bool shift = false;

			T * aux = new T[capacity];
			for (unsigned int i = 0; i < size; i++)
				if (i != index) aux[shift ? i - 1 : i] = data[i]; else shift = true;

			delete[] data;
			data = aux;

			size = size - 1;
		}

		bool is_full() { return max_capacity == 0 ? false : size == max_capacity; };
		bool is_empty() { return size == 0; };
		T get_one(unsigned int const & index) { return data[index]; };
		T * get_all() { return data; };
		unsigned int get_size() { return size; };
		unsigned int get_capacity() { return capacity; };

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

		virtual ~DynamicObject() { delete[] data; };

		//===== Protected functions =====//
	protected:
		void resize()
		{
			if (size < capacity)
				return;

			T * aux = new T[capacity + default_capacity];
			memcpy(aux, data, size * sizeof(T));

			delete[] data;
			data = aux;

			capacity = capacity + default_capacity;
		};

		//===== Private variables =====//
	protected:
		const unsigned int default_capacity = 4;
		unsigned int max_capacity = 0;
		unsigned int capacity;
		unsigned int size = 0;

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

	//////////////////////////////////////////
	//===== Stack object datastructure =====//
	//////////////////////////////////////////

	template <typename T>
	class API Stack : public DynamicObject<T>
	{
	public:
		Stack() {};
		Stack(unsigned int capacity) : DynamicObject() { max_capacity = capacity; };

		void pop(unsigned int index) { remove(index); };
		void pop() { remove(size - 1, ); };
		T peek(unsigned int index) { return get_one(index); };
		T peek() { return get_one(size - 1); };

		bool operator != (unsigned int n) { return size != n; }

		virtual ~Stack() = default;
	};
}