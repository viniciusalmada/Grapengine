#include "ge_application.hpp"

#include "ge_event_type.hpp"
#include "ge_renderer.hpp"
#include "ge_shader.hpp"
#include "ge_vertex_array.hpp"
#include "ge_window.hpp"

struct Application::Impl
{
  Scope<Window> window;
  bool running = true;
  bool minimized = false;
  Ref<ShaderProgram> shader;

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
                    [](const EvData& ev)
                    {
                      const auto& [_, w, h] = *std::get_if<WindowResizeData>(&ev);
                      Renderer::SetViewport(0, 0, w, h);
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

  m_pimpl->shader =
    MakeRef<ShaderProgram>(std::filesystem::path{ "assets/shaders/PositionAndColor.vshader.glsl" },
                           std::filesystem::path{ "assets/shaders/PositionAndColor.fshader.glsl" });

  m_pimpl->shader->Bind();
  m_pimpl->shader->UploadFloat("width", (float)m_pimpl->window->GetWidth());
  m_pimpl->shader->UploadFloat("height", (float)m_pimpl->window->GetHeight());
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
