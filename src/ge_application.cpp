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

  // clang-format off
  // X - left to right axis
  // Y - bottom to top axis
  // Z - back to front axis
  float vertices[] = {
    // Front face
    -0.5f, -0.5f,  +0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
    +0.5f, -0.5f,  +0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
    +0.5f, +0.5f,  +0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, +0.5f,  +0.5f,  1.0f, 0.0f, 0.0f, 1.0f,

    // Right face
    +0.5f, -0.5f,  +0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
    +0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
    +0.5f, +0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
    +0.5f, +0.5f,  +0.5f,  0.0f, 1.0f, 0.0f, 1.0f,

    // Back face
    +0.5f, -0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, +0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
    +0.5f, +0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,

    // Left face
    -0.5f, -0.5f,  -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  +0.5f,  1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, +0.5f,  +0.5f,  1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, +0.5f,  -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,

    // Top face
    -0.5f, +0.5f,  +0.5f,  1.0f, 0.0f, 1.0f, 1.0f,
    +0.5f, +0.5f,  +0.5f,  1.0f, 0.0f, 1.0f, 1.0f,
    +0.5f, +0.5f,  -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, +0.5f,  -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,

    // Bottom face
    -0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
    +0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
    +0.5f, -0.5f,  +0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  +0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
  };
  // clang-format on

  auto vbo = std::make_shared<VertexBuffer>(vertices,
                                            (uint32_t)(sizeof(float) * 7 * 12),
                                            m_pimpl->vao->GetID());

  vbo->Bind();
  m_pimpl->vao->SetVertexBuffer(vbo);

  unsigned int indices[] = {
    0,  1,  2,  2,  3,  0,  // Front face
    4,  5,  6,  6,  7,  4,  // Right face
    8,  9,  10, 10, 11, 8,  // Back face
    12, 13, 14, 14, 15, 12, // Left face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20, // Bottom face
  };
  auto ibo = std::make_shared<IndexBuffer>(indices, 36, m_pimpl->vao->GetID());
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

      Renderer::DrawIndexed(m_pimpl->vao, 36);

      m_pimpl->window->OnUpdate();
    }
  }
}
