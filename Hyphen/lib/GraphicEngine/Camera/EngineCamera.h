#pragma once

#define ENGINE_CAMERA_H_

#include "../../Window/WindowInstance.h"
#include "../../CompiledHeaders.h"
#include "../../Layer/Overlay.h"
#include "../../Math/Math.h"
#include "../../Math/UtilityMacros.h"
#include "Camera.h"

namespace Hyphen
{
	class EngineCamera : public Overlay
	{
	public:
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event& e) override;

		void on_mouse_move(MouseMove& e);
		void set_view(ViewPort & viewport);
		void on_key_press(KeyDown& e);
		void on_mouse_down(MouseButtonDown& e);
		void on_mouse_up(MouseButtonUp& e);

		virtual ~EngineCamera() = default;
	public:
		Camera camera;
		ViewPort * viewport = nullptr;
		bool is_cursor_visible = true;
	private:
		MainWindow & main_window = MainWindow::get_instance();
		bool is_right_click = false;
		unsigned short int right_click_no = 0;
		float run_speed = 0.15;
		float prev_x = 0;
		float prev_y = 0;
	};
}