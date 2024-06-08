#include "EditorLayer.hpp"

#include "nativescripts/CamController.hpp"

static constexpr const auto CLEAR_COLOR = 0x222222FF;

using namespace GE;

EditorLayer::EditorLayer() :
    Layer("EditorLayer"),
    m_scene(Scene::Make()),
    m_front_camera_entity(m_scene->CreateEntity("Front Camera")),
    m_oblique_camera_entity(m_scene->CreateEntity("Oblique Camera")),
    m_scene_panel(nullptr)
{
}

void EditorLayer::OnAttach()
{
  m_scene->AddComponent<CameraComponent>(m_front_camera_entity,
                                         Vec3{ 0, 0, 10 },
                                         Vec3{ 0, 0, 0 },
                                         true,
                                         false);
  m_scene->AddComponent<CameraComponent>(m_oblique_camera_entity,
                                         Vec3{ 10, 10, -10 },
                                         Vec3{ 0, 0, 0 },
                                         false,
                                         false);

  constexpr auto CUBE_COUNT = 1'00;
  constexpr auto LIM = 20.0f;

  //  auto simple_shader = MakeRef<PosAndTex2DShader>();
  auto material_shader = MakeRef<MaterialShader>();

  //  bool use_solid_color = true;
  for (u32 i = 0; i < CUBE_COUNT; i++)
  {
    std::string name{ "Cube " + std::to_string(i) };
    auto cube_ent = m_scene->CreateEntity(name.c_str());
    m_scene->AddComponent<PrimitiveComponent>(cube_ent, Cube::Make(), Colors::RandomColor());
    m_scene->AddComponent<TransformComponent>(cube_ent,
                                              Vec3{ Random::GenFloat(-LIM, LIM),
                                                    Random::GenFloat(-LIM, LIM),
                                                    Random::GenFloat(-LIM, LIM) });
    //    if (use_solid_color)
    //      m_scene->AddComponent<ColorOnlyComponent>(cube_ent, simple_shader);
    //    else
    m_scene->AddComponent<MaterialComponent>(cube_ent, material_shader);
    //    use_solid_color = !use_solid_color;
  }

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

static u64 s_timer_checker = 0;

void EditorLayer::OnImGuiUpdate(TimeStep ts)
{
  static ImGuiDockNodeFlags dock_node_flags = ImGuiDockNodeFlags_None;

  ImGuiViewport* vp = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(vp->Pos);
  ImGui::SetNextWindowSize(vp->Size);
  ImGui::SetNextWindowViewport(vp->ID);
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_None                    //
                                  | ImGuiWindowFlags_MenuBar               //
                                  | ImGuiWindowFlags_NoDocking             //
                                  | ImGuiWindowFlags_NoTitleBar            //
                                  | ImGuiWindowFlags_NoCollapse            //
                                  | ImGuiWindowFlags_NoResize              //
                                  | ImGuiWindowFlags_NoMove                //
                                  | ImGuiWindowFlags_NoBringToFrontOnFocus //
                                  | ImGuiWindowFlags_NoNavFocus;

  //  if (dock_node_flags & ImGuiDockNodeFlags_PassthruCentralNode)
  //    window_flags |= ImGuiWindowFlags_NoBackground;

  static auto dockspace_open = true;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Dockspace", &dockspace_open, window_flags);
  ImGui::PopStyleVar(3);

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigDockingWithShift = true;
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
  {
    ImGuiID dock_id = ImGui::GetID("MyDock");
    ImGui::DockSpace(dock_id, ImVec2{ 0, 0 }, dock_node_flags);
  }

  static bool show_demo = false;
  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit"))
        Ctrl::App::Close();
      if (ImGui::MenuItem("Show demo", nullptr, &show_demo))
      {
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

  m_scene_panel.OnImGuiRender();

  ImGui::Begin("Stats");
  {
    static Renderer::Statistics stats{};
    static f64 fps{};
    if (s_timer_checker > 1'000)
    {
      stats = Renderer::GetStats();
      fps = static_cast<double>(Ctrl::App::GetFPS());
      s_timer_checker = 0;
    }
    ImGui::Text("Renderer stats:");
    ImGui::Text("Draw calls: %05" PRIu64, stats.draw_calls);
    ImGui::Text("Vertices count: %" PRIu64, stats.vertices_count);
    ImGui::Text("Indices count: %" PRIu64, stats.indices_count);
    ImGui::Text("Time spent to batch: %" PRIu64 "ms", stats.time_spent);
    ImGui::Text("Batches per second: %" PRIu64, 1'000 / stats.time_spent);
    ImGui::Text("FPS %.2f", fps);
    s_timer_checker += ts.u();
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

  if (show_demo)
    ImGui::ShowDemoWindow(nullptr);
}

void EditorLayer::OnEvent(Event& e)
{
  m_scene->OnEvent(e);
}
