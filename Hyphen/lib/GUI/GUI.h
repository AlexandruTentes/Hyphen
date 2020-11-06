#pragma once

#include "../CompiledHeaders.h"

#ifdef WINDOWS

#define GUI_H_

#include "../Layer/Layer.h"
#include "../../thirdparty/imgui/imgui_impl_opengl3.h"
#include "../../thirdparty/imgui/imgui_impl_win32.h"

//For now the GUI works only for windows machines only

namespace Hyphen
{
	class GUI : public Layer
	{
	public:
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event & e) override;

		void set_handler(HWND & hwnd) { handler = hwnd; }

		virtual ~GUI() = default;
	private:
		HWND handler = NULL;
	};
}
#endif