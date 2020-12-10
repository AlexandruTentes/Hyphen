#pragma once

#define PARSER_H_

#include "../../CompiledHeaders.h"
#include "../Type/Model.h"
#include "../../Math/UtilityFunctions.h"
#include "../../Math/Math.h"
#include "OBJParser.h"

namespace Hyphen
{
	void read_raw_model(FileAndPath& file);
}