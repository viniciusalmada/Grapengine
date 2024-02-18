#include "Grapengine/grapengine.hpp"
#include "core/ge_entry_point.hpp"

#include <iostream>

class SimpleLayer : public GE::Layer
{
public:
  SimpleLayer() : GE::Layer("Simple") {}

  void OnAttach() override { m_world = GE::MakeScope<GE::WorldReference>(); }

  void OnUpdate(GE::TimeStep) override
  {
    GE::Renderer::SetClearColor(GE::Color{ 0x222222FF }.ToVec4());
    GE::Renderer::Clear();
    m_world->DrawBatch();
  }

private:
  GE::Scope<GE::WorldReference> m_world = nullptr;
};

class Client : public GE::Application
{
public:
  Client() : Application("Grapengine", 1280, 720, "assets/ic_grapengine.png")
  {
    GE::Ref<SimpleLayer> simple = GE::MakeRef<SimpleLayer>();
    this->AddLayer(simple);
  }
};

GE::Scope<GE::Application> CreateApplication()
{
  return GE::MakeScope<Client>();
}