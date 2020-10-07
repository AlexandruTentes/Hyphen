#include "Engine/GraphicEngine/lib/Utility/IncludeAll.h"

#include "Engine/GraphicEngine/lib/Display.h"
#include "Engine/GraphicEngine/lib/Shader.h"
#include "Engine/GraphicEngine/lib/Render.h"
#include "Engine/GraphicEngine/lib/Utility/Parser.h"

int main()
{
	//Render render = Render(vertex_arr, 6);
	Display display = Display(NULL, NULL);
	//Mesh mesh = Mesh();
	Shader shader = Shader();

	read_model_format();

	GLint max_vertex;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex);
	std::cout << max_vertex << std::endl;

	//render.draw(& display, & vertices, & mesh, & shader);
}