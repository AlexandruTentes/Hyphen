#pragma once

#define CAMERA_H_

#include "../../CompiledHeaders.h"
#include "../../Math/Math.h"

// A namespace for the camera
namespace Hyphen
{
	// The Camera class
	class Camera
	{
		// Private initializations
		private:

			//========================//
			//	Camera specific data  //
			//========================//

			float lat = 0, lon = 0;													// View angles (degrees)   
			float eyex = 0, eyey = 0, eyez = 0;											// Eye point                
			float centerx = 0, centery = 0, centerz = 0;									// Look point               
			float upx = 0, upy = 0, upz = 0;												// View up vector 			

			double sensitivity = 30;											// Camera movement sensitivity
			double angle = 90.0;												// Angle of the camera FOV
			double lat_up_angle_difference = 5.0;								// The angle by which we subtract 90.0 degrees 
																				// to limit the look up in y axis
			double lat_down_angle_difference = 5.0;

		// Public functions
		public:
			Camera() {};

			// The camera constructor which sets all the initial 'Camera specific data'
			Camera(	float const & lat, float const & lon,
					float const & eyex, float const & eyey, float const & eyez,
					float const & upx, float const & upy, float const & upz);


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
			void set_camera_data(Matrix4d<float>& view);

			// Sets camera in the scene
			void set_lookat_point(Matrix4d<float> & view);

			// Sets the camera rotation sensitivity
			void set_sensitivity(int & sensitivity);

			// Sets camera position x
			void set_eyex(float & x);

			// Sets camera position y
			void set_eyey(float& y);

			// Sets camera position z
			void set_eyez(float& z);

			// Sets the camera rotation angle
			void set_rotation_angle(float& angle);

			// Set latitude look up angle difference
			void set_lat_up_angle_diff(float& value);

			// Set latitude look down angle difference
			void set_lat_down_angle_diff(float& value);

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