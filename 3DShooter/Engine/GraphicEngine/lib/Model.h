#pragma once

#define MODEL_H_

#include "Type/Index.h"
#include "Type/Vertex.h"
#include "Type/Normal.h"
#include "Type/Texture.h"

///////////////////////////////////////
//===== The mdoel datastructure =====//
///////////////////////////////////////

class Model
{
	public:
		Model(Vertex vertex, Normal normal, Texture texture, Index index);

		~Model();
	private:
		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
};