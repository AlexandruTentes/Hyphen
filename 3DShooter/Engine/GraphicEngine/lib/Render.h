#pragma once

#define RENDER_H_

#include "Display.h"
#include "Type/Vertex.h"
#include "Mesh.h"
#include "Shader.h"

class Render
{
	public:
		Render(Vector3df * arr, int size);

		void draw(Display * display, Vertex * vertices, Mesh * mesh, Shader * shader);

		~Render();
	private:
		int size = 0;
		Vector3df * data;
};