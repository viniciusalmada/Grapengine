#include "log/ge_logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

using namespace GE;

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
  const std::string_view filename{ "(%s:%#)" };
#else
  std::string_view filename{ "" };
#endif
  std::string pattern;
  pattern.append("%n %^%L:[%T.%e]");
  pattern.append(filename);
  pattern.append(" %v%$");
  spdlog::set_pattern(pattern);

  Logger& logger = GetInstance();

  logger.m_library_logger = spdlog::stdout_color_mt("🍇");
  logger.m_library_logger->set_level(spdlog::level::trace);
  logger.m_client_logger = spdlog::stdout_color_mt("🍷");
  logger.m_client_logger->set_level(spdlog::level::trace);

  GE_INFO("Logger initialized")
}

Ptr<spdlog::logger>& GE::Logger::GetLibLogger()
{
  return Logger::GetInstance().m_library_logger;
}

Ptr<spdlog::logger>& GE::Logger::GetClientLogger()
{
  return Logger::GetInstance().m_client_logger;
}
void GE::Logger::Shutdown()
{
  GE_INFO("Logger shutdown")

  Logger::GetInstance().m_client_logger.reset();
  Logger::GetInstance().m_library_logger.reset();
}

Logger& Logger::GetInstance()
{
  static Logger logger{};
  return logger;
}
