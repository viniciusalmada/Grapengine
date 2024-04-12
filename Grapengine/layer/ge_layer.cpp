#include "layer/ge_layer.hpp"

#include "core/ge_time_step.hpp"

using namespace GE;

GE::Layer::Layer(std::string_view name) : m_name(name)
{
  GE_INFO("Create layer <{}>", name)

  m_name = name;
}

Layer::~Layer()
{
  GE_INFO("Destroy layer <{}>", m_name)
}
void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate(TimeStep) {}
void Layer::OnEvent(Event&) {}
const std::string& Layer::GetName() const
{
  return m_name;
}
void Layer::OnImGuiUpdate() {}
