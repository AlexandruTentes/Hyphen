#include "../lib/Render.h"

Render::Render(Vector3df * arr, int size)
{
	data = arr;
	this->size = size;
}

void Render::draw(Display * display, Vertex * vertices, Mesh * mesh, Shader * shader)
{
	//vertices->add(data, size);

	mesh->load(vertices);

	shader->load_shaders(global::shader_path);
	shader->compile_shaders();

	shader->bind();
	shader->unbind();

	display->draw(mesh, shader);
}

Render::~Render()
{

}
