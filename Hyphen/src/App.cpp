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

		get_files_directory(std::string(model_path), model_extension);
				
		//EngineCamera * camera = new EngineCamera(view);
		//layer_stack.push_overlay(camera);

		//===== =====//
		while (app_window->window->is_running)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.5, 0.25, 0.5, 1.0);

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

		//layer_stack.pop_overlay(camera);
		
		delete app_window;
	}
}