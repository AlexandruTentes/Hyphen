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
		Key(int key) : key(key) {};
		int get_key() { return key; };
	protected:
		int key;
	};

	//===== Key pressed event =====//
	struct API KeyDown : Key
	{		
		EVENT_MEMBER_SETTER(KeyDown, KEYDOWN)
		KeyDown(int key) : Key(key) {};
	};

	//===== Key released event =====//
	struct API KeyUp : Key
	{
		EVENT_MEMBER_SETTER(KeyUp, KEYUP)
		KeyUp(int key) : Key(key) {};
	};
}