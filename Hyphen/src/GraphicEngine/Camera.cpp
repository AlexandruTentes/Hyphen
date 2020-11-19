#include "../../lib/GraphicEngine/Camera.h"

namespace Hyphen
{
	Camera::Camera(GLdouble lat, GLdouble lon,
		GLfloat eyex, GLfloat eyey, GLfloat eyez,
		GLfloat upx, GLfloat upy, GLfloat upz) :
		lat(lat), lon(lon),
		eyex(eyex), eyey(eyey), eyez(eyez),
		upx(upx), upy(upy), upz(upz)
	{
		// First camera setup, calculate the look at point
		calculate_lookpoint();
	}

	void Camera::camera_motion(int x, int y)
	{
		// Move the camera only if the window is focused
		if (unfocused == false)
		{
			int screen_width = GetSystemMetrics(SM_CXSCREEN);
			int screen_height = GetSystemMetrics(SM_CYSCREEN);

			// Calculate the difference in cursor possition from a start point (middle of the window)
			double delta_x = (double)x - width / 2;
			double delta_y = (double)y - height / 2;

			// Calculate the rotation angle based on the deltas
			double lat_calc = ((double)delta_y / ((double)screen_height / 2)) * (double)angle / 2 * ((double)sensitivity / 100);
			double lon_calc = ((double)delta_x / ((double)screen_width / 2)) * (double)angle / 2 * ((double)sensitivity / 100);

			// If there was movement in x, rotate camera accordingly
			if (delta_x != 0)
			{
				lon -= lon_calc;
			}

			// If there was movement in y, rotate camera accordingly
			if (delta_y != 0)
			{
				// Set bounds for y coordonates (latitude)
				if (lat - lat_calc > -angle + lat_down_angle_difference &&
					lat - lat_calc < angle - lat_up_angle_difference)
					lat -= lat_calc;

				// If lat gets past -90, set the lat to the minumum degrees allowed
				if (lat - lat_calc < -angle + lat_down_angle_difference)
					lat = -angle + lat_down_angle_difference;

				// If lat gets past 90, set the lat to the maximum degrees allowed
				if (lat - lat_calc > angle - lat_up_angle_difference)
					lat = angle - lat_up_angle_difference;
			}

			// Check if we are allowed to set the cursor back to the middle of the window
			if (center_cursor_status == true)

				// Place cursor back to the middle of the window
				glutWarpPointer(width / 2, height / 2);
		}
	}

	void Camera::calculate_lookpoint()
	{
		centerx = eyex + (GLfloat)(cos(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD));
		centery = eyey + (GLfloat)(sin(lat * DEG_TO_RAD));
		centerz = eyez + (GLfloat)(cos(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD));
	}

	void Camera::set_sensitivity(int sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	void Camera::set_eyex(GLfloat x)
	{
		eyex = x;
	}

	void Camera::set_eyey(GLfloat y)
	{
		eyey = y;
	}

	void Camera::set_eyez(GLfloat z)
	{
		eyez = z;
	}

	void Camera::set_rotation_angle(double angle)
	{
		this->angle = angle;
	}

	void Camera::set_lat_up_angle_diff(double value)
	{
		lat_up_angle_difference = value;
	}

	void Camera::set_lat_down_angle_diff(double value)
	{
		lat_down_angle_difference = value;
	}

	GLdouble Camera::get_lat()
	{
		return lat;
	}

	GLdouble Camera::get_lon()
	{
		return lon;
	}

	GLdouble Camera::get_eyex()
	{
		return eyex;
	}

	GLdouble Camera::get_eyey()
	{
		return eyey;
	}

	GLdouble Camera::get_eyez()
	{
		return eyez;
	}

	void Camera::set_lookat_point()
	{
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	}

}