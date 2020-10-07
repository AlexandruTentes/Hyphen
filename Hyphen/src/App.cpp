#include "../lib/App.h"

namespace Hyphen
{
	void App::run()
	{
		Window * app_window = Window::create();

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";

		while (app_window->window->is_running)
		{
			app_window->window->update();
		}
		
		delete app_window;
		std::cin.get();
	}
}