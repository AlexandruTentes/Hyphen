#include "../../lib/Math/UtilityFunctions.h"

namespace Hyphen
{
	void get_files_directory(Collection<FileAndPath, std::string> & files, std::string& path, 
		std::string* extension, int const& size, const char * file_root)
	{
		std::string original_path = path;
		path += "\\";
		int i = 0;
		int j = 0;
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

					if (!grep(file.cFileName, ".."))
					{
						if (!grep(file.cFileName, "."))
							get_files_directory(files, path + file.cFileName, extension, size, file.cFileName);

						for (j = 0; j < size; j++)
						{
							add_data = false;

							if (grep(file.cFileName, extension[j], false))
							{
								add_data = true;
								break;
							}
						}

						if (add_data)
						{
							FileAndPath * aux = new FileAndPath(file.cFileName, j, original_path, file_root);
							files.add(aux, path + file.cFileName);
							i++;
						}
					}
				}

				FindClose(file_handler);
			}
		}
		catch (const std::exception& err)
		{
			std::cerr << "\tEXCEPTION IN READING FOLDER" << "\n\t\t" << err.what() << std::endl;
		}
	}

	void get_folder_first_children(DynamicObject<char *>& children, std::string& path)
	{
		WIN32_FIND_DATA file;
		HANDLE file_handler;

		try
		{
			if ((file_handler = FindFirstFile((path + "\\*").c_str(), &file)) != INVALID_HANDLE_VALUE)
			{
				while (true)
				{
					if (FindNextFileA(file_handler, &file) == 0)
						break;

					if (!grep(file.cFileName, ".."))
						if (!grep(file.cFileName, "."))
						{
							char* c = new char[260];
							memcpy(c, file.cFileName, 260);
							children.push(c);
						}
				}

				FindClose(file_handler);
			}
		}
		catch (const std::exception& err)
		{
			std::cerr << "\tEXCEPTION IN READING FOLDER" << "\n\t\t" << err.what() << std::endl;
		}
	}

	void get_folder_first_children(std::map<std::string, bool>& children, std::string& path)
	{
		WIN32_FIND_DATA file;
		HANDLE file_handler;

		try
		{
			if ((file_handler = FindFirstFile((path + "\\*").c_str(), &file)) != INVALID_HANDLE_VALUE)
			{
				while (true)
				{
					if (FindNextFileA(file_handler, &file) == 0)
						break;

					if (!grep(file.cFileName, ".."))
						if (!grep(file.cFileName, "."))
							if (children.count(file.cFileName) == 0)
								children[file.cFileName] = GetFileAttributesA(TEXT(
									(path + "\\" + file.cFileName).c_str())) == FILE_ATTRIBUTE_DIRECTORY;
				}

				FindClose(file_handler);
			}
		}
		catch (const std::exception& err)
		{
			std::cerr << "\tEXCEPTION IN READING FOLDER" << "\n\t\t" << err.what() << std::endl;
		}
	}

	int get_sizeof_gltype(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		return 0;
	}
}