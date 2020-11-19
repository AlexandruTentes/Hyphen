#include "../../../lib/GraphicEngine/Type/Normal.h"

namespace Hyphen
{
	void Normal::add(Vector3d<float> normal)
	{
		push(normal);
	}
}