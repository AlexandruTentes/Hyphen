#pragma once

#define IMGUIINCLUDE_H_

#include "../CompiledHeaders.h"

#ifdef WINDOWS //For now the GUI works only for windows machines
#include "../thirdparty/imgui/imgui_impl_win32.h"
#define HANDLER HWND 
#elif defined(LINUX)
#include "../thirdparty/imgui/" // to be implemented later
#endif

#ifdef OPENGL //For now the GUI works only with opengl
#include "../thirdparty/imgui/imgui_impl_opengl3.h"
#endif
