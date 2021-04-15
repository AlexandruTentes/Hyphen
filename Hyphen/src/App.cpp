#include "../lib/App.h"

namespace Hyphen
{
	void App::run()
	{
		get_files_directory(folder.get(model_path), std::string(model_path), model_extension,
			sizeof(model_extension) / sizeof(model_extension[0]));
		get_files_directory(folder.get(shader_path), std::string(shader_path), shader_extension,
			sizeof(shader_extension) / sizeof(shader_extension[0]));
		get_files_directory(folder.get(miscs_path), std::string(miscs_path), model_extension,
			sizeof(model_extension) / sizeof(model_extension[0]));

		KeyDown kd;
		MouseMove mv;
		HyphenWindow * app_window = HyphenWindow::create();

		if (!app_window->init())
			std::cerr << "Error at window initialization!\n";
				
		auto prev_t = std::chrono::system_clock::now();
		int frame_count = 0;

		//===== =====//
		while (app_window->window->is_running)
		{
			auto current_t = std::chrono::system_clock::now();
			frame_count++;
			long long prev_time = std::chrono::duration_cast<std::chrono::seconds>(
				prev_t.time_since_epoch()).count();
			long long current_time = std::chrono::duration_cast<std::chrono::seconds>(
				current_t.time_since_epoch()).count();

			if (current_time - prev_time >= 1)
			{
				std::cout << "FPS: " << frame_count << "\n";
				frame_count = 0;
				prev_t = current_t;
			}

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