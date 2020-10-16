#pragma once

#define APP_H_

#include "Platform.h"
#include "Graphics/Window/Window.h"
#include "../lib/Listener.h"

namespace Hyphen
{
	class API App
	{
	public:
		void run();
	private:
		Listener & listener = Listener::get_instance();
	};

	App * create();
}