#pragma once

#define EVENT_H_

#include "CompiledHeaders.h"

namespace WindowAPI
{
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

	class Event
	{
		friend class Dispacher;
	public:
		virtual EventType get_type() { return NONE; };
		virtual int get_category() { return 0; };
		template <class T> T & cast() { return static_cast<T &>(*this); };

		bool in_category(EventCategory category) { return get_category() & category; };
	};

	class Dispatcher
	{
	public:
		template <class T>
		bool dispatch(Event & e, void (* func)(T &))
		{
			auto & event = e.cast<T>();

			if (func == nullptr)
			{
				std::cout << "CALLBACK NULL" << std::endl;

				return false;
			}

			if (event.get_type() == T::get_static_type())
			{
				func(event);

				return true;
			}
			else
				std::cout << "EVENT TYPE MISMATCH " << event.get_type() << "--" << T::get_static_type() << std::endl;

			return false;
		}
	};
}