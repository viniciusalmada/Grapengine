#include "core/ge_application.hpp"

#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "layer/ge_layer.hpp"
#include "renderer/ge_renderer.hpp"

#include <GLFW/glfw3.h>
#include <core/ge_platform.hpp>
#include <core/ge_time_step.hpp>
#include <renderer/ge_camera.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>
#include <utils/ge_ipubsub.hpp>

using namespace GE;

struct Application::Impl
{
  Scope<Window> window;
  bool running = true;
  bool minimized = false;
  u64 last_frame_time{ 0 };
  std::vector<Ref<Layer>> layers;
  Scope<Camera> camera;

  void Finish() { running = false; }
};

Application::Application(std::string&& title, u32 width, u32 height, std::string&& icon)
{
  m_pimpl = MakeScope<Impl>();

  m_pimpl->window =
    MakeScope<Window>(WindowProps{ title, width, height, icon }, [this](Event& e) { OnEvent(e); });

  const float aspectRatio = width / (float)height;
  m_pimpl->camera = MakeScope<Camera>(aspectRatio, Vec3{ 0, 5, 5 }, Vec3{ 2.5, 0, 2.5 });
  auto shader = std::static_pointer_cast<PosAndTex2DShader>(
    ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_TEXTURE2D));
  shader->UpdateViewProjectionMatrix(m_pimpl->camera->GetViewProjection());

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);
}

Application::~Application() = default;

void Application::Run() const
{
  while (m_pimpl->running)
  {
    u64 time_ms = Platform::GetCurrentTimeMS();
    TimeStep step{ time_ms - m_pimpl->last_frame_time };
    m_pimpl->last_frame_time = time_ms;

    if (!m_pimpl->minimized)
    {
      std::ranges::for_each(m_pimpl->layers, [&](auto&& l) { l->OnUpdate(step); });
    }

    m_pimpl->window->OnUpdate();
  }
}

void GE::Application::OnEvent(Event& ev)
{
  Event::Dispatch(EvType::WINDOW_CLOSE,
                  ev,
                  [this](auto&&)
                  {
                    m_pimpl->Finish();
                    return true;
                  });

  Event::Dispatch(EvType::WINDOW_RESIZE,
                  ev,
                  [this](const EvData& ev)
                  {
                    const auto& [_, w, h] = *std::get_if<WindowResizeData>(&ev);
                    Renderer::SetViewport(0, 0, w, h);
                    return true;
                  });
}

void GE::Application::AddLayer(const Ref<Layer>& layer) const
{
  m_pimpl->layers.push_back(layer);
  layer->OnAttach();
}
