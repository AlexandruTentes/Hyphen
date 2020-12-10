#include "../../lib/GraphicEngine/Render.h"

namespace Hyphen
{
	void Renderer::render(Model& m)
	{
		if (m.rendered)
			return;

		shader.load_shaders();
		shader.compile_shaders();

		//Loading the vertex buffer
		vb.load(m.vertex);
		vb.generate_buffers();

		//Loading the index buffer
		ib.load(m.index);
		ib.generate_buffers();

		//Loading the layout
		layout.load(GL_FLOAT, 3);	//Vertex layout
		//layout.load(GL_FLOAT, 4);

		//Preparing the vertex array
		va.add_buffer(&vb, &ib, &layout);
		ib.bind();

		m.rendered = true;

		view.set(0, 0, -3, 0,
			0, 0, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0);
	}

	void Renderer::draw(Model& m)
	{
		if (!m.rendered)
			return;

		shader.bind();

		glm::mat4 get_transformation = get_transformation_matrix(m.data.scale,
			m.data.translation, TO_RAD(m.data.rotation[0]),
			TO_RAD(m.data.rotation[1]), TO_RAD(m.data.rotation[2]));
		glm::mat4 get_perspective = get_perspective_matrix(70.0f,
			(float)width / height, 0.01f, 1000.0f);
		glm::mat4 get_view = get_view_matrix(get_perspective, view);
		glm::mat4 get_mat = get_calc_matrix(get_transformation, get_view);

		shader.set_uniform_matrix4fv("transform", get_mat);
		shader.set_uniform4f("color", glm::vec4(
			m.data.color[0] / 256, m.data.color[1] / 256,
			m.data.color[2] / 256, m.data.opacity));

		glDrawElements(GL_TRIANGLES, m.index.vertex.get_size(), GL_UNSIGNED_INT, nullptr);
	}
}