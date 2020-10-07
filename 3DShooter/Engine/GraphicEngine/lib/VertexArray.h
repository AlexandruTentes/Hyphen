#pragma once

#define VERTEXARRAY_H_

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexBufferLayout.h"

class VertexArray
{
	public:
		VertexArray();

		void add_buffer(VertexBuffer * vertex_buffer, IndexBuffer * index_buffer, VertexBufferLayout * layout);
		void bind();
		void unbind();

		~VertexArray();
	private:
		GLuint size = 0;
		GLuint array_buffer;
};