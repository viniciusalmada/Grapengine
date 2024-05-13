#ifndef GRAPENGINE_EVENT_HPP
#define GRAPENGINE_EVENT_HPP

#include "core/ge_config.hpp"
#include "ge_event_type.hpp"

#include <functional>

namespace GE
{
  class EventHandler
  {
  public:
    explicit EventHandler();

    void SetData(EvData data);
    void SetHandled();

    void Then(const std::function<void()>& action);
    void Then(const std::function<void(const EvData&)>& action);
    void ThenWithRes(const std::function<bool(const EvData&)>& action);

    explicit operator bool() const;

  private:
    EvData m_data;
    bool m_handled = false;
  };

  class Event
  {
  public:
    explicit Event(EvType type, EvData data = std::monostate());

    [[nodiscard]] bool IsHandled() const;
    void SetHandled();

    [[nodiscard]] EvType GetType() const;
    [[nodiscard]] bool IsType(EvType type) const;

    [[nodiscard]] EventHandler& When(EvType t);

  private:
    EventHandler m_handler;
    EvType m_type = EvType::NONE;
  };

  class EventsHelper
  {
  public:
    static EventsHelper& Get();
    static void Init() { Get(); }
    static void Shutdown() {}

    EventHandler& Invalid() { return m_invalid_handler; }

  private:
    EventHandler m_invalid_handler;
  };
}

#endif
