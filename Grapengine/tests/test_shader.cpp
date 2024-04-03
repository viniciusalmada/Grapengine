#include "core/ge_memory.hpp"
#include "core/ge_window.hpp"
#include "renderer/ge_shader.hpp"

#include <exception>
#include <gtest/gtest.h>

const std::string INVALID_VSHADER = R"(
#version 330 core
layout (location = 0) in vec3 in_position;
out vec4 out_color;
void main()
{
    gl_Position = vec4(in_position, 1.0f);
    out_color = in_color;
})";

const std::string INVALID_FSHADER = R"(
#version 330 core
in vec4 out_color;
out vec4 fragColor;
void mainn()
{
    fragColor = out_color;
})";
const std::string VALID_VSHADER = R"(
#version 330 core
layout (location = 0) in vec3 in_position;
out vec4 out_color;
void main()
{
    gl_Position = vec4(in_position, 1.0f);
    out_color = vec4(0,0,0,1);
})";

const std::string VALID_FSHADER = R"(
#version 330 core
in vec4 out_color;
out vec4 fragColor;
void main()
{
    fragColor = out_color;
})";

TEST(ShaderProgram, Shader)
{
  using namespace GE;
  Scope<Window> window = MakeScope<Window>(WindowProps{ "Test", 1, 1, {}}, nullptr);
  EXPECT_NE(window, nullptr);

  ASSERT_DEATH({ Shader shader_program(std::string{ "" }, std::string{ "" }); }, "linking");
  ASSERT_DEATH({ Shader shader_program(INVALID_VSHADER, INVALID_FSHADER); }, "Vertex");
  ASSERT_DEATH({ Shader shader_program(VALID_VSHADER, INVALID_FSHADER); }, "Fragment");

  Shader shader_program(VALID_VSHADER, VALID_FSHADER);
  EXPECT_TRUE(shader_program.IsValid());

  shader_program.Unbind();
  EXPECT_FALSE(shader_program.IsBound());
}