#pragma once

#define MOUSEEVENT_H_

#include "../Event.h"

namespace WindowAPI
{
	//===== Mouse parent class =====//
	class Mouse : public Event
	{
	public:
		float get_x() { return x; };
		float get_y() { return y; };

		virtual int get_category() override { return MOUSE | INPUT; };

	protected:
		Mouse(float x, float y) : x(x), y(y) {};

		float x, y;
	};

	//===== Mouse button event =====//
	class MouseButton : public Mouse
	{
	public:
		int get_button() { return button; };

		virtual int get_category() override { return MOUSEBUTTON | INPUT; };

	protected:
		MouseButton(float x, float y, int button) : Mouse(x, y), button(button) {};

		int button;
	};

	//===== Mouse move event =====//
	class MouseMove : public Mouse
	{
	public:
		MouseMove(float x, float y) : Mouse(x, y) {};

		static EventType get_static_type() { return MOUSEMOVE; };
		virtual EventType get_type() override { return MOUSEMOVE; };
	};

	//===== Mouse scroll event =====//
	class MouseScroll : public Mouse
	{
	public:
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset) {};

		static EventType get_static_type() { return MOUSESCROLL; };
		virtual EventType get_type() override { return MOUSESCROLL; };
	};

	//===== Mouse button pressed event =====//
	class MouseButtonDown : public MouseButton
	{
	public:
		MouseButtonDown(float x, float y, int button) : MouseButton(x, y, button) {};

		static EventType get_static_type() { return MOUSEDOWN; };
		virtual EventType get_type() override { return MOUSEDOWN; };
	};

	//===== Mouse button released event =====//
	class MouseButtonUp : public MouseButton
	{
	public:
		MouseButtonUp(float x, float y, int button) : MouseButton(x, y, button) {};

		static EventType get_static_type() { return MOUSEUP; };
		virtual EventType get_type() override { return MOUSEUP; };
	};
}