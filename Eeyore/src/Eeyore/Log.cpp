#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "erpch.h" 

namespace Eeyore {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {

		spdlog::set_pattern("%^[%T] %n: %v%$");//timestamp, name of looger, error message, colored
		s_CoreLogger = spdlog::stdout_color_mt("EEYORE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}