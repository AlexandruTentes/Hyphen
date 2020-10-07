#pragma once

#define VERTEXBUFFER_H_

#include "../Utility/IncludeAll.h"
#include "../Type/Vertex.h"
#include "../Utility/UtilityDataStructures.h"

class VertexBuffer : public DynamicObject<GLuint>
{
	public:
		void load(Vertex * vertex);
		void generate_buffers();
		void bind();
		void unbind() const;

		~VertexBuffer();
	private:
		DynamicObject<Vertex> cache;
};
