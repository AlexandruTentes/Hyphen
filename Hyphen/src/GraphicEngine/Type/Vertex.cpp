#include "../../../lib/GraphicEngine/Type/Vertex.h"

namespace Hyphen
{
	void Vertex::add(Vector3d<float> vertex)
	{
		push(vertex);
	}
}