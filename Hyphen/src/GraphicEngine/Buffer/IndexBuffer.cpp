#include "../../../lib/GraphicEngine/Buffer/IndexBuffer.h"

namespace Hyphen
{
	void IndexBuffer::load(Index * data)
	{
		push((GLuint)0);
		cache.push(data);
	}

	void IndexBuffer::generate_buffers()
	{
		glGenBuffers(get_size(), get_all());

		Vector3d<int> aux;
		DynamicObject<Vector3d<int>> vertex_index(cache.get_all()->get_size());
		for (unsigned int i = 0; i < vertex_index.get_capacity(); i++)
		{
			aux.init(0);
			if (!cache.get_all()->has_fourth)
			{
				aux.vec[0] = cache.get_all()->get_one(i).mat[0][0];
				aux.vec[1] = cache.get_all()->get_one(i).mat[1][0];
				aux.vec[2] = cache.get_all()->get_one(i).mat[2][0];
			}
			else
			{
				aux.vec[0] = cache.get_all()->get_one(i).mat[0][0];
				aux.vec[1] = cache.get_all()->get_one(i).mat[2][0];
				aux.vec[2] = cache.get_all()->get_one(i).mat[3][0];
			}

			vertex_index.push(aux);
		}


		for (GLuint i = 0; i < cache.get_size(); i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_one(get_size() - 1));
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_index.get_size() *
				sizeof(vertex_index.get_one(0)), & vertex_index.get_all()[0], GL_STATIC_DRAW);
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