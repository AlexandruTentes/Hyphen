#include "../../lib/GraphicEngine/Renderer.h"

namespace Hyphen
{
	void Renderer::render_model(Model * m)
	{
		if (m->data->rendered)
			return;

		m->data->shader.load_shader(m->data->shader.name);
		m->data->shader.link_shaders();

		va.new_vao(m);
		va.bind(m);
		buffer.unload();
		buffer.new_buffer();

		//Loading the vertex buffer
		buffer.load_buffer(GL_ARRAY_BUFFER, m->vertex.get_all(), m->vertex.get_size() *
			sizeof(m->vertex.get_all()[0]), GL_STATIC_DRAW);

		layout.load(GL_FLOAT, 3);
		va.add_buffer(&layout);

		//Loading the index buffer
		buffer.load_buffer(GL_ELEMENT_ARRAY_BUFFER, m->index.vertex.get_all(), m->index.vertex.get_size() *
			sizeof(m->index.vertex.get_all()[0]), GL_STATIC_DRAW);

		va.unbind();
		m->data->rendered = true;
	}

	void Renderer::clear()
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::draw_scene()
	{
		clear();
		for(auto const& m : scenes.get(bound_scene)->models)
		{
			m.second->bind_data((std::string) m.first);
			draw_model(m.second);
		}
	}

	void Renderer::draw_model(Model* m)
	{
		va.bind(m);
		m->data->shader.bind();

		m->data->shader.set_uniform_matrix4fv("transform_mat", get_transformation_matrix(m->data->scale,
			m->data->translation, TO_RAD(m->data->rotation[0]),
			TO_RAD(m->data->rotation[1]), TO_RAD(m->data->rotation[2])));
		m->data->shader.set_uniform_matrix4fv("view_mat", get_view_matrix(view));
		m->data->shader.set_uniform_matrix4fv("projection_mat", get_perspective_matrix(70.0f,
			aspect_ratio, 0.1f, 1000.0f));
		m->data->shader.set_uniform4f("color", glm::vec4(
			m->data->color[0] / 256, m->data->color[1] / 256,
			m->data->color[2] / 256, m->data->opacity));

		glDrawElements(GL_TRIANGLES, m->index.vertex.get_size(), GL_UNSIGNED_INT, nullptr);
		va.unbind();
	}
}