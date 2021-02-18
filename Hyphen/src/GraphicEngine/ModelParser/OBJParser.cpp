#include "../../../lib/GraphicEngine/ModelParser/OBJParser.h"

namespace Hyphen
{
	OBJParser::OBJParser()
	{
		memset(ascii_lookup, 0, sizeof(ascii_lookup));
		ascii_lookup[' '] = true;
		ascii_lookup['/'] = true;
		ascii_lookup['\0'] = true;
		ascii_lookup['\n'] = true;
	}

	//////////////////////////////////////////////////////////
	//===== The .obj extension parser function handler =====//
	//////////////////////////////////////////////////////////

	void OBJParser::indexing(std::string const & word)
	{
		switch (count)
		{
		case 0: { _index.mat[0][0] = stoi(word); break; }
		case 1: { _index.mat[0][1] = texture.has_texture ? stoi(word) : 0;
			if (!texture.has_texture) { count++; indexing(word); } break; }
		case 2: { _index.mat[0][2] = normal.has_normal ? stoi(word) : 0;
			if (!normal.has_normal) { count++; indexing(word); } break; }
		case 3: { _index.mat[1][0] = stoi(word); break; }
		case 4: { _index.mat[1][1] = texture.has_texture ? stoi(word) : 0;
			if (!texture.has_texture) { count++; indexing(word); } break; }
		case 5: { _index.mat[1][2] = normal.has_normal ? stoi(word) : 0;
			if (!normal.has_normal) { count++; indexing(word); } break; }
		case 6: { _index.mat[2][0] = stoi(word); break; }
		case 7: { _index.mat[2][1] = texture.has_texture ? stoi(word) : 0;
			if (!texture.has_texture) { count++; indexing(word); } break; }
		case 8: { _index.mat[2][2] = normal.has_normal ? stoi(word) : 0;
			if (!normal.has_normal) { count++; indexing(word); } break; }
		case 9: { _index.mat[3][0] = stoi(word); index.has_fourth = true; break; }
		case 10: { _index.mat[3][1] = texture.has_texture ? stoi(word) : 0;
			if (!texture.has_texture) { count++; indexing(word); } break; }
		case 11: { _index.mat[3][2] = normal.has_normal ? stoi(word) : 0; break; }
		default: { index.add(_index); count = -1; read_index = 0; }
		}
	}

	void OBJParser::parse_extension(std::string const & word)
	{
		check_alphabet = word == "v" || word == "vn" || word == "vt" || word == "f" || word == "s" || word == "g";

		if (read_vertex)
		{
			switch (count)
			{
			case 0: { _vertex.vec[0] = stof(word); break; }
			case 1: { _vertex.vec[1] = stof(word); break; }
			case 2: { _vertex.vec[2] = stof(word); break; }
			default: {vertex.add(_vertex); count = -1; read_vertex = 0; }
			}
			count++;
		}

		if (read_texture)
		{
			if (!check_alphabet)
			{
				switch (count)
				{
				case 0: { _texture.vec[0] = stof(word); texture.has_texture = true; break; }
				case 1: { _texture.vec[1] = stof(word); texture.has_texture = true; break; }
				case 2: { _texture.vec[2] = stof(word); texture.has_texture = true; break; }
				default: {texture.add(_texture); count = -1; read_texture = 0; }
				}
				count++;
			}
			else { texture.add(_texture); count = 0; read_texture = 0; }
		}

		if (read_normal)
		{
			switch (count)
			{
			case 0: { _normal.vec[0] = stof(word); break; }
			case 1: { _normal.vec[1] = stof(word); break; }
			case 2: { _normal.vec[2] = stof(word); break; }
			default: {normal.add(_normal); count = -1; read_normal = 0; normal.has_normal = true; }
			}
			count++;
		}

		if (read_index)
		{
			if (!check_alphabet)
			{
				indexing(word);
				count++;
			}
			else { index.add(_index); count = 0; read_index = 0; }

		}

		if (word == "v") read_vertex = 1;
		if (word == "vt") read_texture = 1;
		if (word == "vn") read_normal = 1;
		if (word == "f") read_index = 1;
	}

	void OBJParser::read_extension(std::string const& path, std::string& model_name, std::string const & file_root)
	{
		read(path, ascii_lookup, std::bind(&OBJParser::parse_extension, this, std::placeholders::_1), false, true, '#');
		models.add(new Model(vertex, normal, texture, index, model_name, file_root), model_name);
	}
}