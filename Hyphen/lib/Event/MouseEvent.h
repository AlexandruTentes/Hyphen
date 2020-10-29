#pragma once

#define MOUSEEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Mouse parent class =====//
	class API Mouse : public Event, public Singleton<Mouse>
	{
	public:
		static const EventType type = MOUSE;
		EventType get_type() override { return type; }
		Mouse() {}
		float get_x() { return x; };
		float get_y() { return y; };
		virtual ~Mouse() = default;
	protected:
		Mouse(float x, float y) : x(x), y(y) {};
		float x, y;
	};

	//===== Mouse move event =====//
	class API MouseMove : public Mouse, public Singleton<MouseMove>
	{
	public:
		static const EventType type = MOUSEMOVE;
		EventType get_type() override { return type; }
		MouseMove() {}
		MouseMove(float x, float y) : Mouse(x, y) {};
		virtual ~MouseMove() = default;
	};

	//===== Mouse scroll event =====//
	class API MouseScroll : public Mouse, public Singleton<MouseScroll>
	{
	public:
		static const EventType type = MOUSESCROLL;
		EventType get_type() override { return type; }
		MouseScroll() {}
		MouseScroll(float x_offset, float y_offset) : Mouse(x_offset, y_offset) {};
		virtual ~MouseScroll() = default;
	};

	//===== Mouse button pressed event =====//
	class API MouseButtonDown : public Mouse, public Singleton<MouseButtonDown>
	{
	public:
		static const EventType type = MOUSEBUTTONDOWN;
		EventType get_type() override { return type; }
		MouseButtonDown() {}
		MouseButtonDown(float x, float y, int button) : Mouse(x, y), button(button) {};
		int get_button() { return button; };
		virtual ~MouseButtonDown() = default;
	protected:
		int button;
	};

	//===== Mouse button released event =====//
	class API MouseButtonUp : public Mouse, public Singleton<MouseButtonUp>
	{
	public:
		static const EventType type = MOUSEBUTTONUP;
		EventType get_type() override { return type; }
		MouseButtonUp() {}
		MouseButtonUp(float x, float y, int button) : Mouse(x, y), button(button) {};
		int get_button() { return button; };
		virtual ~MouseButtonUp() = default;
	protected:
		int button;
	};
}