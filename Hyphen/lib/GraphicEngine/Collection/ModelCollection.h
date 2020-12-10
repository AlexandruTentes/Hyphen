#pragma once

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"
#include "../Type/Model.h"

namespace Hyphen
{
	class ModelCollection
	{
	public:
		SINGLETONIZE(ModelCollection)

		void add(Model& model);
		void remove(Model& model);
		bool exists(Model& model);
		bool exists(std::string& name);
		Model& get(unsigned int i);

		virtual ~ModelCollection() = default;
	private:
		DynamicObject<Model> models;
		DynamicObject<std::string> names;
	};
}