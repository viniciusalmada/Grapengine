#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

bool GL::IsVAOBound(u32 vaoID)
{
  u32 current_VAO = 0;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (i32*)(&current_VAO));
  const bool is_any_vao_bound = current_VAO != 0;
  if (!is_any_vao_bound)
    return false;

  const bool is_vao_bound = current_VAO == vaoID;
  if (!is_vao_bound)
    return false;

  return true;
}