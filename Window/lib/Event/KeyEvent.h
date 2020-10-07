#pragma once

#define KEYEVENT_H_

#include "../Event.h"

namespace WindowAPI
{
	//===== Parent key class =====//
	class Key : public Event
	{
	public:
		int get_key() { return key; };
		virtual int get_category() override { return KEYBOARD | INPUT; };

	protected:
		Key(int key) : key(key) {};

		int key;
	};

	//===== Key pressed event =====//
	class KeyDown : public Key
	{
	public:
		KeyDown(int key) : Key(key) {};

		static EventType get_static_type() { return KEYDOWN; };
		virtual EventType get_type() override { return KEYDOWN; };
	};

	//===== Key released event =====//
	class KeyUp : public Key
	{
	public:
		KeyUp(int key) : Key(key) {};

		static EventType get_static_type() { return KEYUP; };
		virtual EventType get_type() override { return KEYUP; };
	};
}