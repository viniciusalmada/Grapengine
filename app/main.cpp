#include "Grapengine/grapengine.hpp"
#include "core/ge_entry_point.hpp"
#include "drawables/ge_mesh.hpp"

#include <drawables/ge_cube.hpp>
#include <iostream>
#include <optional>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

class SimpleLayer : public GE::Layer
{
public:
  SimpleLayer() : GE::Layer("Simple") {}

  void OnAttach() override
  {
    m_shader = GE::MakeScope<GE::PosAndTex2DShader>();
    m_world = GE::MakeScope<GE::WorldReference>(m_shader);
    m_cam.emplace(45.0f, 1280.0f / 720.0f);
    m_mesh = GE::MakeScope<GE::Mesh>("assets/objs/teapot.obj", m_shader);
  }

  void OnUpdate(GE::TimeStep ts) override
  {
    GE::Renderer::SetClearColor(GE::Color{ 0x222222FF }.ToVec4());
    GE::Renderer::Clear();

    if (m_cam.has_value())
      m_cam.value().OnUpdate(ts);

    m_shader->Activate();
    m_shader->UpdateViewProjectionMatrix(m_cam.value().GetViewProjection());

    m_world->DrawBatch();
    m_mesh->Draw();
  }

  void OnEvent(GE::Event& ev) override { m_cam.value().OnEvent(ev); }

private:
  GE::Ref<GE::IShaderProgram> m_shader = nullptr;
  GE::Scope<GE::WorldReference> m_world = nullptr;
  std::optional<GE::EditorCamera> m_cam{};
  GE::Scope<GE::Mesh> m_mesh{};
};

class Client : public GE::Application
{
public:
  Client() : Application("Grapengine", 1280, 720, "assets/ic_grapengine.png")
  {
    GE_INFO("Client application creation");

    GE::Ref<SimpleLayer> simple = GE::MakeRef<SimpleLayer>();
    this->AddLayer(simple);
  }
};

GE::Scope<GE::Application> CreateApplication()
{
  return GE::MakeScope<Client>();
}