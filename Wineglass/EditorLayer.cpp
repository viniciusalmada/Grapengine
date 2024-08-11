#include "EditorLayer.hpp"

#include "nativescripts/CamController.hpp"

static constexpr const auto CLEAR_COLOR = 0x222222;

using namespace GE;

EditorLayer::EditorLayer() :
    Layer("EditorLayer"),
    m_scene(Scene::Make("Default")),
    m_front_camera_entity(m_scene->CreateEntity("Front Camera")),
    m_oblique_camera_entity(m_scene->CreateEntity("Oblique Camera")),
    m_scene_panel(nullptr)
{
}

void EditorLayer::OnAttach()
{
  auto amb_light = m_scene->CreateEntity("Ambient light");
  auto& c = m_scene->AddComponent<AmbientLightComponent>(amb_light, Colors::WHITE, .25f);
  c.SetActive(true);

  auto l1 = m_scene->CreateEntity("L1");
  m_scene->AddComponent<LightSourceComponent>(l1, Colors::RED, Vec3{ 0, 0, 0 }, 1.0f, true);
  auto l2 = m_scene->CreateEntity("L2");
  m_scene->AddComponent<LightSourceComponent>(l2, Colors::BLUE, Vec3{ 5, 5, 5 }, 1.0f, true);

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

  for (u32 i = 0; i < CUBE_COUNT; i++)
  {
    std::string name{ "Cube " + std::to_string(i) };
    auto cube_ent = m_scene->CreateEntity(name.c_str());
    m_scene->AddComponent<PrimitiveComponent>(cube_ent, Cube::Make(), Colors::WHITE);
    m_scene->AddComponent<TransformComponent>(cube_ent,
                                              Vec3{ Random::GenFloat(-LIM, LIM),
                                                    Random::GenFloat(-LIM, LIM),
                                                    Random::GenFloat(-LIM, LIM) });
  }

  {
    auto mesh_ent = m_scene->CreateEntity("Mesh");
    m_scene->AddComponent<PrimitiveComponent>(mesh_ent,
                                              MakeRef<Mesh>("assets/objs/teapot.obj"),
                                              Colors::WHITE);
    m_scene->AddComponent<TransformComponent>(mesh_ent);
  }

  {
    constexpr auto RADIUS = 0.1f;
    constexpr auto LENGHT = 100.0f;
    auto c_x = m_scene->CreateEntity("CX");
    m_scene->AddComponent<PrimitiveComponent>(
      c_x,
      Cylinder{ Vec3{ 0, 0, 0 }, RADIUS, Vec3{ 1, 0, 0 }, LENGHT }.GetDrawable(),
      Colors::RED);
    m_scene->AddComponent<TransformComponent>(c_x);
    auto c_y = m_scene->CreateEntity("CY");
    m_scene->AddComponent<PrimitiveComponent>(
      c_y,
      Cylinder{ Vec3{ 0, 0, 0 }, RADIUS, Vec3{ 0, 1, 0 }, LENGHT }.GetDrawable(),
      Colors::GREEN);
    m_scene->AddComponent<TransformComponent>(c_y);
    auto c_z = m_scene->CreateEntity("CZ");
    m_scene->AddComponent<PrimitiveComponent>(
      c_z,
      Cylinder{ Vec3{ 0, 0, 0 }, RADIUS, Vec3{ 0, 0, 1 }, LENGHT }.GetDrawable(),
      Colors::BLUE);
    m_scene->AddComponent<TransformComponent>(c_z);
  }

  m_scene->AddComponent<NativeScriptComponent>(m_front_camera_entity).Bind<CamController>();

  m_scene_panel = MakeRef<SceneHierarchyPanel>(m_scene);

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
      if (ImGui::MenuItem("Save Scene"))
      {
        SceneSerializer{ m_scene }.SerializeToFile("SaveScene.json");
      }
      if (ImGui::MenuItem("Load Scene"))
      {
        m_scene = Scene::Make("Untitled");
        m_scene_panel->SetContext(m_scene);
        SceneSerializer{ m_scene }.DeserializeFromFile("SaveScene.json");
        // bool scenes_equal = *m_old_scene == *m_scene;
        // GE_ASSERT(scenes_equal, "Scenes not equal");
      }
      if (ImGui::MenuItem("Exit"))
        Ctrl::App::Close();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("Show demo", nullptr, &show_demo))
      {
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

  m_scene_panel->OnImGuiRender();

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
    //    ImGui::Text("Draw calls: %05" PRIu64, stats.draw_calls);
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
