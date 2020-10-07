#pragma once

#define MATH_H_

///////////////////////////////////////
//===== Vector 3D datastructure =====//
///////////////////////////////////////

struct Vector3df
{
	float x;
	float y;
	float z;

	Vector3df() {};

	Vector3df(float x, float y, float z) :
		x(x), y(y), z(z) {};

	Vector3df(Vector3df const & vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
	};
};

struct Vector3di
{
	int x;
	int y;
	int z;

	Vector3di() {};

	Vector3di(int x, int y, int z) :
		x(x), y(y), z(z) {};

	Vector3di(Vector3di const & vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
	};
};

///////////////////////////////////////
//===== Matrix 3D datastructure =====//
///////////////////////////////////////

struct Matrix3di
{
	Vector3di first;
	Vector3di second;
	Vector3di third;

	Matrix3di() {};

	Matrix3di(Vector3di first, Vector3di second, Vector3di third) :
		first(first), second(second), third(third) {};

	Matrix3di(Matrix3di const & matrix)
	{
		first = matrix.first;
		second = matrix.second;
		third = matrix.third;
	};
};