#include "EditorLayer.hpp"

#include "nativescripts/CamController.hpp"

static constexpr const auto CLEAR_COLOR = 0x222222FF;

using namespace GE;

namespace
{
  //  constexpr auto DEFAULT_FOV = 45.0f;
  //  constexpr auto HD_RATIO = 1280.0f / 720.0f;

  DISABLE_WARNING_PUSH
  WARN_CONVERSION_OF_GREATER_SIZE
  void* SafeConversion(u32 i)
  {
    return reinterpret_cast<void*>(i); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
  }
  DISABLE_WARNING_POP
}

EditorLayer::EditorLayer() : Layer("EditorLayer") {}

void EditorLayer::OnAttach()
{
  m_scene = Scene::Make();

  m_front_camera_entity = m_scene->CreateEntity("Front Camera");
  m_scene->AddComponent<CameraComponent>(m_front_camera_entity, true, false);
  m_scene->AddComponent<TransformComponent>(
    m_front_camera_entity,
    Transform::LookAt({ 0, 0, -10 }, { 0, 0, 0 }, { 0, 1, 0 }));

  m_oblique_camera_entity = m_scene->CreateEntity("Oblique Camera");
  m_scene->AddComponent<CameraComponent>(m_oblique_camera_entity, false, false);
  m_scene->AddComponent<TransformComponent>(
    m_oblique_camera_entity,
    Transform::LookAt({ 10, 10, -10 }, { 0, 0, 0 }, { 0, 1, 0 }));

  //  auto camera_ent = m_scene->CreateEntity("Camera");
  //  m_scene->AddComponent<CameraComponent>(camera_ent, cam);

  Ref<IShaderProgram> simple_shader = MakeRef<PosAndTex2DShader>();
  Ref<Cube> cube = Cube::Make(Colors::BLUE, simple_shader, Texture2D::Make());
  auto cube_ent = m_scene->CreateEntity("Cube");
  m_scene->AddComponent<PrimitiveComponent>(cube_ent, cube->GetVAO());
  m_scene->AddComponent<TransformComponent>(cube_ent, Mat4{});
  m_scene->AddComponent<ColorOnlyComponent>(cube_ent, simple_shader);

  m_scene->AddComponent<NativeScriptComponent>(m_front_camera_entity);
  m_scene->GetComponent<NativeScriptComponent>(m_front_camera_entity).Bind<CamController>();

  m_scene->AddComponent<NativeScriptComponent>(m_oblique_camera_entity);
  m_scene->GetComponent<NativeScriptComponent>(m_oblique_camera_entity).Bind<CamController>();

  //
  //
  //  m_simple_shader = MakeRef<PosAndTex2DShader>();
  //  m_mat_shader = MakeRef<MaterialShader>();
  //  m_light_1 = Cube::Make(Colors::WHITE, m_simple_shader, Texture2D::Make());
  //  m_light_1->SetScale(0.5, 0.5, 0.5);
  //  m_light_2 = Cube::Make(Colors::WHITE, m_simple_shader, Texture2D::Make());
  //  m_light_2->SetScale(0.5, 0.5, 0.5);
  //  m_world_ref = MakeRef<WorldReference>(m_simple_shader, 20);
  //  m_mesh = MakeRef<Mesh>("assets/objs/teapot.obj", m_mat_shader);
  m_fb = Framebuffer::Make({ 1280, 720 });
}

void EditorLayer::OnUpdate(TimeStep ts)
{
  if (m_fb->GetDimension() != m_viewport_dimension)
  {
    m_fb->Resize(m_viewport_dimension);
    m_scene->OnViewportResize(m_viewport_dimension);
  }

  m_fb->Bind();

  //  if (/*m_viewport_focused &&*/ m_viewport_hovered)
  //    m_cam.OnUpdate(ts);

  Renderer::SetClearColor(Color{ CLEAR_COLOR }.ToVec4());
  Renderer::Clear();

  m_scene->OnUpdate(ts);

  //  m_simple_shader->Activate();
  //  m_simple_shader->UpdateViewProjectionMatrix(m_cam.GetViewProjection());
  //  m_mat_shader->Activate();
  //  m_mat_shader->UpdateViewProjectionMatrix(m_cam.GetViewProjection());
  //
  //  m_world_ref->DrawBatch();
  //
  //  // Draw 'light' cube
  //  m_light_1->SetColor(m_light_color_1);
  //  m_light_1->SetTranslate(m_light_pos_1);
  //  m_light_1->Draw();
  //  m_light_2->SetColor(m_light_color_2);
  //  m_light_2->SetTranslate(m_light_pos_2);
  //  m_light_2->Draw();
  //
  //  // Set default ambient light setup
  //  m_mat_shader->Activate();
  //  m_mat_shader->UpdateAmbientColor(m_ambient_color);
  //  m_mat_shader->UpdateAmbientStrength(m_ambient_str);
  //  m_mat_shader->UpdateLightPosition({ m_light_pos_1, m_light_pos_2 });
  //  m_mat_shader->UpdateLightColor({ m_light_color_1, m_light_color_2 });
  //  m_mat_shader->UpdateLightStrength({ m_light_strength, m_light_strength });
  //
  //  m_mesh->Draw();

  m_fb->Unbind();
}

