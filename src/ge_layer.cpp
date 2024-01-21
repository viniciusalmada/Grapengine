#include "layer/ge_layer.hpp"

#include "core/ge_time_step.hpp"

using namespace GE;

struct Layer::Impl
{
  std::string name;
};

GE::Layer::Layer(const std::string& name) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->name = name;
}

Layer::~Layer() = default;
void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate(TimeStep) {}
void Layer::OnEvent(Event&) {}
const std::string& Layer::GetName() const
{
  return m_pimpl->name;
}
