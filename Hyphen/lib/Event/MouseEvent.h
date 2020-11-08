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
		Mouse(float x, float y, int button) : x(x), y(y), button(button) {};
		float get_x() { return x; };
		float get_y() { return y; };
		int get_button() { return button; };
	protected:
		float x, y;
		int button = NULL;
	};

	//===== Mouse move event =====//
	struct API MouseMove : Mouse
	{
		EVENT_MEMBER_SETTER(MouseMove, MOUSEMOVE)
		MouseMove(float x, float y) : Mouse(x, y, NULL) {};
	};

	//===== Mouse scroll event =====//
	struct API MouseScroll : Mouse
	{
		EVENT_MEMBER_SETTER(MouseScroll, MOUSESCROLL)
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset, NULL) {};
	};

	//===== Mouse button pressed event =====//
	struct API MouseButtonDown : Mouse
	{
		EVENT_MEMBER_SETTER(MouseButtonDown, MOUSEBUTTONDOWN)
		MouseButtonDown(float x, float y, int button) : Mouse(x, y, button) {};
	};

	//===== Mouse button released event =====//
	struct API MouseButtonUp : Mouse
	{
		EVENT_MEMBER_SETTER(MouseButtonUp, MOUSEBUTTONUP)
		MouseButtonUp(float x, float y, int button) : Mouse(x, y, button) {};
	};
}