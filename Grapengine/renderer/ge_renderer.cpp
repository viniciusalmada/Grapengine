#include "renderer/ge_renderer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_vertex_array.hpp"

#include <drawables/ge_drawing_object.hpp>
#include <glad/glad.h>

using namespace GE;

void OpenGLDebuggerFunc(GLenum /* source */,
                        GLenum /* type */,
                        u32 id,
                        GLenum /* severity */,
                        GLsizei /* length */,
                        const char* message,
                        const void* /* userParam */)
{
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;

  std::stringstream ss;
  ss << "OpenGL Error:" << std::endl;
  ss << "  (0x" << std::setfill('0') << std::setw(4) << std::hex << id << "): " << message
     << std::endl;
  GE_ASSERT(false, ss.str().c_str())
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
  glDepthFunc(GL_LESS);

  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Renderer::SetViewport(u32 x, u32 y, u32 width, u32 height)
{
  glViewport((i32)x, (i32)y, (i32)width, (i32)height);
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

void Renderer::DrawIndexed(const Ref<VertexArray>& vao, i32 count)
{
  vao->Bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::SetWireframeRenderMode(bool enabled)
{
  glPolygonMode(GL_FRONT_AND_BACK, u32(enabled ? GL_LINE : GL_FILL));
}

void Renderer::DrawObject(const Ref<DrawingObject>& primitive)
{
  primitive->Bind();
  glDrawElements(GL_TRIANGLES, primitive->IndicesCount(), GL_UNSIGNED_INT, nullptr);
}