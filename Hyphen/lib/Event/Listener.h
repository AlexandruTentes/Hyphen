#pragma once

#include "../CompiledHeaders.h"

#define LISTENER_H_

#include "Dispatcher.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"

namespace Hyphen
{
#define DISPATCH(x, y) dispatch_event(&x, y, this);
#define REGISTER(x) register_event(&x, this);

	class API Listener
	{
	public:
		// Wrapper around the dispatcher call for events
		template <class T, class U> void dispatch_event(void(U::*func)(T &), Event & e, U * instance)
		{ 
			dispatcher.dispatch<T>(e, std::bind(func, instance, std::placeholders::_1)); 
		}

		// Wrapper around the dispatcher call for events
		template <class T, class U> void register_event(void(U::*func)(T &), U * instance)
		{
			T::get_instance().callback = std::bind(func, instance, std::placeholders::_1);
		}

		virtual ~Listener() = default;
	private:
		Dispatcher dispatcher;
	};

}