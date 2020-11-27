#include "../../lib/GraphicEngine/Parser.h"

namespace Hyphen
{
	std::string model_extension[] =
	{
		".obj"
	};

	///////////////////////////////////////////
	//===== The parser global variables =====//
	///////////////////////////////////////////

	bool ascii_lookup[256];

	Vector3d<float> _vertex;
	Vector3d<float> _normal;
	Vector3d<float> _texture;
	Matrix4d<int> _index(0);

	Vertex vertex;
	Normal normal;
	Texture texture;
	Index index;

	short unsigned int read_vertex = 0;
	short unsigned int read_normal = 0;
	short unsigned int read_texture = 0;
	short unsigned int read_index = 0;
	short unsigned int next = 0;

	int count = 0;
	int no_def = 3;
	int no = no_def;

	bool check_alphabet = false;

	//////////////////////////////////////////////////////////
	//===== The .obj extension parser function handler =====//
	//////////////////////////////////////////////////////////

	void indexing(std::string word)
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

	void parse_obj_extension(std::string & word)
	{
		check_alphabet = word == "v" || word == "vn" || word == "vt" || word == "f" || word == "s";

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
			switch (count)
			{
			case 0: { _texture.vec[0] = stof(word); break; }
			case 1: { _texture.vec[1] = stof(word); break; }
			case 2: { _texture.vec[2] = stof(word); break; }
			default: {texture.add(_texture); count = -1; read_texture = 0; texture.has_texture = true; }
			}
			count++;
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
			} else { index.add(_index); count = 0; read_index = 0; }

		}

		if (word == "v") read_vertex = 1;
		if (word == "vt") read_texture = 1;
		if (word == "vn") read_normal = 1;
		if (word == "f") read_index = 1;
	}

	Model read_model_format(ModelExtension extension)
	{
		ascii_lookup[' '] = true;
		ascii_lookup['/'] = true;
		ascii_lookup['\0'] = true;
		ascii_lookup['\n'] = true;

		FileAndPath files = get_files_directory(model_path, model_extension[extension]);

		for (int i = 0; i < files.size; i++)
		{
			read(files.path[i] + "\\" + files.file[i], ascii_lookup, parse_obj_extension, false, true, '#');
		}

		Model model(vertex, normal, texture, index);
		return model;
	}
}