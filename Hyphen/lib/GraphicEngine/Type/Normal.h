#pragma once

#define NORMAL_H_

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"
#include "../../Math/Math.h"

namespace Hyphen
{
	class Normal : DynamicObject<Vector3d<float>>
	{
	public:
		bool has_normal = false;
		void add(Vector3d<float> normal);
	};
}