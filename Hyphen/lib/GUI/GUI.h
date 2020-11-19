#pragma once

#include "../CompiledHeaders.h"
#include "../Layer/Overlay.h"

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