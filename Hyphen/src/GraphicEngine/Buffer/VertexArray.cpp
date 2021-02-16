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

	void VertexArray::add_buffer(VertexBufferLayout * layout)
	{
		_VertexBufferLayout * data = layout->get_all();
		GLuint offset = 0;

		//These lines will throw a GL error if they attempt to set multiple layouts to the same vertex buffer
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, data[0].size, data[0].type, data[0].normalized ? GL_TRUE : GL_FALSE, layout->get_stride(), (const void *)offset);

		//offset += data[0].size * get_sizeof_gltype(data[0].type);
		size++;
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