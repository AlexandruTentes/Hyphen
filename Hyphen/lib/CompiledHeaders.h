#pragma once

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <tuple>
#include <functional>
#include <fstream>
#include <math.h>
#include <chrono>

#include "../thirdparty/glm/glm.hpp"
#include "../thirdparty/glm/gtx/transform.hpp"
#include "../thirdparty/glm/gtc/type_ptr.hpp"
#include "../thirdparty/glm/gtc/matrix_transform.hpp"

#include "GlobalVariables.h"
#include "Math/UtilityMacros.h"
#include "Event/KeyCodes.h"

//////////////////////////////////
//===== Platform libraries =====//
//////////////////////////////////

#ifdef _WIN64 //Detecting if the platform is windows
	//#include <d3d9.h> //Including DirectX api for windows platform
	#include <windows.h> //Including win api for windows platform
	#include <WindowsX.h> //Including win api extention 
	#define WINDOWS
	#define OPENGL //This should be DIRECTX instead, functionality will come later on
	#define DEBUG_OPENGL
#elif defined(__linux__) //Detecting linux
	#define LINUX
	#define OPENGL
#elif defined(__APPLE__) //Detecting Mac OS X
	#define APPLE
	#define OPENGL
#elif defined(__FreeBSD__) //Detecting FreeBSD
	#define FREEBSD
	#define OPENGL
#else
	#error The window api is not meant to work on this platform!
#endif

////////////////////////////////////////
//===== Application dependancies =====//
////////////////////////////////////////

#ifdef BUILD_DLL
	#include <GL\glew.h>
	#include <GL\freeglut.h>
#endif