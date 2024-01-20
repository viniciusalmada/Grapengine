#ifndef GRAPENGINE_EVENT_HPP
#define GRAPENGINE_EVENT_HPP

#include "core/ge_config.hpp"
#include "core/ge_macros.hpp"
#include "ge_event_type.hpp"
namespace GE
{
  class Event
  {
  public:
    GE3D explicit Event(EvData data);
    GE3D ~Event();

    [[nodiscard]] GE3D bool IsHandled() const;
    void GE3D SetHandled(bool handled);

    [[nodiscard]] GE3D EvType GetType() const;
    [[nodiscard]] GE3D const EvData& GetData() const;

    template <typename Fun>
    static void Dispatch(EvType t, Event& e, Fun fun)
    {
      EvType type = e.GetType();
      if (type != t)
        return;

      bool handled = fun(std::ref(e.GetData()));
      e.SetHandled(handled);
    }

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif
