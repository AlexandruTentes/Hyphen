#pragma once

#define EVENT_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"

namespace Hyphen
{
#define SET_CLASS_TYPE(x)	static EventType get_static_type() { return x; }; \
							virtual EventType get_type() override { return x; };

	enum EventType
	{
		NONE,
		KEYDOWN, KEYUP,
		MOUSEDOWN, MOUSEUP, MOUSEMOVE, MOUSESCROLL,
		WINDOWCLOSE, WINDOWRESIZE, WINDOWCREATE, WINDOWFOCUS, WINDOWLOSTFOCUS, WINDOWMOVE
	};

	enum EventCategory
	{
		WINDOW = 1 << 0,
		INPUT = 1 << 1,
		KEYBOARD = 1 << 2,
		MOUSE = 1 << 3,
		MOUSEBUTTON = 1 << 4
	};

	class API Event
	{
		friend class Dispatcher;
	public:
		virtual EventType get_type() { return NONE; };
		virtual int get_category() { return 0; };

		bool in_category(EventCategory category) { return get_category() & category; };
	};

	class Dispatcher
	{
	public:
		template <class T>
		bool dispatch(Event & e, void (* func)(T &))
		{
			auto & event = static_cast<T &>(e);

			if (func == nullptr)
				return false;

			if (event.get_type() == T::get_static_type())
			{
				func(event);

				return true;
			}
			else return false;
		}
	};
}