#include "../lib/Camera.h"

camera::Camera::Camera(GLdouble lat, GLdouble lon,
	GLfloat eyex, GLfloat eyey, GLfloat eyez,
	GLfloat upx, GLfloat upy, GLfloat upz) :
	lat(lat), lon(lon),
	eyex(eyex), eyey(eyey), eyez(eyez),
	upx(upx), upy(upy), upz(upz)
{
	// First camera setup, calculate the look at point
	calculate_lookpoint();
}

void camera::Camera::camera_motion(int x, int y)
{
	// Move the camera only if the window is focused
	if (global::unfocused == false)
	{
		int screen_width = GetSystemMetrics(SM_CXSCREEN);
		int screen_height = GetSystemMetrics(SM_CYSCREEN);

		// Calculate the difference in cursor possition from a start point (middle of the window)
		double delta_x = (double)x - global::width / 2;
		double delta_y = (double)y - global::height / 2;

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
		if(global::center_cursor_status == true)

			// Place cursor back to the middle of the window
			glutWarpPointer(global::width / 2, global::height / 2);
	}
}

void camera::Camera::calculate_lookpoint()
{
	centerx = eyex + (GLfloat) (cos(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD));
	centery = eyey + (GLfloat) (sin(lat * DEG_TO_RAD));
	centerz = eyez + (GLfloat) (cos(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD));
}

void camera::Camera::set_sensitivity(int sensitivity)
{
	this->sensitivity = sensitivity;
}

void camera::Camera::set_eyex(GLfloat x)
{
	eyex = x;
}

void camera::Camera::set_eyey(GLfloat y)
{
	eyey = y;
}

void camera::Camera::set_eyez(GLfloat z)
{
	eyez = z;
}

void camera::Camera::set_rotation_angle(double angle)
{
	this->angle = angle;
}

void camera::Camera::set_lat_up_angle_diff(double value)
{
	lat_up_angle_difference = value;
}

void camera::Camera::set_lat_down_angle_diff(double value)
{
	lat_down_angle_difference = value;
}

GLdouble camera::Camera::get_lat()
{
	return lat;
}

GLdouble camera::Camera::get_lon()
{
	return lon;
}

GLdouble camera::Camera::get_eyex()
{
	return eyex;
}

GLdouble camera::Camera::get_eyey()
{
	return eyey;
}

GLdouble camera::Camera::get_eyez()
{
	return eyez;
}

void camera::Camera::set_lookat_point()
{
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}
