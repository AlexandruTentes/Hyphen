#include "../../lib/Storage/FileAndPath.h"

namespace Hyphen
{
	FileAndPath::FileAndPath(std::string const& file, unsigned int const& extension_index, 
		std::string const& path, std::string const& file_root)
	{
		add(file, extension_index, path, file_root);
	}

	void FileAndPath::add(std::string const& file, unsigned int const& extension_index,
		std::string const& path, std::string const& file_root)
	{
		this->file = file;
		this->path = path;
		this->extension_index = extension_index;
		this->file_root = file_root;
	}
}