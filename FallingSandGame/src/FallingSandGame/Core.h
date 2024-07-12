#pragma once

#ifdef FSG_PLATFORM_WINDOWS
	#ifdef FSG_BUILD_DLL
		#define FSG_API __declspec(dllexport)
	#else
		#define FSG_API __declspec(dllimport)
    #endif
#else
	#error Falling Sand Game only Supports Windows!
#endif