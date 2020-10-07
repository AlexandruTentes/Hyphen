#pragma once

#define VERTEX_H_

#include "../Utility/IncludeAll.h"
#include "../Utility/UtilityDataStructures.h"
#include "../Utility/Math.h"

class Vertex : public DynamicObject<Vector3df>
{
	public:
		void add(Vector3df vertex);
	private:
};