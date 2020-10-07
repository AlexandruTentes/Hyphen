#pragma once

#define WINDOW_H_

#include "../../CompiledHeaders.h"

namespace Hyphen
{
	class Window
	{
	public:
		WindowAPI::Window * window = WindowAPI::Window::create_window();;
	public:
		static Window * create();

		virtual bool init() = 0;

		virtual ~Window() {};
	private:
	};
}