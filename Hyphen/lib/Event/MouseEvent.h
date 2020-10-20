#pragma once

#define MOUSEEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Mouse parent class =====//
	template <class T>
	class Mouse : public Event
	{
	public:
		void(*callback)(T &) = nullptr;
	public:
		static T & get_instance() { static T instance; return instance; };

		Mouse(const Mouse & other) = delete;
		Mouse & operator = (const Mouse & other) = delete;

		float get_x() { return x; };
		float get_y() { return y; };
		void set_callback(void(*func)(T &)) { callback = func; };
		virtual int get_category() override { return MOUSE | INPUT; };

	protected:
		Mouse() {};
		Mouse(float x, float y) : x(x), y(y) {};

		float x, y;
	};

	//===== Mouse move event =====//
	class API MouseMove : public Mouse<MouseMove>
	{
	public:
		MouseMove() {};
		MouseMove(float x, float y) : Mouse(x, y) {};

		SET_CLASS_TYPE(MOUSEMOVE)
	};

	//===== Mouse scroll event =====//
	class API MouseScroll : public Mouse<MouseScroll>
	{
	public:
		MouseScroll() {};
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset) {};

		SET_CLASS_TYPE(MOUSESCROLL)
	};

	//===== Mouse button pressed event =====//
	class API MouseButtonDown : public Mouse<MouseButtonDown>
	{
	public:
		MouseButtonDown() {};
		MouseButtonDown(float x, float y, int button) : Mouse(x, y), button(button) {};

		int get_button() { return button; };

		SET_CLASS_TYPE(MOUSEDOWN)
		virtual int get_category() override { return MOUSEBUTTON | INPUT; };
	protected:
		int button;
	};

	//===== Mouse button released event =====//
	class API MouseButtonUp : public Mouse<MouseButtonUp>
	{
	public:
		MouseButtonUp() {};
		MouseButtonUp(float x, float y, int button) : Mouse(x, y), button(button) {};

		int get_button() { return button; };

		SET_CLASS_TYPE(MOUSEUP)
		virtual int get_category() override { return MOUSEBUTTON | INPUT; };
	protected:
		int button;
	};
}