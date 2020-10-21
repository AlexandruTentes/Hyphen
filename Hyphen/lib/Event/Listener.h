#pragma once

#include "../CompiledHeaders.h"

#define LISTENER_H_

#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/WindowEvent.h"

namespace Hyphen
{
	class Listener
	{
	public:
		template <class T> void register_event(void(*func)(T &)) { T::get_instance().set_callback(func); }
	};

}