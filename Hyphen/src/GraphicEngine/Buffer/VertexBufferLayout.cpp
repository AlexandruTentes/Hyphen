#include "../../../lib/GraphicEngine/Buffer/VertexBufferLayout.h"

namespace Hyphen
{
	void VertexBufferLayout::load(GLuint type, GLuint size)
	{
		push(_VertexBufferLayout{ type, size, (type == GL_UNSIGNED_BYTE ? true : false) });

		if(!once)
			this->stride += size * get_sizeof_gltype(type);

		once = true;
	}

	GLuint VertexBufferLayout::get_stride() const
	{
		return stride;
	}
}