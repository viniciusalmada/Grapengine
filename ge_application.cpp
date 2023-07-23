#include "ge_application.hpp"

#include "ge_entities.hpp"
#include "ge_renderer.hpp"
#include "ge_window.hpp"

constexpr auto VERTEX_PER_QUAD = 6;
constexpr auto MAX_QUADS = 100;
constexpr auto MAX_VERTICES = MAX_QUADS * 4;
constexpr auto MAX_INDICES = MAX_QUADS * VERTEX_PER_QUAD;

struct Application::Impl
{
  std::unique_ptr<Window> window;
  bool running = true;
  bool minimized = false;

  static Application* instance;
};

Application* Application::Impl::instance = nullptr;

Application::Application(std::string&& title, unsigned int width, unsigned int height)
{
  m_pimpl = std::make_unique<Impl>();
  if (m_pimpl->instance != nullptr)
    throw std::exception("App already instantiated!");

  m_pimpl->instance = this;

  m_pimpl->window = std::make_unique<Window>(WindowProps{ title, width, height });

  Renderer::Init();

  // TESTING
  std::shared_ptr<VertexArray> vao = std::make_unique<VertexArray>();
  vao->Bind();

  auto vbo = std::make_shared<VertexBuffer>(MAX_VERTICES * sizeof(SimpleVertexData), vao->GetID());

  vao->SetVertexBuffer(vbo);

  std::vector<uint32_t> quad_indices(MAX_INDICES);
  uint32_t offset = 0;
  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    quad_indices[i + 0] = offset + 0;
    quad_indices[i + 1] = offset + 1;
    quad_indices[i + 2] = offset + 2;

    quad_indices[i + 3] = offset + 3;
    quad_indices[i + 4] = offset + 0;
    quad_indices[i + 5] = offset + 1;
  }
  auto ibo = std::make_shared<IndexBuffer>(quad_indices, vao->GetID());
  vao->SetIndexBuffer(ibo);


}
