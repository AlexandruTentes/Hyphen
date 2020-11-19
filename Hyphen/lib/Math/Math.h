#pragma once

#define MATH_H_

#include "../CompiledHeaders.h"

namespace Hyphen
{
	////////////////////////////////////
	//===== Vector datastructure =====//
	////////////////////////////////////

	template <class T>
	struct Vector2d
	{
		T x, y;
		Vector2d() {};
		Vector2d(T def) { init(def); };
		Vector2d(T x, T y) : x(x), y(y) {};
		void init(T def)
		{
			x = def; y = def;
		}
	};

	template <class T>
	struct Vector3d
	{
		T x, y, z;
		Vector3d() {};
		Vector3d(T def) { init(def); }
		Vector3d(T x, T y, T z) :
			x(x), y(y), z(z) {};
		void init(T def)
		{
			x = def; y = def; z = def;
		}
	};

	template <class T>
	struct Vector4d
	{
		T x, y, z, t;
		Vector4d() {};
		Vector4d(T def) { init(def); }
		Vector4d(T x, T y, T z, T t) :
			x(x), y(y), z(z), t(t) {};
		void init(T def)
		{
			x = def; y = def; z = def; t = def;
		}
	};

	template <class T>
	struct Vector5d
	{
		T x, y, z, t, k;
		Vector5d() {};
		Vector5d(T def) { init(def); }
		Vector5d(T x, T y, T z, T t, T k) : 
			x(x), y(y), z(z), t(t), k(k) {}
		void init(T def)
		{
			x = def; y = def; z = def; t = def; k = def;
		}
	};

	////////////////////////////////////
	//===== Matrix datastructure =====//
	////////////////////////////////////

	template <class T>
	struct Matrix2d
	{
		Vector2d<T> vec_x, vec_y;
		Matrix2d() {};
		Matrix2d(T def) { init(def); }
		Matrix2d(Vector2d<T> vec_x, Vector2d<T> vec_y) :
			vec_x(vec_x), vec_y(vec_y) {};
		Matrix2d(T vec_x_x, T vec_x_y,
			T vec_y_x, T vec_y_y)
		{
			vec_x.x = vec_x_x; vec_x.y = vec_x_y;
			vec_y.x = vec_y_x; vec_y.y = vec_y_y;
		};
		void init(T def)
		{
			vec_x.init(def); vec_y.init(def);
		}
	};

	template <class T>
	struct Matrix3d
	{
		Vector3d<T> vec_x, vec_y, vec_z;
		Matrix3d() {};
		Matrix3d(T def) { init(def); }
		Matrix3d(Vector3d<T> vec_x, Vector3d<T> vec_y, Vector3d<T> vec_z) :
			vec_x(vec_x), vec_y(vec_y), vec_z(vec_z) {};
		Matrix3d(T vec_x_x, T vec_x_y, T vec_x_z,
			T vec_y_x, T vec_y_y, T vec_y_z,
			T vec_z_x, T vec_z_y, T vec_z_z)
		{
			vec_x.x = vec_x_x; vec_x.y = vec_x_y; vec_x.z = vec_x_z;
			vec_y.x = vec_y_x; vec_y.y = vec_y_y; vec_y.z = vec_y_z;
			vec_z.x = vec_z_x; vec_z.y = vec_z_y; vec_z.z = vec_z_z;
		};
		void init(T def)
		{
			vec_x.init(def); vec_y.init(def); vec_z.init(def);
		}
	};

	template <class T>
	struct Matrix4d
	{
		Vector4d<T> vec_x, vec_y, vec_z, vec_t;
		Matrix4d() {};
		Matrix4d(T def) { init(def); }
		Matrix4d(Vector4d<T> vec_x, Vector4d<T> vec_y,
			Vector4d<T> vec_z, Vector4d<T> vec_t) :
			vec_x(vec_x), vec_y(vec_y), vec_z(vec_z), vec_t(vec_t) {};
		Matrix4d(T vec_x_x, T vec_x_y, T vec_x_z, T vec_x_t,
			T vec_y_x, T vec_y_y, T vec_y_z, T vec_y_t,
			T vec_z_x, T vec_z_y, T vec_z_z, T vec_z_t,
			T vec_t_x, T vec_t_y, T vec_t_z, T vec_t_t)
		{
			vec_x.x = vec_x_x; vec_x.y = vec_x_y; vec_x.z = vec_x_z; vec_x.t = vec_x_t;
			vec_y.x = vec_y_x; vec_y.y = vec_y_y; vec_y.z = vec_y_z; vec_y.t = vec_y_t;
			vec_z.x = vec_z_x; vec_z.y = vec_z_y; vec_z.z = vec_z_z; vec_z.t = vec_z_t;
			vec_t.x = vec_t_x; vec_t.y = vec_t_y; vec_t.z = vec_t_z; vec_t.t = vec_t_t;
		};
		void init(T def)
		{
			vec_x.init(def); vec_y.init(def); vec_z.init(def); vec_t.init(def);
		}
	};

	template <class T>
	struct Matrix5d
	{
		Vector5d<T> vec_x, vec_y, vec_z, vec_t, vec_k;
		Matrix5d() {};
		Matrix5d(T def) { init(def); }
		Matrix5d(Vector5d<T> vec_x, Vector5d<T> vec_y,
			Vector5d<T> vec_z, Vector5d<T> vec_t, Vector5d<T> vec_k) :
			vec_x(vec_x), vec_y(vec_y), vec_z(vec_z), vec_t(vec_t), vec_k(vec_k) {};
		Matrix5d(T vec_x_x, T vec_x_y, T vec_x_z, T vec_x_t, T vec_x_k,
			T vec_y_x, T vec_y_y, T vec_y_z, T vec_y_t, T vec_y_k,
			T vec_z_x, T vec_z_y, T vec_z_z, T vec_z_t, T vec_z_k,
			T vec_t_x, T vec_t_y, T vec_t_z, T vec_t_t, T vec_t_k,
			T vec_k_x, T vec_k_y, T vec_k_z, T vec_k_t, T vec_k_k)
		{
			vec_x.x = vec_x_x; vec_x.y = vec_x_y;
			vec_x.z = vec_x_z; vec_x.t = vec_x_t; vec_x.k = vec_x_k;
			vec_y.x = vec_y_x; vec_y.y = vec_y_y;
			vec_y.z = vec_y_z; vec_y.t = vec_y_t; vec_y.k = vec_y_k;
			vec_z.x = vec_z_x; vec_z.y = vec_z_y;
			vec_z.z = vec_z_z; vec_z.t = vec_z_t; vec_z.k = vec_z_k;
			vec_t.x = vec_t_x; vec_t.y = vec_t_y;
			vec_t.z = vec_t_z; vec_t.t = vec_t_t; vec_t.k = vec_t_k;
			vec_k.x = vec_k_x; vec_k.y = vec_k_y;
			vec_k.z = vec_k_z; vec_k.t = vec_k_t; vec_k.k = vec_k_k;
		};
		void init(T def)
		{
			vec_x.init(def); vec_y.init(def);
			vec_z.init(def); vec_t.init(def); vec_k.init(def);
		}
	};

	//////////////////////////////////////////////
	//===== Vector mathematical operations =====//
	//////////////////////////////////////////////

	//soon

	//////////////////////////////////////////////
	//===== Matrix mathematical operations =====//
	//////////////////////////////////////////////

	//soon
}