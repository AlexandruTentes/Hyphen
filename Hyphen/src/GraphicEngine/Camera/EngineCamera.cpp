#include "../../../lib/GraphicEngine/Camera/EngineCamera.h"

namespace Hyphen
{
	EngineCamera::EngineCamera(Matrix4d<float>& view)
	{
		this->view = view;

		camera.set_camera_data(this->view);
	}

	void EngineCamera::attach()
	{
		camera.calculate_lookpoint();
	}

	void EngineCamera::detach()
	{

	}

	void EngineCamera::update()
	{
		handled = false;
		camera.set_lookat_point(view);

		if (center_cursor_status && right_click_no == 1)
		{
			if (is_cursor_visible)
			{
				main_window.main_window->show_cursor(false);
				is_cursor_visible = false;
			}
			main_window.main_window->set_cursor_pos(width * 0.5, height * 0.5);
		}
		else if (!is_cursor_visible)
		{
			main_window.main_window->set_cursor_pos(prev_x, prev_y);
			main_window.main_window->show_cursor(true);
			is_cursor_visible = true;
		}
	}

	void EngineCamera::event(Event& e)
	{
		DISPATCH(EngineCamera::on_mouse_move, e);
		DISPATCH(EngineCamera::on_key_press, e);
		DISPATCH(EngineCamera::on_mouse_down, e);
		DISPATCH(EngineCamera::on_mouse_up, e);
	}

	void EngineCamera::on_mouse_move(MouseMove& e)
	{
		// Check if we are allowed to set the cursor back to the middle of the window
		if (center_cursor_status && right_click_no == 1)
		{
			camera.calculate_lookpoint();
			camera.camera_motion(e.get_x(), e.get_y());
		}
		else if(is_cursor_visible)
		{
			prev_x = e.get_x();
			prev_y = e.get_y();
		}
	}

	void EngineCamera::on_key_press(KeyDown& e)
	{
		if ((char)e.get_key() == 'D')
		{
			camera.set_eyex(camera.get_eyex() - run_speed * cos(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyez(camera.get_eyez() + run_speed * sin(camera.get_lon() * DEG_TO_RAD));
		}
		if ((char)e.get_key() == 'A')
		{
			camera.set_eyex(camera.get_eyex() + run_speed * cos(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyez(camera.get_eyez() + run_speed * -sin(camera.get_lon() * DEG_TO_RAD));
		}
		if ((char)e.get_key() == 'W')
		{
			camera.set_eyez(camera.get_eyez() + run_speed * cos(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyex(camera.get_eyex() + run_speed * sin(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyey(camera.get_eyey() + run_speed * sin(camera.get_lat() * DEG_TO_RAD));
		}
		if ((char)e.get_key() == 'S')
		{
			camera.set_eyez(camera.get_eyez() - run_speed * cos(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyex(camera.get_eyex() + run_speed * -sin(camera.get_lon() * DEG_TO_RAD));
			camera.set_eyey(camera.get_eyey() - run_speed * sin(camera.get_lat() * DEG_TO_RAD));
		}
	}

	void EngineCamera::on_mouse_down(MouseButtonDown& e)
	{
		is_right_click = e.get_button() == 1;
	}

	void EngineCamera::on_mouse_up(MouseButtonUp& e)
	{
		is_right_click = is_right_click && e.get_button() == 1;
		right_click_no += is_right_click;
		right_click_no %= 2;
		is_right_click = false;
	}
}