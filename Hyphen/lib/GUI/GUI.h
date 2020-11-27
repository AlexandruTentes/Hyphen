#pragma once

#include "../CompiledHeaders.h"
#include "../Layer/Overlay.h"
#include "../Math/Math.h"

#define GUI_H_

#ifdef WINDOWS //For now the GUI works only for windows machines
	#include "../../thirdparty/imgui/imgui_impl_win32.h"
	#define HANDLER HWND 
#elif defined(LINUX)
	#include "../../thirdparty/imgui/" // to be implemented later
#endif

#ifdef OPENGL //For now the GUI works only with opengl
	#include "../../thirdparty/imgui/imgui_impl_opengl3.h"
#endif

namespace Hyphen
{
	struct temporary_globals
	{
		SINGLETONIZE(temporary_globals)

		float scale = 1.0f;
		float rotation_x = 0.0f;
		float rotation_y = 0.0f;
		float rotation_z = 0.0f;
		float translation[3] = { 0.0f, 0.0f, 0.0f };
	};

	class GUI : public Overlay
	{
	public:
		HANDLER handler = NULL;
	public:
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event & e) override;

		void on_mouse_move(MouseMove & e);
		void on_mouse_button_down(MouseButtonDown & e);
		void on_mouse_button_up(MouseButtonUp & e);
		void on_scroll(MouseScroll & e);
		void on_key_down(KeyDown & e);
		void on_key_up(KeyUp & e);
		void on_key_typed(KeyTyped & e);

		virtual ~GUI() = default;
	};
}