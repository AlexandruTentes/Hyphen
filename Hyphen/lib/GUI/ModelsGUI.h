#pragma once

#define MODELSGUI_H_

#include "../CompiledHeaders.h"
#include "../GraphicEngine/Type/Model.h"

namespace Hyphen
{
	class ModelsGUI
	{
	public:
		template <class T>
		void show(T * gui);
		virtual ~ModelsGUI() = default;
	};

	template<class T>
	inline void ModelsGUI::show(T* gui)
	{
		Model* m;
		bool open_popup = false;
		bool is_item_hover;
		bool is_hover;
		unsigned int model_index;
		for (unsigned int i = 0; i < gui->folder.files.get_size(); i++)
		{
			is_hover = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenDisabled |
				ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup);
			is_item_hover = ImGui::IsItemHovered();
			//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 1.0f);
			//ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 0.8f));
			ImGui::BeginGroup();
			ImGui::Image((ImTextureID)i, ImVec2(aspect_ratio * 30.0, aspect_ratio * 30.0));
			ImGui::SameLine();
			open_popup = ImGui::Button(gui->folder.files.get_one(i).file.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0);
			model_index = gui->models.get_index(gui->folder.files.get_one(i).file);
			gui->renderer->view = gui->camera->view;

			if (is_item_hover && gui->drag && !gui->start_drag)
			{
				gui->drag_model_index = i - 1;
				gui->start_drag = true;
			}

			if (gui->start_drag && gui->drag && is_hover && i == gui->drag_model_index && !gui->is_preview)
			{
				gui->model_dragndrop = true;
				read_raw_model(gui->folder.files.get_one(gui->drag_model_index));
				ImGui::OpenPopup("");
				ImGui::SetNextWindowPos(ImVec2(ImGui::GetMousePos().x - aspect_ratio * 30.0 * 0.5,
					ImGui::GetMousePos().y - aspect_ratio * 30.0 * 0.5));
				ImGui::BeginPopup("", ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs);
				ImGui::Image((ImTextureID)i, ImVec2(aspect_ratio * 30.0, aspect_ratio * 30.0));
				ImGui::EndPopup();
			}

			if (gui->dragndrop && gui->model_dragndrop)
			{
				if (!is_hover)
				{
					model_index = gui->models.get_index(gui->folder.files.get_one(gui->drag_model_index).file) - 1;
					m = gui->models.get(model_index);
					m->model_scene_no++;
				}
				gui->start_drag = false;
				gui->dragndrop = false;
				gui->model_dragndrop = false;
			}

			if (gui->start_drag && gui->drag && !is_hover)
			{
				model_index = gui->models.get_index(gui->folder.files.get_one(gui->drag_model_index).file) - 1;
				m = gui->models.get(model_index);
				std::string model_scene_name =
					m->model_name + std::to_string(m->model_scene_no);

				if (!gui->scenes.get(gui->renderer->bound_scene)->models[model_scene_name])
				{
					ModelTransfData* data = new ModelTransfData();
					data->translation[0] = (float)ImGui::GetMousePos().x / width;
					data->translation[2] = (float)ImGui::GetMousePos().y / height;
					gui->model_transf_data.add(data, model_scene_name);
					m->bind_data(model_scene_name);
					gui->renderer->render_model(m);
					gui->scenes.get(gui->renderer->bound_scene)->models[model_scene_name] = m;
				}
				else
				{
					gui->model_transf_data.get(model_scene_name)->translation[0] = -(float)ImGui::GetMousePos().x / width * 10;
					//model_transf_data.get(model_scene_name)->translation[2] = -(float) 1 / ImGui::GetMousePos().y;
				}
			}

			if (open_popup)
			{
				read_raw_model(gui->folder.files.get_one(i));
				model_index = gui->models.get_index(gui->folder.files.get_one(i).file);
				m = gui->models.get(model_index - 1);
				m->GUI_begin();
				m->bind_data(m->model_name);
				gui->renderer->render_model(m);
				ImGui::OpenPopup((gui->folder.files.get_one(i).file + " Transformation Matrix").c_str());
			}
			if (ImGui::BeginPopup((gui->folder.files.get_one(i).file + " Transformation Matrix").c_str()))
			{
				ImGui::Text(gui->folder.files.get_one(i).file.c_str());
				m = gui->models.get(model_index - 1);
				m->fbo.bind();
				gui->renderer->clear();
				m->bind_data(m->model_name);
				gui->renderer->draw_model(m);
				m->fbo.unbind();
				m->GUI();
				gui->is_preview = true;
				ImGui::EndPopup();
			}
			else if (gui->models.get_size() && model_index && gui->models.get(model_index - 1)->is_preview)
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