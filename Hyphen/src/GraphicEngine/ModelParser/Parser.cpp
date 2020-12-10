#include "../../../lib/GraphicEngine/ModelParser/Parser.h"

namespace Hyphen
{
	void read_raw_model(Path & path)
	{
		switch (path.extension_index)
		{
		case OBJ:
		{
			OBJParser obj;
			obj.read_extension(path.path + "\\" + path.model_file, path.model_file);
		}
		}
	}
}