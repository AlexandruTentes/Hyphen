#pragma once

#define NORMAL_H_

#include "../Utility/IncludeAll.h"
#include "../Utility/UtilityDataStructures.h"
#include "../Utility/Math.h"

class Normal : DynamicObject<Vector3df>
{
	public:
		void add(Vector3df normal);
	private:
};