#include "../../../lib/Window/API/OpenGLWindows.h"

#ifdef OPENGLWINDOWWINDOWS_H_

namespace Hyphen
{
	HyphenWindow * HyphenWindow::create()
	{
		return new OpenGLWindowWindows;
	}

	bool OpenGLWindowWindows::init()
	{
		//===== Casting the parent class instance as the child Windows window =====//
		window_windows = static_cast<Windows *>(window);
		bool basic_window_init = window->init();
		handler = window_windows->get_handler();
		gui = new GUI();

		if (!(hglrc = wglCreateContext(window_windows->hdc)))
		{
			MessageBox(window_windows->handler, "Could not get rendering context!", "Window Creation Error", MB_OK);
			window_windows->kill_window();
			return false;
		}

		if (!wglMakeCurrent(window_windows->hdc, hglrc))
		{
			MessageBox(window_windows->handler, "Could not set the rendering context!", "Window Creation Error", MB_OK);
			window_windows->kill_window();
			return false;
		}
		
		glewInit();
		window->show();
		gui->set_handler(handler);
		stack.push_overlay(gui);
		return basic_window_init;
	}

	OpenGLWindowWindows::~OpenGLWindowWindows()
	{
		stack.pop_overlay(gui);

		if (hglrc && //In case there is a rendering context
			!wglMakeCurrent(NULL, NULL) && //Attempt to free the rendering context from the device context
			!wglDeleteContext(hglrc)) //Attempt to delete the rendering context
			hglrc = NULL;

		delete window;
	}
}

#endif