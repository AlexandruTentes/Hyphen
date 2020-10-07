#pragma once

#define PARSER_H_

#include "IncludeAll.h"
#include "../Model.h"
#include "UtilityFunctions.h"
#include "Math.h"

namespace uf = utility_functions;
namespace sm = string_manipulation;

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

void read_model_format(ModelExtension extension = OBJ);