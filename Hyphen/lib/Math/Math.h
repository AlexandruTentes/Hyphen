#pragma once

#define MATH_H_

#include "../CompiledHeaders.h"

namespace Hyphen
{
#define DEFAULTING(size)	for (unsigned int i = 0; i < size; i++) \
								for (unsigned int j = 0; j < size; j++) \
									mat[i][j] = def;

	////////////////////////////////////
	//===== Vector datastructure =====//
	////////////////////////////////////

	template <class T>
	struct Vector2d
	{
		T vec[2];
		Vector2d() { init(0); };
		Vector2d(T const & def) { init(def); };
		Vector2d(T const & x, T const & y) 
		{
			set(x, y);
		};
		void set(T const& x, T const& y)
		{
			vec[0] = x; vec[1] = y;
		}
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def;
		}
	};

	template <class T>
	struct Vector3d
	{
		T vec[3];
		Vector3d() { init(0); };
		Vector3d(T const & def) { init(def); }
		Vector3d(T const & x, T const & y, T const & z)
		{
			set(x, y, z);
		};
		void set(T const& x, T const& y, T const& z)
		{
			vec[0] = x; vec[1] = y; vec[2] = z;
		};
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def; vec[2] = def;
		}
	};

	template <class T>
	struct Vector4d
	{
		T vec[4];
		Vector4d() { init(0); };
		Vector4d(T const & def) { init(def); }
		Vector4d(T const & x, T const & y, T const & z, T const & t)
		{
			set(x, y, z, t);
		}
		void set(T const& x, T const& y, T const& z, T const& t)
		{
			vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = t;
		}
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def; vec[2] = def; vec[3] = def;
		}
	};

	template <class T>
	struct Vector5d
	{
		T vec[5];
		Vector5d() { init(0); };
		Vector5d(T const & def) { init(def); }
		Vector5d(T const & x, T const & y, T const & z, T const & t, T const & k)
		{
			set(x, y, z, t, k);
		}
		void set(T const& x, T const& y, T const& z, T const& t, T const& k)
		{
			vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = t; vec[4] = k;
		}
		void init(T const & def)
		{
			vec[0] = def; vec[1] = def; vec[2] = def; vec[3] = def; vec[4] = def;
		}
	};

	////////////////////////////////////
	//===== Matrix datastructure =====//
	////////////////////////////////////

	template <class T>
	struct Matrix2d
	{
		T mat[2][2];

		Matrix2d() { init(0); };
		Matrix2d(T ** arr) { mat = arr; }
		Matrix2d(T const & def) { init(def); }
		Matrix2d(Vector2d<T> const & vec_x, Vector2d<T> const & vec_y)
		{
			set(vec_x, vec_y);
		};
		Matrix2d(T const & vec_x_x, T const & vec_x_y,
			T & vec_y_x, T & vec_y_y)
		{
			set(vec_x_x, vec_x_y, vec_y_x, vec_y_y);
		};
		void set(T const& vec_x_x, T const& vec_x_y,
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
		Vector2d<T> get_vector(unsigned short int index)
		{
			return Vector2d<T>(mat[index][0], mat[index][1]);
		}
		void init(T const & def)
		{
			DEFAULTING(2);
		}

		Matrix2d<T> & operator * (Matrix2d<T> const & other)
		{
			return multiply(* this, other);
		}
	};

	template <class T>
	struct Matrix3d
	{
		T mat[3][3];
		Vector3d<T> c_vec_x, c_vec_y, c_vec_z;
		Matrix3d() { init(0); };
		Matrix3d(T ** arr) { mat = arr; }
		Matrix3d(T const & def) { init(def); }
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
		void set(Vector3d<T> const& vec_x, Vector3d<T> const& vec_y, Vector3d<T> const& vec_z)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1]; mat[0][2] = vec_x.vec[2];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1]; mat[1][2] = vec_y.vec[2];
			mat[2][0] = vec_z.vec[0]; mat[2][1] = vec_z.vec[1]; mat[2][2] = vec_z.vec[2];
		}
		Vector3d<T> get_vector(unsigned short int index)
		{
			return Vector3d<T>(mat[index][0], mat[index][1], mat[index][2]);
		}
		void init(T const & def)
		{
			DEFAULTING(2);
		}
		Matrix3d<T> & operator *(Matrix3d<T> const & other)
		{
			return multiply(* this, other);
		}
	};

	template <class T>
	struct Matrix4d
	{
		T mat[4][4];
		Matrix4d() { init(0); };
		Matrix4d(T ** arr) { mat = arr; }
		Matrix4d(T const & def) { init(def); }
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
		void set(Vector4d<T> const& vec_x, Vector4d<T> const& vec_y,
			Vector4d<T> const& vec_z, Vector4d<T> const& vec_t)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1]; mat[0][2] = vec_x.vec[2]; mat[0][3] = vec_x.vec[3];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1]; mat[1][2] = vec_y.vec[2]; mat[1][3] = vec_y.vec[3];
			mat[2][0] = vec_z.vec[0]; mat[2][1] = vec_z.vec[1]; mat[2][2] = vec_z.vec[2]; mat[2][3] = vec_z.vec[3];
			mat[3][0] = vec_t.vec[0]; mat[3][1] = vec_t.vec[1]; mat[3][2] = vec_t.vec[2]; mat[3][3] = vec_t.vec[3];
		}
		Vector4d<T> get_vector(unsigned short int index)
		{
			return Vector4d<T>(mat[index][0], mat[index][1], mat[index][2], mat[index][3]);
		}
		void init(T const & def)
		{
			DEFAULTING(4)
		}
		Matrix4d<T> & operator * (Matrix4d<T> const & other)
		{
			return multiply(* this, other);
		}
		std::string print()
		{
			std::string res = "";

			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					res += std::to_string(mat[i][j]) + " ";
				}

				res += "\n";
			}


			return res;
		}
	};

	template <class T>
	struct Matrix5d
	{
		T mat[5][5];
		Matrix5d() { init(0); };
		Matrix5d(T ** arr) { mat = arr; }
		Matrix5d(T def) { init(def); }
		Matrix5d(Vector5d<T> vec_x, Vector5d<T> vec_y,
			Vector5d<T> vec_z, Vector5d<T> vec_t, Vector5d<T> vec_k)
		{
			mat[0][0] = vec_x.vec[0]; mat[0][1] = vec_x.vec[1]; 
			mat[0][2] = vec_x.vec[2]; mat[0][3] = vec_x.vec[3]; mat[0][4] = vec_x.vec[4];
			mat[1][0] = vec_y.vec[0]; mat[1][1] = vec_y.vec[1]; 
			mat[1][2] = vec_y.vec[2]; mat[1][3] = vec_y.vec[3]; mat[1][4] = vec_y.vec[4];
			mat[2][0] = vec_z.vec[0]; mat[2][1] = vec_z.vec[1]; 
			mat[2][2] = vec_z.vec[2]; mat[2][3] = vec_z.vec[3]; mat[2][4] = vec_z.vec[4];
			mat[3][0] = vec_t.vec[0]; mat[3][1] = vec_t.vec[1];
			mat[3][2] = vec_t.vec[2]; mat[3][3] = vec_t.vec[3]; mat[3][4] = vec_t.vec[4];
			mat[4][0] = vec_k.vec[0]; mat[4][1] = vec_k.vec[1];
			mat[4][2] = vec_k.vec[2]; mat[4][3] = vec_k.vec[3]; mat[4][4] = vec_k.vec[4];
		}
		Matrix5d(T vec_x_x, T vec_x_y, T vec_x_z, T vec_x_t, T vec_x_k,
			T vec_y_x, T vec_y_y, T vec_y_z, T vec_y_t, T vec_y_k,
			T vec_z_x, T vec_z_y, T vec_z_z, T vec_z_t, T vec_z_k,
			T vec_t_x, T vec_t_y, T vec_t_z, T vec_t_t, T vec_t_k,
			T vec_k_x, T vec_k_y, T vec_k_z, T vec_k_t, T vec_k_k)
		{
			mat[0][0] = vec_x_x; mat[0][1] = vec_x_y;
			mat[0][2] = vec_x_z; mat[0][3] = vec_x_t; mat[0][4] = vec_x_k;
			mat[1][0] = vec_y_x; mat[1][1] = vec_y_y;
			mat[1][2] = vec_y_z; mat[1][3] = vec_y_t; mat[1][4] = vec_y_k;
			mat[2][0] = vec_z_x; mat[2][1] = vec_z_y;
			mat[2][2] = vec_z_z; mat[2][3] = vec_z_t; mat[2][4] = vec_z_k;
			mat[3][0] = vec_t_x; mat[3][1] = vec_t_y;
			mat[3][2] = vec_t_z; mat[3][3] = vec_t_t; mat[3][4] = vec_t_k;
			mat[4][0] = vec_k_x; mat[4][1] = vec_k_y;
			mat[4][2] = vec_k_z; mat[4][3] = vec_k_t; mat[4][4] = vec_k_k;
		};
		void init(T def)
		{
			DEFAULTING(5)
		}
		Matrix5d<T> & operator * (Matrix5d<T> const & other)
		{
			return multiply(* this, other);
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
	static glm::mat4 get_transformation_matrix(K const & scale, K * translation, K const & x_rot, K const & y_rot, K const & z_rot)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(translation[0], translation[1], translation[2]));
		transform = glm::rotate(transform, x_rot, glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, y_rot, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, z_rot, glm::vec3(0, 0, 1));
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
	static glm::mat4 get_view_matrix(Matrix4d<K> view)
	{
		glm::vec3 poz = glm::vec3(view.mat[0][0], view.mat[0][1], view.mat[0][2]);
		glm::vec3 forward = glm::vec3(view.mat[1][0], view.mat[1][1], view.mat[1][2]);
		glm::vec3 up = glm::vec3(view.mat[2][0], view.mat[2][1], view.mat[2][2]);
		glm::mat4 view_mat(1.0f);
		view_mat = glm::lookAt(poz, poz + forward, up);
		return view_mat;
	}
}