#include "../lib/App.h"

#include "../lib/GraphicEngine/Shader.h"
#include "../lib/GraphicEngine/Buffer/VertexBufferLayout.h"
#include "../lib/GraphicEngine/Collection/FolderData.h"

namespace Hyphen
{
	void App::run()
	{
		KeyDown kd;
		MouseMove mv;
		HyphenWindow * app_window = HyphenWindow::create();

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";

		DynamicObject<FileAndPath> files;
		get_files_directory(files, std::string(model_path), model_extension, sizeof(model_extension) / sizeof(model_extension[0]));
		FolderData::get_instance().files = files;
				
		//===== =====//
		while (app_window->window->is_running)
		{
			glClearColor(0.5, 0.25, 0.5, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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