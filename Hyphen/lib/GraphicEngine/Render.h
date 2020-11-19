#pragma once

#define RENDER_H_

#include "Type/Vertex.h"
#include "Mesh.h"
#include "Shader.h"

namespace Hyphen
{
	class Render
	{
	public:
		Render(Vector3d<float> * arr, int size);

		void draw(Vertex * vertices, Mesh * mesh, Shader * shader);

		~Render();
	private:
		int size = 0;
		Vector3d<float> * data;
	};
}