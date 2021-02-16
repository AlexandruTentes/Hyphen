#pragma once

#define FRAMEBUFFER_H_

#include "../../CompiledHeaders.h"
#include "../../GlobalVariables.h"

namespace Hyphen
{
	class FrameBuffer
	{
	public:
		void generate_buffers();
		void bind();
		void unbind() const;
		unsigned int get_id();
		unsigned int get_tex();
		void remove();

		virtual ~FrameBuffer() = default;
	private:
		unsigned int fbo = 0;
		unsigned int tex = 0;
		unsigned int rbo = 0;
	};
}