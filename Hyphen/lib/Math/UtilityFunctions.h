#pragma once

#define UTILITYFUNCTIONS_H_

#include "../CompiledHeaders.h"
#include "DynamicDatastructure.h"
#include "../Event/Event.h"
#include "Strmanip.h"
#include "../GraphicEngine/Collection/FolderDataCollection.h"

namespace Hyphen
{
	void get_files_directory(std::string & path, std::string const & identifier = "");
	void read_models(std::string* extension, unsigned int extension_size, 
		std::string* texture = nullptr, unsigned int texture_size = 0);
	void read_shaders();
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