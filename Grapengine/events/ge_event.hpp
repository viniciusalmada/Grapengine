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
    POINTER_TO_IMPLEMENTATION_IDIOM
  };

  class Event
  {
  public:
    GE3D explicit Event(EvType type, EvData data = std::monostate());
    GE3D ~Event();

    [[nodiscard]] GE3D bool IsHandled() const;
    void SetHandled();

    [[nodiscard]] GE3D EvType GetType() const;
    [[nodiscard]] GE3D bool IsType(EvType) const;

    EventHandler& When(EvType t);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif
