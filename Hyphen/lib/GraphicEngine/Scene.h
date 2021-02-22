#pragma once

#define SCENE_H_

#include "../CompiledHeaders.h"
#include "../Math/DynamicDatastructure.h"
#include "Type/Model.h"
#include "../Storage/Filesystem.h"
#include "../GUI/GUIComponents.h"
#include "Camera/EngineCamera.h"
#include "ModelParser/Parser.h"

namespace Hyphen
{
	class Scene
	{
	public:
		Scene(std::string& name);
		void GUI();
		template <class T>
		void load_main_camera(T * gui);

		virtual ~Scene() = default;
	public:
		Filesystem& folder = Filesystem::get_instance();
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	public:
		unsigned int collection_index = 0;
		std::map<std::string, Model*> models;
		std::map<std::string, ViewPort> cameras;
		std::string bound_camera;
		std::string name;
		unsigned short int no = 0;
		bool is_preview = false;
	private:
		SearchBar model_searchbar;
	};

	template<class T>
	inline void Scene::load_main_camera(T* gui)
	{
		Collection<Model, std::string>& models = Collection<Model, std::string>::get_instance();
		read_raw_model(*folder.get(miscs_path).get((std::string)miscs_path + (std::string)"\\Camera\\Camera.obj"));

		Model* m = models.get((std::string)"Camera.obj");
		std::string model_scene_name = "MainCamera";

		ModelTransfData* data = new ModelTransfData();
		data->translation[0] = 0.0f;
		data->translation[1] = 1.2f;
		data->translation[2] = -10.0f;
		data->rotation[1] = 180.0f;
		model_transf_data.add(data, model_scene_name);
		m->bind_data(model_scene_name);
		gui->renderer->render_model(m);
		m->data->camera = true;
		this->models[model_scene_name] = m;

		cameras[model_scene_name].view.set(0, 1.2, -10, 0,
			0, 0, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0);;
		bound_camera = model_scene_name;
	}
}