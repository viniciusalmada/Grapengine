#include "ge_application.hpp"

#include "ge_entities.hpp"
#include "ge_renderer.hpp"
#include "ge_shader.hpp"
#include "ge_window.hpp"

#include <ge_event_type.hpp>
#include <ge_transformations.hpp>

constexpr auto VERTEX_PER_QUAD = 6;
constexpr auto MAX_QUADS = 100;
constexpr auto MAX_VERTICES = MAX_QUADS * 4;
constexpr auto MAX_INDICES = MAX_QUADS * VERTEX_PER_QUAD;

const auto VERTEX_SHADER = R"glsl(
#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 out_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = (u_proj) * (u_view) * (u_model) * vec4(in_position, 1.0);
    out_color = in_color;
}

)glsl";
const auto FRAG_SHADER = R"glsl(
#version 330 core

in vec4 out_color;

out vec4 fragColor;

void main()
{
    fragColor = out_color;
}

)glsl";

// clang-format off
  // X - left to right axis
  // Y - bottom to top axis
  // Z - near to far axis
  float vertices[] = {
    // Front face - RED
    -0.5, -0.5,  +0.5,  1.0f, 0.3f, 0.3f, 1.0f,
    +0.5, -0.5,  +0.5,  1.0f, 0.3f, 0.3f, 1.0f,
    +0.5, +0.5,  +0.5,  1.0f, 0.3f, 0.3f, 1.0f,
    -0.5, +0.5,  +0.5,  1.0f, 0.3f, 0.3f, 1.0f,

    // Right face - GREEN
    +0.5, -0.5,  +0.5,  0.3f, 1.0f, 0.3f, 1.0f,
    +0.5, -0.5,  -0.5,  0.3f, 1.0f, 0.3f, 1.0f,
    +0.5, +0.5,  -0.5,  0.3f, 1.0f, 0.3f, 1.0f,
    +0.5, +0.5,  +0.5,  0.3f, 1.0f, 0.3f, 1.0f,

    // Back face - BLUE
    +0.5, -0.5,  -0.5,  0.3f, 0.3f, 1.0f, 1.0f,
    -0.5, -0.5,  -0.5,  0.3f, 0.3f, 1.0f, 1.0f,
    -0.5, +0.5,  -0.5,  0.3f, 0.3f, 1.0f, 1.0f,
    +0.5, +0.5,  -0.5,  0.3f, 0.3f, 1.0f, 1.0f,

    // Left face - YELLOW
    -0.5, -0.5,  -0.5,  1.0f, 1.0f, 0.3f, 1.0f,
    -0.5, -0.5,  +0.5,  1.0f, 1.0f, 0.3f, 1.0f,
    -0.5, +0.5,  +0.5,  1.0f, 1.0f, 0.3f, 1.0f,
    -0.5, +0.5,  -0.5,  1.0f, 1.0f, 0.3f, 1.0f,

    // Top face - MAGENTA
    -0.5, +0.5,  +0.5,  1.0f, 0.3f, 1.0f, 1.0f,
    +0.5, +0.5,  +0.5,  1.0f, 0.3f, 1.0f, 1.0f,
    +0.5, +0.5,  -0.5,  1.0f, 0.3f, 1.0f, 1.0f,
    -0.5, +0.5,  -0.5,  1.0f, 0.3f, 1.0f, 1.0f,

    // Bottom face - CYAN
    -0.5, -0.5,  -0.5,  0.3f, 1.0f, 1.0f, 1.0f,
    +0.5, -0.5,  -0.5,  0.3f, 1.0f, 1.0f, 1.0f,
    +0.5, -0.5,  +0.5,  0.3f, 1.0f, 1.0f, 1.0f,
    -0.5, -0.5,  +0.5,  0.3f, 1.0f, 1.0f, 1.0f,
  };
// clang-format on

