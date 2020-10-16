#pragma once

#include "../CompiledHeaders.h"

//===== Check if the OS is Windows =====//
#ifdef WINDOWS

#define WINDOWS_H_

#include "../WindowAPI.h"
#include "../WindowManager.h"

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

//===== The win api procedure =====//
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

//===== Getting the window manager singleton instance =====//
static WindowAPI::WindowManager<HWND> & window_manager_instance =
WindowAPI::WindowManager<HWND>::get_instance();

namespace WindowAPI
{
	class Windows : public Window
	{
	public:
		Windows(const WindowSpecs & specs);

		bool init() override;
		void create() override;
		void update() override;
		void destroy() override;
		void show() override;
		void resize() override;
		void on_event(Event & e) override;

		void window_msg_handler();
		void kill_window();

		virtual ~Windows() override;

	//===== Public variables =====//
	public:
		HDC hdc = NULL; //GDI device context
		HWND handler = NULL; //Window handler
		HINSTANCE hinstance = NULL; //This application's handler
		std::string class_name = "test_class";
		Dispatcher dispacher;

	private:
		WindowSpecs specs;
	};
}

#endif // WINDOWS