#pragma once

#define LIGHT_H_

#include "../../CompiledHeaders.h"
#include "../../Math/Math.h"

namespace Hyphen
{
	class Light
	{
	public:
		Light();
		virtual ~Light() = default;
	private:
		Vector3d<float> init_position;
		Vector3d<float> init_direction;
		Vector3d<float> init_color;
		Vector3d<float> init_ambient;
		Vector3d<float> init_diffuse;
		Vector3d<float> init_specular;
		float init_ambient_strength = 0.1f;
	public:
		Vector3d<float> * ambient = &init_ambient;
		Vector3d<float> * diffuse = &init_diffuse;
		Vector3d<float> * specular = &init_specular;
		Vector3d<float> * position = &init_position;
		Vector3d<float> * direction = &init_direction;
		Vector3d<float> * color = &init_color;
		float* ambient_strength = &init_ambient_strength;
	};
}