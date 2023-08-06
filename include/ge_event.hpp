#ifndef GRAPHIC_ENGINE3D_GE_EVENT_HPP
#define GRAPHIC_ENGINE3D_GE_EVENT_HPP

#include "ge_event_type.hpp"

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
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_EVENT_HPP
