#include <Satoshi/stpch.hpp>
#include "Log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Satoshi::Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Satoshi::Log::s_ClientLogger;

void Satoshi::Log::Init()
{
	std::vector<spdlog::sink_ptr> logSinks;
		
	logSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	logSinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/Satoshi.log"));

	logSinks[0]->set_pattern("%^[%T] %n: %v%$");
	logSinks[1]->set_pattern("%[%T] [%l] %n: %v%$");
	
	s_CoreLogger = std::make_shared<spdlog::logger>("SATOSHI", begin(logSinks), end(logSinks));
	spdlog::register_logger(s_CoreLogger);
	s_CoreLogger->set_level(spdlog::level::trace);
	s_CoreLogger->flush_on(spdlog::level::trace);

	s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
	spdlog::register_logger(s_ClientLogger);
	s_ClientLogger->set_level(spdlog::level::trace);
	s_ClientLogger->flush_on(spdlog::level::trace);
}

void Satoshi::Log::End()
{
	s_CoreLogger->~logger();
	s_ClientLogger->~logger();
}