const Vec3 cubePositions[] = { Vec3(0.0f, 0.0f, 0.0f),    Vec3(2.0f, 5.0f, -15.0f),
                               Vec3(-1.5f, -2.2f, -2.5f), Vec3(-3.8f, -2.0f, -12.3f),
                               Vec3(2.4f, -0.4f, -3.5f),  Vec3(-1.7f, 3.0f, -7.5f),
                               Vec3(1.3f, -2.0f, -2.5f),  Vec3(1.5f, 2.0f, -2.5f),
                               Vec3(1.5f, 0.2f, -1.5f),   Vec3(-1.3f, 1.0f, -1.5f) };

struct Application::Impl
{
  std::unique_ptr<Window> window;
  bool running = true;
  bool minimized = false;
  std::shared_ptr<VertexArray> vao;
  std::shared_ptr<Shader> shader;

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

  auto vbo =
    std::make_shared<VertexBuffer>(vertices, (uint32_t)(sizeof(vertices)), m_pimpl->vao->GetID());

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

  m_pimpl->shader = std::make_shared<Shader>(VERTEX_SHADER, FRAG_SHADER);

  m_pimpl->shader->Bind();

  //  const Mat4<float> T = Transform::Translate(-15, -15, -15);
  //  const Mat4<float> S = Transform::Scale(0.08f, 0.08f, 0.08f);
  //    const Mat4<float> R = Transform::RotateX(30) * Transform::RotateY(30);

  // Move draw to origin (-5, +5)
  // Scale to normalize coordinates -5x = -0.4 (margin of 0.6)
  // Rotate in X and Y axis after transformations
  const auto M = Transform::Identity(); ///*R **/ S * T;

  m_pimpl->shader->UploadMat4F("u_model", M);

  const auto V =
    Transform::LookAt(Vec3{ 0.0f, 0.0f, 4.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
  /*Transform::LookAt(std::make_tuple(0.f, 0.f, 10.f),
                                        std::make_tuple(0.f, 0.f, 0.f),
                                        std::make_tuple(0.f, 1.f, 0.f));*/
  m_pimpl->shader->UploadMat4F("u_view", V);

  const auto P = Transform::Perspective(60.0f, 1.0f, 0.1f, 100.f);
  std::cout << Transform::ToString(P) << std::endl;
  m_pimpl->shader->UploadMat4F("u_proj", P);
}

Application::~Application() = default;

void Application::Run()
{
  //  long long sec_count = 0;
  //  float rot = 0;
  //  float transl_x = 0;
  //  bool increment = true;
  while (m_pimpl->running)
  {
    auto start = std::chrono::high_resolution_clock ::now();
    if (!m_pimpl->minimized)
    {
      Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
      Renderer::Clear();

      float angle = 0.0f;
      for (auto cubePosition : cubePositions)
      {
        Mat4 i_model = Transform::Translate(cubePosition.x, cubePosition.y, cubePosition.z);
        i_model = i_model * Transform::Rotate(angle, Vec3{ 1.0f, 0.3f, 0.5f });
        m_pimpl->shader->UploadMat4F("u_model", i_model);
        Renderer::DrawIndexed(m_pimpl->vao, 36);
        angle += 20.0f;
      }

      m_pimpl->window->OnUpdate();
    }
    //    auto end = std::chrono::high_resolution_clock ::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    //    sec_count += duration.count();
    //    if (sec_count > 16)
    //    {
    //      m_pimpl->shader->Bind();
    //
    //      Mat4<float> model_matx = Transform::RotateX(rot / 2);
    //      Mat4<float> model_maty = Transform::RotateY(rot += 1);
    //      Mat4<float> model_transl;
    //      if (increment)
    //      {
    //        model_transl = Transform::Translate(transl_x -= 0.01f, 0.0, 0.0);
    //        if (transl_x <= -0.5)
    //          increment = !increment;
    //      }
    //      else
    //      {
    //        model_transl = Transform::Translate(transl_x += 0.01f, 0.0, 0.0);
    //        if (transl_x >= 0.5)
    //          increment = !increment;
    //      }
    //      auto model_mat = model_transl * model_matx * model_maty;
    //      m_pimpl->shader->UploadMat4F("u_model", model_mat);
    //      sec_count = 0;
    //  }
    //    std::cout << "FPS: " << 1000 / duration.count() << std::endl;
  }
}
