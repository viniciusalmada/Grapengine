#include "log/ge_logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

using namespace GE;

struct Logger::Impl
{
  static Ref<spdlog::logger> library_logger;
  static Ref<spdlog::logger> client_logger;
};

Ref<spdlog::logger> Logger::Impl::library_logger = nullptr;
Ref<spdlog::logger> Logger::Impl::client_logger = nullptr;

void Logger::Init()
{
  /* Pattern:
   * %^: start color range (can be used only once)
   * %T: ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
   * %n: Logger's name
   * %v: The actual text to log
   * %$	end color range (can be used only once)
   */
#define SHOW_FILENAMES
#if defined(SHOW_FILENAMES)
  std::string_view filename{ "(%s:%#)" };
#else
  std::string_view filename{ "" };
#endif
  std::string pattern;
  pattern.append("%n %^%L:[%T.%e]");
  pattern.append(filename);
  pattern.append(" %v%$");
  spdlog::set_pattern(pattern);

  Impl::library_logger = spdlog::stdout_color_mt("🍇");
  Impl::library_logger->set_level(spdlog::level::trace);
  Impl::client_logger = spdlog::stdout_color_mt("🍷");
  Impl::client_logger->set_level(spdlog::level::trace);

  GE_INFO("Logger initialized")
}

Ref<spdlog::logger>& GE::Logger::GetLibLogger()
{
  return Impl::library_logger;
}

Ref<spdlog::logger>& GE::Logger::GetClientLogger()
{
  return Impl::client_logger;
}
void GE::Logger::Shutdown()
{
  GE_INFO("Logger shutdown")

  Impl::client_logger.reset();
  Impl::library_logger.reset();
}
