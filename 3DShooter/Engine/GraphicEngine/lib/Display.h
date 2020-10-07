#pragma once

#define DISPLAY_H_

#include "Utility/IncludeAll.h"
#include "Mesh.h"
#include "Shader.h"

class Display
{
	private:
		static void GLAPIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar * message, const void * userParam);

	public:
		Display(GLFWmonitor * monitor, GLFWwindow * share);

		void draw(Mesh * mesh, Shader * shader);

		virtual ~Display();
	private:
		GLFWwindow * window;
};