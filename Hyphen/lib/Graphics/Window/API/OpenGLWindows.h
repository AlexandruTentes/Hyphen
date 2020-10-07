#pragma once

#include "../Window.h"

//===== Check if the Graphical API is opengl =====//
#if defined OPENGL && defined WINDOWS

#define OPENGLWINDOWWINDOWS_H_

namespace Hyphen
{
	class OpenGLWindowWindows : public Window
	{
	public:
		bool init() override;

		//===== Nesting deconstructors =====//
		virtual ~OpenGLWindowWindows() override;

	//===== Private functions =====//
	private:
		GLvoid resize_scene(GLsizei width, GLsizei height);

	private:
		WindowAPI::Windows * window_windows;
		HGLRC hglrc = NULL;	//Rendering device context
	};
}

#endif