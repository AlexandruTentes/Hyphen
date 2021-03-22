#pragma once

#define MODELSGUI_H_

#include "../CompiledHeaders.h"
#include "../GraphicEngine/Type/Model.h"
#include "GUIComponents.h"

namespace Hyphen
{
	class ModelsGUI
	{
	public:
		template <class T>
		void show(T * gui);
		virtual ~ModelsGUI() = default;
	public:
		Collection<Scene, std::string>& scenes = Collection<Scene, std::string>::get_instance();
		Filesystem& folder = Filesystem::get_instance();
	private:
		SearchBar model_searchbar;
	};

	template<class T>
	void ModelsGUI::show(T* gui)
	{
		Model* m;
		bool open_popup = false;
		bool is_item_hover;
		bool is_hover;
		unsigned int model_index;
		bool is_filter_text = model_searchbar.new_searchbar();

		for (unsigned int i = 0; i < folder.get(model_path).get_size(); i++)
		{
			//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 1.0f);
			//ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 0.8f));
			ImGui::BeginGroup();
			ImGui::Image((ImTextureID)i, ImVec2(aspect_ratio * 30.0, aspect_ratio * 30.0));
			ImGui::SameLine();
			open_popup = ImGui::Button(folder.get(model_path).get(i)->file_root.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0);
			model_index = gui->models.get_index(folder.get(model_path).get(i)->file);
			gui->drag_model_to_scene(i, folder.get(model_path).get(i)->file, folder.get(model_path));
			
			// Model Preview implementation
			if (open_popup)
			{
				// Ready the pop-up begin data
				read_raw_model(*folder.get(model_path).get(i));
				model_index = gui->models.get_index(folder.get(model_path).get(i)->file);
				m = gui->models.get(model_index - 1);
				m->bind_data(m->model_name);
				m->GUI_begin();
				gui->renderer->render_model(m);

				// If the model doesn t have a viewport, create a new one
				if (gui->cameras.count(m->model_name) == 0)
				{
					ViewPort viewport;
					viewport.view.set(	0, 1.2, -10,
										0, 0, 1,
										0, 1, 0);
					gui->cameras[m->model_name] = viewport;
					gui->bound_camera = m->model_name;
				}
				else gui->bound_camera = m->model_name;
				ImGui::OpenPopup((folder.get(model_path).get(i)->file + " Preview Properties").c_str());
			}

			//Start the popup, binding the fbo, transformation matrix else ready the pop-up end
			if (ImGui::BeginPopup((folder.get(model_path).get(i)->file + " Preview Properties").c_str()))
			{
				ImGui::Text(folder.get(model_path).get(i)->file.c_str());
				m = gui->models.get(model_index - 1);
				m->fbo.bind();
				gui->renderer->clear();
				m->bind_data(m->model_name);
				gui->renderer->draw_model(m);
				m->fbo.unbind();
				ImVec2 img_size = ImVec2(350, 200);
				ImGui::Image((ImTextureID)m->fbo.get_tex(), img_size, ImVec2(0, 1), ImVec2(1, 0));
				m->GUI();
				m->GUI_preview();
				gui->is_preview = true;
				ImGui::EndPopup();
			}
			else if (gui->models.get_size() && model_index && 
				gui->models.get(model_index - 1)->is_preview && gui->is_preview)
			{
				gui->is_preview = false;
				gui->models.get(model_index - 1)->GUI_end();
			}

			ImGui::EndGroup();
			//ImGui::PopStyleColor();
			//ImGui::PopStyleVar();
		}
	}
}