#pragma once

#define WINDOW_H_

#include "../CompiledHeaders.h"
#include "Platform/Windows.h"
#include "WindowAPI.h"

namespace Hyphen
{
	class HyphenWindow
	{
	public:
		Window * window = Window::create_window();
	public:
		static HyphenWindow * create();

		virtual bool init() = 0;

		virtual ~HyphenWindow() {};
	private:
	};
}