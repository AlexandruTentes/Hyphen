#pragma once

#define SCENE_H_

#include "../CompiledHeaders.h"
#include "../Math/DynamicDatastructure.h"
#include "Type/Model.h"

namespace Hyphen
{
	class Scene
	{
	public:
		Scene(std::string& name);
		virtual ~Scene() = default;
	public:
		unsigned int collection_index = 0;
		std::map<std::string, Model*> models;
		std::map<std::string, Matrix4d<float>> cameras;
		std::string bound_camera;
		std::string name;
	};
}