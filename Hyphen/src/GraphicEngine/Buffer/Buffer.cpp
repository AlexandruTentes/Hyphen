#include "../../../lib/GraphicEngine/Buffer/Buffer.h"

namespace Hyphen
{
	void Buffer::new_buffer()
	{
		glGenBuffers(capacity, array_buffer);
		size = 0;
	}

	void Buffer::unload()
	{
		if (size)
		{
			glDeleteBuffers(capacity, array_buffer);
			size = 0;
		}
	}

	Buffer::~Buffer()
	{
		unload();
	}
}