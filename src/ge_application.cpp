#include "core/ge_application.hpp"

#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "renderer/ge_renderer.hpp"

#include <GLFW/glfw3.h>
#include <renderer/ge_camera.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <utils/ge_ipubsub.hpp>

class CameraChangePub : public IPublisher<Mat4>
{
};

struct Application::Impl
{
  Scope<Window> window;
  bool running = true;
  bool minimized = false;
  Scope<Camera> camera;
  CameraChangePub camera_change_pub{};
  Vec2 mouse_press_pos{ 0, 0 };

  static Application* instance;

  void Finish() { running = false; }

  void OnEvent(Event& event)
  {
    Event::Dispatch(EvType::WINDOW_CLOSE,
                    event,
                    [this](auto&&)
                    {
                      Finish();
                      return true;
                    });

    Event::Dispatch(EvType::WINDOW_RESIZE,
                    event,
                    [this](const EvData& ev)
                    {
                      const auto& [_, w, h] = *std::get_if<WindowResizeData>(&ev);
                      Renderer::SetViewport(0, 0, w, h);
                      camera->SetAspectRatio(static_cast<float>(w) / static_cast<float>(h));
                      camera_change_pub.Publish(camera->GetViewProjection());
                      return true;
                    });

    Event::Dispatch(EvType::KEY_PRESS,
                    event,
                    [&](const EvData& ev)
                    {
                      // const auto& [_, k] = *std::get_if<KeyPressData>(&ev);
                      // const float step = 0.25f;
                      // if (k == GLFW_KEY_W)
                      //   cam_pos.z -= step;
                      // else if (k == GLFW_KEY_S)
                      //   cam_pos.z += step;
                      // else if (k == GLFW_KEY_A)
                      //   cam_pos.x -= step;
                      // else if (k == GLFW_KEY_D)
                      //   cam_pos.x += step;
                      // else if (k == GLFW_KEY_Q)
                      //   cam_pos.y += step * 4;
                      // else if (k == GLFW_KEY_E)
                      //   cam_pos.y -= step * 4;
                      //
                      // camera = Camera{ cam_pos, pitch, yaw };
                      // camera_change_pub.Publish(
                      //   camera.GetViewProjection(window->GetWidth(), window->GetHeight()));
                      return true;
                    });

    Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
                    event,
                    [&](const EvData& ev)
                    {
                      const auto& [_, bt] = *std::get_if<MouseButtonPressData>(&ev);
                      if (bt == GLFW_MOUSE_BUTTON_1)
                      {
                        camera->StartMovement(window->GetCursorPos());
                      }
                      return true;
                    });

    Event::Dispatch(EvType::MOUSE_BUTTON_RELEASE,
                    event,
                    [&](const EvData& ev)
                    {
                      const auto& [_, bt] = *std::get_if<MouseButtonReleaseData>(&ev);
                      if (bt == GLFW_MOUSE_BUTTON_1)
                      {
                        camera->StopMovement();
                        camera->MeasureMovement(window->GetCursorPos());
                        camera_change_pub.Publish(camera->GetViewProjection());
                      }
                      return true;
                    });

    Event::Dispatch(EvType::MOUSE_MOVE,
                    event,
                    [&](const EvData& ev)
                    {
                      if (!camera->IsMoving())
                        return false;

                      const auto& [_, x, y] = *std::get_if<MouseMoveData>(&ev);
                      camera->MeasureMovement({ x, y });
                      camera_change_pub.Publish(camera->GetViewProjection());
                      return true;
                    });
  }
};

Application* Application::Impl::instance = nullptr;

Application::Application(std::string&& title, u32 width, u32 height)
{
  m_pimpl = MakeScope<Impl>();
  if (m_pimpl->instance != nullptr)
    throw std::exception("App already instantiated!");

  m_pimpl->instance = this;

  m_pimpl->window = MakeScope<Window>(WindowProps{ title, width, height },
                                      [this](Event& e) { m_pimpl->OnEvent(e); });
  m_pimpl->camera = MakeScope<Camera>(static_cast<float>(width) / static_cast<float>(height),
                                      Vec3{ 5, 2, 5 },
                                      180.0f,
                                      0.0f);

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);

  ShadersLibrary::Get().SubToCameraPub(m_pimpl->camera_change_pub);

  //  {
  ////    Vec3 eye{ 0.0f, 4.0f, 4.0f };
  ////    //    Vec3 target{ 0, 0, 0 };
  ////    //    Vec3 dir = (target - eye).Normalize();
  //    m_pimpl->camera = Camera{
  //      eye,
  //      90.0f,
  //      0.0,
  //      0,
  //    };
  //  }

  m_pimpl->camera_change_pub.Publish(m_pimpl->camera->GetViewProjection());
}

Application::~Application() = default;

void Application::Run(const std::function<void(Window&)>& onLoop) const
{
  while (m_pimpl->running)
  {
    if (!m_pimpl->minimized)
    {

      onLoop(std::ref(*m_pimpl->window));

      m_pimpl->window->OnUpdate();
    }
  }
}
