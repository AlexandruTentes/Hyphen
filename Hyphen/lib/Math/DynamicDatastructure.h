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
	class DynamicObject
	{
		//===== Public functions =====//
	public:
		DynamicObject(DynamicObject const& data);	//Copy constructor which makes a clone
		DynamicObject(DynamicObject&& data);	//Move constructor which steals data 
		DynamicObject();
		DynamicObject(unsigned int const& size);
		DynamicObject(T* data, unsigned int const& size); // Create an array object with the given size and data at once (uses memcpy)

		void push(T const& item); // Pushes an item at the end of the array, always
		bool has(T const& item);
		void remake();
		void clear();
		void remove(unsigned int const& index);
		bool is_full();
		bool is_empty();
		T & get_one(unsigned int const & index);
		T * get_all();
		unsigned int get_size();
		unsigned int get_capacity();

		DynamicObject& operator = (DynamicObject const& data);	// Copy assignment
		DynamicObject& operator = (DynamicObject&& data);	//Move assignment

		virtual ~DynamicObject();

	protected:
		void resize();

	protected:
		const unsigned int default_capacity = 4;
		unsigned int max_capacity = 0;
		unsigned int capacity;
		unsigned int size = 0;
		unsigned int initialized_capacity = 0;
		T * data;
	};

	//===== Implementation =====//

	template<class T>
	DynamicObject<T>::DynamicObject(DynamicObject const& data)
	{
		max_capacity = data.max_capacity;
		capacity = data.capacity;
		size = data.size;
		initialized_capacity = data.initialized_capacity;
		this->data = new T[size];
		memcpy(this->data, data.data, size * sizeof(T));
	}

	template<class T>
	DynamicObject<T>::DynamicObject(DynamicObject && data)
	{
		max_capacity = data.max_capacity;
		capacity = data.capacity;
		size = data.size;
		initialized_capacity = data.initialized_capacity;
		this->data = data.data;
		data.data = nullptr;
	}

	template<class T>
	DynamicObject<T>::DynamicObject()
	{
		capacity = default_capacity;
		data = new T[capacity];
	}

	template<class T>
	DynamicObject<T>::DynamicObject(unsigned int const& size)
	{
		capacity = size;
		initialized_capacity = size;
		data = new T[capacity];
	}

	template<class T>
	DynamicObject<T>::DynamicObject(T* data, unsigned int const& size)
	{
		capacity = size;
		initialized_capacity = size;
		this->data = new T[capacity];
		memcpy(this->data, data, size * sizeof(data[0]));
	}

	template<class T>
	void DynamicObject<T>::push(T const& item)
	{
		if (is_full())
			return;

		resize();
		data[size] = item;
		size++;
	}

	template<class T>
	bool DynamicObject<T>::has(T const& item)
	{
		for (unsigned int i = 0; i < size; i++)
			if (data[i] == item)
				return true;

		return false;
	}

	template<class T>
	void DynamicObject<T>::remake()
	{
		delete[] data;
		size = 0;
		capacity = initialized_capacity != 0 ? initialized_capacity : default_capacity;
		data = new T[capacity];
	}

	template<class T>
	inline void DynamicObject<T>::clear()
	{
		size = 0;
	}

	template<class T>
	void DynamicObject<T>::remove(unsigned int const& index)
	{
		if (index >= size)
			return;

		if (index == size - 1)
		{
			size = size - 1;
			return;
		}

		bool shift = false;
		T* aux = new T[capacity];
		for (unsigned int i = 0; i < size; i++)
			if (i != index) aux[shift ? i - 1 : i] = data[i]; else shift = true;
		delete[] data;
		data = aux;
		size = size - 1;
	}

	template<class T>
	inline bool DynamicObject<T>::is_full()
	{
		return max_capacity == 0 ? false : size == max_capacity;
	}

	template<class T>
	inline bool DynamicObject<T>::is_empty()
	{
		return size == 0;
	}

	template<class T>
	inline T& DynamicObject<T>::get_one(unsigned int const& index)
	{
		return data[index];
	}

	template<class T>
	inline T* DynamicObject<T>::get_all()
	{
		return data;
	}

	template<class T>
	inline unsigned int DynamicObject<T>::get_size()
	{
		return size;
	}

	template<class T>
	inline unsigned int DynamicObject<T>::get_capacity()
	{
		return capacity;
	}

	template<class T>
	void DynamicObject<T>::resize()
	{
		if (size < capacity)
			return;

		T* aux = new T[capacity + default_capacity];
		memcpy(aux, data, size * sizeof(T));
		delete[] data;
		data = aux;
		capacity = capacity + default_capacity;
	}

	template<class T>
	DynamicObject<T>& DynamicObject<T>::operator=(DynamicObject const& data)
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

	template<class T>
	DynamicObject<T>& DynamicObject<T>::operator=(DynamicObject && data)
	{
		if (this == &data)
			return *this;

		delete[] this->data;
		capacity = data.capacity;
		size = data.size;
		this->data = data.data;
		data.data = nullptr;
		return *this;
	}

	template<class T>
	DynamicObject<T>::~DynamicObject()
	{
		delete[] data;
	}

	//////////////////////////////////////////////////////////////
	//===== Stack object datastructure using DynamicObject =====//
	//////////////////////////////////////////////////////////////

	template <typename T>
	class Stack : public DynamicObject<T>
	{
	public:
		Stack() {};
		Stack(unsigned int capacity);

		void pop(unsigned int index);
		void pop();
		T peek(unsigned int index);
		T peek();

		bool operator != (unsigned int n);

		virtual ~Stack() = default;
	};
	
	//===== Implementation =====//

	template<typename T>
	Stack<T>::Stack(unsigned int capacity) : DynamicObject()
	{
		max_capacity = capacity;
	}

	template<typename T>
	inline void Stack<T>::pop(unsigned int index)
	{
		remove(index);
	}

	template<typename T>
	inline void Stack<T>::pop()
	{
		remove(size - 1, );
	}

	template<typename T>
	inline T Stack<T>::peek(unsigned int index)
	{
		return get_one(index);
	}

	template<typename T>
	inline T Stack<T>::peek()
	{
		return get_one(size - 1);
	}

	template<typename T>
	inline bool Stack<T>::operator!=(unsigned int n)
	{
		return size != n;
	}

	///////////////////////////
	//===== Linked List =====//
	///////////////////////////

	template <class T>
	struct NodeList
	{
		T * value;
		NodeList* next;
	};

	template <class T>
	class List
	{
	public:
		List();

		void insert(T * data);
		NodeList<T> * get_list();
		void remove_first();
		unsigned int get_size();
		void print();

		virtual ~List();
	private:
		NodeList<T> * root = nullptr;
		NodeList<T> * current = nullptr;

		unsigned int size = 0;
	};

	//===== Implementation =====//

	template<class T>
	List<T>::List()
	{
		root = new NodeList<T>();
		root->next = nullptr;
		current = root;
	}

	template<class T>
	void List<T>::insert(T * data)
	{
		NodeList<T>* aux = new NodeList<T>();
		aux->value = data;
		aux->next = nullptr;

		current->next = aux;
		current = aux;

		size++;
	}

	template<class T>
	inline NodeList<T>* List<T>::get_list()
	{
		return root->next;
	}

	template<class T>
	void List<T>::remove_first()
	{
		delete root->next;
		root->next = root->next->next;
		size--;
	}

	template<class T>
	inline unsigned int List<T>::get_size()
	{
		return size;
	}

	template<class T>
	void List<T>::print()
	{
		NodeList<T>* aux = root->next;

		while (aux != nullptr)
		{
			std::cout << aux->data << (aux->next == nullptr ? "" : " -> ");
			aux = aux->next;
		}

		std::cout << "\n";
	}

	template<class T>
	List<T>::~List()
	{
		NodeList<T>* aux = root->next;

		while (root != nullptr)
		{
			delete root;
			root = aux;

			if (aux == nullptr)
				return;
			aux = root->next;
		}
	}

	///////////////////////////
	//===== Binary tree =====//
	///////////////////////////

	template <class T>
	struct NodeTree
	{
		T value;
		unsigned int depth = 0;
		NodeTree * parent = nullptr;
		NodeTree * left;
		NodeTree * right;
	};

	template <class T>
	class OBT
	{
	public:
		OBT();

		void insert(T & data);
		bool search(T & value);
		void remove(T & data);
		NodeTree<T> * get_min(NodeTree<T>* node);

		virtual ~OBT();
	private:
		NodeTree<T>* new_node(T * data);
		bool recursive_search(NodeTree<T> * node, T * value);
		NodeTree<T> * recursive_insert(NodeTree<T> * node, T * data);
		NodeTree<T>* recursive_remove(NodeTree<T>* node, T* value);
		void recursive_delete(NodeTree<T>* node);

	private:
		NodeTree * tree = nullptr;
		unsigned int size = 0;
	};

	//===== Implementation =====//

	template<class T>
	inline OBT<T>::OBT()
	{
	}

	template<class T>
	inline void OBT<T>::insert(T & data)
	{
		recursive_insert(tree, data);
		size++;
	}

	template<class T>
	inline bool OBT<T>::search(T & value)
	{
		return recursive_search(tree, value);
	}

	template<class T>
	inline void OBT<T>::remove(T & data)
	{
		tree = recursive_remove(tree, data);
	}

	template<class T>
	NodeTree<T>* OBT<T>::get_min(NodeTree<T>* node)
	{
		if (node != nullptr && node->left == nullptr)
			return node;

		get_min(node->left);

		return nullptr;
	}

	template<class T>
	inline OBT<T>::~OBT()
	{
		recursive_delete(tree);
	}

	template<class T>
	NodeTree<T>* OBT<T>::new_node(T* data)
	{
		NodeTree<T>* aux = new NodeTree<T>();
		aux->value = data;
		aux->left = nullptr;
		aux->right = nullptr;
		return aux;
	}

	template<class T>
	bool OBT<T>::recursive_search(NodeTree<T> * node, T * value)
	{
		if (value == node->value)
			return true;

		if (value < node->value)
			recursive_search(node->left, value);
		else
			recursive_search(node->right, value);

		return false;
	}

	template<class T>
	NodeTree<T> * OBT<T>::recursive_insert(NodeTree<T>* node, T* data)
	{
		if (node == nullptr)
		{
			node = new_node(data);
			return node;
		}

		if (data < node->value)
		{
			node->left = recursive_insert(node->left, data);
			node->left->parent = node;
			node->left->depth = node->depth + 1;
		}
		else if (data > node->value)
		{
			node->right = recursive_insert(node->right, data);
			node->right->parent = node;
			node->right->depth = node->depth + 1;
		}
	}

	template<class T>
	NodeTree<T>* OBT<T>::recursive_remove(NodeTree<T>* node, T* value)
	{
		if (node == nullptr)
			return node;

		if (value < node->value)
		{
			node->left = recursive_remove(node->left, value);

			if (node->left != nullptr)
				node->left->parent = node;
		}
		else if (value > node->value)
		{
			node->right = recursive_remove(node->right, value);

			if (node->right != nullptr)
				node->right->parent = node;
		}
		else
		{
			if (node->left == nullptr)
			{
				NodeTree<T>* aux = node->right;
				aux->depth -= 1;
				delete node;
				return aux;
			}
			else if (node->right == nullptr)
			{
				NodeTree<T>* aux = node->left;
				aux->depth -= 1;
				delete node;
				return aux;
			}

			NodeTree<T>* aux = get_min(node->right);
			node->value = aux->value;
			node->right = recursive_remove(node->right, aux->value);
		}

		return node;
	}

	template<class T>
	void OBT<T>::recursive_delete(NodeTree<T>* node)
	{
		if (node->left != nullptr)
			recursive_delete(node->left);

		if (node->right != nullptr)
			recursive_delete(node->right);

		if (node->left == nullptr && node->right == nullptr)
			delete node;
	}

	////////////////////////////////////////////////
	//===== Priority queue using binary heap =====//
	////////////////////////////////////////////////

	template <class T>
	struct NodeQueue
	{
		T value;
		unsigned int priority;
	};

	template <class T>
	class BinaryPriorityQueue
	{
	public:
	private:
	};

	//===== Implementation =====//

	////////////////////////////////////////////////////////////
	//===== Collection datastructure using DynamicObject =====//
	////////////////////////////////////////////////////////////

	struct nulltype {};

	template <class T, class K = nulltype>
	class Collection
	{
	public:
		SINGLETONIZE(Collection)

		void add(T * data, K & key);
		void add(T * data);
		void remove(T * data);
		void remove(T * data, K & key);
		bool exists(T * data);
		bool exists(K & key);
		unsigned int get_size();
		unsigned int get_index(K & key);
		T * get(unsigned int const i);
		T * get(K const & key);

		virtual ~Collection();
	private:
		DynamicObject<T *> collection;
		std::map<K, unsigned int> map;
	};

	//===== Implementation =====//

	template<class T, class K>
	void Collection<T, K>::add(T * data, K & key)
	{
		if (data->collection_index != 0)
			return;

		data->collection_index = get_size() + 1;
		collection.push(data);
		map[key] = collection.get_size();
	}

	template<class T, class K>
	void Collection<T, K>::add(T * data)
	{
		if (data->collection_index != 0)
			return;

		data->collection_index = get_size() + 1;
		collection.push(data);
	}

	template<class T, class K>
	void Collection<T, K>::remove(T * data)
	{
		if (data->collection_index == 0)
			return;

		collection.remove(data->collection_index - 1);
		data->collection_index = 0;
	}

	template<class T, class K>
	void Collection<T, K>::remove(T* data, K& key)
	{
		if (data->collection_index == 0)
			return;

		collection.remove(data->collection_index - 1);
		data->collection_index = 0;
		map.erase(key);
	}

	template<class T, class K>
	inline bool Collection<T, K>::exists(T * data)
	{
		return data->collection_index != 0;
	}

	template<class T, class K>
	inline bool Collection<T, K>::exists(K & key)
	{
		return map[key] != 0;
	}

	template<class T, class K>
	inline unsigned int Collection<T, K>::get_size()
	{
		return collection.get_size();
	}

	template<class T, class K>
	inline unsigned int Collection<T, K>::get_index(K & key)
	{
		return map[key];
	}

	template<class T, class K>
	inline T* Collection<T, K>::get(unsigned int const i)
	{
		return collection.get_one(i);;
	}

	template<class T, class K>
	inline T* Collection<T, K>::get(K const & key)
	{
		return collection.get_one(map[key] - 1);
	}

	template<class T, class K>
	Collection<T, K>::~Collection()
	{
		for (unsigned int i = 0; i < get_size(); i++)
			delete collection.get_one(i);
	}
}