#pragma once

#define MATH_H_

#include "../CompiledHeaders.h"

namespace Hyphen
{
	////////////////////////////////////
	//===== Vector datastructure =====//
	////////////////////////////////////

#define VECTOR(K, T)	K() { init(0); }; \
						K(T const& def) { init(def); }; \
						T& operator[](unsigned short int index) \
						{ return vec[index]; }

	template <class T>
	struct Vector2d
	{
		T vec[2];
		VECTOR(Vector2d, T)
		Vector2d(T const & x, T const & y) 
		{
			set(x, y);
		};
		void set(T const& x, T const& y)
		{
			vec[0] = x; vec[1] = y;
		}
		void set(T & x, T & y)
		{
			vec[0] = x; vec[1] = y;
		}
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def;
		}
		Vector2d<T> mul(T const& scalar)
		{
			return Vector2d<T>(vec[0] * scalar, vec[1] * scalar);
		}
		Vector2d<T> add(T const& scalar)
		{
			return Vector2d<T>(vec[0] + scalar, vec[1] + scalar);
		}
		Vector2d<T> sub(T const& scalar)
		{
			return Vector2d<T>(vec[0] - scalar, vec[1] - scalar);
		}
	};

	template <class T>
	struct Vector3d
	{
		T vec[3];
		VECTOR(Vector3d, T)
		Vector3d(T const & x, T const & y, T const & z)
		{
			set(x, y, z);
		};
		void set(T* data)
		{
			vec[0] = data[0]; vec[1] = data[1]; vec[2] = data[2];
		}
		void set(T const& x, T const& y, T const& z)
		{
			vec[0] = x; vec[1] = y; vec[2] = z;
		};
		void set(T & x, T & y, T & z)
		{
			vec[0] = x; vec[1] = y; vec[2] = z;
		};
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def; vec[2] = def;
		}
		Vector3d<T> cross(Vector3d<T> & other)
		{
			return Vector3d<T>(
				vec[1] * other.vec[2] - vec[2] * other.vec[1],
				vec[2] * other.vec[0] - vec[0] * other.vec[2], 
				vec[0] * other.vec[1] - vec[1] * other.vec[0]);
		}
		Vector3d<T> mul(T const& scalar)
		{
			return Vector3d<T>(vec[0] * scalar, vec[1] * scalar, vec[2] * scalar);
		}
		Vector3d<T> add(T const& scalar)
		{
			return Vector3d<T>(vec[0] + scalar, vec[1] + scalar, vec[2] + scalar);
		}
		Vector3d<T> sub(T const& scalar)
		{
			return Vector3d<T>(vec[0] - scalar, vec[1] - scalar, vec[2] - scalar);
		}
	};

	template <class T>
	struct Vector4d
	{
		T vec[4];
		VECTOR(Vector4d, T)
		Vector4d(T const & x, T const & y, T const & z, T const & t)
		{
			set(x, y, z, t);
		}
		void set(T const& x, T const& y, T const& z, T const& t)
		{
			vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = t;
		}
		void set(T & x, T & y, T & z, T & t)
		{
			vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = t;
		}
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def; vec[2] = def; vec[3] = def;
		}
		Vector4d<T> mul(T const& scalar)
		{
			return Vector4d<T>(vec[0] * scalar, vec[1] * scalar, vec[2] * scalar, vec[3] * scalar);
		}
		Vector4d<T> add(T const& scalar)
		{
			return Vector4d<T>(vec[0] + scalar, vec[1] + scalar, vec[2] + scalar, vec[3] + scalar);
		}
		Vector4d<T> sub(T const& scalar)
		{
			return Vector4d<T>(vec[0] - scalar, vec[1] - scalar, vec[2] - scalar, vec[3] - scalar);
		}
	};

	////////////////////////////////////
	//===== Matrix datastructure =====//
	////////////////////////////////////

