#pragma once
// post build command copy /Y "$(TargetDir)$(ProjectName).dll" "$(SolutionDir)Game\$(ProjectName).dll"
#ifdef FSE_PLATFORM_WINDOWS
	#ifdef FSE_BUILD_DLL
		#define FSE_API __declspec(dllexport)
	#else
		#define FSE_API __declspec(dllimport)
    #endif
#else
	#error Falling Sand Game only Supports Windows!
#endif