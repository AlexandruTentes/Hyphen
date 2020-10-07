#pragma once

#include <iostream>
#include <string>
#include <map>

#ifdef _WIN64 //Detecting if the platform is windows
	#include <windows.h> //Including win api for windows platform
	#define WINDOWS
#elif defined(__linux__) //Detecting linux
	#define LINUX
#elif defined(__APPLE__) //Detecting Mac OS X
	#define APPLE
#elif defined(__FreeBSD__) //Detecting FreeBSD
	#define FREEBSD
#else
	#error The window api is not meant to work on this platform!
#endif