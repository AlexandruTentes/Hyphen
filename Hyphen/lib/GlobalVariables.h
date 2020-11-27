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
	extern float aspect_ratio;

	//========================================================//
	//						Statics							  //
	//========================================================//
	static const char * window_title = "Dev Env";
	static const char * shader_path = "Shader";
	static const char * model_path = "Model";
	static const float PI = 3.141592653f;
}