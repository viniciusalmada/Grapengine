#include "core/ge_application.hpp"

#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "renderer/ge_renderer.hpp"

#include <GLFW/glfw3.h>
#include <renderer/ge_camera.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_color_shader.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>
#include <utils/ge_ipubsub.hpp>

class ResizeChangePub : public IPublisher<Vec2>
{
};

class CameraChangePub : public IPublisher<Mat4>
{
};

static float y = 0;

struct Application::Impl
{
  Scope<Window> window;
  bool running = true;
  bool minimized = false;
  Camera camera{ { 0.0f, 5.0f, 5.0f }, { 0, y, 0 } };
  Ref<Texture2D> tex;
  ResizeChangePub resize_change_pub{};
  CameraChangePub camera_change_pub{};

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
                      resize_change_pub.Publish({ (float)w, (float)h });
                      return true;
                    });
    Event::Dispatch(EvType::KEY_TYPED,
                    event,
                    [&](const EvData& ev)
                    {
                      const auto& [_, k] = *std::get_if<KeyTypedData>(&ev);
                      if (k == GLFW_KEY_UP)
                        y += 1;
                      if (k == GLFW_KEY_DOWN)
                        y -= 1;
                      std::cout << "Pitch = " << y << std::endl;

                      camera = Camera{ { 0.0f, 5.0f, 5.0f }, { 0, y, 0 }};
                      camera_change_pub.Publish(camera.GetViewProjection());

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

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);

  //  m_pimpl->shader->Bind();

  ShadersLibrary::Get().SubToCameraPub(m_pimpl->camera_change_pub);
  ShadersLibrary::Get().SubToResizePub(m_pimpl->resize_change_pub);

  m_pimpl->tex = MakeScope<Texture2D>("assets/dice.jpg");
  m_pimpl->tex->Bind(0);

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

  m_pimpl->camera_change_pub.Publish(m_pimpl->camera.GetViewProjection());

  m_pimpl->resize_change_pub.Publish(
    Vec2{ (float)m_pimpl->window->GetWidth(), (float)m_pimpl->window->GetHeight() });

  //  {
  //    auto sh = std::static_pointer_cast<PosAndColorShader>(
  //      ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_COLOR));
  //    sh->Activate();
  //    sh->UploadWidth((float)m_pimpl->window->GetWidth());
  //    sh->UploadHeight((float)m_pimpl->window->GetHeight());
  //  }
}

Application::~Application() = default;

void Application::Run(const std::function<void(Window&)>& onLoop)
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
