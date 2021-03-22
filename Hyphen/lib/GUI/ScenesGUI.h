#pragma once

#define SCENESGUI_H_

#include "../CompiledHeaders.h"
#include "GUIComponents.h"

namespace Hyphen
{
	class ScenesGUI
	{
	public:
		template <class T>
		void show(T* gui);
		virtual ~ScenesGUI() = default;
	public:
		Collection<Scene, std::string>& scenes = Collection<Scene, std::string>::get_instance();
	};

	template<class T>
	void ScenesGUI::show(T* gui)
	{
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.3));
		ImGui::Begin("Scenes", NULL, ImGuiWindowFlags_NoResize);

		if (ImGui::Button("+", ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0)))
		{
			std::string name = "Scene" + std::to_string(gui->renderer->scenes_no);
			Scene* s = new Scene(std::string(name));
			s->no = gui->renderer->scenes_no;
			gui->renderer->scenes_no++;
			s->load_scene_data(gui);
			scenes.add(s, name);
		}

		for (unsigned int i = 0; i < scenes.get_size(); i++)
		{
			if (ImGui::Button(scenes.get(i)->name.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0)))
				gui->bind_scene(scenes.get(i)->name);
		}

		ImGui::End();
	}
}