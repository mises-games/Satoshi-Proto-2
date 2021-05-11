#ifndef LOG_HPP
#define LOG_HPP

#include "Base.hpp"
#include <spdlog/spdlog.h>

namespace Satoshi 
{
	class Log
	{
	public:
		static void Init();
		static void End();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define ST_CORE_TRACE(...)		::Satoshi::Log::GetCoreLogger()->trace(__VA_ARGS__);		::Satoshi::Log::GetCoreLogger()->flush()
#define ST_CORE_INFO(...)		::Satoshi::Log::GetCoreLogger()->info(__VA_ARGS__);			::Satoshi::Log::GetCoreLogger()->flush()
#define ST_CORE_WARN(...)		::Satoshi::Log::GetCoreLogger()->warn(__VA_ARGS__);			::Satoshi::Log::GetCoreLogger()->flush()
#define ST_CORE_ERROR(...)		::Satoshi::Log::GetCoreLogger()->error(__VA_ARGS__);		::Satoshi::Log::GetCoreLogger()->flush()
#define ST_CORE_CRITICAL(...)	::Satoshi::Log::GetCoreLogger()->critical(__VA_ARGS__);		::Satoshi::Log::GetCoreLogger()->flush()

#define ST_TRACE(...)			::Satoshi::Log::GetClientLogger()->trace(__VA_ARGS__);		::Satoshi::Log::GetClientLogger()->flush()
#define ST_INFO(...)			::Satoshi::Log::GetClientLogger()->info(__VA_ARGS__);		::Satoshi::Log::GetClientLogger()->flush()
#define ST_WARN(...)			::Satoshi::Log::GetClientLogger()->warn(__VA_ARGS__);		::Satoshi::Log::GetClientLogger()->flush()
#define ST_ERROR(...)			::Satoshi::Log::GetClientLogger()->error(__VA_ARGS__);		::Satoshi::Log::GetClientLogger()->flush()
#define ST_CRITICAL(...)		::Satoshi::Log::GetClientLogger()->critical(__VA_ARGS__);	::Satoshi::Log::GetClientLogger()->flush()

#endif // !LOG_HPP
