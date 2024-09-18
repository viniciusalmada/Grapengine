#include "MainLayer.hpp"

namespace
{
  const std::set<GE::KeyCode>& MoveKeys()
  {
    static const std::set<GE::KeyCode> MOVE_KEYS{ GE::KeyCode::A, GE::KeyCode::D, GE::KeyCode::W,
                                                  GE::KeyCode::S, GE::KeyCode::E, GE::KeyCode::Q };
    return MOVE_KEYS;
  }

  class CameraController final : public GE::ScriptableEntity
  {
  public:
    CameraController(GE::Entity e, GE::Scene& s, u32 w, u32 h) :
        GE::ScriptableEntity(e, s), m_dim(w, h)
    {
    }
    ~CameraController() override = default;

    void OnCreate() override
    {
      auto& camera_comp = m_scene.GetComponent<GE::CameraComponent>(m_entity);
      auto dist =
        camera_comp.GetCamera().GetPosition().Distance(camera_comp.GetCamera().GetTarget());
      const auto& vp = camera_comp.GetCamera().GetViewport();
      m_dim.width = vp.width * dist;
      m_dim.height = vp.height * dist;
    }
    void OnDestroy() override {}
    void OnUpdate(GE::TimeStep ts) override
    {
      if (std::ranges::none_of(MoveKeys(), [](auto&& k) { return GE::Input::IsKeyPressed(k); }))
        return;

      constexpr f32 acc = 0.01f;
      constexpr f32 speed = 0.01f;
      // v(t) = v₀ + a.t
      const f32 incr = speed * ts.f();

      auto& camera_comp = m_scene.GetComponent<GE::CameraComponent>(m_entity);
      if (!camera_comp.IsActive())
        return;

      auto cam_pos = camera_comp.GetCamera().GetPosition();
      auto tar_pos = camera_comp.GetCamera().GetTarget();

      if (GE::Input::IsKeyPressed(GE::KeyCode::A))
      {
        cam_pos.x -= incr;
        tar_pos.x -= incr;
      }
      else if (GE::Input::IsKeyPressed(GE::KeyCode::D))
      {
        cam_pos.x += incr;
        tar_pos.x += incr;
      }
      else if (GE::Input::IsKeyPressed(GE::KeyCode::W))
      {
        cam_pos.y += incr;
        tar_pos.y += incr;
      }
      else if (GE::Input::IsKeyPressed(GE::KeyCode::S))
      {
        cam_pos.y -= incr;
        tar_pos.y -= incr;
      }
      else if (GE::Input::IsKeyPressed(GE::KeyCode::E))
      {
        cam_pos.z -= incr;
        // tar_pos.z -= incr;
      }
      else if (GE::Input::IsKeyPressed(GE::KeyCode::Q))
      {
        cam_pos.z += incr;
        // tar_pos.z += incr;
      }

      camera_comp.GetCamera().SetView(cam_pos, tar_pos);
    }

    const auto& GetDim() const { return m_dim; }

  private:
    GE::Dimension m_dim{};
  };
}

MainLayer::MainLayer() :
    GE::Layer("MainLayer"), m_scene(GE::Scene::Make("MainLayer")), m_camera(0), m_target_plane(0)
{
  // GE::SceneSerializer{m_scene}.DeserializeFromFile("Assets/scenes/Scene_Learn.yaml");
}

MainLayer::~MainLayer() = default;

void MainLayer::OnAttach()
{
  m_scene->OnAttach();

  GE::Vec3 eye{ 0, 0, 12 };
  GE::Vec3 target{ 0, 0, 0 };
  m_camera = m_scene->CreateEntity("Camera");
  m_scene->AddComponent<GE::CameraComponent>(m_camera, eye, target, true, false);
  m_scene->AddComponent<GE::NativeScriptComponent>(m_camera).Bind<CameraController>(1, 1);

  auto amb_light = m_scene->CreateEntity("AmbientLight");
  m_scene->AddComponent<GE::AmbientLightComponent>(amb_light, GE::Colors::WHITE, 0.5f);

  auto light_src = m_scene->CreateEntity("Light");
  m_scene->AddComponent<GE::LightSourceComponent>(light_src, GE::Colors::WHITE, eye, 10.0f, true);

  for (i32 i = 0; i < 10; i++)
  {
    GE::Entity cube = m_scene->CreateEntity("Cube_" + std::to_string(i));
    m_scene->AddComponent<GE::PrimitiveComponent>(cube,
                                                  GE::Cube{}.GetDrawable(),
                                                  GE::Colors::RandomColor());
    m_scene->AddComponent<GE::TransformComponent>(cube);
    auto dir =
      GE::Vec3{ GE::Random::GenFloat(-100.0f, 100.0f), GE::Random::GenFloat(-100.0f, 100.0f), 0 };
    m_directions.emplace(cube, dir.Normalize());
    m_cubes.push_back(cube);
  }

  m_target_plane = m_scene->CreateEntity("TargetPlane");
  m_scene->AddComponent<GE::PrimitiveComponent>(m_target_plane,
                                                GE::Cube{}.GetDrawable(),
                                                GE::Color{ 0x333333 });
  m_scene->AddComponent<GE::TransformComponent>(m_target_plane,
                                                GE::Vec3{ 0.0f, 0.0f, 0.0f },
                                                GE::Vec3{ 12, 12, 0.1 });
}

void MainLayer::OnUpdate(GE::TimeStep step)
{
  Layer::OnUpdate(step);

  GE::Renderer::SetClearColor(GE::Color{ 0x111111 }.ToVec4());
  GE::Renderer::Clear();

  m_scene->OnUpdate(step);

  GE::TransformComponent& tc = m_scene->GetComponent<GE::TransformComponent>(m_target_plane);
  GE::NativeScriptComponent& nsc = m_scene->GetComponent<GE::NativeScriptComponent>(m_camera);
  const GE::Dimension& target_dim = static_cast<CameraController*>(nsc.GetInstance())->GetDim();
  tc.Scale().x = target_dim.width;
  tc.Scale().y = target_dim.height;
  tc.Position().x = m_scene->GetComponent<GE::CameraComponent>(m_camera).GetCamera().GetTarget().x;
  tc.Position().y = m_scene->GetComponent<GE::CameraComponent>(m_camera).GetCamera().GetTarget().y;

  for (GE::Entity& ent : m_cubes)
  {
    GE::TransformComponent& tc = m_scene->GetComponent<GE::TransformComponent>(ent);
    auto& pos = tc.Position();
    pos += m_directions.at(ent) * step.f() * 0.01f;

    if (pos.x > (target_dim.width / 2.5f) || pos.x < (i32(-target_dim.width) / 2.5f))
    {
      GE::Vec3& dir = m_directions.at(ent);
      dir.x = -dir.x;
    }
    else if (pos.y > (target_dim.height / 2.5f) || pos.y < (i32(-target_dim.height) / 2.5f))
    {
      GE::Vec3& dir = m_directions.at(ent);
      dir.y = -dir.y;
    }
  }
}

void MainLayer::OnEvent(GE::Event& event)
{
  Layer::OnEvent(event);
  event                              //
    .When(GE::EvType::WINDOW_RESIZE) //
    .Then(
      [&](const GE::EvData& data)
      {
        auto resize_data = *std::get_if<GE::WindowResizeData>(&data);
        GE::Dimension vp{ resize_data.first, resize_data.second };
        m_scene->OnViewportResize(vp);
        GE::Renderer::SetViewport(0, 0, vp);
      });
}
