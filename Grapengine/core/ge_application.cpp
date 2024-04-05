#include "core/ge_application.hpp"

#include "core/ge_platform.hpp"
#include "core/ge_time_step.hpp"
#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "input/ge_input.hpp"
#include "layer/ge_imgui_layer.hpp"
#include "layer/ge_layer.hpp"
#include "renderer/ge_camera.hpp"
#include "renderer/ge_renderer.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

using namespace GE;

struct Application::Impl
{
  Ref<Window> window;
  bool running = true;
  bool minimized = false;
  u64 last_frame_time{ 0 };
  std::vector<Ref<Layer>> layers;
  Ref<ImGuiLayer> imgui_layer;

  void Init(std::string_view title,
            u32 width,
            u32 height,
            std::string_view icon,
            const EventCallbackFn& cb)
  {
    window = MakeScope<Window>(WindowProps{ title, width, height, icon }, cb);
    Input::Initialize(window);
    imgui_layer = ImGuiLayer::Make(window);
    imgui_layer->OnAttach();
  }

  void OnEvent(Event& event)
  {
    imgui_layer->OnEvent(event);

    for (const auto& layer : layers | std::views::reverse)
    {
      if (event.IsHandled())
        break;
      layer->OnEvent(event);
    }

    event //
      .When(EvType::WINDOW_CLOSE)
      .Then([this] { Finish(); });
  }

  void Run()
  {
    while (running)
    {
      u64 time_ms = Platform::GetCurrentTimeMS();
      TimeStep step{ time_ms - last_frame_time };
      last_frame_time = time_ms;

      if (!minimized)
      {
        std::ranges::for_each(layers, [&](auto&& l) { l->OnUpdate(step); });

        imgui_layer->Begin();
        std::ranges::for_each(layers, [&](auto&& l) { l->OnImGuiUpdate(); });
        imgui_layer->End();
      }

      window->OnUpdate();
    }
  }

  void Finish() { running = false; }

  void OnDestroy()
  {
    Input::Shutdown();
    imgui_layer->OnDetach();
    std::ranges::for_each(layers, [](auto&& l) { l->OnDetach(); });
  }
};

Application::Application(std::string_view title, u32 width, u32 height, std::string_view icon)
{
  GE_INFO("Application creation")

  m_pimpl = MakeScope<Impl>();
  m_pimpl->Init(title, width, height, icon, [this](auto&& e) { OnEvent(e); });

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);
}

Application::~Application()
{
  m_pimpl->OnDestroy();
  m_pimpl.reset();

  GE_INFO("Application shutdown")
}

void Application::Run() const
{
  m_pimpl->Run();
}

void GE::Application::OnEvent(Event& event)
{
  m_pimpl->OnEvent(event);
}

void GE::Application::AddLayer(const Ref<Layer>& layer) const
{
  m_pimpl->layers.push_back(layer);
  layer->OnAttach();
}

void GE::Application::Close() const
{
  m_pimpl->Finish();
}
