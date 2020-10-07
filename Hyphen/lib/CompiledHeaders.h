#pragma once

#include <Window.h>
#include <iostream>
#include <string>
#include <map>

//////////////////////////////////
//===== Platform libraries =====//
//////////////////////////////////

#ifdef _WIN64 //Detecting if the platform is windows
	//#include <d3d9.h> //Including DirectX api for windows platform
	#define WINDOWS
	#define OPENGL //This should be DIRECTX instead, functionality will come later on
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
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#endif