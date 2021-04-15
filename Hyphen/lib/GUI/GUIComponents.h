#pragma once

#define GUICOMPONENTS_H_

#include "../CompiledHeaders.h"
#include "ImGuiInclude.h"

namespace Hyphen
{
	//////////////////////////
	//===== Search bar =====//
	//////////////////////////

	class SearchBar
	{
	public:
		SearchBar();
		SearchBar(ImGuiInputTextFlags flags);
		SearchBar(std::string & name, ImGuiInputTextFlags flags);
		bool new_searchbar();
		virtual ~SearchBar() = default;
	private:
		static int callback(ImGuiInputTextCallbackData* data);
	private:
		std::string name = "";
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackAlways | ImGuiInputTextFlags_CallbackCharFilter;
		bool is_filter_text = false;
		static const unsigned short int  input_text_buffer_size = 50;
		char input_text_buffer[input_text_buffer_size];
	};
}