#pragma once

#define MESH_H_

#include "../CompiledHeaders.h"
#include "Type/Vertex.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "VertexArray.h"

namespace Hyphen
{
	class Mesh
	{
	public:
		Mesh();

		void draw();
		void load(Vertex const & vertices);

		virtual ~Mesh();
	private:
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		VertexBufferLayout layout;

		int drawn_obj_count;
	};
}