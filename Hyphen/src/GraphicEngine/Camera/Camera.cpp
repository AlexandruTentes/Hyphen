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
		lat = PI;
		lon = 0;
		eyex = view.mat[0][0];
		eyey = view.mat[0][1];
		eyez = view.mat[0][2];
		centerx = view.mat[1][0];
		centery = view.mat[1][1];
		centerz = view.mat[1][2];
		upx = view.mat[2][0];
		upy = view.mat[2][1];
		upz = view.mat[2][2];
	}

	void Camera::camera_motion(int const& x, int const& y)
	{
		// Move the camera only if the window is focused
		if (true)//unfocused == false)
		{
			// Calculate the difference in cursor possition from a start point (middle of the window)
			float delta_x = (float)x - half_width;
			float delta_y = (float)y - half_height;

			// Calculate the rotation angle based on the deltas
			float lat_calc = ((float)delta_y / half_height) * (float)angle * 0.5 * sensitivity;
			float lon_calc = ((float)delta_x / half_width) * (float)angle * 0.5 * sensitivity;

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
		}
	}

	void Camera::calculate_lookpoint()
	{
		centerx = (GLfloat)(cos(lat * DEG_TO_RAD) * sin(lon * DEG_TO_RAD));
		centery = (GLfloat)(sin(lat * DEG_TO_RAD));
		centerz = (GLfloat)(cos(lat * DEG_TO_RAD) * cos(lon * DEG_TO_RAD));
		glm::vec3 direction(centerx, centery, centerz);
		glm::vec3 right(sin(lon * DEG_TO_RAD - HALF_PI), 0, cos(lon * DEG_TO_RAD - HALF_PI));
		glm::vec3 up = glm::cross(right, direction);
		upx = up.x;
		upy = up.y;
		upz = up.z;
	}

	void Camera::set_sensitivity(int sensitivity)
	{
		this->sensitivity = sensitivity * 0.01;
	}

	void Camera::set_eyex(float x)
	{
		eyex = x;
	}

	void Camera::set_eyey(float y)
	{
		eyey = y;
	}

	void Camera::set_eyez(float z)
	{
		eyez = z;
	}

	void Camera::set_rotation_angle(float angle)
	{
		this->angle = angle;
	}

	void Camera::set_lat_up_angle_diff(float value)
	{
		lat_up_angle_difference = value;
	}

	void Camera::set_lat_down_angle_diff(float value)
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
		unsigned raw_1 = 0;
		unsigned raw_2 = 1;
		unsigned raw_3 = 2;

		view.mat[raw_1][0] = eyex;
		view.mat[raw_1][1] = eyey;
		view.mat[raw_1][2] = eyez;

		view.mat[raw_2][0] = centerx;
		view.mat[raw_2][1] = centery;
		view.mat[raw_2][2] = centerz;

		view.mat[raw_3][0] = upx;
		view.mat[raw_3][1] = upy;
		view.mat[raw_3][2] = upz;
	}

}