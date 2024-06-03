#include "renderer/ge_renderer.hpp"

#include "core/ge_assert.hpp"
#include "drawables/ge_drawing_object.hpp"
#include "ge_batch_renderer.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_vertex_array.hpp"

#include <glad/glad.h>

using namespace GE;

void OpenGLDebuggerFunc(GLenum source,
                        GLenum type,
                        u32 id,
                        GLenum severity,
                        GLsizei length,
                        const char* message,
                        const void* userParam);

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void OpenGLDebuggerFunc([[maybe_unused]] GLenum source,
                        [[maybe_unused]] GLenum type,
                        [[maybe_unused]] u32 id,
                        [[maybe_unused]] GLenum severity,
                        [[maybe_unused]] GLsizei len,
                        [[maybe_unused]] const char* message,
                        [[maybe_unused]] const void* param)
{
  constexpr auto BUFFER_INFO_ID = 0x20071;
  constexpr auto SHADER_RECOMPILED = 0x20092;
  if (id == BUFFER_INFO_ID || id == SHADER_RECOMPILED)
    return;

  std::stringstream ss;
  ss << "OpenGL Error:\n";
  ss << "  (0x" << std::setfill('0') << std::setw(4) << std::hex << id << "): " << message << '\n';
  GE_ASSERT(false, ss.str().c_str())
}

namespace
{
  Renderer::Statistics s_stats{};
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

void Renderer::SetViewport(u32 x, u32 y, Dimension dim)
{
  glViewport(i32(x), i32(y), i32(dim.width), i32(dim.height));
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

void Renderer::DrawIndexed(const Ptr<VertexArray>& vao, i32 count)
{
  vao->Bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::SetWireframeRenderMode(bool enabled)
{
  glPolygonMode(GL_FRONT_AND_BACK, u32(enabled ? GL_LINE : GL_FILL));
}

void Renderer::DrawObject(const Ptr<DrawingObject>& primitive)
{
  primitive->Bind();
  glDrawElements(GL_TRIANGLES, primitive->IndicesCount(), GL_UNSIGNED_INT, nullptr);
}

const Renderer::Statistics& Renderer::GetStats()
{
  return s_stats;
}

//--------------------------------------------------------------------------------------------------
static BatchRenderer& GetBatchRenderer()
{
  static BatchRenderer batch_renderer;
  return batch_renderer;
}

void Renderer::Batch::Begin()
{
  GE_PROFILE;
  s_stats.vertices_count = 0;
  s_stats.indices_count = 0;
  GetBatchRenderer().Begin();
}

void Renderer::Batch::End()
{
  GE_PROFILE;
  GetBatchRenderer().End();
  s_stats.draw_calls++;
}

void Renderer::Batch::PushObject(Ptr<IShaderProgram> shader,
                                 VerticesData&& vd,
                                 const std::vector<u32>& indices,
                                 const Mat4& modelMat)
{
  GE_PROFILE;
  s_stats.vertices_count += vd.GetCount();
  s_stats.indices_count += indices.size();
  GetBatchRenderer().PushObject(shader, std::move(vd), indices, modelMat);
}
