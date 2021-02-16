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
		bool rendered = false;
		float scale = 1.0f;
		float rotation[3] = { 0.0f, 0.0f, 0.0f };
		float translation[3] = { 0.0f, 0.0f, 0.0f };
		float color[3] = { 128.0f, 128.0f, 128.0f };
		float opacity = 1.0f;
		float animation_speed = 1.0f;
		int rotation_angle = 50;
		int selected_shader_index = 0;
		Shader shader;
		unsigned int collection_index = 0;
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
		void bind_data(std::string& key);
		void GUI();
		void GUI_begin();
		void GUI_end();
		virtual ~Model();
	public:
		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
		FrameBuffer fbo;
		std::string model_name;
		std::string model_root;
		DynamicObject<char*> shaders;
		ModelTransfData * data;
		unsigned int model_scene_no = 0;
		unsigned int collection_index = 0;
		unsigned int vao_index = 0;
		bool animation = false;
		float speed = 0.0f;
		float relative_speed = 0.0f;
		bool is_preview = false;
		Collection<ModelTransfData, std::string>& model_transf_data = 
			Collection<ModelTransfData, std::string>::get_instance();
	};
}