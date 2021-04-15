#include "../../lib/GraphicEngine/Scene.h"

namespace Hyphen
{
	Scene::Scene(std::string& name)
	{
		this->name = name;

		shader.load_shader("SceneFilter");
		shader.link_shaders();
		shader.set_uniform1i("filtertex", 0);
		glGenVertexArrays(1, &quad_vao);
		glGenBuffers(1, &quad_vbo);
		glBindVertexArray(quad_vao);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(draw_quad), draw_quad, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glBindVertexArray(0);
	}

	void Scene::GUI()
	{
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.5));
		ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_NoResize);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		bool open_popup = false;
		std::string model_index;
		bool is_filter_text = model_searchbar.new_searchbar();
		for (auto & m : models)
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
					ImGui::Text("Camera Rotation:");
					ImGui::SliderFloat3("View Direction", viewport.view[1].vec, -1.0, 1.0);
					ImGui::SliderFloat3("Camera Roll", viewport.view[2].vec, 0, 359);
					ImGui::SliderFloat("Longitude", &viewport.lon, 0, 359);
					ImGui::SliderFloat("Latitude", &viewport.lat, 0, 359);
					if (ImGui::Button("Bind here"))
					{
						if (!model_transf_data.get(bound_camera)->camera_preview)
						{
							active_cameras[bound_camera].remove();
							active_cameras.erase(bound_camera);
						}

						bound_camera = m.first;
						active_cameras[bound_camera].generate_buffers();
					}
					bool preview_camera = ImGui::Button("Preview");
					if (preview_camera && !model_transf_data.get(m.first)->camera_preview)
					{
						active_cameras[m.first].generate_buffers();
						model_transf_data.get(m.first)->camera_preview = true;
					}
					else if (preview_camera && model_transf_data.get(m.first)->camera_preview)
					{
						if (m.first != bound_camera)
						{
							active_cameras[m.first].remove();
							active_cameras.erase(m.first);
						}

						model_transf_data.get(m.first)->camera_preview = false;
					}
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

			if (model_transf_data.get(m.first)->camera_preview)
			{
				ImGui::SetNextWindowSize(ImVec2(0, 0));
				ImGui::Begin((m.first + " Preview").c_str(), &model_transf_data.get(m.first)->camera_preview,
					ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize |
					ImGuiWindowFlags_UnsavedDocument);
				ImVec2 img_size = ImVec2(200, 200);
				ImGui::Image((ImTextureID)active_cameras[m.first].get_tex(), img_size, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::End();

				if (!model_transf_data.get(m.first)->camera_preview && m.first != bound_camera)
				{
					active_cameras[m.first].remove();
					active_cameras.erase(m.first);
				}
			}
		}
		ImGui::End();
	}

	void Scene::draw_filter_quad()
	{
		shader.bind();
		glBindVertexArray(quad_vao);
		glBindTexture(GL_TEXTURE_2D, active_cameras[bound_camera].get_tex());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		shader.unbind();
	}
}