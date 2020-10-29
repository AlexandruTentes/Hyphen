#pragma once

#define DISPATCHER_H_

#include "Event.h"

//Ignoring 'dll not available by client' warning as the Dispatcher should 
//ever be used by the engine itself only
#pragma warning( disable : 4251 )

namespace Hyphen
{
	class Dispatcher
	{
	public:
		template <class T>
		bool dispatch(Event & e, std::function<void(T &)> func)
		{
			try
			{
				if (T::type != e.get_type())
					return false;

				auto & event = static_cast<T &>(e);
				func(event);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		virtual ~Dispatcher() = default;
	};
}