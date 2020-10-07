#include "../lib/VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &array_buffer);	 
}

void VertexArray::add_buffer(VertexBuffer * vertex_buffer, IndexBuffer * index_buffer, VertexBufferLayout * layout)
{
	bind();

	vertex_buffer->bind();
	index_buffer->bind();

	_VertexBufferLayout * data = layout->get_all();
	GLuint offset = 0;

	for (GLuint i = 0; i < layout->get_size(); i++)
	{
		//These lines will throw a GL error if they attempt to set multiple layouts to the same vertex buffer
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, data[i].size, data[i].type, data[i].normalized ? GL_TRUE : GL_FALSE, layout->get_stride(), (const void *) offset);
		
		offset += data[i].size * uf::get_sizeof_gltype(data[i].type);
		size++;
	}
}

void VertexArray::bind()
{
	glBindVertexArray(array_buffer);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	for(unsigned int i = 0; i < size; i++)
		glDisableVertexAttribArray(i);

	glDeleteVertexArrays(1, & array_buffer);
}
