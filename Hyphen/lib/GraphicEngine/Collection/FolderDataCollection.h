#pragma once

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"

namespace Hyphen
{
	struct File
	{
		bool known = false;
		std::string name;
		std::string extension;

		File(std::string const & name, std::string const & extension)
		{
			this->name = name; this->extension = extension;
		}
	};

	struct FolderData
	{
		std::string identifier;
		std::string path;
		std::string folder_name;
		DynamicObject<File> files;
	};

	struct ShaderPath
	{
		std::string path;
		std::string folder_name;
		std::string vertex_shader;
		std::string fragment_shader;
	};

	struct ModelPath
	{
		std::string path;
		std::string folder_name;
		std::string model_file;
		unsigned int extension_index;
		std::string texture_file;
		bool has_model = false;
		bool has_texture = false;
	};

	class FolderDataCollection
	{
	public:
		SINGLETONIZE(FolderDataCollection)
		FolderDataCollection(ModelPath const & path);
		FolderDataCollection(ShaderPath const& path);
		void add(ShaderPath const& path);
		void add(ModelPath const& path);

		virtual ~FolderDataCollection() = default;
	public:
		DynamicObject<ModelPath> model_folders;
		DynamicObject<ShaderPath> shader_folders;
		DynamicObject<FolderData> folder_data;
	};
}