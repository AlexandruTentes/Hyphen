#pragma once

#include "WindowAPI.h"

#define MAINENGINEWINDOW_H_

namespace Hyphen
{
	class MainWindow
	{
	public:
		SINGLETONIZE(MainWindow)

	public:
		Window* main_window = nullptr;
	};
}