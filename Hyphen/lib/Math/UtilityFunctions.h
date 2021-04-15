#pragma once

#define UTILITYFUNCTIONS_H_

#include "../CompiledHeaders.h"
#include "DynamicDatastructure.h"
#include "../Event/Event.h"
#include "Strmanip.h"
#include "../Storage/Filesystem.h"

namespace Hyphen
{
	void get_files_directory(Collection<FileAndPath, std::string> & files, std::string& path, 
		std::string* extension, int const& size, const char * file_root = nullptr);
	void get_folder_first_children(DynamicObject<char *> & children, std::string& path);
	void get_folder_first_children(std::map<std::string, bool>& children, std::string& path);
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