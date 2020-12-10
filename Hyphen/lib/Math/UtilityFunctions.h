#pragma once

#define UTILITYFUNCTIONS_H_

#include "../CompiledHeaders.h"
#include "DynamicDatastructure.h"
#include "../Event/Event.h"
#include "Strmanip.h"

namespace Hyphen
{
	void get_files_directory(DynamicObject<FileAndPath>& files, std::string& path, std::string* extension, int const& size);
	int get_sizeof_gltype(unsigned int type);

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