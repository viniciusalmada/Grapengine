#include "core/ge_application.hpp"

#include "core/ge_platform.hpp"
#include "core/ge_time_step.hpp"
#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "input/ge_input.hpp"
#include "layer/ge_imgui_layer.hpp"
#include "layer/ge_layer.hpp"
#include "renderer/ge_renderer.hpp"
#include "renderer/ge_texture_2d.hpp"

using namespace GE;

Application::Application(std::string_view title, u32 width, u32 height, std::string_view icon)
{
  GE_INFO("Application creation")

  Init(title, width, height, icon, [this](auto&& e) { OnEvent(e); });

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);
}

Application::~Application()
{
  OnDestroy();

  GE_INFO("Application shutdown")
}

void Application::Init(std::string_view title,
                       u32 width,
                       u32 height,
                       std::string_view icon,
                       const EventCallbackFn& cb)
{
  m_window = MakeScope<Window>(WindowProps{ title, width, height, icon }, cb);
  Input::Initialize(m_window);
  m_imgui_layer = ImGuiLayer::Make(m_window);
  m_imgui_layer->OnAttach();
}

void Application::Finish()
{
  m_running = false;
}

void Application::OnDestroy()
{
  Input::Shutdown();
  m_imgui_layer->OnDetach();
  std::ranges::for_each(m_layers, [](auto&& l) { l->OnDetach(); });
}

void Application::Run()
{
  while (m_running)
  {
    u64 time_ms = Platform::GetCurrentTimeMS();
    TimeStep step{ time_ms - m_last_frame_time };
    m_last_frame_time = time_ms;

    if (!m_minimized)
    {
      std::ranges::for_each(m_layers, [&](auto&& l) { l->OnUpdate(step); });

      m_imgui_layer->Begin();
      std::ranges::for_each(m_layers, [&](auto&& l) { l->OnImGuiUpdate(); });
      m_imgui_layer->End();
    }

    m_window->OnUpdate();
  }
}

void GE::Application::OnEvent(Event& event)
{
  m_imgui_layer->OnEvent(event);

  for (const auto& layer : m_layers | std::views::reverse)
  {
    if (event.IsHandled())
      break;
    layer->OnEvent(event);
  }

  event //
    .When(EvType::WINDOW_CLOSE)
    .Then([this] { Finish(); });
}

void GE::Application::AddLayer(const Ref<Layer>& layer)
{
  m_layers.push_back(layer);
  layer->OnAttach();
}

void GE::Application::Close()
{
  Finish();
}

Ref<ImGuiLayer> GE::Application::GetImGuiLayer() const
{
  return m_imgui_layer;
}
