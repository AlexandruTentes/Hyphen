#pragma once

#define CAMERA_H_

#include "Utility/IncludeAll.h"

#define DEG_TO_RAD 0.017453293												  // Constant to turn degrees to radians

// A namespace for the camera
namespace camera
{
	// The Camera class
	class Camera
	{
		// Private initializations
		private:

			//========================//
			//	Camera specific data  //
			//========================//

			GLdouble lat, lon;													// View angles (degrees)   
			GLfloat  eyex, eyey, eyez;											// Eye point                
			GLfloat  centerx, centery, centerz;									// Look point               
			GLfloat  upx, upy, upz;												// View up vector 			

			double sensitivity = 30;											// Camera movement sensitivity
			double angle = 90.0;												// Angle of the camera FOV
			double lat_up_angle_difference = 5.0;								// The angle by which we subtract 90.0 degrees 
																				// to limit the look up in y axis
			double lat_down_angle_difference = 5.0;

		// Public functions
		public:

			// The camera constructor which sets all the initial 'Camera specific data'
			Camera(GLdouble lat, GLdouble lon,
				   GLfloat eyex, GLfloat eyey, GLfloat eyez,
				   GLfloat upx, GLfloat upy, GLfloat upz);


			//==========================//
			//	Camera logic functions  //
			//==========================//

			// Function which calculates the camera rotation angle
			void camera_motion(int x, int y);

			// Function which calculates the camera look at point (centerx, centery, centerz)
			void calculate_lookpoint();

			//====================//
			//	Setter functions  //
			//====================//

			// Sets camera in the scene
			void set_lookat_point();

			// Sets the camera rotation sensitivity
			void set_sensitivity(int sensitivity);

			// Sets camera position x
			void set_eyex(GLfloat x);

			// Sets camera position y
			void set_eyey(GLfloat y);

			// Sets camera position z
			void set_eyez(GLfloat z);

			// Sets the camera rotation angle
			void set_rotation_angle(double angle);

			// Set latitude look up angle difference
			void set_lat_up_angle_diff(double value);

			// Set latitude look down angle difference
			void set_lat_down_angle_diff(double value);			

			//====================//
			//	Getter functions  //
			//====================//


			// Get the camera latitude angle
			GLdouble get_lat();

			// Get the camera longitude angle
			GLdouble get_lon();

			// Get the camera x position
			GLdouble get_eyex();

			// Get the camera y position
			GLdouble get_eyey();

			// Get the camera z position
			GLdouble get_eyez();
	};
}