#include "ge_renderer.hpp"

#include "ge_entities.hpp"

#include <glad/glad.h>

void OpenGLDebuggerFunc(GLenum /* source */,
                        GLenum /* type */,
                        unsigned int id,
                        GLenum /* severity */,
                        GLsizei /* length */,
                        const char* message,
                        const void* /* userParam */)
{
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;

  std::cerr << "OpenGL Error:" << std::endl;
  std::cerr << "  (0x" << std::setfill('0') << std::setw(4) << std::hex << id << "): " << message
            << std::endl;
}

void Renderer::Init()
{
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(OpenGLDebuggerFunc, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);

  // Enable wireframe mode
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  glViewport(x, y, width, height);
}

void Renderer::SetClearColor(const Vec4& color)
{
  const auto& [r, g, b, a] = color;
  glClearColor(r, g, b, a);
}

void Renderer::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawIndexed(std::shared_ptr<VertexArray> vao, int count)
{
  vao->Bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
