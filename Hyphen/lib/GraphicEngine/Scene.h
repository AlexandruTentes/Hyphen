#pragma once

#define SCENE_H_

#include "../CompiledHeaders.h"
#include "../Math/DynamicDatastructure.h"
#include "Type/Model.h"
#include "../Storage/Filesystem.h"
#include "../GUI/GUIComponents.h"
#include "Camera/EngineCamera.h"
#include "ModelParser/Parser.h"
#include "Material/Light.h"

namespace Hyphen
{
	class Scene
	{
	public:
		Scene(std::string& name);
		void GUI();
		void draw_filter_quad();
		template <class T>
		void load_scene_data(T * gui);

		virtual ~Scene() = default;
	public:
		Filesystem& folder = Filesystem::get_instance();
		Collection<Model, std::string>& cache_models = Collection<Model, std::string>::get_instance();
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	public:
		unsigned int collection_index = 0;
		std::map<std::string, Model*> models;
		std::map<std::string, ViewPort> cameras;
		std::map<std::string, Light> lights;
		std::map<std::string, FrameBuffer> active_cameras;
		Light environment_light;
		std::string bound_camera;
		std::string name;
		unsigned short int no = 0;
		bool is_preview = false;
	private:
		SearchBar model_searchbar;
		Shader shader;
		unsigned int quad_vbo, quad_vao;
		float draw_quad[24] = {	// positions   // texCoords
								-1.0f,  1.0f,  0.0f, 1.0f,
								-1.0f, -1.0f,  0.0f, 0.0f,
								 1.0f, -1.0f,  1.0f, 0.0f,

								-1.0f,  1.0f,  0.0f, 1.0f,
								 1.0f, -1.0f,  1.0f, 0.0f,
								 1.0f,  1.0f,  1.0f, 1.0f };
	};

	template<class T>
	void Scene::load_scene_data(T* gui)
	{
		read_raw_model(*folder.get(miscs_path).get((std::string)miscs_path + (std::string)"\\Camera\\Camera.obj"));
		read_raw_model(*folder.get(miscs_path).get((std::string)miscs_path + (std::string)"\\EnvironmentLight\\EnvironmentLight.obj"));

		Model* m;
		std::string model_scene_name;
		ModelTransfData* data;

		//Loading the camera
		m = cache_models.get((std::string)"Camera.obj");
		model_scene_name = "MainCamera" + std::to_string(no);
		data = new ModelTransfData();
		data->rotation->vec[1] = 180.0f;
		model_transf_data.add(data, model_scene_name);
		m->bind_data(model_scene_name);
		gui->renderer->render_model(m);
		m->data->camera = true;
		this->models[model_scene_name] = m;
		cameras[model_scene_name].view.set(0.0f, 1.2f, -10.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f);
		data->position = &cameras[model_scene_name].view[0];
		bound_camera = model_scene_name;
		active_cameras[bound_camera].generate_buffers();
		
		//Loading the environment light
		m = cache_models.get((std::string)"EnvironmentLight.obj");
		model_scene_name = "EnvironmentLight" + std::to_string(no);
		data = new ModelTransfData();
		model_transf_data.add(data, model_scene_name);
		m->bind_data(model_scene_name);
		gui->renderer->render_model(m);
		this->models[model_scene_name] = m;
		data->position = environment_light.position;
		data->rotation = environment_light.direction;
		data->color = environment_light.color;
	}
}