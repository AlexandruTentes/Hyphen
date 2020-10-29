#pragma once

#define KEYEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Parent key event class (raw) =====//
	class API Key : public Event
	{
	public:
		EVENT_MEMBER_SETTER(Key, KEY)
		Key() {}
		int get_key() { return key; };
		virtual ~Key() = default;
	protected:
		Key(int key) : key(key) {};
		int key;
	};

	//===== Key pressed event =====//
	class API KeyDown : public Key
	{		
	public:
		EVENT_MEMBER_SETTER(KeyDown, KEYDOWN)
		KeyDown() {}
		KeyDown(int key) : Key(key) {};
		virtual ~KeyDown() = default;
	};

	//===== Key released event =====//
	class API KeyUp : public Key
	{
	public:
		EVENT_MEMBER_SETTER(KeyUp, KEYUP)
		KeyUp() {}
		KeyUp(int key) : Key(key) {};
		virtual ~KeyUp() = default;
	};
}