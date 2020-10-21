#include "../../../lib/Window/API/DirectXWindows.h"

#ifdef DIRECTXWINDOWWINDOWS_H_

namespace Hyphen
{
	Window * Window::create()
	{
		return new DirectXWindowWindows;
	}

	DirectXWindowWindows::~DirectXWindowWindows()
	{
		window->close();
	}
}

#endif // DIRECTXWINDOW_H_
