#pragma once

#define GLOBALVARIABLES_H_

#include <string>

namespace Hyphen
{
	//========================================================//
	//						Externals						  //
	//========================================================//
	extern bool unfocused;														// Check if the window is focused
	extern bool center_cursor_status;											// Store a flag to know if to set the cursor to center
	extern unsigned int width, height;											// window width and height
	extern unsigned int prev_width, prev_height;
	extern int min_width, min_height;

	//========================================================//
	//						Statics							  //
	//========================================================//
	static const std::string window_title = "Dev Env";
	static const std::string shader_path = "Shader";
	static const std::string model_path = "Model";
}