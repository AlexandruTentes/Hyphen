#pragma once

#define RENDER_H_

#include "../CompiledHeaders.h"
#include "Type/Vertex.h"
#include "Shader.h"
#include "Type/Model.h"
#include "Buffer/Buffer.h"
#include "Buffer/VertexBufferLayout.h"
#include "Buffer/VertexArray.h"
#include "Scene.h"

namespace Hyphen
{
	class Renderer
	{
	public:
		void draw_model(Model* m);
		void draw_scene();
		void render_model(Model * m);
		void clear(unsigned int flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		virtual ~Renderer() = default;
	public:
		Matrix3d<float> view;
		std::string bound_scene;
		unsigned int scenes_no = 0;
		Collection<Scene, std::string>& scenes = Collection<Scene, std::string>::get_instance();
	private:
		VertexBufferLayout layout;
		VertexArray va;
		Buffer buffer;
	};
}