void EditorLayer::OnImGuiUpdate()
{
  static ImGuiDockNodeFlags dock_node_flags = ImGuiDockNodeFlags_None;

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  ImGuiViewport* vp = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(vp->Pos);
  ImGui::SetNextWindowSize(vp->Size);
  ImGui::SetNextWindowViewport(vp->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
  window_flags |= ImGuiWindowFlags_NoTitleBar              //
                  | ImGuiWindowFlags_NoCollapse            //
                  | ImGuiWindowFlags_NoResize              //
                  | ImGuiWindowFlags_NoMove                //
                  | ImGuiWindowFlags_NoBringToFrontOnFocus //
                  | ImGuiWindowFlags_NoNavFocus;

  if (dock_node_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  static auto dockspace_open = true;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Dockspace demo", &dockspace_open, window_flags);
  ImGui::PopStyleVar();

  ImGui::PopStyleVar(2);

  ImGuiIO& io = ImGui::GetIO();
  //  io.IniFilename = nullptr;
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
  {
    ImGuiID dock_id = ImGui::GetID("MyDock");
    ImGui::DockSpace(dock_id, ImVec2{ 0, 0 }, dock_node_flags);
  }

  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit"))
        Ctrl::App::Close();
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

  ImGui::Begin("Settings");

  static int cam = 0;
  ImGui::RadioButton("Front camera", &cam, 0);
  ImGui::RadioButton("Oblique camera", &cam, 1);

  m_scene->GetComponent<CameraComponent>(m_front_camera_entity).active = cam == 0;
  m_scene->GetComponent<CameraComponent>(m_oblique_camera_entity).active = cam == 1;

  ImGui::End();

  //  ImGui::Begin("Settings");
  //  ImGui::SliderFloat("AmbientStrength", &m_ambient_str, 0, 1);
  //  ImGui::SliderFloat3("LightPos1", &m_light_pos_1.x, -10, 10);
  //  {
  //    Vec3 light_color = m_light_color_1.ToVec3();
  //    ImGui::ColorEdit3("LightColor1", &light_color.x);
  //    m_light_color_1 = Color(light_color);
  //  }
  //  ImGui::SliderFloat3("LightPos2", &m_light_pos_2.x, -10, 10);
  //  {
  //    Vec3 light_color = m_light_color_2.ToVec3();
  //    ImGui::ColorEdit3("LightColor2", &light_color.x);
  //    m_light_color_2 = Color(light_color);
  //  }
  //  ImGui::SliderFloat("LightStrength", &m_light_strength, 0, 10);
  //  ImGui::End();

  ImGui::Begin("Viewport");

  //  m_viewport_focused = ImGui::IsWindowFocused();
  m_viewport_hovered = ImGui::IsWindowHovered();
  Ctrl::App::AllowImGuiEvents(/*!m_viewport_focused ||*/ !m_viewport_hovered);
  ImVec2 vp_size = ImGui::GetContentRegionAvail();
  m_viewport_dimension.width = u32(vp_size.x);
  m_viewport_dimension.height = u32(vp_size.y);
  RendererID tex = m_fb->GetColorAttachmentID();
  const auto [w, h] = m_fb->GetDimension();
  ImVec2 size{ f32(w), f32(h) };
  ImGui::Image(SafeConversion(u32(tex)), size, { 0, 1 }, { 1, 0 });
  ImGui::End();
  ImGui::PopStyleVar();

  ImGui::End();
}

void EditorLayer::OnEvent(Event& e)
{
  m_scene->OnEvent(e);
  //  m_cam.OnEvent(e);
}
