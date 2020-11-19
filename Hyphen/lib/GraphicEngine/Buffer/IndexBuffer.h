#pragma once

#define INDEXBUFFER_H_

#include "../../CompiledHeaders.h"
#include "../Type/Index.h"

namespace Hyphen
{
	class IndexBuffer : public DynamicObject<GLuint>
	{
	public:
		void load(Index * data);
		void generate_buffers();
		void bind();
		void unbind() const;

		~IndexBuffer();
	private:
		DynamicObject<Index> cache;
	};
}