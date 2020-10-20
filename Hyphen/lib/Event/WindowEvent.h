#pragma once

#define WINDOWEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Parent window event class (raw) =====//
	template<class T>
	class WindowEvent : public Event
	{
	public:
		void(*callback)(T &) = nullptr;
	public:
		static T & get_instance() { static T instance; return instance; };

		WindowEvent(const WindowEvent & other) = delete;
		WindowEvent & operator = (const WindowEvent & other) = delete;

		int get_width() { return initial_width; };
		int get_height() { return initial_height; };
		void set_callback(void(*func)(T &)) { callback = func; };
		virtual int get_category() override { return WINDOW; };
	protected:
		WindowEvent() {};
		WindowEvent(int width, int height) : 
			initial_width(width), initial_height(height) {};

		int initial_width, initial_height;
	};

	//===== Window resize event =====//
	class API WindowResize : public WindowEvent<WindowResize>
	{
	public:
		WindowResize() {};
		WindowResize(unsigned int width, unsigned int height) :
			width(width), height(height) {};

		unsigned int get_resize_width() { return width; };
		unsigned int get_resize_height() { return height; };

		SET_CLASS_TYPE(WINDOWRESIZE)

	private:
		unsigned short int width, height;
	};

	//===== Window close event =====//
	class API WindowClose : public WindowEvent<WindowClose>
	{
	public:
		WindowClose() {};

		SET_CLASS_TYPE(WINDOWCLOSE)
	};

	//===== Window create event =====//
	class API WindowCreate : public WindowEvent<WindowCreate>
	{
	public:
		WindowCreate() {};
		WindowCreate(int width, int height) : WindowEvent(width, height){};

		SET_CLASS_TYPE(WINDOWCREATE)
	};

	//===== Window on focus event =====//
	class API WindowFocus : public WindowEvent<WindowFocus>
	{
	public:
		WindowFocus() {};

		SET_CLASS_TYPE(WINDOWFOCUS)
	};

	//===== Window lost focus event =====//
	class API WindowLostFocus : public WindowEvent<WindowLostFocus>
	{
	public:
		WindowLostFocus() {};

		SET_CLASS_TYPE(WINDOWLOSTFOCUS)
	};

	//===== Window move event =====//
	class API WindowMove : public WindowEvent<WindowMove>
	{
	public:
		WindowMove() {};

		SET_CLASS_TYPE(WINDOWMOVE)
	};
}