#pragma once
#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
namespace FallingSandGame
{
	class FSG_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;}
	private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
//core log 
#define FSG_CORE_ERROR(...)		::FallingSandGame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FSG_CORE_WARN(...)		::FallingSandGame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FSG_CORE_INFO(...)		::FallingSandGame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FSG_CORE_TRACE(...)		::FallingSandGame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FSG_CORE_FATAL(...)		::FallingSandGame::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log 
#define FSG_ERROR(...)		::FallingSandGame::Log::GetClientLogger()->error(__VA_ARGS__)
#define FSG_WARN(...)		::FallingSandGame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FSG_INFO(...)		::FallingSandGame::Log::GetClientLogger()->info(__VA_ARGS__)
#define FSG_TRACE(...)		::FallingSandGame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FSG_FATAL(...)		::FallingSandGame::Log::GetClientLogger()->fatal(__VA_ARGS__)