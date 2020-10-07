#pragma once

#define MESH_H_

#include "Utility/IncludeAll.h"
#include "Type/Vertex.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "VertexArray.h"

class Mesh
{
	public:
		Mesh();

		void draw();
		void load(Vertex * vertices);

		virtual ~Mesh();
	private:
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		VertexBufferLayout layout;

		int drawn_obj_count;
};