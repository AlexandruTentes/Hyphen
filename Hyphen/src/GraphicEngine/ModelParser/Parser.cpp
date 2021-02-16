#include "../../../lib/GraphicEngine/ModelParser/Parser.h"

namespace Hyphen
{
	void read_raw_model(FileAndPath& file)
	{
		switch (file.extension_index)
		{
		case OBJ:
		{
			OBJParser obj;
			obj.read_extension(file.path + "\\" + file.file, file.file, file.file_root);
		}
		}
	}
}