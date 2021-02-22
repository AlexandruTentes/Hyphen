#pragma once

#define FILESYSTEM_H_

#include "../CompiledHeaders.h"
#include "FileAndPath.h"
#include "../Math/DynamicDatastructure.h"

namespace Hyphen
{
	/////////////////////////////////////////////////////////////////
	//===== Virtual filesystem datastructure using Collection =====//
	/////////////////////////////////////////////////////////////////

	class Filesystem
	{
	public:
		SINGLETONIZE(Filesystem)

		Collection<FileAndPath, std::string> &get(const char* root);
		void add(const char* root, FileAndPath * data, std::string & data_key);

		virtual ~Filesystem() = default;
	private:
		std::map<const char *, Collection<FileAndPath, std::string>> path_root;
	};
}