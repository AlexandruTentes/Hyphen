#pragma once

#define SHADER_H_

#include "Utility/IncludeAll.h"
#include "Utility/UtilityFunctions.h"
#include "Utility/UtilityDataStructures.h"
#include "Utility/Strmanip.h"

namespace uf = utility_functions;
namespace sm = string_manipulation;

enum
{
	GL_VERTEX_POSITION,
	GL_VERTEX_COLOR
};

class Shader
{
	public:
		Shader();

		void bind();
		void unbind();
		void load_shaders(std::string folder);
		void compile_shaders();
		void catch_shader_error(GLuint shader, GLuint flag, bool is_prog, std::string err);
		void set_uniform4f(std::string name, float v0, float v1, float v2, float v3);
		GLuint create_shader(std::string text, GLenum shader_type);

		void resize(int size);
		void insert(GLuint shader);

		GLuint get_program_handler();

		virtual ~Shader();
	private:
		const int default_capacity = 4;
		int capacity;

		GLuint shader_handler;

		GLuint size = 0;
		GLuint * shaders;

		GLuint get_uniform_location(std::string name);
};