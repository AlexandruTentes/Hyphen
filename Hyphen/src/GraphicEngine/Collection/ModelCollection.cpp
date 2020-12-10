#include "../../../lib/GraphicEngine/Collection/ModelCollection.h"

namespace Hyphen
{
	void ModelCollection::add(Model& model)
	{
		if (model.collection_index != 0)
			return;

		model.collection_index = models.get_size() + 1;
		models.push(model);
		names.push(model.model_name);
	};

	void ModelCollection::remove(Model& model)
	{
		if (model.collection_index == 0)
			return;

		models.remove(model.collection_index - 1);
		names.remove(model.collection_index - 1);
		model.collection_index = 0;
	};

	bool ModelCollection::exists(Model& model)
	{
		return model.collection_index != 0;
	}

	bool ModelCollection::exists(std::string& name)
	{
		return names.has(name);
	}

	Model& ModelCollection::get(unsigned int i) { return models.get_one(i); };
}