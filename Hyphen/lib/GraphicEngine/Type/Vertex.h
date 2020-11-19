#pragma once

#define VERTEX_H_

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"
#include "../../Math/Math.h"

namespace Hyphen
{
	class Vertex : public DynamicObject<Vector3d<float>>
	{
	public:
		void add(Vector3d<float> vertex);
	private:
	};
}