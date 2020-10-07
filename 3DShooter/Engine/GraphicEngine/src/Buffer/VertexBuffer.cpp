#include "../../lib/Buffer/VertexBuffer.h"

void VertexBuffer::load(Vertex * data)
{
	push((GLuint) 0);
	cache.push(data);
}

void VertexBuffer::generate_buffers()
{
	glGenBuffers(get_size(), get_all());

	for (GLuint i = 0; i < cache.get_size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, get_one(get_size() - 1));
		glBufferData(GL_ARRAY_BUFFER, cache.get_size() *
			sizeof(cache.get_one(0)), cache.get_all(), GL_STATIC_DRAW);
	}
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, get_one(get_size() - 1));
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(get_size(), get_all());
}
