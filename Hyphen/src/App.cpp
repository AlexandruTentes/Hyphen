#include "../lib/App.h"

#include "../lib/GraphicEngine/Shader.h"
#include "../lib/GraphicEngine/Buffer/VertexBuffer.h"
#include "../lib/GraphicEngine/Buffer/IndexBuffer.h"
#include "../lib/GraphicEngine/Buffer/VertexBufferLayout.h"
#include "../lib/GraphicEngine/VertexArray.h"

namespace Hyphen
{
	void App::run()
	{
		KeyDown kd;
		MouseMove mv;
		HyphenWindow * app_window = HyphenWindow::create();		

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";

		//===== TEMPORARY: showcase purposes =====//

		//Preparing the shaders
		Shader shader;
		shader.load_shaders(shader_path);
		shader.compile_shaders();
		
		//Loading the model data
		Model m = read_model_format();

		//Loading the vertex buffer
		VertexBuffer vb;
		vb.load(& m.vertex);
		vb.generate_buffers();

		//Loading the index buffer
		IndexBuffer ib;
		ib.load(& m.index);
		ib.generate_buffers();

		//Loading the layout
		VertexBufferLayout layout;
		layout.load(GL_FLOAT, 3);	//Vertex layout
		//layout.load(GL_FLOAT, 4);

		//Preparing the vertex array
		VertexArray va;
		va.add_buffer(&vb, &ib, &layout);
				
		//===== =====//

		while (app_window->window->is_running)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.5, 0.25, 0.5, 1.0);

			shader.bind();
			
			Matrix4d<float> get_transformation = get_transformation_matrix(temporary_globals::get_instance().scale,
				temporary_globals::get_instance().translation, TO_RAD(temporary_globals::get_instance().rotation_x),
				TO_RAD(temporary_globals::get_instance().rotation_y), TO_RAD(temporary_globals::get_instance().rotation_z));

			Matrix4d<float> get_perspective = get_perspective_matrix(60.0f, aspect_ratio, 0.1f, 100.0f);

			Matrix4d<float> view(0, 0, -3.0, 0,
				0, 0, 1.0, 0,
				0, 1.0, 0, 0,
				0, 0, 0, 0);

			Matrix4d<float> get_view = get_view_matrix(get_perspective, view);

			Matrix4d<float> get_mat = get_calc_matrix(get_transformation, get_view);

			std::cout << "model: \n" << get_transformation.print() << "\n";

			shader.set_uniform_matrix4fv("transform", get_transformation);

			va.bind();
			vb.bind();
			ib.bind();
			glDrawElements(GL_TRIANGLES, m.vertex.get_size(), GL_UNSIGNED_INT, nullptr);
			ib.unbind();
			vb.unbind();
			va.unbind();

			/*
			if (poll_event(&kd))
				std::cout << "POLING KEY: " << kd.get_key() << std::endl;

			if (poll_event(&mv))
				std::cout << "POLLING MOUSE: x: " << mv.get_x() << " y: " << mv.get_y() << std::endl;
				*/

			for (unsigned int i = layer_stack.get_overlays().get_size(); i >= 1; i--)
				layer_stack.get_overlays().get_one(i - 1)->update();

			app_window->window->update();
		}
		
		delete app_window;
	}
}