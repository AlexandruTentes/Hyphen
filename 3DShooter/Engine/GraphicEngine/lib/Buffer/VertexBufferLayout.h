#pragma once

#define VERTEXBUFFERLAYOUT_H_

#include "../Utility/IncludeAll.h"
#include "../Utility/UtilityFunctions.h"

namespace uf = utility_functions;

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
};