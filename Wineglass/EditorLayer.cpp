#include "EditorLayer.hpp"

#include "nativescripts/CamController.hpp"

static constexpr const auto CLEAR_COLOR = 0x222222FF;

using namespace GE;

EditorLayer::EditorLayer() : Layer("EditorLayer"), m_scene_panel(nullptr) {}

void EditorLayer::OnAttach()
{
  m_scene = Scene::Make();

  m_front_camera_entity = m_scene->CreateEntity("Front Camera");
  m_scene->AddComponent<CameraComponent>(m_front_camera_entity,
                                         Vec3{ 0, 0, 10 },
                                         Vec3{ 0, 0, 0 },
                                         true,
                                         false);

  m_oblique_camera_entity = m_scene->CreateEntity("Oblique Camera");
  m_scene->AddComponent<CameraComponent>(m_oblique_camera_entity,
                                         Vec3{ 10, 10, -10 },
                                         Vec3{ 0, 0, 0 },
                                         false,
                                         false);

  auto simple_shader = MakeRef<PosAndTex2DShader>();
  auto material_shader = MakeRef<MaterialShader>();
  auto cube_1_ent = m_scene->CreateEntity("Cube Blue");
  auto cube_2_ent = m_scene->CreateEntity("Cube Red");
  auto cube_3_ent = m_scene->CreateEntity("Cube Green");
  auto cube_4_ent = m_scene->CreateEntity("Cube Yellow");
  m_scene->AddComponent<PrimitiveComponent>(cube_1_ent, Cube::Make(), Colors::BLUE);
  m_scene->AddComponent<PrimitiveComponent>(cube_2_ent, Cube::Make(), Colors::RED);
  m_scene->AddComponent<PrimitiveComponent>(cube_3_ent, Cube::Make(), Colors::GREEN);
  m_scene->AddComponent<PrimitiveComponent>(cube_4_ent, Cube::Make(), Colors::YELLOW);
  m_scene->AddComponent<TransformComponent>(cube_1_ent, Vec3{ 0, 0, 0 }, Vec3{ 1, 1, 1 });
  m_scene->AddComponent<TransformComponent>(cube_2_ent, Vec3{ 1, 1, 1 }, Vec3{ 1, 1, 1 });
  m_scene->AddComponent<TransformComponent>(cube_3_ent, Vec3{ 2, 2, 2 }, Vec3{ 1, 1, 1 });
  m_scene->AddComponent<TransformComponent>(cube_4_ent, Vec3{ 3, 3, 3 }, Vec3{ 1, 1, 1 });
  m_scene->AddComponent<ColorOnlyComponent>(cube_1_ent, simple_shader);
  m_scene->AddComponent<MaterialComponent>(cube_2_ent, material_shader);
  m_scene->AddComponent<MaterialComponent>(cube_3_ent, material_shader);
  m_scene->AddComponent<MaterialComponent>(cube_4_ent, material_shader);

  m_scene->AddComponent<NativeScriptComponent>(m_front_camera_entity).Bind<CamController>();

  m_scene_panel.SetContext(m_scene);

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

  Renderer::SetClearColor(Color{ CLEAR_COLOR }.ToVec4());
  Renderer::Clear();

  m_scene->OnUpdate(ts);

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

  m_scene_panel.OnImGuiRender();

  ImGui::Begin("Stats");
  {
    const auto& stats = Renderer::GetStats();
    ImGui::Text("Renderer stats:");
    ImGui::Text("Draw calls: %05lu", stats.draw_calls);
    ImGui::Text("Vertices count: %lu", stats.vertices_count);
    ImGui::Text("Indices count: %lu", stats.indices_count);
  }
  ImGui::End();

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
  ImGui::Image(TypeUtils::ToVoidPtr(u32(tex)), size, { 0, 1 }, { 1, 0 });
  ImGui::End();
  ImGui::PopStyleVar();

  ImGui::End();
}

void EditorLayer::OnEvent(Event& e)
{
  m_scene->OnEvent(e);
}
