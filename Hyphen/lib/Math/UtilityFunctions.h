#pragma once

#define UTILITYFUNCTIONS_H_

#include "../CompiledHeaders.h"
#include "../Event/Event.h"

namespace Hyphen
{
	template <class T> bool poll_event(T * e)
	{
		bool res = EventPoll::get_instance().event_poll[e->get_type()];

		if (res)
		{
			EventPoll::get_instance().event_poll[e->get_type()] = false;
			* e = * static_cast<T *>(EventPoll::get_instance().event_array[T::type]);
		}

		return res;
	}
}