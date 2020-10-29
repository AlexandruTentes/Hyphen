#pragma once

#define EVENT_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Math/DynamicDatastructure.h"

namespace Hyphen
{
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