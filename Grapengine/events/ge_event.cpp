#include "events/ge_event.hpp"

using namespace GE;

namespace
{
  EventHandler INVALID_HANDLER;
}

struct EventHandler::Impl
{
  EvData data;
  bool handled = false;
};

EventHandler::EventHandler() : m_pimpl(MakeScope<Impl>()) {}

void GE::EventHandler::Then(const std::function<void()>& action)
{
  if (this == &INVALID_HANDLER)
    return;

  action();
  m_pimpl->handled = true;
}

void GE::EventHandler::Then(const std::function<void(const EvData&)>& action)
{
  if (this == &INVALID_HANDLER)
    return;

  action(std::ref(m_pimpl->data));
  m_pimpl->handled = true;
}

void GE::EventHandler::ThenWithRes(const std::function<bool(const EvData&)>& action)
{
  if (this == &INVALID_HANDLER)
    return;

  m_pimpl->handled = action(std::ref(m_pimpl->data));
}

GE::EventHandler::operator bool() const
{
  return m_pimpl->handled;
}
void GE::EventHandler::SetData(EvData data)
{
  m_pimpl->data = data;
}

EventHandler::~EventHandler() = default;

struct Event::Impl
{
  EventHandler handler;
  EvType type;
};

Event::Event(EvType type, EvData data) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->handler.SetData(std::move(data));
  m_pimpl->type = type;
}

Event::~Event() = default;

bool Event::IsHandled() const
{
  return bool(m_pimpl->handler);
}

EvType Event::GetType() const
{
  return m_pimpl->type;
}

EventHandler& GE::Event::When(EvType t)
{
  if (this->GetType() != t)
    return INVALID_HANDLER;

  return m_pimpl->handler;
}
