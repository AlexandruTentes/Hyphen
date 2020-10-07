#include "../lib/Display.h"

Display::Display(GLFWmonitor * monitor, GLFWwindow * share)
{
	// Initialize the library 
	if (!glfwInit())
	{
		std::cerr << "COULD NOT INITIALIZE GLFW" << std::endl;
		return;
	}

	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(global::width, global::height, global::window_title.c_str(), monitor, share);

	if (!window)
	{
		std::cerr << "COULD NOT CREATE THE WINDOW" << std::endl;
		glfwTerminate();
		return;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Setting the window refresh interval (1 = my display refresh rate)
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "COULD NOT INITIALIZE GLEW" << std::endl;
		return;
	}

	// Enabling opengl debug event
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_callback, 0);
}

Display::~Display()
{
	glfwTerminate();
}

void GLAPIENTRY Display::gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, 
	GLsizei length, const GLchar * message, const void * userParam)
{
	std::cerr << std::endl;
	std::cerr << "TYPE: " << (type == GL_DEBUG_TYPE_ERROR ? "GL ERROR" : "") << "\tSEVERITY: " << severity << std::endl;
	std::cerr << "SOURCE: " << source << "\tMESSAGE: " << message << std::endl;
	std::cerr << std::endl;
}

void Display::draw(Mesh * mesh, Shader * shader)
{
	try
	{
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			
			shader->bind();
			mesh->draw();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "ERROR IN DRAW LOOP" << std::endl;
	}
}