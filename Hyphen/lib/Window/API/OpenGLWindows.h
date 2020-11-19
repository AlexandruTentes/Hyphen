#pragma once

#include "../Window.h"

//===== Check if the Graphical API is opengl =====//
#if defined OPENGL && defined WINDOWS

#define OPENGLWINDOWWINDOWS_H_

namespace Hyphen
{
#ifdef DEBUG_OPENGL
	static std::map<std::string, bool> opengl_error_lookup;
#endif 

	class OpenGLWindowWindows : public HyphenWindow
	{
	private:
#ifdef DEBUG_OPENGL
		static void GLAPIENTRY opengl_debug_callback(GLenum source, GLenum type,
			GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			std::string key = std::to_string(type) + std::to_string(severity) + std::to_string(id);

			if (!opengl_error_lookup[key])
			{
				opengl_error_lookup[key] = true;
				std::cerr << "TYPE: " << (type == GL_DEBUG_TYPE_ERROR ? "ERROR" : "WARNING") << "\tSEVERITY: " << severity << "\tID: " << id << "\n";
				std::cerr << "SOURCE: " << source << "\nMESSAGE: " << message << "\n\n";
			}
		};
#endif
	public:
		bool init() override;
		HWND get_handler() { return handler; }

		//===== Nesting deconstructors =====//
		virtual ~OpenGLWindowWindows();
	private:
		Windows * window_windows;
		HGLRC hglrc = NULL;	//Rendering device context
		HWND handler = NULL;
	};
}

#endif