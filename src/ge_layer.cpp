#include "layer/ge_layer.hpp"

#include "core/ge_time_step.hpp"

using namespace GE;

struct Layer::Impl
{
  std::string name;
};

GE::Layer::Layer(std::string_view name) : m_pimpl(MakeScope<Impl>())
{
  GE_INFO("Create layer <{}>", name)

  m_pimpl->name = name;
}

Layer::~Layer()
{
  GE_INFO("Destroy layer <{}>", m_pimpl->name)
}
void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate(TimeStep) {}
void Layer::OnEvent(Event&) {}
const std::string& Layer::GetName() const
{
  return m_pimpl->name;
}
void Layer::OnImGuiUpdate() {}
