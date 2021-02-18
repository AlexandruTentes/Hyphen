#include "../../../lib/GraphicEngine/Camera/Camera.h"

namespace Hyphen
{
	void Camera::set_camera_data(ViewPort & viewport)
	{
		this->viewport = &viewport;
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
				viewport->lon -= lon_calc;
			}

			// If there was movement in y, rotate camera accordingly
			if (delta_y != 0)
			{
				// Set bounds for y coordonates (latitude)
				if (viewport->lat - lat_calc > -angle + lat_down_angle_difference &&
					viewport->lat - lat_calc < angle - lat_up_angle_difference)
					viewport->lat -= lat_calc;

				// If lat gets past -90, set the lat to the minumum degrees allowed
				if (viewport->lat - lat_calc < -angle + lat_down_angle_difference)
					viewport->lat = -angle + lat_down_angle_difference;

				// If lat gets past 90, set the lat to the maximum degrees allowed
				if (viewport->lat - lat_calc > angle - lat_up_angle_difference)
					viewport->lat = angle - lat_up_angle_difference;
			}
		}
	}

	void Camera::calculate_lookpoint()
	{
		viewport->view.mat[1][0] = (GLfloat)(cos(viewport->lat * DEG_TO_RAD) * sin(viewport->lon * DEG_TO_RAD));
		viewport->view.mat[1][1] = (GLfloat)(sin(viewport->lat * DEG_TO_RAD));
		viewport->view.mat[1][2] = (GLfloat)(cos(viewport->lat * DEG_TO_RAD) * cos(viewport->lon * DEG_TO_RAD));
		glm::vec3 direction(viewport->view.mat[1][0], viewport->view.mat[1][1], viewport->view.mat[1][2]);
		glm::vec3 right(sin(viewport->lon * DEG_TO_RAD - HALF_PI), 0, cos(viewport->lon * DEG_TO_RAD - HALF_PI));
		glm::vec3 up = glm::cross(right, direction);
		viewport->view.mat[2][0] = up.x;
		viewport->view.mat[2][1] = up.y;
		viewport->view.mat[2][2] = up.z;
	}

	void Camera::set_sensitivity(int sensitivity)
	{
		this->sensitivity = sensitivity * 0.01;
	}

	void Camera::set_eyex(float x)
	{
		viewport->view.mat[0][0] = x;
	}

	void Camera::set_eyey(float y)
	{
		viewport->view.mat[0][1] = y;
	}

	void Camera::set_eyez(float z)
	{
		viewport->view.mat[0][2] = z;
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
		return viewport->lat;
	}

	float Camera::get_lon()
	{
		return viewport->lon;
	}

	float Camera::get_eyex()
	{
		return viewport->view.mat[0][0];
	}

	float Camera::get_eyey()
	{
		return viewport->view.mat[0][1];
	}

	float Camera::get_eyez()
	{
		return viewport->view.mat[0][2];
	}
}