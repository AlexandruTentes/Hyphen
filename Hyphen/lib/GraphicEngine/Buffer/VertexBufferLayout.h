#pragma once

#define VERTEXBUFFERLAYOUT_H_

#include "../../CompiledHeaders.h"
#include "../../Math/UtilityFunctions.h"

namespace Hyphen
{
	struct _VertexBufferLayout
	{
		GLuint type;
		GLuint size;
		bool normalized;
	};

	class VertexBufferLayout : public DynamicObject<_VertexBufferLayout>
	{
	public:
		void load(GLuint type, GLuint size);
		GLuint get_stride() const;
	private:
		GLuint stride = 0;
		bool once = false;
	};
}