#define MATRIX(L, K, T)	L() { init(0); }; \
						L(T const& def) { init(def); } \
						K<T>& operator[](unsigned short int index) \
						{ return mat[index]; }

	template <class T>
	struct Matrix2d
	{
		Vector2d<Vector2d<T>> mat;
		MATRIX(Matrix2d, Vector2d, T)
		Matrix2d(Vector2d<T> const & vec_x, Vector2d<T> const & vec_y)
		{
			set(vec_x, vec_y);
		};
		Matrix2d(T const & vec_x_x, T const & vec_x_y,
			T const& vec_y_x, T const& vec_y_y)
		{
			set(vec_x_x, vec_x_y, vec_y_x, vec_y_y);
		};
		void set(T const& vec_x_x, T const& vec_x_y,
			T& vec_y_x, T& vec_y_y)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y;
		};
		void set(T& vec_x_x, T& vec_x_y,
			T& vec_y_x, T& vec_y_y)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y;
		};
		void set(Vector2d<T> const& vec_x, Vector2d<T> const& vec_y)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1];
		};
		void init(T const & def)
		{
			mat[0].init(def); mat[1].init(def);
		}
	};

	template <class T>
	struct Matrix3d
	{
		Vector3d<Vector3d<T>> mat;
		MATRIX(Matrix3d, Vector3d, T)
		Matrix3d(Vector3d<T> const & vec_x, Vector3d<T> const & vec_y, Vector3d<T> const & vec_z)
		{
			set(vec_x, vec_y, vec_z);
		}
		Matrix3d(T const & vec_x_x, T const & vec_x_y, T const & vec_x_z,
			T const & vec_y_x, T const & vec_y_y, T const & vec_y_z,
			T const & vec_z_x, T const & vec_z_y, T const & vec_z_z)
		{
			set(vec_x_x, vec_x_y, vec_x_z,
				vec_y_x, vec_y_y, vec_y_z,
				vec_z_x, vec_z_y, vec_z_z);
		};
		void set(T const& vec_x_x, T const& vec_x_y, T const& vec_x_z,
			T const& vec_y_x, T const& vec_y_y, T const& vec_y_z,
			T const& vec_z_x, T const& vec_z_y, T const& vec_z_z)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y; mat[0][2] = vec_x_z;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y; mat[1][2] = vec_y_z;
			mat[2][0] = vec_z_x; mat[2][1] = vec_z_y; mat[2][2] = vec_z_z;
		};
		void set(T & vec_x_x, T & vec_x_y, T & vec_x_z,
			T & vec_y_x, T & vec_y_y, T & vec_y_z,
			T & vec_z_x, T & vec_z_y, T & vec_z_z)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y; mat[0][2] = vec_x_z;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y; mat[1][2] = vec_y_z;
			mat[2][0] = vec_z_x; mat[2][1] = vec_z_y; mat[2][2] = vec_z_z;
		};
		void set(Vector3d<T> const& vec_x, Vector3d<T> const& vec_y, Vector3d<T> const& vec_z)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1]; mat[0][2] = vec_x.vec[2];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1]; mat[1][2] = vec_y.vec[2];
			mat[2][0] = vec_z.vec[0]; mat[2][1] = vec_z.vec[1]; mat[2][2] = vec_z.vec[2];
		}
		void init(T const & def)
		{
			mat[0].init(def); mat[1].init(def); mat[2].init(def);
		}
	};

	template <class T>
	struct Matrix4d
	{
		Vector4d<Vector4d<T>> mat;
		MATRIX(Matrix4d, Vector4d, T)
		Matrix4d(Vector4d<T> const & vec_x, Vector4d<T> const & vec_y,
			Vector4d<T> const & vec_z, Vector4d<T> const & vec_t)
		{
			set(vec_x, vec_y, vec_z, vec_t);
		}
		Matrix4d(T const & vec_x_x, T const & vec_x_y, T const & vec_x_z, T const & vec_x_t,
			T const & vec_y_x, T const & vec_y_y, T const & vec_y_z, T const & vec_y_t,
			T const & vec_z_x, T const & vec_z_y, T const & vec_z_z, T const & vec_z_t,
			T const & vec_t_x, T const & vec_t_y, T const & vec_t_z, T const & vec_t_t)
		{
			set(vec_x_x, vec_x_y, vec_x_z, vec_x_t,
				vec_y_x, vec_y_y, vec_y_z, vec_y_t,
				vec_z_x, vec_z_y, vec_z_z, vec_z_t,
				vec_t_x, vec_t_y, vec_t_z, vec_t_t);
		};
		void set(T const& vec_x_x, T const& vec_x_y, T const& vec_x_z, T const& vec_x_t,
			T const& vec_y_x, T const& vec_y_y, T const& vec_y_z, T const& vec_y_t,
			T const& vec_z_x, T const& vec_z_y, T const& vec_z_z, T const& vec_z_t,
			T const& vec_t_x, T const& vec_t_y, T const& vec_t_z, T const& vec_t_t)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y; mat[0][2] = vec_x_z; mat[0][3] = vec_x_t;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y; mat[1][2] = vec_y_z; mat[1][3] = vec_y_t;
			mat[2][0] = vec_z_x; mat[2][1] = vec_z_y; mat[2][2] = vec_z_z; mat[2][3] = vec_z_t;
			mat[3][0] = vec_t_x; mat[3][1] = vec_t_y; mat[3][2] = vec_t_z; mat[3][3] = vec_t_t;
		};
		void set(T & vec_x_x, T & vec_x_y, T & vec_x_z, T & vec_x_t,
			T & vec_y_x, T & vec_y_y, T & vec_y_z, T & vec_y_t,
			T & vec_z_x, T & vec_z_y, T & vec_z_z, T & vec_z_t,
			T & vec_t_x, T & vec_t_y, T & vec_t_z, T & vec_t_t)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y; mat[0][2] = vec_x_z; mat[0][3] = vec_x_t;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y; mat[1][2] = vec_y_z; mat[1][3] = vec_y_t;
			mat[2][0] = vec_z_x; mat[2][1] = vec_z_y; mat[2][2] = vec_z_z; mat[2][3] = vec_z_t;
			mat[3][0] = vec_t_x; mat[3][1] = vec_t_y; mat[3][2] = vec_t_z; mat[3][3] = vec_t_t;
		};
		void set(Vector4d<T> const& vec_x, Vector4d<T> const& vec_y,
			Vector4d<T> const& vec_z, Vector4d<T> const& vec_t)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1]; mat[0][2] = vec_x.vec[2]; mat[0][3] = vec_x.vec[3];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1]; mat[1][2] = vec_y.vec[2]; mat[1][3] = vec_y.vec[3];
			mat[2][0] = vec_z.vec[0]; mat[2][1] = vec_z.vec[1]; mat[2][2] = vec_z.vec[2]; mat[2][3] = vec_z.vec[3];
			mat[3][0] = vec_t.vec[0]; mat[3][1] = vec_t.vec[1]; mat[3][2] = vec_t.vec[2]; mat[3][3] = vec_t.vec[3];
		}
		void init(T const & def)
		{
			mat[0].init(def); mat[1].init(def); mat[2].init(def); mat[3].init(def);
		}
	};

	//////////////////////////////////////////////
	//===== Vector mathematical operations =====//
	//////////////////////////////////////////////

	//soon

	//////////////////////////////////////////////
	//===== Matrix mathematical operations =====//
	//////////////////////////////////////////////
	
	//===== Template function which multiplies two matrices =====//
	template<class T>
	T multiply(T const & left, T const & right)
	{
		T aux;
		unsigned int size = sizeof(aux.mat[0]) / sizeof(aux.mat[0][0]);
	
		for (unsigned int i = 0; i < size; i++)
			for (unsigned int j = 0; j < size; j++)
			{
				aux.mat[i][j] = 0;
				for (unsigned int k = 0; k < size; k++)
					aux.mat[i][j] += (left.mat[i][k] * right.mat[k][j]);
			}
		return aux;
	}

	//===== Templated function which calculates the scale/position/rotation matrix
	template<class K>
	static glm::mat4 get_transformation_matrix(K const & scale, Vector3d<K> & translation, Vector3d<K>& rot)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(translation[0], translation[1], translation[2]));
		transform = glm::rotate(transform, rot[0] * DEG_TO_RAD, glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, rot[1] * DEG_TO_RAD, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, rot[2] * DEG_TO_RAD, glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(scale, scale, scale));

		//glm::mat4 rot = rot_z * rot_y * rot_x;
		//return poz * rot * mscale;
		return transform;
	}

	//===== Templated function which calculates the fov/aspect/znear/zfar matrix =====//
	template <class K>
	static glm::mat4 get_perspective_matrix(K fov, K aspect_ratio, K z_near, K z_far)
	{
		fov = (float)DEG_TO_RAD * fov;
		return glm::perspective(fov, aspect_ratio, z_near, z_far);
	}

	//===== Templated function which calculates =====//
	template <class K>
	static glm::mat4 get_view_matrix(Matrix3d<K> view)
	{
		glm::vec3 poz = glm::vec3(view.mat[0][0], view.mat[0][1], view.mat[0][2]);
		glm::vec3 forward = glm::vec3(view.mat[1][0], view.mat[1][1], view.mat[1][2]);
		glm::vec3 up = glm::vec3(view.mat[2][0], view.mat[2][1], view.mat[2][2]);
		glm::mat4 view_mat(1.0f);
		view_mat = glm::lookAt(poz, poz + forward, up);
		return view_mat;
	}
}