#pragma once

#define INDEX_H_

#include "../Utility/IncludeAll.h"
#include "../Utility/UtilityDataStructures.h"
#include "../Utility/Math.h"

class Index : public DynamicObject<Matrix3di>
{
	public:
		void add(Matrix3di index);
	private:
};