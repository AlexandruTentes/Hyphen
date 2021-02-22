#include "../../lib/GraphicEngine/Scene.h"

namespace Hyphen
{
	Scene::Scene(std::string& name)
	{
		this->name = name;
	}

	void Scene::GUI()
	{
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.5));
		ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoResize);

		bool open_popup = false;
		std::string model_index;
		bool is_filter_text = model_searchbar.new_searchbar();
		for (auto const& m : models)
		{
			ImGui::Image((ImTextureID)0, ImVec2(aspect_ratio * 30.0, aspect_ratio * 30.0));
			ImGui::SameLine();
			open_popup = ImGui::Button(m.first.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));

			if (open_popup)
			{
				is_preview = true;
				m.second->GUI_begin();
				ImGui::OpenPopup((m.first + " Properties").c_str());
			}
			if (ImGui::BeginPopup((m.first + " Properties").c_str()))
			{
				ImGui::Text((m.first + " Properties").c_str());
				ImGui::NewLine();
				m.second->bind_data((std::string) m.first);

				if (m.second->data->camera)
				{
					ViewPort& viewport = cameras[m.first];
					Vector4d<float> pos(viewport.view.get_vector(0));
					Vector4d<float> dir(viewport.view.get_vector(1));
					Vector4d<float> up(viewport.view.get_vector(2));
					ImGui::Text("Camera Rotation:");
					ImGui::SliderFloat3("View Direction", dir.vec, -1.0, 1.0);
					ImGui::SliderFloat3("Camera Roll", up.vec, 0, 359);
					ImGui::SliderFloat("Longitude", &viewport.lon, 0, 359);
					ImGui::SliderFloat("Latitude", &viewport.lat, 0, 359);
					if (ImGui::Button("Bind here"))
						bound_camera = m.first;
					viewport.view.set(pos, dir, up, viewport.view.get_vector(3));
					ImGui::NewLine();
					ImGui::Text("Camera Data:");
				}

				m.second->GUI();
				ImGui::EndPopup();
			}
			else if (is_preview && m.second->is_preview && m.second->is_data_bound((std::string)m.first))
			{
				is_preview = false;
				m.second->GUI_end(); 
			}
		}
		ImGui::End();
	}
}