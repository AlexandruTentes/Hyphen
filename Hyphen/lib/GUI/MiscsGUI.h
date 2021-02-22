#pragma once

#define MISCSGUI_H_

#include "../CompiledHeaders.h"
#include "GUIComponents.h"

namespace Hyphen
{
	class MiscsGUI
	{
	public:
		template <class T>
		static void at_drop(T * gui, Model* m, ModelTransfData* data);
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
			ImGui::Button("Camera", ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));
			gui->drag_model_to_scene(i, folder.get(miscs_path).get(i)->file, folder.get(miscs_path), at_drop);
			ImGui::EndGroup();
		}
		
		ImGui::End();
	}

	template<class T>
	void MiscsGUI::at_drop(T * gui, Model * m, ModelTransfData* data)
	{
		Scene * scene = gui->scenes.get(gui->renderer->bound_scene);
		scene->cameras["Camera" + std::to_string(scene->no) + std::to_string(m->model_scene_no)].view.set(
			data->translation[0], data->translation[1], data->translation[2], 0,
			0, 0, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0);
		data->rotation[1] = 180.0f;
		data->camera = true;
	}
}