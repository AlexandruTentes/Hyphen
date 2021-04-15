#include "../../../lib/GraphicEngine/ModelParser/Parser.h"

namespace Hyphen
{
	void read_raw_model(FileAndPath& file)
	{
		Collection<Model, std::string>& models = Collection<Model, std::string>::get_instance();

		if (models.exists(file.file))
			return;

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