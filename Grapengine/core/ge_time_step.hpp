#ifndef GE_TIME_STEP_HPP
#define GE_TIME_STEP_HPP

namespace GE
{
  class TimeStep
  {
  public:
    explicit TimeStep(const u64 ms) : m_time_ms(ms) {}

    [[nodiscard]] f32 f() const { return static_cast<f32>(m_time_ms); }

    [[nodiscard]] u64 u() const { return m_time_ms; }

  private:
    u64 m_time_ms;
  };
}

#endif // GE_TIME_STEP_HPP
