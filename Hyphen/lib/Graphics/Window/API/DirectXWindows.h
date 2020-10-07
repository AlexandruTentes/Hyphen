#pragma once

#include "../Window.h"

//===== Check if the Graphical API is opengl =====//
#if defined DIRECTX && defined WINDOWS

#define DIRECTXWINDOWWINDOWS_H_

namespace Hyphen
{
	class DirectXWindowWindows : public Window
	{
	public:
		virtual ~DirectXWindowWindows() override;
	private:
	};
}

#endif