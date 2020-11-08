#pragma once

#define WINDOW_H_

#include "../CompiledHeaders.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/WindowEvent.h"
#include "../Layer/LayerStack.h"
#include "../Event/Dispatcher.h"

namespace Hyphen
{
	struct WindowSpecs
	{
		unsigned short int width;
		unsigned short int height;
		std::string title;

		WindowSpecs(const std::string & title = "Dev Window", 
			unsigned short int width = 1200, unsigned short int height = 7002) :
			title(title), width(width), height(height) {}
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
			bool ignore = false;

			//Handle top of the stack, then propagate cascade-like if not handled
			for (unsigned int i = layer_stack.get_overlays().get_size(); i >= 1; i--)
			{
				if (layer_stack.get_overlays().peek(i - 1)->get_status())
				{
					layer_stack.get_overlays().peek(i - 1)->event(e);
					ignore = true;
					break;
				}
			}

			if(!ignore)
				//Only handle the top of the stack element
				layer_stack.get_layers().peek()->event(e);

			dispatcher.dispatch<T>(e, T::get_instance().callback);
		}
		
		virtual ~Window() = default;
	public:
		bool is_running = false;
		bool is_vsync = false;
		bool is_minimized = false;
		bool is_fullscreen = false;
		bool is_focused = true;
	protected:
		LayerStack & layer_stack = LayerStack::get_instance();
	private:
		Dispatcher dispatcher;
	};
}