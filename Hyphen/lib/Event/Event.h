#pragma once

#define EVENT_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"

#pragma warning( disable : 4251 )

namespace Hyphen
{
#define EVENT_MEMBER_SINGLETONIZE(T)	static T & get_instance() { static T instance; return instance; } \
										T(const T &) = delete; \
										T(T &&) = delete; \
										T operator = (const T &) = delete; \
										T operator = (T &&) = delete;
										
#define EVENT_MEMBER_SETTER(T, x)		std::function<void(T &)> callback = nullptr; \
										static const EventType type = x; \
										EventType get_type() override { return type; } \
										EVENT_MEMBER_SINGLETONIZE(T)

	enum EventType
	{
		NONE,
		KEY, KEYDOWN, KEYUP,
		MOUSE, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSESCROLL, MOUSEMOVE,
		WINDOWEVENT, WINDOWRESIZE, WINDOWCLOSE, WINDOWCREATE, WINDOWFOCUS, WINDOWLOSTFOCUS, WINDOWMOVE
	};

	class API Event
	{
	public:
		virtual EventType get_type() { return NONE; }
		virtual ~Event() = default;
	};
}