#include "../../../lib/GraphicEngine/Buffer/VertexArray.h"

namespace Hyphen
{
	VertexArray::VertexArray()
	{}

	void VertexArray::new_vao(Model* m)
	{
		glGenVertexArrays(1, &array_buffer);
		m->vao_index = array_buffer;
		index_map[array_buffer] = m;
	}

	void VertexArray::unload(GLuint index)
	{
		if (index == 0)
			return;

		array_buffer = index;

		for (unsigned int i = 0; i < size; i++)
			glDisableVertexAttribArray(i);

		index_map[array_buffer]->vao_index = 0;
		index_map.erase(array_buffer);
		glDeleteVertexArrays(1, &array_buffer);
	}

	void VertexArray::bind(Model* m)
	{
		array_buffer = m->vao_index;
		glBindVertexArray(array_buffer);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray()
	{
		for (std::map<int, Model*>::iterator it = index_map.begin(); it != index_map.end(); it++)
			unload(it->first);
	}
}