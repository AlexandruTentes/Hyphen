#pragma once

#define FOLDERDATA_H_

#include "../CompiledHeaders.h"

namespace Hyphen
{
	///////////////////////////////////////////////////////////
	//===== Class which stores a filename and it's path =====//
	///////////////////////////////////////////////////////////

	class FileAndPath
	{
		//===== Public functions =====//
	public:
		FileAndPath(std::string const& file, unsigned int const& extension_index,
			std::string const& path, std::string const& file_root);
		void add(std::string const& file, unsigned int const& extension_index,
			std::string const& path, std::string const& file_root);

		virtual ~FileAndPath() = default;
	public:
		std::string file;
		unsigned int extension_index;
		std::string file_root;
		std::string path;
		unsigned int collection_index = 0;
	};
}