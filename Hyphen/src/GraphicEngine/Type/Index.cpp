#include "../../../lib/GraphicEngine/Type/Index.h"

namespace Hyphen
{
	void Index::add(Matrix4d<int> index)
	{
		push(index);
	}
}