#pragma once

#include "../../CompiledHeaders.h"

//===== Check if the OS is Windows =====//
#ifdef WINDOWS

#define WINDOWS_H_

#include "../WindowAPI.h"
#include "../WindowManager.h"

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

//===== The win api procedure =====//
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

//===== Getting the window manager singleton instance =====//
static Hyphen::WindowManager<HWND> & window_manager_instance =
Hyphen::WindowManager<HWND>::get_instance();

namespace Hyphen
{
	enum MouseKeyMap
	{
		LEFT_BTN, RIGHT_BTN, MIDDLE_BTN
	};

	class Windows : public Window
	{
	public:
		Windows(const WindowSpecs & specs);

		bool init() override;
		void create() override;
		void update() override;
		void destroy() override;
		void show() override;
		void resize(unsigned int width = 0, unsigned int height = 0) override;
		void set_cursor_pos(float x, float y) override;
		void show_cursor(bool status) override;

		void window_msg_handler();
		void kill_window();
		HWND get_handler() { return handler; }

		virtual ~Windows();

	//===== Public variables =====//
	public:
		HDC hdc = NULL; //GDI device context
		HWND handler = NULL; //Window handler
		HINSTANCE hinstance = NULL; //This application's handler
		POINT client_coords; //A POINT structure that contains client coords data
		std::string class_name = "test_class";

	public:
		WindowSpecs specs;
	};
}

#endif // WINDOWS