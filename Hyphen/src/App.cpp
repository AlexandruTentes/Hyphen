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
		/*
		float poz[6] = {
			-1.0f, -1.0f,
			1.0f, -1.0f,
			0.0f, 1.0f
		};

		unsigned int r;
		glGenBuffers(1, &r);
		glBindBuffer(GL_ARRAY_BUFFER, r);
		glBufferData(GL_ARRAY_BUFFER, sizeof(poz), poz, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		*/
		//Preparing the shaders
		Shader shader;
		shader.load_shaders(shader_path);
		shader.compile_shaders();

		//Loading the model data
		/*
		Vertex v;
		v.add(Vector3d<float>(-1.0, -1.0, 0.0));
		v.add(Vector3d<float>(1.0, -1.0, 0.0));
		v.add(Vector3d<float>(0.0, 1.0, 0.0));
		Normal n;
		Texture t;
		Index i;
		i.add(Matrix3d<int>(0, 0, 0,
							1, 0, 0,
							2, 0, 0));
		Model m(v, n, t, i); //read_model_format();*/
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

			for (unsigned int i = layer_stack.get_overlays().get_size(); i >= 1 ; i--)
				layer_stack.get_overlays().get_one(i - 1)->update();

			app_window->window->update();
		}
		
		delete app_window;
	}
}