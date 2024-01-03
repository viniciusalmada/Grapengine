#include "core/ge_window.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"

#include <exception>
#include <gtest/gtest.h>

TEST(VertexArray, VertexArray)
{
  EXPECT_DEATH({ Ref<VertexArray> vao = MakeRef<VertexArray>(); }, "");

  Scope<Window> window = MakeScope<Window>(WindowProps{ "Test", 1, 1 }, nullptr);
  EXPECT_NE(window, nullptr);

  Ref<VertexArray> vao = MakeRef<VertexArray>();
  EXPECT_TRUE(vao->IsValid());
}

TEST(VertexArray, VertexBuffer)
{
  Scope<Window> window = MakeScope<Window>(WindowProps{ "Test", 1, 1 }, nullptr);
  EXPECT_NE(window, nullptr);

  Ref<VertexArray> vao = MakeRef<VertexArray>();
  vao->Unbind();
  float vertices[] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };
  EXPECT_DEATH(
    { Ref<VertexBuffer> vbo = MakeRef<VertexBuffer>(vertices, sizeof(float) * 6, vao->GetID()); },
    "binding");

}