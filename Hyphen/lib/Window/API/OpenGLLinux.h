#pragma once

#include "../Window.h"

//===== Check if the Graphical API is opengl =====//
#if defined OPENGL && defined LINUX

#define OPENGLWINDOWLINUX_H_

namespace Hyphen
{
	class OpenGLWindowLinux : public HyphenWindow
	{
	public:
		virtual ~OpenGLWindowLinux() override;
	private:
		HGLRC hglrc = NULL;	//Rendering device context
	};
}

#endif#pragma once
