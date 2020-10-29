#pragma once

#include "../Window.h"

//===== Check if the Graphical API is opengl =====//
#if defined OPENGL && defined WINDOWS

#define OPENGLWINDOWWINDOWS_H_

namespace Hyphen
{
	class OpenGLWindowWindows : public HyphenWindow
	{
	public:
		bool init() override;

		//===== Nesting deconstructors =====//
		virtual ~OpenGLWindowWindows();

	//===== Private functions =====//
	private:
		GLvoid resize_scene(GLsizei width, GLsizei height);

	private:
		Windows * window_windows;
		HGLRC hglrc = NULL;	//Rendering device context
	};
}

#endif