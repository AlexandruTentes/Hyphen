#include "../../../lib/GraphicEngine/Type/Model.h"

namespace Hyphen
{
	Model::Model()
	{}

	Model::Model(Vertex& vertex, Normal& normal, Texture& texture, Index& index,
		std::string const& model_name, std::string const& model_root)
	{
		data = new ModelTransfData();
		model_transf_data.add(data, (std::string)model_name);
		set(vertex, normal, texture, index, model_name, model_root);
	}

	void Model::set(Vertex& vertex, Normal& normal, Texture& texture, Index& index,
		std::string const& model_name, std::string const& model_root)
	{
		this->vertex = std::move(vertex);
		this->normal = std::move(normal);
		this->texture = std::move(texture);
		this->index = std::move(index);
		this->model_name = model_name;
		this->model_root = model_root;
	}

	void Model::set(Model& model)
	{
		set(model.vertex, model.normal, model.texture, model.index, model.model_name, model.model_root);
	}

	void Model::animate()
	{
		preview_data.relative_speed = preview_data.animation_speed * 0.0001;

		float sinc = sinf(preview_data.speed);
		float cosc = cosf(preview_data.speed);
		data->translation[0] = sinc;
		data->translation[2] = cosc;
		data->rotation[0] = preview_data.speed * preview_data.rotation_angle;
		data->rotation[1] = preview_data.speed * preview_data.rotation_angle;
		data->rotation[2] = preview_data.speed * preview_data.rotation_angle;

		preview_data.speed += preview_data.relative_speed;
	}

	void Model::GUI_preview()
	{
		ImGui::SliderFloat("Animation Speed", &preview_data.animation_speed, 0, 10);
		ImGui::SliderInt("Rotation Angle", &preview_data.rotation_angle, 0, 360);
		bool btn = ImGui::Button("Animation: ");

		if (btn && !preview_data.animation)
			preview_data.animation = true;
		else if (btn && preview_data.animation)
			preview_data.animation = false;

		ImGui::SameLine();
		ImGui::Text(preview_data.animation ? " ON" : " OFF");

		if (preview_data.animation)
			animate();
	}

	void Model::bind_data(std::string& key)
	{
		data = model_transf_data.get(key);
	}

	bool Model::is_data_bound(std::string& key)
	{
		return model_transf_data.get(key) == data;
	}

	void Model::GUI_begin()
	{
		//Prepare preview fbo
		if (fbo.get_id() == 0)
			fbo.generate_buffers();

		is_preview = true;
		shaders.push((char*)data->shader.name.c_str());
		get_folder_first_children(shaders, (std::string)shader_path);
	}

	void Model::GUI()
	{
		//Begin the GUI implementation
		ImGui::SliderFloat("Scale", &data->scale, 0, 1);
		ImGui::SliderFloat3("Position", data->translation, -9.0, 9.0);
		ImGui::SliderFloat3("Rotation", data->rotation, 0, 359);
		ImGui::SliderFloat3("Color", data->color, 0, 255);
		ImGui::SliderFloat("Opacity", &data->opacity, 0, 1);
		if (ImGui::Combo("Shaders List", &data->selected_shader_index, shaders.get_all(), shaders.get_size()))
		{
			data->shader.name = shaders.get_all()[data->selected_shader_index];
			data->shader.load_shader(data->shader.name);
			data->shader.link_shaders();
		}
	}

	void Model::GUI_end()
	{
		is_preview = false;

		for (unsigned int i = 0; i < shaders.get_size(); i++)
		{
			//Fix DynamicObject datastructure to be able to delete the leaks
			//std::cout << "delete " << i << " elem " << shaders.get_all()[i] << "\n";
			//delete[] shaders.get_all()[i];
		}

		shaders.clear();
	}

	Model::~Model()
	{
		fbo.remove();
	}

}
