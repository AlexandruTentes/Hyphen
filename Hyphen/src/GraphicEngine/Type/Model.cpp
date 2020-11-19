#include "../../../lib/GraphicEngine/Type/Model.h"

namespace Hyphen
{
	Model::Model(Vertex vertex, Normal normal, Texture texture, Index index) :
		vertex(std::move(vertex)), normal(std::move(normal)),
		texture(std::move(texture)), index(std::move(index))
	{}

	Model::~Model()
	{}
}
