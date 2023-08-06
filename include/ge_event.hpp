#ifndef GRAPHICENGINE3D_GE_EVENT_HPP
#define GRAPHICENGINE3D_GE_EVENT_HPP

#include "ge_event_type.hpp"

class Event
{
public:
  GE3D explicit Event(EvData data);
  GE3D ~Event();

  [[nodiscard]] bool IsHandled() const;
  void GE3D SetHandled(bool handled);

  [[nodiscard]] EvType GE3D GetType() const;

  template <typename Fun>
  [[nodiscard]] static bool Dispatch(EvType t, Event& e, Fun fun)
  {
    EvType type = e.GetType();
    if (type != t)
      return false;

    bool handled = fun(std::ref(e));
    e.SetHandled(handled);
    return true;
  }

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_EVENT_HPP
