#pragma once

#define OBJPARSER_H_

#include "../../CompiledHeaders.h"
#include "../Type/Model.h"
#include "../../Math/Strmanip.h"
#include "../Collection/ModelCollection.h"

namespace Hyphen
{
	class OBJParser
	{
	public:
		Vector3d<float> _vertex;
		Vector3d<float> _normal;
		Vector3d<float> _texture;
		Matrix4d<int> _index;

		Vertex vertex;
		Normal normal;
		Texture texture;
		Index index;
		ModelCollection& models = ModelCollection::get_instance();

		short unsigned int read_vertex = 0;
		short unsigned int read_normal = 0;
		short unsigned int read_texture = 0;
		short unsigned int read_index = 0;
		short unsigned int next = 0;

		int count = 0;
		int no_def = 3;
		int no = no_def;

		bool check_alphabet = false;
		bool ascii_lookup[256];
	public:
		OBJParser();

		//////////////////////////////////////////////////////////////
		//===== The parser handler function for .obj extension =====//
		//////////////////////////////////////////////////////////////

		void parse_extension(std::string const& word);
		void indexing(std::string const & word);
		void read_extension(std::string const& path, std::string& model_name);

		virtual ~OBJParser() = default;
	};
}