#pragma once

#define MOUSEEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Mouse parent class =====//
	class API Mouse : public Event
	{
	public:
		EVENT_MEMBER_SETTER(Mouse, MOUSE)
		Mouse() {}
		float get_x() { return x; };
		float get_y() { return y; };
		virtual ~Mouse() = default;
	protected:
		Mouse(float x, float y) : x(x), y(y) {};
		float x, y;
	};

	//===== Mouse move event =====//
	class API MouseMove : public Mouse
	{
	public:
		EVENT_MEMBER_SETTER(MouseMove, MOUSEMOVE)
		MouseMove() {}
		MouseMove(float x, float y) : Mouse(x, y) {};
		virtual ~MouseMove() = default;
	};

	//===== Mouse scroll event =====//
	class API MouseScroll : public Mouse
	{
	public:
		EVENT_MEMBER_SETTER(MouseScroll, MOUSESCROLL)
		MouseScroll() {}
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset) {};
		virtual ~MouseScroll() = default;
	};

	//===== Mouse button pressed event =====//
	class API MouseButtonDown : public Mouse
	{
	public:
		EVENT_MEMBER_SETTER(MouseButtonDown, MOUSEBUTTONDOWN)
		MouseButtonDown() {}
		MouseButtonDown(float x, float y, int button) : Mouse(x, y), button(button) {};
		int get_button() { return button; };
		virtual ~MouseButtonDown() = default;
	protected:
		int button;
	};

	//===== Mouse button released event =====//
	class API MouseButtonUp : public Mouse
	{
	public:
		EVENT_MEMBER_SETTER(MouseButtonUp, MOUSEBUTTONUP)
		MouseButtonUp() {}
		MouseButtonUp(float x, float y, int button) : Mouse(x, y), button(button) {};
		int get_button() { return button; };
		virtual ~MouseButtonUp() = default;
	protected:
		int button;
	};
}