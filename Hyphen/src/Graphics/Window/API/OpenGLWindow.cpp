#include "../../../../lib/Graphics/Window/API/OpenGLWindows.h"

#ifdef OPENGLWINDOWWINDOWS_H_

namespace Hyphen
{
	Window * Window::create()
	{
		return new OpenGLWindowWindows;
	}

	bool OpenGLWindowWindows::init()
	{
		//===== Casting the parent class instance as the child Windows window =====//
		window_windows = static_cast<WindowAPI::Windows *>(window);

		bool basic_window_init = window->init();

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

		window->show();

		return basic_window_init;
	}

	GLvoid OpenGLWindowWindows::resize_scene(GLsizei width, GLsizei height)
	{
		//Branchless if(height == 0) then height = 1, else retian previous height
		//division by 0 protection!
		height = (height != 0) * height + 1 * (height == 0);

		glViewport(0, 0, width, height);
	}

	OpenGLWindowWindows::~OpenGLWindowWindows()
	{
		if (hglrc && //In case there is a rendering context
			!wglMakeCurrent(NULL, NULL) && //Attempt to free the rendering context from the device context
			!wglDeleteContext(hglrc)) //Attempt to delete the rendering context
			hglrc = NULL;

		delete window;
	}
}

#endif