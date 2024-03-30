#include "Grapengine/grapengine.hpp"
#include "core/ge_entry_point.hpp"
#include "drawables/ge_mesh.hpp"
#include "imgui.h"

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
    m_light = GE::Cube::Make(GE::Colors::WHITE, m_shader, GE::Texture2D::Make());
    m_light->SetScale(0.5f, 0.5f, 0.5f);
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
    m_shader->UpdateAmbientColor(GE::Vec3{ 1, 1, 1 });
    m_shader->UpdateAmbientStrength(1.0f);

    m_light->SetTranslate(m_light_pos);
    m_light->Draw();
    m_shader->UpdateLightPosition(m_light_pos);

    m_world->ShowPlatform(m_show_platform);
    m_world->DrawBatch();

    GE::Renderer::SetWireframeRenderMode(m_show_mesh_wired);
    m_shader->UpdateAmbientStrength(0.1f);
    m_mesh->Draw();
    GE::Renderer::SetWireframeRenderMode(false);
  }

  void OnEvent(GE::Event& ev) override { m_cam.value().OnEvent(ev); }

  void OnImGuiUpdate() override
  {
    ImGui::Checkbox("Wireframe", &m_show_mesh_wired);
    ImGui::Checkbox("Show platform", &m_show_platform);
    ImGui::SliderFloat3("LightPos", &m_light_pos.x, -10, 10);
  }

private:
  GE::Ref<GE::PosAndTex2DShader> m_shader = nullptr;
  GE::Vec3 m_light_pos{ 3.8f, 4.8f, 4.7f };
  GE::Ref<GE::Cube> m_light = nullptr;
  GE::Scope<GE::WorldReference> m_world = nullptr;
  bool m_show_platform = false;
  std::optional<GE::EditorCamera> m_cam{};
  GE::Scope<GE::Mesh> m_mesh{};
  bool m_show_mesh_wired = false;
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