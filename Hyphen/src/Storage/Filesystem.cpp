#include "../../lib/Storage/Filesystem.h"

namespace Hyphen
{
	Collection<FileAndPath, std::string>& Filesystem::get(const char* root)
	{
		return path_root[root];
	}

	void Filesystem::add(const char* root, FileAndPath * data, std::string& data_key)
	{
		path_root[root].add(data, data_key);
	}
}