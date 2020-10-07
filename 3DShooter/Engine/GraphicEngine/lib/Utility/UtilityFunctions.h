#pragma once

#define UTILITYFUNCTIONS_H_

#include "IncludeAll.h"
#include "Strmanip.h"
#include "UtilityDataStructures.h"

namespace sm = string_manipulation;

namespace utility_functions
{
	void get_files_recursive(FileAndPath * files, std::string path, std::string * extension, int size = 0);
	FileAndPath get_files_directory(std::string root, std::string * extension, int size = 0);
	FileAndPath get_files_directory(std::string root, std::string extension);
	FileAndPath get_files_directory(std::string root);
	int get_sizeof_gltype(GLuint type);
}