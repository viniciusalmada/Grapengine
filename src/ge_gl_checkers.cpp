#include "ge_gl_checkers.hpp"

#include <glad/glad.h>

bool GL::CheckValidVAO(unsigned int vaoID)
{
  // Check valid parent VAO
  bool is_valid_vao = glIsVertexArray(vaoID);
  if (!is_valid_vao)
    return false;

  // Check passed VAO is bound
  uint32_t current_VAO = 0;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (int*)(&current_VAO));

  bool is_any_vao_bound = current_VAO != 0;
  if (!is_any_vao_bound)
    return false;

  bool is_vao_bound = current_VAO == vaoID;
  if (!is_vao_bound)
    return false;

  return true;
}