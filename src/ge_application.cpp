#include "core/ge_application.hpp"

#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "input/ge_input.hpp"
#include "layer/ge_layer.hpp"
#include "renderer/ge_renderer.hpp"

#include <GLFW/glfw3.h>
#include <core/ge_platform.hpp>
#include <core/ge_time_step.hpp>
#include <renderer/ge_camera.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>
#include <utils/ge_ipubsub.hpp>

using namespace GE;

struct Application::Impl
{
  Ref<Window> window;
  Scope<Input> input;
  bool running = true;
  bool minimized = false;
  u64 last_frame_time{ 0 };
  std::vector<Ref<Layer>> layers;
  // Scope<Camera> camera;

  void Finish() { running = false; }

  // void OnMousePress(KeyCode bt) const
  // {
  //   if (!camera->IsAiming() && bt == KeyCode::MOUSE_BT_LEFT)
  //     camera->StartAiming(input->GetMouseXY());
  //
  //   if (!camera->IsAiming() && bt == KeyCode::MOUSE_BT_MIDDLE)
  //     camera->StartMoving(input->GetMouseXY());
  // }
  //
  // void OnMouseMove(f32 x, f32 y) const
  // {
  //   if (camera->IsAiming())
  //     camera->ChangeAimPoint({ x, y });
  //   if (camera->IsMoving())
  //     camera->ChangeLocation({ x, y });
  // }
  //
  // void OnMouseRelease(KeyCode bt) const
  // {
  //   if (camera->IsAiming() && bt == KeyCode::MOUSE_BT_LEFT)
  //   {
  //     camera->StopAiming();
  //     camera->ChangeAimPoint(input->GetMouseXY());
  //   }
  //   if (camera->IsMoving() && bt == KeyCode::MOUSE_BT_MIDDLE)
  //   {
  //     camera->StopMoving();
  //     camera->ChangeLocation(input->GetMouseXY());
  //   }
  // }
  //
  // void OnMouseScroll(f32 diffY) const { camera->SetZoom(-diffY); }
};

Application::Application(std::string_view title, u32 width, u32 height, std::string_view icon)
{
  GE_INFO("Application creation")

  m_pimpl = MakeScope<Impl>();

  m_pimpl->window =
    MakeScope<Window>(WindowProps{ title, width, height, icon }, [this](Event& e) { OnEvent(e); });
  m_pimpl->input = MakeScope<Input>(m_pimpl->window);

  // const f32 aspectRatio = f32(width) / (f32)height;
  // m_pimpl->camera = MakeScope<Camera>(aspectRatio, Vec3{ 0, 5, 5 }, 223.0f, -40);
  //  auto shader = std::static_pointer_cast<PosAndTex2DShader>(
  //    ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_TEXTURE2D));
  // shader->UpdateViewProjectionMatrix(m_pimpl->camera->GetViewProjection());

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
      // if (m_pimpl->camera->IsAiming() || m_pimpl->camera->IsMoving())
      // {
      //   auto shader = std::static_pointer_cast<PosAndTex2DShader>(
      //     ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_TEXTURE2D));
      //   shader->UpdateViewProjectionMatrix(m_pimpl->camera->GetViewProjection());
      // }

      std::ranges::for_each(m_pimpl->layers, [&](auto&& l) { l->OnUpdate(step); });
    }

    m_pimpl->window->OnUpdate();
  }
}

// f32 x = -1;
// f32 y = -1;

void GE::Application::OnEvent(Event& event)
{
  for (const auto& layer : m_pimpl->layers)
    layer->OnEvent(event);

  Event::Dispatch(EvType::WINDOW_CLOSE,
                  event,
                  [this](auto&&)
                  {
                    m_pimpl->Finish();
                    return true;
                  });

  Event::Dispatch(EvType::WINDOW_RESIZE,
                  event,
                  [](const EvData& ev)
                  {
                    const auto& [_, w, h] = *std::get_if<WindowResizeData>(&ev);
                    Renderer::SetViewport(0, 0, w, h);
                    return true;
                  });
  // Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
  //                 event,
  //                 [this](const EvData& ev)
  //                 {
  //                   const auto& [_, bt] = *std::get_if<MouseButtonPressData>(&ev);
  //                   m_pimpl->OnMousePress(bt);
  //                   return true;
  //                 });
  //
  // Event::Dispatch(EvType::MOUSE_BUTTON_RELEASE,
  //                 event,
  //                 [this](const EvData& ev)
  //                 {
  //                   const auto& [_, bt] = *std::get_if<MouseButtonReleaseData>(&ev);
  //                   m_pimpl->OnMouseRelease(bt);
  //                   return true;
  //                 });
  //
  // Event::Dispatch(EvType::MOUSE_MOVE,
  //                 event,
  //                 [this](const EvData& ev)
  //                 {
  //                   const auto& [_, x, y] = *std::get_if<MouseMoveData>(&ev);
  //                   m_pimpl->OnMouseMove(x, y);
  //                   return true;
  //                 });
  //
  // Event::Dispatch(EvType::MOUSE_SCROLL,
  //                 event,
  //                 [this](const EvData& ev)
  //                 {
  //                   const auto& [_, x, y] = *std::get_if<MouseScrollData>(&ev);
  //                   m_pimpl->OnMouseScroll(y);
  //                   auto shader = std::static_pointer_cast<PosAndTex2DShader>(
  //                     ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_TEXTURE2D));
  //                   shader->UpdateViewProjectionMatrix(m_pimpl->camera->GetViewProjection());
  //                   return true;
  //                 });
}

void GE::Application::AddLayer(const Ref<Layer>& layer) const
{
  m_pimpl->layers.push_back(layer);
  layer->OnAttach();
}
