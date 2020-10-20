#pragma once

#include "../CompiledHeaders.h"

#define LISTENER_H_

#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/WindowEvent.h"

namespace Hyphen
{
#define REGISTER(x) void register_event(void(*func)(x &)) { x::get_instance().set_callback(func); }

	class Listener
	{
	public:
		REGISTER(KeyDown)
		REGISTER(KeyUp)
		REGISTER(MouseMove)
		REGISTER(MouseScroll)
		REGISTER(MouseButtonDown)
		REGISTER(MouseButtonUp)
		REGISTER(WindowResize)
		REGISTER(WindowClose)
		REGISTER(WindowCreate)
		REGISTER(WindowFocus)
		REGISTER(WindowLostFocus)
		REGISTER(WindowMove)
	};

}