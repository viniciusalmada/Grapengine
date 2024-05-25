#include "layer/ge_layer.hpp"

#include "core/ge_time_step.hpp"
#include "profiling/ge_profiler.hpp"

using namespace GE;

GE::Layer::Layer(std::string_view name) : m_name(name)
{
  GE_PROFILE;
  GE_INFO("Create layer <{}>", name)
}

Layer::~Layer()
{
  GE_PROFILE;
  GE_INFO("Destroy layer <{}>", m_name)
}
void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate(TimeStep /*ts*/) {}
void Layer::OnEvent(Event& /*ev*/) {}
const std::string& Layer::GetName() const
{
  return m_name;
}
void Layer::OnImGuiUpdate() {}
