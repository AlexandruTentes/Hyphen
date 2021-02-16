#pragma once

#define SHADER_H_

#include "../CompiledHeaders.h"
#include "../Math/UtilityFunctions.h"
#include "../Math/Math.h"
#include "../GlobalVariables.h"

namespace Hyphen
{
	enum
	{
		GL_VERTEX_POSITION,
		GL_VERTEX_COLOR
	};

	class ShaderProgramCache
	{
	public:
		SINGLETONIZE(ShaderProgramCache)

		virtual ~ShaderProgramCache() = default;
	public:
		std::map<const std::string, GLuint> cache;
	};

	class Shader : public DynamicObject<GLuint>
	{
	public:
		Shader();

		void bind();
		void unbind();
		void load_shaders();
		void load_shader(std::string const& shader);
		void load_shader_default();
		void link_shaders();
		void catch_shader_error(GLuint shader, GLuint flag, bool is_prog, std::string & err);
		void set_uniform4f(std::string const& name, glm::vec4 const & col);
		void set_uniform_matrix4fv(std::string const& name, glm::mat4 const & mat);
		void set_uniform1i(std::string const& name, int data);
		GLuint compile_shader(std::string & text, GLenum shader_type);

		GLuint get_program_handler();

		virtual ~Shader();
	public:
		unsigned int collection_index = 0;
		std::string name = "Default";
		ShaderProgramCache & shader_cache = ShaderProgramCache::get_instance();
	private:
		GLuint shader_handler;
		GLuint get_uniform_location(std::string name);
		bool to_link = true;
	};
}