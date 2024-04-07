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
    explicit Event(EvType type, EvData data = std::monostate());
    ~Event();

    [[nodiscard]] bool IsHandled() const;
    void SetHandled();

    [[nodiscard]] EvType GetType() const;
    [[nodiscard]] bool IsType(EvType) const;

    [[nodiscard]] EventHandler& When(EvType t);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif
