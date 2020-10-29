#pragma once

#define WINDOWMANAGER_H_

#include "../CompiledHeaders.h"
#include "WindowAPI.h"

////////////////////////////////////////////////////////////////
//===== singleton class that manages all created windows =====//
////////////////////////////////////////////////////////////////

namespace Hyphen
{
	template <typename T>
	class WindowManager
	{
	public:
		static WindowManager & get_instance() { static WindowManager instance; return instance; }

		//===== Don't allow c++ to make a copy of this singleton =====//
		WindowManager(const WindowManager &) = delete;
		WindowManager & operator = (const WindowManager &) = delete;
		//===== =====//

		void window_initialization(Window * window);

		void insert(T hwnd, Window * window);
		std::map<T, Window *> get_all();
		Window * get_one_window(T hwnd);
		void remove(T hwnd);

		virtual ~WindowManager();

	//===== Private functions =====//
	private:
		WindowManager() {};

	private:
		Window * window_init;

		std::map<T, Window *> windows;
	};

	////////////////////////////////////////////////////////////
	//===== WindowManager member function implementation =====//
	////////////////////////////////////////////////////////////

	template <typename T>
	Hyphen::WindowManager<T>::~WindowManager()
	{
		windows.clear();
	}

	template <typename T>
	std::map<T, Window *> Hyphen::WindowManager<T>::get_all()
	{
		return windows;
	}

	template <typename T>
	void Hyphen::WindowManager<T>::window_initialization(Window * window)
	{
		window_init = window;
	}

	template <typename T>
	void Hyphen::WindowManager<T>::remove(T hwnd)
	{
		windows.erase(hwnd);
	}

	template <typename T>
	Window * Hyphen::WindowManager<T>::get_one_window(T hwnd)
	{
		return windows[hwnd] == nullptr ? window_init : windows[hwnd];
	}

	template <typename T>
	void Hyphen::WindowManager<T>::insert(T hwnd, Window * window)
	{
		windows[hwnd] = window;
	}

}