#include "../../../lib/GraphicEngine/Collection/FolderDataCollection.h"

namespace Hyphen
{
	FolderDataCollection::FolderDataCollection(ModelPath const& path)
	{
		add(path);
	}

	FolderDataCollection::FolderDataCollection(ShaderPath const& path)
	{
		add(path);
	}

	void FolderDataCollection::add(ShaderPath const& path)
	{
		this->shader_folders.push(path);
	}

	void FolderDataCollection::add(ModelPath const& path)
	{
		this->model_folders.push(path);
	}
}