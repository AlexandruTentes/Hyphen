#include "../../../lib/GraphicEngine/Buffer/IndexBuffer.h"

namespace Hyphen
{
	void IndexBuffer::load(Index const & data)
	{
		push((GLuint)0);
		cache.push(data);
	}

	void IndexBuffer::generate_buffers()
	{
		glGenBuffers(get_size(), get_all());

		for (GLuint i = 0; i < cache.get_size(); i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_one(get_size() - 1));
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, cache.get_all()->vertex.get_size() *
				sizeof(cache.get_all()->vertex.get_one(0)), & cache.get_all()->vertex.get_all()[0], GL_STATIC_DRAW);
		}
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_one(get_size() - 1));
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(get_size(), get_all());
	}
}