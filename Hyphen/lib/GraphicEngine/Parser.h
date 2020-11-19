#pragma once

#define PARSER_H_

#include "../CompiledHeaders.h"
#include "Type/Model.h"
#include "../Math/UtilityFunctions.h"
#include "../Math/Math.h"
#include "../Math/Strmanip.h"

namespace Hyphen
{
	//===== Model file extension =====//
	enum ModelExtension
	{
		OBJ
	};

	//////////////////////////////////////////////////////////////
	//===== The parser handler function for .obj extension =====//
	//////////////////////////////////////////////////////////////

	void parse_obj_extension(std::string & word);

	////////////////////////////////////////////////////////////
	//===== The file format reader function of the model =====//
	////////////////////////////////////////////////////////////

	Model read_model_format(ModelExtension extension = OBJ);
}