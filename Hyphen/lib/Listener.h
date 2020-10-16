#pragma once

#include "CompiledHeaders.h"

#define LISTENER_H_

#include "WindowEvent.h"

namespace Hyphen
{
#define REGISTER(x) void register_event(void(*func)(x &)) { x::get_instance().set_callback(func); }

	class Listener
	{
	public:
		static Listener & get_instance() { static Listener instance; return instance; };

		Listener() {};
		Listener(const Listener &) = delete;
		Listener & operator = (const Listener &) = delete;

		void register_event(void(*func)(WindowAPI::KeyDown &)) { std::cout << &WindowAPI::KeyDown::get_instance() << std::endl; WindowAPI::KeyDown::get_instance().set_callback(func); }
		//REGISTER(KeyDown)
		REGISTER(WindowAPI::KeyUp)
		REGISTER(WindowAPI::MouseMove)
		REGISTER(WindowAPI::MouseScroll)
		REGISTER(WindowAPI::MouseButtonDown)
		REGISTER(WindowAPI::MouseButtonUp)
		REGISTER(WindowAPI::WindowResize)
		REGISTER(WindowAPI::WindowClose)
	};

}