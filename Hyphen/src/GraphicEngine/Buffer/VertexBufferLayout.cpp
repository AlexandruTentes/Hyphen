#include "../../../lib/GraphicEngine/Buffer/VertexBufferLayout.h"

namespace Hyphen
{
	void VertexBufferLayout::load(GLuint type, GLuint size)
	{
		push(_VertexBufferLayout{ type, size, (type == GL_UNSIGNED_BYTE ? true : false) });

		this->stride += size * get_sizeof_gltype(type);
	}

	GLuint VertexBufferLayout::get_stride() const
	{
		return stride;
	}
}