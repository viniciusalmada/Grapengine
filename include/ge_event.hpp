#ifndef GRAPHICENGINE3D_GE_EVENT_HPP
#define GRAPHICENGINE3D_GE_EVENT_HPP

#include "ge_event_type.hpp"

class Event
{
  explicit Event(EvData data);
  ~Event();

  [[nodiscard]] bool IsHandled() const;
  void SetHandled(bool handled);

  [[nodiscard]] EvType GetType() const;

  template <typename Fun>
  [[nodiscard]] static bool Dispatch(EvType t, Event& e, const Fun& fun)
  {
    EvType type = e.GetType();
    if (type != t)
      return false;

    e.SetHandled(fun(e));
    return true;
  }

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_EVENT_HPP
