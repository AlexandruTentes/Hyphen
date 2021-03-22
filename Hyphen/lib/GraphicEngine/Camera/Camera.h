#pragma once

#define CAMERA_H_

#include "../../CompiledHeaders.h"
#include "../../Math/Math.h"
#include "../Type/Model.h"

// A namespace for the camera
namespace Hyphen
{
	struct ViewPort
	{
		Matrix3d<float> view;
		float lat = PI, lon = 0;
		ModelTransfData* model_data = nullptr;
	};

	// The Camera class
	class Camera
	{
	// Private initializations
	private:

		//========================//
		//	Camera specific data  //
		//========================//

		ViewPort * viewport;

		float sensitivity = 30 * 0.01;											// Camera movement sensitivity
		float angle = 90.0;												// Angle of the camera FOV
		float lat_up_angle_difference = 5.0;								// The angle by which we subtract 90.0 degrees 
																			// to limit the look up in y axis
		float lat_down_angle_difference = 5.0;
	public:
			bool is_clip = false;

	// Public functions
	public:
		//==========================//
		//	Camera logic functions  //
		//==========================//

		// Function which calculates the camera rotation angle
		void camera_motion(int const& x, int const& y);

		// Function which calculates the camera look at point (centerx, centery, centerz)
		void calculate_lookpoint();

		//====================//
		//	Setter functions  //
		//====================//

		// Sets the camera initial data
		void set_camera_data(ViewPort & viewport);

		// Sets the camera rotation sensitivity
		void set_sensitivity(int sensitivity);

		// Sets camera position x
		void set_eyex(float x);

		// Sets camera position y
		void set_eyey(float y);

		// Sets camera position z
		void set_eyez(float z);

		// Sets the camera rotation angle
		void set_rotation_angle(float angle);

		// Set latitude look up angle difference
		void set_lat_up_angle_diff(float value);

		// Set latitude look down angle difference
		void set_lat_down_angle_diff(float value);

		//====================//
		//	Getter functions  //
		//====================//


		// Get the camera latitude angle
		float get_lat();

		// Get the camera longitude angle
		float get_lon();

		// Get the camera x position
		float get_eyex();

		// Get the camera y position
		float get_eyey();

		// Get the camera z position
		float get_eyez();
	};
}