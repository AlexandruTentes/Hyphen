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
		main_window.main_window = window;

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
		
		if(glewInit() != GLEW_OK)
		{
			MessageBox(window_windows->handler, "Could not initialize glew!", "Window Creation Error", MB_OK);
			window_windows->kill_window();
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);
		
		window->show();
		gui->handler = handler;
		stack.push_overlay(gui);
	
#ifdef DEBUG_OPENGL
		// Enabling opengl debug event
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(opengl_debug_callback, 0);
#endif

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