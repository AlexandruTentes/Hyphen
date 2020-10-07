#include "../../lib/Utility/UtilityFunctions.h"

void utility_functions::get_files_recursive(FileAndPath * files, std::string path, std::string * extenstion, int size)
{
	std::string original_path = path;
	path += "\\";
	int i = 0;
	bool add_data = true;

	WIN32_FIND_DATA file;
	HANDLE file_handler;

	try
	{
		if ((file_handler = FindFirstFile((path + "*").c_str(), &file)) != INVALID_HANDLE_VALUE)
		{
			while (true)
			{
				if (FindNextFileA(file_handler, &file) == 0)
					break;
				
				if (!sm::grep(file.cFileName, ".."))
				{
					if (!sm::grep(file.cFileName, "."))
						get_files_recursive(files, path + file.cFileName, extenstion, size);

					for (int j = 0; j < size; j++)
					{
						add_data = false;

						if (sm::grep(file.cFileName, extenstion[j]))
						{
							add_data = true;
							break;
						}
					}

					if (add_data)
					{
						files->add(file.cFileName, original_path);
						i++;
					}
				}
			}

			FindClose(file_handler);
		}
	}
	catch (const std::exception & err)
	{
		std::cerr << "\tEXCEPTION IN READING FOLDER" << "\n\t\t" << err.what() << std::endl;
	}
}

FileAndPath utility_functions::get_files_directory(std::string root, std::string * extension, int size)
{
	FileAndPath files = FileAndPath();

	get_files_recursive(& files, root, extension, size);

	return files;
}

FileAndPath utility_functions::get_files_directory(std::string root, std::string extension)
{
	FileAndPath files = FileAndPath();

	std::string * temp = new std::string[1];
	temp[0] = extension;

	get_files_recursive(&files, root, temp, 1);
	delete [] temp;

	return files;
}

FileAndPath utility_functions::get_files_directory(std::string root)
{
	FileAndPath files = FileAndPath();

	get_files_recursive(& files, root, {});

	return files;
}

int utility_functions::get_sizeof_gltype(GLuint type)
{
	switch (type)
	{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
	}

	return 0;
}