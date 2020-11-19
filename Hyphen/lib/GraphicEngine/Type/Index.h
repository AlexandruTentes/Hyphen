#pragma once

#define INDEX_H_

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"
#include "../../Math/Math.h"

namespace Hyphen
{
	class Index : public DynamicObject<Matrix4d<int>>
	{
	public:
		bool has_fourth = false;
		void add(Matrix4d<int> index);
	};
}