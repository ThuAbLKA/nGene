#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace nGene {
	class NGN_API Log
	{
	public: 
		static void Init(const char* name);

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// core log macors
#define NGN_CORE_TRACE(...)    ::nGene::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NGN_CORE_INFO(...)     ::nGene::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NGN_CORE_WARN(...)     ::nGene::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NGN_CORE_ERROR(...)    ::nGene::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NGN_CORE_CRITICAL(...) ::nGene::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macors
#define NGN_CLIENT_TRACE(...)    ::nGene::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NGN_CLIENT_INFO(...)     ::nGene::Log::GetClientLogger()->info(__VA_ARGS__)
#define NGN_CLIENT_WARN(...)     ::nGene::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NGN_CLIENT_ERROR(...)    ::nGene::Log::GetClientLogger()->error(__VA_ARGS__)
#define NGN_CLIENT_CRITICAL(...) ::nGene::Log::GetClientLogger()->critical(__VA_ARGS__)