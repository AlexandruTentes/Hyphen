#pragma once

#define VERTEXARRAY_H_

#include "../Type/Model.h"
#include "VertexBufferLayout.h"

namespace Hyphen
{
	class VertexArray
	{
	public:
		VertexArray();

		void new_vao(Model* m);
		void unload(GLuint index);
		void bind(Model* m);
		void unbind();

		~VertexArray();
	private:
		GLuint size = 0;
		GLuint array_buffer = 0;
		std::map<int, Model *> index_map;
	};
}