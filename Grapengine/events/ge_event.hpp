#ifndef GRAPENGINE_EVENT_HPP
#define GRAPENGINE_EVENT_HPP

#include "core/ge_config.hpp"
#include "core/ge_macros.hpp"
#include "ge_event_type.hpp"

#include <functional>

namespace GE
{
  class EventHandler
  {
  public:
    explicit EventHandler();
    ~EventHandler();

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
    ~Event();

    [[nodiscard]] bool IsHandled() const;
    void SetHandled();

    [[nodiscard]] EvType GetType() const;
    [[nodiscard]] bool IsType(EvType) const;

    [[nodiscard]] EventHandler& When(EvType t);

  private:
    EventHandler m_handler;
    EvType m_type = EvType::NONE;
  };
}

#endif
