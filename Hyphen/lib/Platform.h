#pragma once

//Check if the platform is windows x64 bit OS
#ifdef _WIN64
	#ifdef BUILD_DLL
		#define API __declspec(dllexport)
	#else
		#define  API __declspec(dllimport)
	#endif
//Otherwise error
#else
	#error This game engine does not work on this platform!
#endif // _WIN64_
