#ifndef GRAPENGINE_GE_LOGGER_HPP
#define GRAPENGINE_GE_LOGGER_HPP

#include "core/ge_macros.hpp"

#if defined(GE_PLATFORM_WINDOWS)
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #define NOGDI
#endif
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_USE_STD_FORMAT
#include <spdlog/spdlog.h>
#undef far
#undef near
#undef NEAR
#undef FAR

namespace GE
{
  class Logger
  {
  public:
    static void Init();

    static Ref<spdlog::logger>& GetLibLogger();
    static Ref<spdlog::logger>& GetClientLogger();

    static void Shutdown();

  private:
    static Ref<spdlog::logger> s_library_logger;
    static Ref<spdlog::logger> s_client_logger;
  };
}

#if defined(GE_DIST)
  #define GE_TRACE(...)
  #define GE_DEBUG(...)
  #define GE_INFO(...)
  #define GE_WARN(...)
  #define GE_ERROR(...)
  #define GE_CRITICAL(...)
#elif defined(GRAPENGINE_CORE) && !defined(GE_DIST)
  #define GE_TRACE(...) SPDLOG_LOGGER_TRACE(::GE::Logger::GetLibLogger(), __VA_ARGS__);
  #define GE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::GE::Logger::GetLibLogger(), __VA_ARGS__);
  #define GE_INFO(...) SPDLOG_LOGGER_INFO(::GE::Logger::GetLibLogger(), __VA_ARGS__);
  #define GE_WARN(...) SPDLOG_LOGGER_WARN(::GE::Logger::GetLibLogger(), __VA_ARGS__);
  #define GE_ERROR(...) SPDLOG_LOGGER_ERROR(::GE::Logger::GetLibLogger(), __VA_ARGS__);
  #define GE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::GE::Logger::GetLibLogger(), __VA_ARGS__);
#elif !defined(GRAPENGINE_CORE) && !defined(GE_DIST)
  #define GE_TRACE(...) SPDLOG_LOGGER_TRACE(::GE::Logger::GetClientLogger(), __VA_ARGS__);
  #define GE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::GE::Logger::GetClientLogger(), __VA_ARGS__);
  #define GE_INFO(...) SPDLOG_LOGGER_INFO(::GE::Logger::GetClientLogger(), __VA_ARGS__);
  #define GE_WARN(...) SPDLOG_LOGGER_WARN(::GE::Logger::GetClientLogger(), __VA_ARGS__);
  #define GE_ERROR(...) SPDLOG_LOGGER_ERROR(::GE::Logger::GetClientLogger(), __VA_ARGS__);
  #define GE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::GE::Logger::GetClientLogger(), __VA_ARGS__);
#endif

#endif // GRAPENGINE_GE_LOGGER_HPP
