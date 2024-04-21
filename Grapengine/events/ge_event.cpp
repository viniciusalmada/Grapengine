#include "events/ge_event.hpp"

using namespace GE;

EventHandler::EventHandler() = default;

void GE::EventHandler::Then(const std::function<void()>& action)
{
  if (this == &EventsHelper::Get().Invalid())
    return;

  action();
  m_handled = true;
}

void GE::EventHandler::Then(const std::function<void(const EvData&)>& action)
{
  if (this == &EventsHelper::Get().Invalid())
    return;

  action(std::ref(m_data));
  m_handled = true;
}

void GE::EventHandler::ThenWithRes(const std::function<bool(const EvData&)>& action)
{
  if (this == &EventsHelper::Get().Invalid())
    return;

  m_handled = action(std::ref(m_data));
}

GE::EventHandler::operator bool() const
{
  return m_handled;
}
void GE::EventHandler::SetData(EvData data)
{
  m_data = data;
}
void GE::EventHandler::SetHandled()
{
  m_handled = true;
}

Event::Event(EvType type, EvData data) : m_type(type)
{
  m_handler.SetData(std::move(data));
}

bool Event::IsHandled() const
{
  return bool(m_handler);
}

EvType Event::GetType() const
{
  return m_type;
}

EventHandler& GE::Event::When(EvType t)
{
  if (this->GetType() != t)
    return EventsHelper::Get().Invalid();

  return m_handler;
}

void GE::Event::SetHandled()
{
  m_handler.SetHandled();
}

bool GE::Event::IsType(EvType t) const
{
  return m_type == t;
}

EventsHelper& EventsHelper::Get()
{
  static EventsHelper helper;
  return helper;
}
