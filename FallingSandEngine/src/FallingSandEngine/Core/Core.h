#pragma once
#include <memory>
#ifdef FSE_PLATFORM_WINDOWS

#if FSE_DYNAMIC_LINK
#ifdef FSE_BUILD_DLL
#define FSE_API __declspec(dllexport)
#else
#define FSE_API __declspec(dllimport)
#endif
#else
#define FSE_API 
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
#define YAML_CPP_STATIC_DEFINE
//shifts bit by x ammount
#define BIT(x) (1 << x)

#define FSE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace FallingSandEngine
{

	//could make these into classes
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}