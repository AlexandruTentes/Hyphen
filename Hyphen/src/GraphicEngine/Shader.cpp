#include "../../lib/GraphicEngine/Shader.h"

namespace Hyphen
{
	Shader::Shader()
	{}

	GLuint Shader::compile_shader(std::string & text, GLenum shader_type)
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

	void Shader::catch_shader_error(GLuint shader, GLuint flag, bool is_prog, std::string & err)
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

	void Shader::set_uniform4f(std::string const& name, Vector4d<float>& col)
	{
		glUniform4f(get_uniform_location(name), col[0], col[1], col[2], col[3]);
	}

	void Shader::set_uniform3f(std::string const& name, Vector3d<float>& col)
	{
		glUniform3f(get_uniform_location(name), col[0], col[1], col[2]);
	}

	void Shader::set_uniform1f(std::string const& name, float const& col)
	{
		glUniform1f(get_uniform_location(name), col);
	}

	void Shader::set_uniform_matrix4fv(std::string const& name, glm::mat4 const & mat)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::set_uniform1i(std::string const& name, int data)
	{
		glUniform1i(get_uniform_location(name), data);
	}

	void Shader::link_shaders()
	{
		if (!to_link)
			return;

		for (unsigned int i = 0; i < size; i++)
			glAttachShader(shader_handler, data[i]);

		glBindAttribLocation(shader_handler, GL_VERTEX_POSITION, "position");
		glBindAttribLocation(shader_handler, GL_VERTEX_COLOR, "color");

		glLinkProgram(shader_handler);
		catch_shader_error(shader_handler, GL_LINK_STATUS, true, std::string("ERROR WHEN ATTEMPTING TO LINK SHADERS"));

		glValidateProgram(shader_handler);
		catch_shader_error(shader_handler, GL_VALIDATE_STATUS, true, std::string("ERROR WHEN ATTEMPTING TO VALIDATE SHADERS"));

		for (unsigned int i = 0; i < size; i++)
		{
			glDetachShader(shader_handler, data[i]);
			glDeleteShader(data[i]);
		}

		clear();
	}

	void Shader::load_shader(std::string const& shader)
	{
		if (shader_cache.cache[shader])
		{
			shader_handler = shader_cache.cache[shader];
			to_link = false;
			return;
		}

		shader_handler = glCreateProgram();
		to_link = true;

		std::cout << "Compile shader " << shader << "\n";

		Collection<FileAndPath, std::string> files;
		get_files_directory(files, std::string(shader_path) + "\\" + shader, shader_extension,
			sizeof(shader_extension) / sizeof(shader_extension[0]), shader.c_str());

		for (int i = 0; i < files.get_size(); i++)
			push(compile_shader(read(
				files.get(i)->path + "\\" + files.get(i)->file),
				grep(files.get(i)->file, ".vs") ?
				GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));

		shader_cache.cache[shader] = shader_handler;
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
			glDetachShader(shader_handler, data[i]);
			glDeleteShader(data[i]);
		}

		glDeleteProgram(shader_handler);
	}
}