#pragma once

#ifdef FSE_PLATFORM_WINDOWS
	#ifdef FSE_BUILD_DLL
		#define FSE_API __declspec(dllexport)
	#else
		#define FSE_API __declspec(dllimport)
    #endif
#else
	#error Falling Sand Game only Supports Windows!
#endif



#ifdef FSE_DEBUG
	#define FSE_ENABLE_ASSERTS
#endif



#ifdef FSE_ENABLE_ASSERTS
	#define FSE_ASSERT(x, ...) {if(!(x)) {FSE_ERROR("Assertion Failed: {0}" __VA_ARGS__); __debugbreak();}}
	#define FSE_CORE_ASSERT(x, ...) {if(!(x)) {FSE_ERROR("Assertion Failed: {0}" __VA_ARGS__); __debugbreak();}}
#else
	#define FSE_ASSERT(x, ...)
	#define FSE_CORE_ASSERT(x, ...)
#endif

//shifts bit by x ammount
#define BIT(x) (1 << x)

#define FSE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)