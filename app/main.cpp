#include "Grapengine/grapengine.hpp"
#include "core/ge_entry_point.hpp"
#include "drawables/ge_mesh.hpp"
#include "imgui.h"
#include "renderer/shader_programs/ge_material_shader.hpp"

#include <drawables/ge_cube.hpp>
#include <iostream>
#include <optional>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

class SimpleLayer : public GE::Layer
{
public:
  SimpleLayer() : GE::Layer("Simple"), m_cam(45.0f, 1280.0f / 720.0f) {}

  void OnAttach() override
  {
    m_simple_shader = GE::MakeScope<GE::PosAndTex2DShader>();
    m_material_shader = GE::MakeScope<GE::MaterialShader>();
    m_light_1 = GE::Cube::Make(GE::Colors::WHITE, m_simple_shader, GE::Texture2D::Make());
    m_light_1->SetScale(0.5f, 0.5f, 0.5f);
    m_light_2 = GE::Cube::Make(GE::Colors::WHITE, m_simple_shader, GE::Texture2D::Make());
    m_light_2->SetScale(0.5f, 0.5f, 0.5f);
    m_world = GE::MakeScope<GE::WorldReference>(m_simple_shader, 10);
    m_mesh = GE::MakeScope<GE::Mesh>("assets/objs/teapot.obj", m_material_shader);
  }

  void OnUpdate(GE::TimeStep ts) override
  {
    GE::Renderer::SetClearColor(GE::Color{ 0x222222FF }.ToVec4());
    GE::Renderer::Clear();

    m_cam.OnUpdate(ts);

    m_simple_shader->Activate();
    m_simple_shader->UpdateViewProjectionMatrix(m_cam.GetViewProjection());
    m_material_shader->Activate();
    m_material_shader->UpdateViewProjectionMatrix(m_cam.GetViewProjection());

    // Draw world reference
    m_world->ShowPlatform(m_show_platform);
    m_world->DrawBatch();

    // Draw 'light' cube
    m_light_1->SetColor(m_light_color_1);
    m_light_1->SetTranslate(m_light_pos_1);
    m_light_1->Draw();
    m_light_2->SetColor(m_light_color_2);
    m_light_2->SetTranslate(m_light_pos_2);
    m_light_2->Draw();

    // Set default ambient light setup
    m_material_shader->Activate();
    m_material_shader->UpdateAmbientColor(m_ambient_color);
    m_material_shader->UpdateAmbientStrength(m_ambient_str);
    m_material_shader->UpdateLightPosition({ m_light_pos_1, m_light_pos_2 });
    m_material_shader->UpdateLightColor({ m_light_color_1, m_light_color_2 });
    m_material_shader->UpdateLightStrength({ m_light_strength, m_light_strength });

    GE::Renderer::SetWireframeRenderMode(m_show_mesh_wired);
    m_mesh->Draw();
    GE::Renderer::SetWireframeRenderMode(false);
  }

  void OnEvent(GE::Event& ev) override { m_cam.OnEvent(ev); }

  void OnImGuiUpdate() override
  {
    ImGui::Checkbox("Wireframe", &m_show_mesh_wired);
    ImGui::Checkbox("Show platform", &m_show_platform);
    ImGui::SliderFloat("AmbientStrength", &m_ambient_str, 0, 1);
    ImGui::SliderFloat3("LightPos1", &m_light_pos_1.x, -10, 10);
    {
      GE::Vec3 light_color = m_light_color_1.ToVec3();
      ImGui::ColorEdit3("LightColor1", &light_color.x);
      m_light_color_1 = GE::Color(light_color);
    }
    ImGui::SliderFloat3("LightPos2", &m_light_pos_2.x, -10, 10);
    {
      GE::Vec3 light_color = m_light_color_2.ToVec3();
      ImGui::ColorEdit3("LightColor2", &light_color.x);
      m_light_color_2 = GE::Color(light_color);
    }
    ImGui::SliderFloat("LightStrength", &m_light_strength, 0, 10);
  }

private:
  GE::Ref<GE::PosAndTex2DShader> m_simple_shader = nullptr;
  GE::Ref<GE::MaterialShader> m_material_shader = nullptr;

  GE::Color m_ambient_color = GE::Colors::WHITE;
  f32 m_ambient_str{ 1.0f };

  GE::Vec3 m_light_pos_1{ 3.8f, 4.8f, 4.7f };
  GE::Vec3 m_light_pos_2{ 3.8f, 4.8f, -4.7f };
  GE::Color m_light_color_1{ 0xFFFFFFFF };
  GE::Color m_light_color_2{ 0xFFFFFFFF };
  f32 m_light_strength{ 5.0f };

  GE::Ref<GE::Cube> m_light_1 = nullptr;
  GE::Ref<GE::Cube> m_light_2 = nullptr;
  GE::Scope<GE::WorldReference> m_world = nullptr;
  bool m_show_platform = false;
  GE::EditorCamera m_cam{};
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