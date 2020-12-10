#pragma once

#define MODEL_H_

#include "Index.h"
#include "Vertex.h"
#include "Normal.h"
#include "Texture.h"
#include "../thirdparty/imgui/imgui.h"
#include "../../GlobalVariables.h"

///////////////////////////////////////
//===== The mdoel datastructure =====//
///////////////////////////////////////

namespace Hyphen
{
	struct ModelTransfData
	{
		float scale = 1.0f;
		float rotation[3] = { 0.0f, 0.0f, 0.0f };
		float translation[3] = { 0.0f, 0.0f, 0.0f };
		float color[3] = { 128.0f, 128.0f, 128.0f };
		float opacity = 1.0f;
		float animation_speed = 1.0f;
		int rotation_angle = 50;
	};

	class Model
	{
	public:
		Model();
		Model(Vertex& vertex, Normal& normal, Texture& texture, Index& index, std::string const& model_name);
		void set(Vertex& vertex, Normal& normal, Texture& texture, Index& index, std::string const& model_name);
		void set(Model& model);
		void animate();
		void GUI();
		virtual ~Model() = default;
	public:
		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
		std::string model_name;
		ModelTransfData data;
		unsigned int collection_index = 0;
		bool rendered = false;
		bool animation = false;
		float speed = 0.0f;
		float relative_speed = 0.0f;
	};
}