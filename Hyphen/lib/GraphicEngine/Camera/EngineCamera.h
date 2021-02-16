#pragma once

#define ENGINE_CAMERA_H_

#include "../../Window/WindowInstance.h"
#include "../../CompiledHeaders.h"
#include "../../Layer/Overlay.h"
#include "../../Math/Math.h"
#include "Camera.h"

namespace Hyphen
{
	class EngineCamera : public Overlay
	{
	public:
		EngineCamera(Matrix4d<float> & view = Matrix4d<float>(	0, 1.2, -10, 0,
																0, 0, 1, 0,
																0, -1, 0, 0,
																0, 0, 0, 0));
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event& e) override;

		void on_mouse_move(MouseMove& e);
		void on_key_press(KeyDown& e);
		void on_mouse_down(MouseButtonDown& e);
		void on_mouse_up(MouseButtonUp& e);

		virtual ~EngineCamera() = default;
	public:
		Matrix4d<float> view;
	private:
		MainWindow & main_window = MainWindow::get_instance();
		Camera camera;
		bool is_right_click = false;
		unsigned short int right_click_no = 0;
		float run_speed = 0.15;
		bool is_cursor_visible = true;
		float prev_x = 0;
		float prev_y = 0;
	};
}