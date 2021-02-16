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
		void load_buffer(GLuint buffer_type, T * data, unsigned int size, GLuint buffer_draw_type);

		virtual ~Buffer();
	private:
		static const unsigned int capacity = 2;
		unsigned int size = 0;

		GLuint array_buffer[capacity];
	};

	template<class T>
	inline void Buffer::load_buffer(GLuint buffer_type, T * data, unsigned int size, GLuint buffer_draw_type)
	{
		glBindBuffer(buffer_type, array_buffer[this->size]);
		glBufferData(buffer_type, size, &data[0], buffer_draw_type);
		this->size++;
	}
}