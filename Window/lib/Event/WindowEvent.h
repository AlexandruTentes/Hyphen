#pragma once

#define WINDOWEVENT_H_

#include "../Event.h"

namespace WindowAPI
{
	template<class T>
	class WindowEvent : public Event
	{
	public:
		void(*callback)(T &) = nullptr;
	public:
		WindowEvent() {};

		static T & get_instance() { static T instance; return instance; }
		void set_callback(void(*func)(T &)) { callback = func; };
		virtual int get_category() override { return WINDOW; };
	};

	//===== Window resize event =====//
	class WindowResize : public WindowEvent<WindowResize>
	{
	public:
		WindowResize() {};
		WindowResize(unsigned short int width, unsigned short int height) :
			width(width), height(height) {};

		unsigned short int get_width() { return width; };
		unsigned short int get_height() { return height; };

		static EventType get_static_type() { return WINDOWRESIZE; };
		virtual EventType get_type() override { return WINDOWRESIZE; };

	private:
		unsigned short int width, height;
	};

	class WindowClose : public WindowEvent<WindowClose>
	{
	public:
		WindowClose() {};

		static EventType get_static_type() { return WINDOWCLOSE; };
		virtual EventType get_type() override { return WINDOWCLOSE; };
	};
}