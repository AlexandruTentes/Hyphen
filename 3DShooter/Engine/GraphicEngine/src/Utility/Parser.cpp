#include "../../lib/Utility/Parser.h"

std::string model_extension[] =
{
	".obj"
};

///////////////////////////////////////////
//===== The parser global variables =====//
///////////////////////////////////////////

Vector3df _vertex;
Vector3df _normal;
Vector3df _texture;
Matrix3di _index;

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

//////////////////////////////////////////////////////////
//===== The .obj extension parser function handler =====//
//////////////////////////////////////////////////////////

void parse_obj_extension(std::string & word)
{
	if (read_vertex && count >= no)
		vertex.add(_vertex);

	if (read_normal && count >= no)
		normal.add(_normal);

	if (read_texture && count >= no)
		texture.add(_texture);

	if (read_index && count >= no)
		index.add(_index);

	//Branchless if(count >= no) then
	//set all reads to false and
	//count to 0 and next to true
	//else retain all tier previous values
	read_index = !(count >= no) * read_index;
	read_normal = !(count >= no) * read_normal;
	read_texture = !(count >= no) * read_texture;
	read_vertex = !(count >= no) * read_vertex;
	count = count * !(count >= no);
	next = (count >= no) * !next;

	//Branchless if(read_vertex || read_texture ||
	//				read_normal || read_index)
	//then count++;
	count += (read_vertex || read_texture ||
		read_normal || read_index);

	if (read_vertex)
	{
		if (next) vertex.add(_vertex);
		switch (count)
		{
		case 1: _vertex.x = stof(word); break;
		case 2: _vertex.y = stof(word); break;
		case 3: _vertex.z = stof(word); break;
		}
	}
	
	if (read_normal)
	{
		if (next) normal.add(_normal);
		switch (count)
		{
		case 1: _normal.x = stof(word); break;
		case 2: _normal.y = stof(word); break;
		case 3: _normal.z = stof(word); break;
		}
	}

	if (read_texture)
	{
		if (next) texture.add(_texture);
		switch (count)
		{
		case 1: _texture.x = stof(word); break;
		case 2: _texture.y = stof(word); break;
		case 3: _texture.z = stof(word); break;
		}
	}

	if (read_index)
	{
		if (next) index.add(_index);
		switch (count)
		{
		case 1: _index.first.x = stoi(word); break;
		case 2: _index.first.y = stoi(word); break;
		case 3: _index.first.z = stoi(word); no += no; break;
		case 4: _index.second.x = stoi(word); break;
		case 5: _index.second.y = stoi(word); break;
		case 6: _index.second.z = stoi(word); no += no; break;
		case 7: _index.third.x = stoi(word); break;
		case 8: _index.third.y = stoi(word); break;
		case 9: _index.third.z = stoi(word); no = no_def; break;
		}
	}

	//Branchless if(word == "v" || word == "vn" || word == "vt" || word == "f") is true, 
	//then turn next to false, else retain the previous value
	next = !(word == "v" || word == "vn" || word == "vt" || word == "f") * next;

	//Brnachless if(word == "v") is true then set read_vertex = true, else retain
	// the previous value
	read_vertex = (word == "v") || read_vertex;
	read_normal = (word == "vn") || read_normal;
	read_texture = (word == "vt") || read_texture;
	read_index = (word == "f") || read_index;
}

void read_model_format(ModelExtension extension)
{
	FileAndPath files = uf::get_files_directory(global::model_path, model_extension[extension]);

	for (int i = 0; i < files.size; i++)
	{
		sm::read(files.path[i] + "\\" + files.file[i], parse_obj_extension, false, true, ' ', '/', '#');
	}

	Model model(vertex, normal, texture, index);
}