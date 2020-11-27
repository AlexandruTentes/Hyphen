#include "../../lib/GraphicEngine/Shader.h"

namespace Hyphen
{
	Shader::Shader()
	{
		shader_handler = glCreateProgram();

		capacity = default_capacity;
		shaders = new GLuint[capacity];
	}

	GLuint Shader::create_shader(std::string text, GLenum shader_type)
	{
		if (text == "")
			return 0;

		GLuint shader = glCreateShader(shader_type);

		if (shader == 0)
			std::cerr << "ERROR COULD NOT CREATE A SHADER" << std::endl;

		const GLchar * shader_text_string[1];
		GLint shader_text_length[1];

		shader_text_string[0] = text.c_str();
		shader_text_length[0] = (int)text.length();

		glShaderSource(shader, 1, shader_text_string, shader_text_length);
		glCompileShader(shader);

		catch_shader_error(shader, GL_COMPILE_STATUS, false, std::string("ERROR AT SHADER COMPILATION"));

		return shader;
	}

	void Shader::catch_shader_error(GLuint shader, GLuint flag, bool is_prog, std::string err)
	{
		GLint success = 0;
		GLchar * error;
		int length = 0;

		if (is_prog)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE)
		{
			if (is_prog)
			{
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
				error = (char *)alloca(length * sizeof(char));
				glGetProgramInfoLog(shader, length, &length, error);
			}
			else
			{
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				error = (char *)alloca(length * sizeof(char));
				glGetShaderInfoLog(shader, length, &length, error);
			}

			glDeleteShader(shader);

			std::cerr << err << "---" << error << std::endl;
		}
	}

	void Shader::set_uniform4f(std::string name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
	}

	void Shader::set_uniform_matrix4fv(std::string name, glm::mat4 const & mat)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::compile_shaders()
	{
		for (unsigned int i = 0; i < size; i++)
			glAttachShader(shader_handler, shaders[i]);

		glBindAttribLocation(shader_handler, GL_VERTEX_POSITION, "position");
		glBindAttribLocation(shader_handler, GL_VERTEX_COLOR, "color");

		glLinkProgram(shader_handler);
		catch_shader_error(shader_handler, GL_LINK_STATUS, true, std::string("ERROR WHEN ATTEMPTING TO LINK SHADERS"));

		glValidateProgram(shader_handler);
		catch_shader_error(shader_handler, GL_VALIDATE_STATUS, true, std::string("ERROR WHEN ATTEMPTING TO VALIDATE SHADERS"));
	}

	void Shader::resize(int size)
	{
		if (size <= capacity)
			return;

		GLuint * aux = new GLuint[size];
		memcpy(aux, shaders, size * sizeof(GLuint));

		delete[] shaders;
		shaders = aux;

		capacity = size;
	}

	void Shader::insert(GLuint shader)
	{
		if (shader == 0)
			return;

		shaders[size] = shader;
		size++;
	}

	void Shader::load_shaders(std::string folder)
	{
		std::string extension[] = { ".vs", ".fs" };
		FileAndPath files = get_files_directory(folder,
			extension, sizeof(extension) / sizeof(extension[0]));

		resize(files.size);

		if (files.size == 0)
		{
			std::cerr << "NO FILES COULD BE LOADED" << std::endl;
			return;
		}

		for (int i = 0; i < files.size; i++)
			insert(create_shader(read(
				files.path[i] + "\\" + files.file[i]), grep(files.file[i], ".vs") ?
				GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));
	}

	void Shader::bind()
	{
		glUseProgram(shader_handler);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	GLuint Shader::get_uniform_location(std::string name)
	{
		unsigned int location = glGetUniformLocation(shader_handler, name.c_str());

		if (location == -1)
			std::cout << "WARNING: Uniform -> " << name << " doesn't exist!" << std::endl;

		return location;
	}

	GLuint Shader::get_program_handler()
	{
		return shader_handler;
	}

	Shader::~Shader()
	{
		for (unsigned int i = 0; i < size; i++)
		{
			glDetachShader(shader_handler, shaders[i]);
			glDeleteShader(shaders[i]);
		}

		glDeleteProgram(shader_handler);

		delete[] shaders;
	}
}