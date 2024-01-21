#include "core/ge_application.hpp"

#include "core/ge_window.hpp"
#include "events/ge_event_type.hpp"
#include "renderer/ge_renderer.hpp"

#include <GLFW/glfw3.h>
#include <renderer/ge_camera.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <utils/ge_ipubsub.hpp>

using namespace GE;

struct Application::Impl
{
  Scope<Window> window;
  bool running = true;
  bool minimized = false;

  void Finish() { running = false; }
};

Application::Application(std::string&& title, u32 width, u32 height, std::string&& icon)
{
  m_pimpl = MakeScope<Impl>();

  m_pimpl->instance = this;

  m_pimpl->window = MakeScope<Window>(WindowProps{ title, width, height, icon },
                                      [this](Event& e) { m_pimpl->OnEvent(e); });
  m_pimpl->camera = MakeScope<Camera>(static_cast<float>(width) / static_cast<float>(height),
                                      Vec3{ 5, 2, 5 },
                                      180.0f,
                                      0.0f);

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);
}

Application::~Application() = default;

void Application::Run(const std::function<void(Window&)>& onLoop) const
{
  while (m_pimpl->running)
  {
    if (!m_pimpl->minimized)
    {

      m_pimpl->window->OnUpdate();
    }
  }
}
