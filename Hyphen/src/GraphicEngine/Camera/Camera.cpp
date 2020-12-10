#include "../../../lib/GraphicEngine/Camera/Camera.h"

namespace Hyphen
{
	Camera::Camera(float const& lat, float const& lon,
		float const& eyex, float const& eyey, float const& eyez,
		float const& upx, float const& upy, float const& upz) :
		lat(lat), lon(lon),
		eyex(eyex), eyey(eyey), eyez(eyez),
		upx(upx), upy(upy), upz(upz)
	{
		// First camera setup, calculate the look at point
		calculate_lookpoint();
	}

	void Camera::set_camera_data(Matrix4d<float>& view)
	{
		lat = view.mat[0][0];
		lon = view.mat[0][1];
		eyex = view.mat[1][0];
		eyey = view.mat[1][1];
		eyez = view.mat[1][2];
		upx = view.mat[2][0];
		upy = view.mat[2][1];
		upz = view.mat[2][2];
	}

	void Camera::camera_motion(int const& x, int const& y)
	{
		// Move the camera only if the window is focused
		if (unfocused == false)
		{
			// Calculate the difference in cursor possition from a start point (middle of the window)
			double delta_x = (double)x - width / 2;
			double delta_y = (double)y - height / 2;

			// Calculate the rotation angle based on the deltas
			double lat_calc = ((double)delta_y / ((double)height / 2)) * (double)angle / 2 * ((double)sensitivity / 100);
			double lon_calc = ((double)delta_x / ((double)width / 2)) * (double)angle / 2 * ((double)sensitivity / 100);

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
			if (center_cursor_status == true);

				// Place cursor back to the middle of the window
				//glutWarpPointer(width / 2, height / 2);
		}
	}

	void Camera::calculate_lookpoint()
	{
		centerx = eyex + (GLfloat)(cos(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD));
		centery = eyey + (GLfloat)(sin(lat * DEG_TO_RAD));
		centerz = eyez + (GLfloat)(cos(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD));
	}

	void Camera::set_sensitivity(int & sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	void Camera::set_eyex(float& x)
	{
		eyex = x;
	}

	void Camera::set_eyey(float& y)
	{
		eyey = y;
	}

	void Camera::set_eyez(float& z)
	{
		eyez = z;
	}

	void Camera::set_rotation_angle(float& angle)
	{
		this->angle = angle;
	}

	void Camera::set_lat_up_angle_diff(float& value)
	{
		lat_up_angle_difference = value;
	}

	void Camera::set_lat_down_angle_diff(float& value)
	{
		lat_down_angle_difference = value;
	}

	float Camera::get_lat()
	{
		return lat;
	}

	float Camera::get_lon()
	{
		return lon;
	}

	float Camera::get_eyex()
	{
		return eyex;
	}

	float Camera::get_eyey()
	{
		return eyey;
	}

	float Camera::get_eyez()
	{
		return eyez;
	}

	void Camera::set_lookat_point(Matrix4d<float> & view)
	{
		//gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		view.mat[0][0] = eyex;
		view.mat[0][1] = eyey;
		view.mat[0][2] = eyez;

		view.mat[1][0] = centerx;
		view.mat[1][1] = centery;
		view.mat[1][2] = centerz;

		view.mat[2][0] = upx;
		view.mat[2][1] = upy;
		view.mat[2][2] = upz;
	}

}