// #ifndef GRAPENGINE_GE_TIME_HPP
// #define GRAPENGINE_GE_TIME_HPP
//
// namespace GE
//{
//   class Timer
//   {
//   public:
//     Timer() { Reset(); }
//
//     void Reset() { m_start = std::chrono::high_resolution_clock ::now(); }
//
//     i64 Nano()
//     {
//       return std::chrono::duration_cast<std::chrono::nanoseconds>(
//                std::chrono::high_resolution_clock::now() - m_start)
//         .count();
//     }
//
////    f32 ElapsedMillis() { return Elapsed() * 1000.0f; }
//
//  private:
//    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
//  };
//
//  class ScopedTimer
//  {
//  public:
//    explicit ScopedTimer(std::string_view name) : m_name(name) {}
//
//    ~ScopedTimer()
//    {
//      i64 time = m_time.Nano();
//      GE_TRACE("[TIMER] {} - {}ns", m_name, time)
//    }
//
//  private:
//    std::string_view m_name;
//    Timer m_time;
//  };
//}
//
// #define TIMER \
//  { \
//    ::GE::ScopedTimer _{ __FUNCTION__ }; \
//  }
//
// #endif // GRAPENGINE_GE_TIME_HPP
