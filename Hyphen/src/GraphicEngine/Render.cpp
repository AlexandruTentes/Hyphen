#include "../../lib/GraphicEngine/Render.h"

namespace Hyphen
{
	Render::Render(Vector3d<float> * arr, int size)
	{
		data = arr;
		this->size = size;
	}

	void Render::draw(Vertex const & vertices, Mesh * mesh, Shader * shader)
	{
		//vertices->add(data, size);

		mesh->load(vertices);

		shader->load_shaders(shader_path);
		shader->compile_shaders();

		shader->bind();
		shader->unbind();

		//display->draw(mesh, shader);
	}

	Render::~Render()
	{

	}
}