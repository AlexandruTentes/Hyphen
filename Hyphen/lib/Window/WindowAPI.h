#pragma once

#define WINDOW_H_

#include "../CompiledHeaders.h"
#include "../Event/KeyCodes.h"
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
		
		WindowSpecs(const std::string & title = window_title,
			unsigned short int width = Hyphen::width, unsigned short int height = Hyphen::height) :
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
		virtual void resize(unsigned int width = 0, unsigned int height = 0) = 0;
		virtual void set_cursor_pos(float x, float y) = 0;
		virtual void show_cursor(bool status) = 0;
		template <class T> 
		void on_event(Event& e);
		
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

	template<class T>
	void Window::on_event(Event& e)
	{
		bool ignore = false;

		//Handle bottom of the stack, then propagate cascade-like if not handled
		for (unsigned int i = 0; i < layer_stack.get_overlays().get_size(); i++)
		{

			if (!layer_stack.get_overlays().peek(i)->get_status())
			{
				//layer_stack.get_overlays().peek(i)->set_status(true);
				layer_stack.get_overlays().peek(i)->event(e);
				ignore = true;
				//break;
			}
		}

		if (!ignore && layer_stack.get_layers() != NULL && layer_stack.get_layers().peek() != nullptr)
			//Only handle the top of the stack element
			layer_stack.get_layers().peek()->event(e);

		dispatcher.dispatch<T>(e, T::get_instance().callback);
	}
}