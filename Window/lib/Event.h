#pragma once

#define EVENT_H_

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
		NONE,
		WINDOW = 1 << 0,
		INPUT = 1 << 1,
		KEYBOARD = 1 << 2,
		MOUSE = 1 << 3,
		MOUSEBUTTON = 1 << 4
	};

	class Event
	{
	public:
		virtual EventType get_type() = 0;
		virtual int get_category() = 0;

		bool in_category(EventCategory category) { return get_category() & category; };
	};

	class Dispatcher
	{
	public:
		Dispatcher(Event & event) : event(event) {};

		template <class T>
		bool register_event(std::function<bool(T &)> func)
		{
			if (event.get_type() == T::get_static_type)
			{
				func(* (T*) & event);

				return true;
			}

			return false;
		}

	private:
		Event & event;
	};
}