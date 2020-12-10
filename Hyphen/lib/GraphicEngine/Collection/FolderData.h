#pragma once

#include "../../CompiledHeaders.h"
#include "../../Math/DynamicDatastructure.h"

namespace Hyphen
{
	class FolderData
	{
	public:
		SINGLETONIZE(FolderData)

		virtual ~FolderData() = default;
	public:
		DynamicObject<FileAndPath> files;
	};
}