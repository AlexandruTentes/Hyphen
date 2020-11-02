#pragma once

#define WINDOWEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Parent window event class (raw) =====//
	class API WindowEvent : public Event
	{
	public:
		EVENT_MEMBER_SETTER(WindowEvent, WINDOWEVENT)
		WindowEvent(int width, int height) :
			initial_width(width), initial_height(height) {};
		int get_width() { return initial_width; };
		int get_height() { return initial_height; };
	protected:
		int initial_width, initial_height;
	};

	//===== Window resize event =====//
	struct API WindowResize : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowResize, WINDOWRESIZE)
		WindowResize(unsigned int width, unsigned int height) : 
			WindowEvent(width, height) {};
	};

	//===== Window close event =====//
	struct API WindowClose : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowClose, WINDOWCLOSE)
	};

	//===== Window create event =====//
	struct API WindowCreate : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowCreate, WINDOWCREATE)
		WindowCreate(int width, int height) : WindowEvent(width, height){};
	};

	//===== Window on focus event =====//
	struct API WindowFocus : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowFocus, WINDOWFOCUS)
	};

	//===== Window lost focus event =====//
	struct API WindowLostFocus : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowLostFocus, WINDOWLOSTFOCUS)
	};

	//===== Window move event =====//
	struct API WindowMove : WindowEvent
	{
		EVENT_MEMBER_SETTER(WindowMove, WINDOWMOVE)
	};
}