#include "ge_ec_registry.hpp"

using namespace GE;

void ECRegistry::Each(const std::function<void(Entity)>& action) const
{
  std::ranges::for_each(m_entities, action);
}
