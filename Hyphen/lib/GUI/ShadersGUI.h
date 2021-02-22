#pragma once

#define SHADERSGUI_H_

#include "../CompiledHeaders.h"
#include "ImGuiInclude.h"
#include "../Math/UtilityFunctions.h"

namespace Hyphen
{
	class ShadersGUI
	{
	public:
		template <class T>
		void show(T* gui);
		virtual ~ShadersGUI() = default;
	private:
		std::map<std::string, bool> shaders;
		std::string search_path = shader_path;
	};

	template<class T>
	void ShadersGUI::show(T* gui)
	{
		get_folder_first_children(shaders, search_path);
				
		for (auto & s : shaders)
		{
			if (ImGui::Button(s.first.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0)))
			{
				search_path = search_path + "\\" + s.first;
				std::cout << search_path << "\n";
				shaders.clear();
				break;
			}
		}
	}
}