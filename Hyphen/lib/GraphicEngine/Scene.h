#pragma once

#define SCENE_H_

#include "../CompiledHeaders.h"
#include "../Math/DynamicDatastructure.h"
#include "Type/Model.h"
#include "../GraphicEngine/Collection/FolderData.h"
#include "../GUI/GUIComponents.h"
#include "Camera/EngineCamera.h"

namespace Hyphen
{
	class Scene
	{
	public:
		Scene(std::string& name);
		void GUI();

		virtual ~Scene() = default;
	public:
		FolderData& folder = FolderData::get_instance();
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	public:
		unsigned int collection_index = 0;
		std::map<std::string, Model*> models;
		std::map<std::string, ViewPort> cameras;
		std::string bound_camera;
		std::string name;
		bool is_preview = false;
	private:
		SearchBar model_searchbar;
	};
}