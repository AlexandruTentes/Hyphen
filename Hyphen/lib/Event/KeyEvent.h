#pragma once

#define KEYEVENT_H_

#include "Event.h"
#include "../Math/DynamicDatastructure.h"

namespace Hyphen
{
	//===== Parent key event class (raw) =====//
	class API Key : public Event, public Singleton<Key>
	{
	public:
		static const EventType type = KEY;
		EventType get_type() override { return type; }
		Key() {}
		int get_key() { return key; };
		virtual ~Key() = default;
	protected:
		Key(int key) : key(key) {};
		int key;
	};

	//===== Key pressed event =====//
	class API KeyDown : public Key, public Singleton<KeyDown>
	{		
	public:
		static const EventType type = KEYDOWN;
		EventType get_type() override { return type; }
		KeyDown() {}
		KeyDown(int key) : Key(key) {};
		virtual ~KeyDown() = default;
	};

	//===== Key released event =====//
	class API KeyUp : public Key, public Singleton<KeyUp>
	{
	public:
		static const EventType type = KEYUP;
		EventType get_type() override { return type; }
		KeyUp() {}
		KeyUp(int key) : Key(key) {};
		virtual ~KeyUp() = default;
	};
}