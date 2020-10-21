#include "../../../lib/Window/API/OpenGLLinux.h"

#ifdef OPENGLWINDOWLINUX_H_

namespace Hyphen
{
	Window * Window::create()
	{
		return new OpenGLWindowLinux;
	}

	OpenGLWindowLinux::~OpenGLWindowLinux()
	{
		window->close();
	}
}

#endif