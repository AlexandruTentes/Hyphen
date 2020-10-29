#pragma once

#define WINDOWEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Parent window event class (raw) =====//
	class API WindowEvent : public Event, public Singleton<WindowEvent>
	{
	public:
		static const EventType type = WINDOWEVENT;
		EventType get_type() override { return type; }
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
	class API WindowResize : public WindowEvent, public Singleton<WindowResize>
	{
	public:
		static const EventType type = WINDOWRESIZE;
		EventType get_type() override { return type; }
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
	class API WindowClose : public WindowEvent, public Singleton<WindowClose>
	{
	public:
		static const EventType type = WINDOWCLOSE;
		EventType get_type() override { return type; }
		WindowClose() {}
		virtual ~WindowClose() = default;
	};

	//===== Window create event =====//
	class API WindowCreate : public WindowEvent, public Singleton<WindowCreate>
	{
	public:
		static const EventType type = WINDOWCREATE;
		EventType get_type() override { return type; }
		WindowCreate() {}
		WindowCreate(int width, int height) : WindowEvent(width, height){};
		virtual ~WindowCreate() = default;
	};

	//===== Window on focus event =====//
	class API WindowFocus : public WindowEvent, public Singleton<WindowFocus>
	{
	public:
		static const EventType type = WINDOWFOCUS;
		EventType get_type() override { return type; }
		WindowFocus() {}
		virtual ~WindowFocus() = default;
	};

	//===== Window lost focus event =====//
	class API WindowLostFocus : public WindowEvent, public Singleton<WindowLostFocus>
	{
	public:
		static const EventType type = WINDOWLOSTFOCUS;
		EventType get_type() override { return type; }
		WindowLostFocus() {}
		virtual ~WindowLostFocus() = default;
	};

	//===== Window move event =====//
	class API WindowMove : public WindowEvent, public Singleton<WindowMove>
	{
	public:
		static const EventType type = WINDOWMOVE;
		EventType get_type() override { return type; }
		WindowMove() {}
		virtual ~WindowMove() = default;
	};
}