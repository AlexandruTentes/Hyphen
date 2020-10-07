#include "../../lib/Buffer/VertexBufferLayout.h"

void VertexBufferLayout::load(GLuint type, GLuint size)
{
	push(_VertexBufferLayout{type, size, (type == GL_UNSIGNED_BYTE ? true : false)});
	stride += size * uf::get_sizeof_gltype(type);
}

GLuint VertexBufferLayout::get_stride() const
{
	return stride;
}