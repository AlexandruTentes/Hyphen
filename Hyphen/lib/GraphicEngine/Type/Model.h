#pragma once

#define MODEL_H_

#include "Index.h"
#include "Vertex.h"
#include "Normal.h"
#include "Texture.h"

///////////////////////////////////////
//===== The mdoel datastructure =====//
///////////////////////////////////////

namespace Hyphen
{
	class Model
	{
	public:
		Model(Vertex vertex, Normal normal, Texture texture, Index index);

		~Model();
	public:
		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
	};
}