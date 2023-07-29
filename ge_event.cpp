#include "ge_event.hpp"

struct Event::Impl
{
  EvData data;
  bool handled = false;
};

Event::Event(EvData data) : m_pimpl(std::make_unique<Impl>())
{
  m_pimpl->data = std::move(data);
}

Event::~Event() = default;

bool Event::IsHandled() const
{
  return m_pimpl->handled;
}

void Event::SetHandled(bool handled)
{
  m_pimpl->handled = handled;
}

EvType Event::GetType() const
{
  return std::visit(TypeGetter{ [](auto&& data) { return std::get<0>(data); } }, m_pimpl->data);
}
