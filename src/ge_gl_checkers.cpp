#include "ge_gl_checkers.hpp"

#include <glad/glad.h>

bool GL::CheckValidVAO(u32 vaoID)
{
  const bool is_valid_vao = glIsVertexArray(vaoID);
  Assert(is_valid_vao, "This VAO fails the validity test.");

  u32 current_VAO = 0;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (i32*)(&current_VAO));
  const bool is_any_vao_bound = current_VAO != 0;
  Assert(is_any_vao_bound, "No VAO bound");

  const bool is_vao_bound = current_VAO == vaoID;
  Assert(is_vao_bound, "The bound VAO differs from given VAO");

  return true;
}