#include "../../lib/Math/DynamicDatastructure.h"

///////////////////////////////////////////////////
//===== The filename and path datastructure =====//
///////////////////////////////////////////////////

namespace Hyphen
{
	FileAndPath::FileAndPath()
	{
		capacity = default_capacity;
		file = new std::string[capacity];
		path = new std::string[capacity];
	};

	void FileAndPath::resize()
	{
		if (size < capacity)
			return;

		std::string * aux = new std::string[capacity + default_capacity];
		std::string * aux_path = new std::string[capacity + default_capacity];

		memcpy(aux, file, this->size);
		memcpy(aux_path, path, this->size);

		delete[] file;
		delete[] path;

		file = aux;
		path = aux_path;

		capacity = capacity + default_capacity;
	};

	void FileAndPath::add(std::string s, std::string p)
	{
		resize();

		file[size] = s;
		path[size] = p;

		size++;
	}

	FileAndPath::~FileAndPath()
	{
		delete[] file;
		delete[] path;
	};
}