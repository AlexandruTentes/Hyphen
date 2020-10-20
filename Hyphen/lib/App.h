#pragma once

#define APP_H_

#include "Platform.h"
#include "Window/Window.h"

namespace Hyphen
{
	class API App
	{
	public:
		void run();
	};

	App * create();
}