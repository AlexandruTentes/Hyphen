#include "../../lib/Math/UtilityFunctions.h"

namespace Hyphen
{
	void get_files_directory(std::string & path, std::string const& identifier)
	{
		FolderDataCollection& folder = FolderDataCollection::get_instance();
		FolderData aux;
		std::string original_path = path;
		path += "\\";
		int i = 0;
		int j = 0;

		WIN32_FIND_DATA file;
		HANDLE file_handler;

		try
		{
			if ((file_handler = FindFirstFile((path + "*").c_str(), & file)) != INVALID_HANDLE_VALUE)
			{
				while (true)
				{
					if (FindNextFileA(file_handler, &file) == 0)
						break;

					if (!grep(file.cFileName, ".."))
					{
						if (!grep(file.cFileName, "."))
						{
							aux.path = original_path;
							aux.folder_name = file.cFileName;
							aux.identifier = identifier;
							folder.folder_data.push(std::move(aux));
							aux.files.remake();

							get_files_directory(path + file.cFileName);
						}

						aux.files.push(std::move(File(file.cFileName. file.)));

						i++;
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

	void read_models(std::string* extension, unsigned int extension_size, std::string* texture, unsigned int texture_size)
	{
		ModelPath aux;
		FolderDataCollection& folder = FolderDataCollection::get_instance();

		for (unsigned int i = 0; i < folder.folder_data.get_size(); i++)
		{
			if (folder.folder_data.get_one(i).identifier == model_path)
			{
				for (unsigned j = 0; j < extension_size; j++)
				{
					for(unsigned int k = 0; )
				}
				
			}
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