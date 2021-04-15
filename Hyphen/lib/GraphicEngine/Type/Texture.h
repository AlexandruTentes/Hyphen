#pragma once

#define TEXTURE_H_

#pragma once

#define NORMAL_H_

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"
#include "../../Math/Math.h"

namespace Hyphen
{
	class Texture : public DynamicObject<Vector3d<float>>
	{
	public:
		bool has_texture = false;
		void add(Vector3d<float> texture);
	};
}