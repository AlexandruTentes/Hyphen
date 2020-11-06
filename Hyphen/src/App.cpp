#include "../lib/App.h"

namespace Hyphen
{
	void App::run()
	{
		KeyDown kd;
		MouseMove mv;
		HyphenWindow * app_window = HyphenWindow::create();

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";

		while (app_window->window->is_running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, 0.0, 0.0, 1.0);

			for (unsigned int i = 0; i < layer_stack.get_overlays().get_size(); i++)
				layer_stack.get_overlays().get_one(i)->update();

			if (poll_event(& kd))
				std::cout << "POLING KEY: " << kd.get_key() << std::endl;

			if (poll_event(&mv))
				std::cout << "POLLING MOUSE: x: " << mv.get_x() << " y: " << mv.get_y() << std::endl;

			app_window->window->update();
		}
		
		delete app_window;
	}
}