#pragma once

#define WINDOW_H_

#include "../CompiledHeaders.h"
#include "../Event/Event.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/WindowEvent.h"

namespace Hyphen
{
	struct WindowSpecs
	{
		unsigned short int width;
		unsigned short int height;
		unsigned short int color_bits;
		unsigned short int depth_bits;
		std::string title;

		WindowSpecs(const std::string & title = "Dev Window", 
			unsigned short int width = 1200, unsigned short int height = 700, 
			unsigned short int color_bits = 32, unsigned short int depth_bits = 32) :
			title(title), width(width), height(height), color_bits(color_bits), 
			depth_bits(depth_bits)
		{}
	};

	class Window
	{
	public:
		//===== Going to return an API window based on the platform =====//
		static Window * create_window(const WindowSpecs & window_specs = WindowSpecs());
		
		virtual bool init() = 0;
		virtual void create() = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;
		virtual void show() = 0;
		virtual void resize() = 0;

		template <class T> void on_event(Event & e)
		{
			dispatcher.dispatch<T>(e, T::get_instance().callback);
		}
		
		virtual ~Window() {};

	public:
		bool is_running = false;
		bool is_vsync = false;
		bool is_minimized = false;
		bool is_fullscreen = false;
		bool is_focused = true;

	private:
		Dispatcher dispatcher;
	};
}