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
			sizeof(m->vertex.get_all()[0]), GL_STATIC_DRAW, GL_FLOAT, 3);

		//Loading the texture buffer
		buffer.load_buffer(GL_ARRAY_BUFFER, m->texture.get_all(), m->texture.get_size() *
			sizeof(m->texture.get_all()[0]), GL_STATIC_DRAW, GL_FLOAT, 2);

		//Loading the normal buffer
		buffer.load_buffer(GL_ARRAY_BUFFER, m->normal.get_all(), m->normal.get_size() *
			sizeof(m->normal.get_all()[0]), GL_STATIC_DRAW, GL_FLOAT, 3);

		//Loading the index buffer
		buffer.load_buffer(GL_ELEMENT_ARRAY_BUFFER, m->index.vertex.get_all(), m->index.vertex.get_size() *
			sizeof(m->index.vertex.get_all()[0]), GL_STATIC_DRAW);

		va.unbind();
		
		m->data->rendered = true;
	}

	void Renderer::clear(unsigned int flags)
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(flags);
	}

	void Renderer::draw_scene()
	{
		for (auto& fbo : scenes.get(bound_scene)->active_cameras)
		{
			view = scenes.get(bound_scene)->cameras[fbo.first].view;
			fbo.second.bind();
			glEnable(GL_DEPTH_TEST);
			clear();

			for (auto const& m : scenes.get(bound_scene)->models)
			{
				m.second->bind_data((std::string)m.first);
				draw_model(m.second);
			}
			fbo.second.unbind();
		}

		glDisable(GL_DEPTH_TEST);
		clear(GL_COLOR_BUFFER_BIT);

		//Draw fullscreen quad
		//Use fbo texture generated as this quad's texture
		scenes.get(bound_scene)->draw_filter_quad();
	}

	void Renderer::draw_model(Model* m)
	{
		va.bind(m);
		m->data->shader.bind();
		glEnable(GL_DEPTH_TEST);
		m->data->shader.set_uniform_matrix4fv("transform_mat", get_transformation_matrix(m->data->scale,
			*m->data->position, *m->data->rotation));
		m->data->shader.set_uniform_matrix4fv("view_mat", get_view_matrix(view));
		m->data->shader.set_uniform_matrix4fv("projection_mat", get_perspective_matrix(70.0f,
			aspect_ratio, 0.1f, 1000.0f));
		m->data->shader.set_uniform3f("view_position", view[0]);
		m->data->shader.set_uniform1f("opacity", m->data->opacity);
		
		//Material data setup
		m->data->shader.set_uniform3f("material.ambient", m->data->color->mul(COLOR_CORRECTION));
		m->data->shader.set_uniform3f("material.diffuse", m->data->color->mul(COLOR_CORRECTION));
		m->data->shader.set_uniform3f("material.specular", Vector3d<float>(0.8, 0.8, 0.8));
		m->data->shader.set_uniform1f("material.shininess", 32.0);

		//Light data setup
		m->data->shader.set_uniform3f("light.position", 
			*scenes.get(bound_scene)->environment_light.position);
		m->data->shader.set_uniform3f("light.ambient", 
			*scenes.get(bound_scene)->environment_light.ambient);
		m->data->shader.set_uniform3f("light.diffuse",
			*scenes.get(bound_scene)->environment_light.diffuse);
		m->data->shader.set_uniform3f("light.specular",
			*scenes.get(bound_scene)->environment_light.specular);
			
		glDrawElements(GL_TRIANGLES, m->index.vertex.get_size(), GL_UNSIGNED_INT, nullptr);
		glDisable(GL_DEPTH_TEST);
		m->data->shader.unbind();
		va.unbind();
	}
}