#include "ge_application.hpp"

#include "ge_entities.hpp"
#include "ge_renderer.hpp"
#include "ge_shader.hpp"
#include "ge_window.hpp"

#include <GLFW/glfw3.h>
#include <ge_event_type.hpp>
#include <glad/glad.h>

constexpr auto VERTEX_PER_QUAD = 6;
constexpr auto MAX_QUADS = 100;
constexpr auto MAX_VERTICES = MAX_QUADS * 4;
constexpr auto MAX_INDICES = MAX_QUADS * VERTEX_PER_QUAD;

struct Application::Impl
{
  std::unique_ptr<Window> window;
  bool running = true;
  bool minimized = false;
  std::shared_ptr<VertexArray> vao;

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
  }
};

Application* Application::Impl::instance = nullptr;

Application::Application(std::string&& title, unsigned int width, unsigned int height)
{
  m_pimpl = std::make_unique<Impl>();
  if (m_pimpl->instance != nullptr)
    throw std::exception("App already instantiated!");

  m_pimpl->instance = this;

  m_pimpl->window = std::make_unique<Window>(WindowProps{ title, width, height },
                                             [this](Event& e) { m_pimpl->OnEvent(e); });

  Renderer::Init();
  Renderer::SetViewport(0, 0, width, height);

  m_pimpl->vao = std::make_shared<VertexArray>();
  m_pimpl->vao->Bind();

  float vertices[] = {
    // Positions                       // Colors (R, G, B, A)
    0.000f,  0.000f,  1.000f,  1.0f, 0.0f, 0.0f, 1.0f, // Vertex 0
    0.894f,  0.000f,  0.447f,  0.0f, 1.0f, 0.0f, 1.0f, // Vertex 1
    0.276f,  0.851f,  0.447f,  0.0f, 0.0f, 1.0f, 1.0f, // Vertex 2
    -0.724f, 0.526f,  0.447f,  1.0f, 1.0f, 0.0f, 1.0f, // Vertex 3
    -0.724f, -0.526f, 0.447f,  0.0f, 1.0f, 1.0f, 1.0f, // Vertex 4
    0.276f,  -0.851f, 0.447f,  1.0f, 0.0f, 1.0f, 1.0f, // Vertex 5
    0.724f,  0.526f,  -0.447f, 1.0f, 0.0f, 0.0f, 1.0f, // Vertex 6
    -0.276f, 0.851f,  -0.447f, 0.0f, 1.0f, 0.0f, 1.0f, // Vertex 7
    -0.894f, 0.000f,  -0.447f, 0.0f, 0.0f, 1.0f, 1.0f, // Vertex 8
    -0.276f, -0.851f, -0.447f, 1.0f, 1.0f, 0.0f, 1.0f, // Vertex 9
    0.724f,  -0.526f, -0.447f, 0.0f, 1.0f, 1.0f, 1.0f, // Vertex 10
    0.000f,  0.000f,  -1.000f, 1.0f, 0.0f, 1.0f, 1.0f  // Vertex 11
  };
  auto vbo = std::make_shared<VertexBuffer>(vertices,
                                            (uint32_t)(sizeof(float) * 7 * 12),
                                            m_pimpl->vao->GetID());

  vbo->Bind();
  m_pimpl->vao->SetVertexBuffer(vbo);

  unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
  auto ibo = std::make_shared<IndexBuffer>(indices, 6, m_pimpl->vao->GetID());
  m_pimpl->vao->SetIndexBuffer(ibo);

  auto shader = std::make_shared<Shader>(R"glsl(
#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(in_position, 1.0);
    vertexColor = in_color;
}

)glsl",

                                         R"glsl(
#version 330 core

in vec4 vertexColor;
out vec4 fragColor;

void main()
{
    fragColor = vertexColor;
}

)glsl");

  shader->Bind();
}

Application::~Application() = default;

void Application::Run()
{
  while (m_pimpl->running)
  {
    if (!m_pimpl->minimized)
    {
      Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
      Renderer::Clear();

      Renderer::DrawIndexed(m_pimpl->vao, 6);

      m_pimpl->window->OnUpdate();
    }
  }
}
