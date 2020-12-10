#pragma once

#define RENDER_H_

#include "../CompiledHeaders.h"
#include "Type/Vertex.h"
#include "Mesh.h"
#include "Shader.h"
#include "Type/Model.h"

namespace Hyphen
{
	class Renderer
	{
	public:
		Renderer() {};

		void render(Model& m);
		void draw(Model& m);

		virtual ~Renderer() = default;
	private:
		Matrix4d<float> view;
		Shader shader;
		VertexBuffer vb;
		IndexBuffer ib;
		VertexBufferLayout layout;
		VertexArray va;
	};
}