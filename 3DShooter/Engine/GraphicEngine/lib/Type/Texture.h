#pragma once

#define TEXTURE_H_

#pragma once

#define NORMAL_H_

#include "../Utility/IncludeAll.h"
#include "../Utility/UtilityDataStructures.h"
#include "../Utility/Math.h"

class Texture : DynamicObject<Vector3df>
{
public:
	void add(Vector3df texture);
private:
};