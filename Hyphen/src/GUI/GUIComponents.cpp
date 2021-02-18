#include "../../lib/GUI/GUIComponents.h"

namespace Hyphen
{
	//////////////////////////
	//===== Search bar =====//
	//////////////////////////

	SearchBar::SearchBar()
	{
	}

	SearchBar::SearchBar(ImGuiInputTextFlags flags)
	{
		this->flags = flags;
	}

	SearchBar::SearchBar(std::string& name, ImGuiInputTextFlags flags)
	{
		this->name = name;
		this->flags = flags;
	}

	bool SearchBar::new_searchbar()
	{
		is_filter_text = ImGui::InputText(name.c_str(), input_text_buffer, input_text_buffer_size, flags, callback);
		return is_filter_text;
	}

	int SearchBar::callback(ImGuiInputTextCallbackData* data)
	{
		/*
		if(data->EventChar)
			std::cout << data->EventChar << "\n";
			*/
		return 0;
	}
}