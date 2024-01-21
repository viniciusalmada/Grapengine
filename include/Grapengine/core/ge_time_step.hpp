#ifndef GE_TIME_STEP_HPP
#define GE_TIME_STEP_HPP

namespace GE
{
  class TimeStep
  {
  public:
    explicit TimeStep(const u64 ms) : m_time_ms(ms) {}

    operator u64() const { return m_time_ms; }

    //    [[nodiscard]] u64 GetSeconds() const { return m_time_sec; }
    //
    //    [[nodiscard]] u64 GetMilliSeconds() const { return m_time_sec * 1000.0f; }

  private:
    u64 m_time_ms;
  };
}

#endif // GE_TIME_STEP_HPP
