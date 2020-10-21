#pragma once

#define KEYEVENT_H_

#include "Event.h"

namespace Hyphen
{
	//===== Parent key event class (raw) =====//
	template <class T>
	class Key : public Event
	{
	public:
		void(*callback)(T &) = nullptr;
	public:
		static T & get_instance() { static T instance; return instance; };

		Key(const Key & other) = delete;
		Key & operator = (const Key & other) = delete;

		void set_callback(void(*func)(T &)) { callback = func; };
		int get_key() { return key; };
		virtual int get_category() override { return KEYBOARD | INPUT; };

	protected:
		Key() {};
		Key(int key) : key(key) {};

		int key;
	};

	//===== Key pressed event =====//
	class API KeyDown : public Key<KeyDown>
	{
	public:
		KeyDown() {};
		KeyDown(int key) : Key(key) {};

		SET_CLASS_TYPE(KEYDOWN)
	};

	//===== Key released event =====//
	class API KeyUp : public Key<KeyUp>
	{
	public:
		KeyUp() {};
		KeyUp(int key) : Key(key) {};

		SET_CLASS_TYPE(KEYUP)
	};
}