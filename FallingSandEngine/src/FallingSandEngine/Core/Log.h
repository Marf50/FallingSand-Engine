#pragma once
#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace FallingSandEngine
{
	class FSE_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;}
	private:
			static Ref<spdlog::logger> s_CoreLogger;
			static Ref<spdlog::logger> s_ClientLogger;
	};
}
//core log 
#define FSE_CORE_ERROR(...)		::FallingSandEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FSE_CORE_WARN(...)		::FallingSandEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FSE_CORE_INFO(...)		::FallingSandEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FSE_CORE_TRACE(...)		::FallingSandEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FSE_CORE_FATAL(...)		::FallingSandEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log 
#define FSE_ERROR(...)		::FallingSandEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FSE_WARN(...)		::FallingSandEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FSE_INFO(...)		::FallingSandEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FSE_TRACE(...)		::FallingSandEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FSE_FATAL(...)		::FallingSandEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)