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
		WindowEvent() {};
		int get_width() { return initial_width; };
		int get_height() { return initial_height; };
		virtual ~WindowEvent() = default;
	protected:
		WindowEvent(int width, int height) : 
			initial_width(width), initial_height(height) {};

		int initial_width, initial_height;
	};

	//===== Window resize event =====//
	class API WindowResize : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowResize, WINDOWRESIZE)
		WindowResize() {}
		WindowResize(unsigned int width, unsigned int height) :
			width(width), height(height) {};
		unsigned int get_resize_width() { return width; };
		unsigned int get_resize_height() { return height; };
		virtual ~WindowResize() = default;
	private:
		unsigned short int width, height;
	};

	//===== Window close event =====//
	class API WindowClose : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowClose, WINDOWCLOSE)
		WindowClose() {}
		virtual ~WindowClose() = default;
	};

	//===== Window create event =====//
	class API WindowCreate : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowCreate, WINDOWCREATE)
		WindowCreate() {}
		WindowCreate(int width, int height) : WindowEvent(width, height){};
		virtual ~WindowCreate() = default;
	};

	//===== Window on focus event =====//
	class API WindowFocus : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowFocus, WINDOWFOCUS)
		WindowFocus() {}
		virtual ~WindowFocus() = default;
	};

	//===== Window lost focus event =====//
	class API WindowLostFocus : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowLostFocus, WINDOWLOSTFOCUS)
		WindowLostFocus() {}
		virtual ~WindowLostFocus() = default;
	};

	//===== Window move event =====//
	class API WindowMove : public WindowEvent
	{
	public:
		EVENT_MEMBER_SETTER(WindowMove, WINDOWMOVE)
		WindowMove() {}
		virtual ~WindowMove() = default;
	};
}