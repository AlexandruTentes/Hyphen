#pragma once

#define MOUSEEVENT_H_

#include "../Event.h"

namespace WindowAPI
{
	//===== Mouse parent class =====//
	template <class T>
	class Mouse : public Event
	{
	public:
		void(*callback)(T &) = nullptr;
	public:
		Mouse() {};

		static T & get_instance() { static T instance; return instance; }
		float get_x() { return x; };
		float get_y() { return y; };
		void set_callback(void(*func)(T &)) { callback = func; };

		virtual int get_category() override { return MOUSE | INPUT; };

	protected:
		Mouse(float x, float y) : x(x), y(y) {};

		float x, y;
	};

	//===== Mouse move event =====//
	class MouseMove : public Mouse<MouseMove>
	{
	public:
		MouseMove() {};
		MouseMove(float x, float y) : Mouse(x, y) {};

		static EventType get_static_type() { return MOUSEMOVE; };
		virtual EventType get_type() override { return MOUSEMOVE; };
	};

	//===== Mouse scroll event =====//
	class MouseScroll : public Mouse<MouseScroll>
	{
	public:
		MouseScroll() {};
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset) {};

		static EventType get_static_type() { return MOUSESCROLL; };
		virtual EventType get_type() override { return MOUSESCROLL; };
	};

	//===== Mouse button pressed event =====//
	class MouseButtonDown : public Mouse<MouseButtonDown>
	{
	public:
		MouseButtonDown() {};
		MouseButtonDown(float x, float y, int button) : Mouse(x, y), button(button) {};

		int get_button() { return button; };

		static EventType get_static_type() { return MOUSEDOWN; };
		virtual EventType get_type() override { return MOUSEDOWN; };
		virtual int get_category() override { return MOUSEBUTTON | INPUT; };
	protected:
		int button;
	};

	//===== Mouse button released event =====//
	class MouseButtonUp : public Mouse<MouseButtonUp>
	{
	public:
		MouseButtonUp() {};
		MouseButtonUp(float x, float y, int button) : Mouse(x, y), button(button) {};

		int get_button() { return button; };

		static EventType get_static_type() { return MOUSEUP; };
		virtual EventType get_type() override { return MOUSEUP; };
		virtual int get_category() override { return MOUSEBUTTON | INPUT; };
	protected:
		int button;
	};
}