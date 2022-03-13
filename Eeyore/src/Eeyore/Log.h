#pragma once
#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
namespace Eeyore {
	class EEYORE_API Log{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
//core log macros
#define ER_CORE_TRACE(...)		::Eeyore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ER_CORE_INFO(...)		::Eeyore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ER_CORE_WARN(...)		::Eeyore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ER_CORE_ERROR(...)		::Eeyore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ER_CORE_FATAL(...)		::Eeyore::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define ER_TRACE(...)			::Eeyore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ER_INFO(...)			::Eeyore::Log::GetClientLogger()->info(__VA_ARGS__)
#define ER_WARN(...)			::Eeyore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ER_ERROR(...)			::Eeyore::Log::GetClientLogger()->error(__VA_ARGS__)
#define ER_FATAL(...)			::Eeyore::Log::GetClientLogger()->fatal(__VA_ARGS__)

//if distribution build
//#define ER_INFO //so to not include in dist build