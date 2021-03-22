#pragma once

#define MISCSGUI_H_

#include "../CompiledHeaders.h"
#include "GUIComponents.h"

namespace Hyphen
{
	class MiscsGUI
	{
	public:
		template<class T>static void at_camera_drop(T * gui, Model* m, ModelTransfData* data);
		template<class T>static void at_env_light_drop(T* gui, Model* m, ModelTransfData* data);
		template <class T>
		void show(T* gui);
		virtual ~MiscsGUI() = default;
	public:
		Filesystem& folder = Filesystem::get_instance();
	};

	template<class T>
	void MiscsGUI::show(T* gui)
	{
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.3));
		ImGui::SetNextWindowPos(ImVec2(0, height * 0.6));
		ImGui::Begin("Miscs", NULL, ImGuiWindowFlags_NoResize);

		for (unsigned int i = 0; i < folder.get(miscs_path).get_size(); i++)
		{
			ImGui::BeginGroup();
			ImGui::Button(folder.get(miscs_path).get(i)->file_root.c_str(), 
				ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));

			if(folder.get(miscs_path).get(i)->file_root == "Camera")
				gui->drag_model_to_scene(i, folder.get(miscs_path).get(i)->file, folder.get(miscs_path), at_camera_drop);
			else if(folder.get(miscs_path).get(i)->file_root == "EnvironmentLight")
				gui->drag_model_to_scene(i, folder.get(miscs_path).get(i)->file, folder.get(miscs_path), at_env_light_drop);

			ImGui::EndGroup();
		}
		
		ImGui::End();
	}

	template<class T>
	void MiscsGUI::at_camera_drop(T * gui, Model * m, ModelTransfData* data)
	{
		Scene * scene = gui->scenes.get(gui->renderer->bound_scene);
		ViewPort& viewport = scene->cameras["Camera" + std::to_string(scene->no) + std::to_string(m->model_scene_no)];
		viewport.view.set(
			data->position->vec[0], data->position->vec[1], data->position->vec[2],
			0, 0, -1,
			0, 1, 0);
		viewport.lon = 180.0f;
		data->camera = true;
		data->position = &viewport.view.mat[0];
		//data->rotation = viewport.view.mat[1];
	}

	template<class T>
	void MiscsGUI::at_env_light_drop(T* gui, Model* m, ModelTransfData* data)
	{
		Collection<Model, std::string>& cache_models = Collection<Model, std::string>::get_instance();
		Scene* scene = gui->scenes.get(gui->renderer->bound_scene);
		std::string model_scene_name = "EnvironmentLight";

		if (scene->models.count(model_scene_name))
		{
			//Remove model
			return;
		}

		scene->models[model_scene_name] = cache_models.get((std::string)"EnvironmentLight.obj");
		data->position = scene->environment_light.position;
		data->rotation = scene->environment_light.direction;
		data->color = scene->environment_light.color;
	}
}