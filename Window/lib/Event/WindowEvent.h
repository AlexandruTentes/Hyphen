#pragma once

#define WINDOWEVENT_H_

#include "../Event.h"

namespace WindowAPI
{
	//===== Window resize event =====//
	class WindowResize : public Event
	{
	public:
		WindowResize(unsigned short int width, unsigned short int height) :
			width(width), height(height) {};

		unsigned short int get_width() { return width; };
		unsigned short int get_height() { return height; };

		virtual int get_category() override { return WINDOW; };
		static EventType get_static_type() { return WINDOWRESIZE; };
		virtual EventType get_type() override { return WINDOWRESIZE; };

	private:
		unsigned short int width, height;
	};

	class WindowClose : public Event
	{
	public:
		WindowClose() {};

		virtual int get_category() override { return WINDOW; };
		static EventType get_static_type() { return WINDOWCLOSE; };
		virtual EventType get_type() override { return WINDOWCLOSE; };
	};
}