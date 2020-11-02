#include "../lib/App.h"

namespace Hyphen
{
	void App::run()
	{
		KeyDown kd;
		HyphenWindow * app_window = HyphenWindow::create();

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";

		while (app_window->window->is_running)
		{
			app_window->window->update();

			if (GetEvent(& kd))
				std::cout << "POLLING WORKED " << std::endl;
		}
		
		delete app_window;
		std::cin.get();
	}

	void App::push_layer(Layer * layer)
	{
		layer_stack.push_layer(layer);
	}

	void App::push_overlay(Layer * overlay)
	{
		layer_stack.push_overlay(overlay);
	}

	void App::pop_layer(Layer * layer)
	{
		layer_stack.pop_layer(layer);
	}

	void App::pop_overlay(Layer * overlay)
	{
		layer_stack.pop_overlay(overlay);
	}
}