#pragma once

#define EVENT_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Math/UtilityMacros.h"

#pragma warning( disable : 4251 )

namespace Hyphen
{
#define EVENT_MEMBER_SETTER(T, x)				std::function<void(T &)> callback = nullptr; \
												static const EventType type = x; \
												EventType get_type() override { return type; }; \
												void copy(const T & other) { * this = other; } \
												virtual ~T() = default; \
												EVENT_MEMBER_PARTIAL_SINGLETONIZE(T)

	enum EventType
	{
		NONE = 0,
		KEY, KEYDOWN, KEYUP, KEYTYPED,
		MOUSE, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSESCROLL, MOUSEMOVE,
		WINDOWEVENT, WINDOWRESIZE, WINDOWCLOSE, WINDOWCREATE, WINDOWFOCUS, WINDOWLOSTFOCUS, WINDOWMOVE,
		END
	};

	class API Event
	{
	public:
		virtual EventType get_type() { return NONE; }
		virtual ~Event() = default;
	};

	class EventPoll
	{
	public:
		EVENT_MEMBER_SINGLETONIZE(EventPoll)
		bool event_poll[END - 1];
		Event * event_array[END - 1];
		virtual ~EventPoll() 
		{
			for (int i = 0; i < END - 1; i++)
				if (event_array[i]) delete event_array[i];
		};
	};
}