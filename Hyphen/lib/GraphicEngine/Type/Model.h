#pragma once

#define MODEL_H_

#include "Index.h"
#include "Vertex.h"
#include "Normal.h"
#include "Texture.h"
#include "../thirdparty/imgui/imgui.h"
#include "../../GlobalVariables.h"
#include "../Buffer/FrameBuffer.h"
#include "../Shader.h"

///////////////////////////////////////
//===== The mdoel datastructure =====//
///////////////////////////////////////

namespace Hyphen
{
	struct ModelTransfData
	{
		ModelTransfData()
		{
			init_rotation.set(0.0f, 0.0f, 0.0f);
			init_position.set(0.0f, 0.0f, 0.0f);
			init_color.set(128.0f, 255.0f, 128.0f);
		};
		bool camera = false;
		bool camera_preview = false;
		bool rendered = false;
		float scale = 1.0f;
		Vector3d<float> init_rotation;
		Vector3d<float> init_position;
		Vector3d<float> init_color;
		Vector3d<float>* position = &init_position;
		Vector3d<float>* rotation = &init_rotation;
		Vector3d<float>* color = &init_color;
		float opacity = 1.0f;
		int selected_shader_index = 0;
		Shader shader;
		unsigned int collection_index = 0;
	};

	struct ModelPreviewData
	{
		float animation_speed = 1.0f;
		int rotation_angle = 50;
		bool animation = false;

		//aux data
		float speed = 0.0f;
		float relative_speed = 0.0f;
	};

	class API Model
	{
	public:
		Model();
		Model(Vertex& vertex, Normal& normal, Texture& texture, Index& index, 
			std::string const& model_name, std::string const& model_root);
		void set(Vertex& vertex, Normal& normal, Texture& texture, Index& index,
			std::string const& model_name, std::string const& model_root);
		void set(Model& model);
		void animate();
		void GUI_preview();
		void bind_data(std::string& key);
		bool is_data_bound(std::string& key);
		void GUI();
		void GUI_begin();
		void GUI_end();
		virtual ~Model();
	public:
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	public:
		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
		FrameBuffer fbo;
		std::string model_name;
		std::string model_root;
		DynamicObject<char*> shaders;
		ModelPreviewData preview_data;
		ModelTransfData * data = nullptr;
		unsigned int model_scene_no = 0;
		unsigned int collection_index = 0;
		unsigned int vao_index = 0;
		bool is_preview = false;
	};
}