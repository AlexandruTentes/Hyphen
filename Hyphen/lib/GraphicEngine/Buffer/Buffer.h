#pragma once

#define BUFFER_H_

#include "../../CompiledHeaders.h"

namespace Hyphen
{
	class Buffer
	{
	public:
		void unload();
		void new_buffer();
		template <class T>
		void load_buffer(GLuint buffer_type, T * data, unsigned int size, GLuint buffer_draw_type,
			GLuint data_type = 0, unsigned int data_type_size = 0);

		virtual ~Buffer();
	private:
		static const unsigned int capacity = 4;
		unsigned int size = 0;

		GLuint array_buffer[capacity];
	};

	template<class T>
	void Buffer::load_buffer(GLuint buffer_type, T * data, unsigned int size, GLuint buffer_draw_type,
		GLuint data_type, unsigned int data_type_size)
	{
		if (!size)
		{
			this->size++;
			return;
		}

		glBindBuffer(buffer_type, array_buffer[this->size]);
		glBufferData(buffer_type, size, &data[0], buffer_draw_type);

		if (data_type_size)
		{
			glEnableVertexAttribArray(this->size);
			glVertexAttribPointer(this->size, data_type_size, data_type,
				(data_type == GL_UNSIGNED_BYTE ? true : false), 0, 0);
		}

		this->size++;
	}
}