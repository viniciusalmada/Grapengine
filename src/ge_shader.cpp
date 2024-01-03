#include "renderer/ge_shader.hpp"

#include "core/ge_assert.hpp"
#include "utils/ge_io.hpp"

#include <glad/glad.h>

namespace
{
  enum class ShaderType
  {
    VERTEX,
    FRAGMENT
  };

  DISABLE_WARNING_PUSH
  DISABLE_UNREACHABLE_CODE
  u32 GetGLShaderType(ShaderType type)
  {
    switch (type)
    {
    case ShaderType::VERTEX:
      return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT:
      return GL_FRAGMENT_SHADER;
    }
  }
  DISABLE_WARNING_POP

  DISABLE_WARNING_PUSH
  DISABLE_UNREACHABLE_CODE
  std::string GetGLShaderName(ShaderType type)
  {
    switch (type)
    {
    case ShaderType::VERTEX:
      return "Vertex";
    case ShaderType::FRAGMENT:
      return "Fragment";
    }
  }
  DISABLE_WARNING_POP

  std::tuple<u32, bool> Compile(const std::string& src, ShaderType type)
  {
    u32 shader = glCreateShader(GetGLShaderType(type));
    const char* chars = src.c_str();
    glShaderSource(shader, 1, &chars, nullptr);

    glCompileShader(shader);

    i32 success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      i32 max_length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<char> info_log;
      info_log.reserve(max_length);
      glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());

      std::string shader_name = GetGLShaderName(type);
      std::stringstream ss;
      ss << "Failure at compiling the " << shader_name << " shader\n";
      ss << info_log.data();
      Assert(false, ss.str().c_str());

      glDeleteShader(shader);
    }
    return std::tuple<u32, bool>{ shader, success == 1 };
  }

  u32 CreateProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
  {
    auto [vertex_shader, vertex_ok] = Compile(vertexSrc, ShaderType::VERTEX);
    if (!vertex_ok)
      return 0;

    auto [fragment_shader, fragment_ok] = Compile(fragmentSrc, ShaderType::FRAGMENT);
    if (!fragment_ok)
    {
      glDeleteShader(vertex_shader);
      return 0;
    }

    auto renderer_id = glCreateProgram();

    glAttachShader(renderer_id, vertex_shader);
    glAttachShader(renderer_id, fragment_shader);

    glLinkProgram(renderer_id);

    i32 is_linked = 0;
    glGetProgramiv(renderer_id, GL_LINK_STATUS, &is_linked);
    if (!is_linked)
    {
      i32 max_length = 0;
      glGetProgramiv(renderer_id, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<char> info_log;
      info_log.resize(max_length);
      glGetProgramInfoLog(renderer_id, max_length, &max_length, info_log.data());

      std::stringstream ss;
      ss << "Failure at linking program!\n";
      ss << info_log.data();
      Assert(false, ss.str().c_str());

      glDeleteProgram(renderer_id);

      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);
      return 0;
    }

    glDetachShader(renderer_id, vertex_shader);
    glDetachShader(renderer_id, fragment_shader);

    return renderer_id;
  }
}

struct ShaderProgram::Impl
{
  u32 renderer_id{ 0 };
  std::unordered_map<std::string, i32> uniforms;

  [[nodiscard]] bool IsBound() const
  {
    i32 curr_program = -1;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curr_program);
    if (curr_program <= 0)
      return false;

    return static_cast<decltype(renderer_id)>(curr_program) == renderer_id;
  }

  i32 RetrieveUniform(const std::string& name)
  {
    Assert(IsBound(), "Shader not bound");

  check:
    if (uniforms.contains(name))
      return uniforms[name];

    i32 location = glGetUniformLocation(renderer_id, name.c_str());
    Assert(location != -1, "Invalid uniform name");

    uniforms[name] = location;
    goto check;
  }
};

ShaderProgram::ShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc) :
    m_pimpl(MakeScope<Impl>())
{
  m_pimpl->renderer_id = CreateProgram(vertexSrc, fragmentSrc);
}

ShaderProgram::ShaderProgram(const std::filesystem::path& vertexPath,
                             const std::filesystem::path& fragPath) :
    m_pimpl(MakeScope<Impl>())
{
  auto vertex_src = IO::ReadFileToString(vertexPath);
  auto frag_src = IO::ReadFileToString(fragPath);
  m_pimpl->renderer_id = CreateProgram(vertex_src, frag_src);
}

void ShaderProgram::Bind()
{
  glUseProgram(m_pimpl->renderer_id);
}

ShaderProgram::~ShaderProgram() = default;

void ShaderProgram::UploadMat4F(const std::string& name, const Mat4& mat)
{
  UploadMat4F(name, mat.ValuePtr());
}

void ShaderProgram::UploadMat4F(const std::string& name, const float* data)
{
  auto location = m_pimpl->RetrieveUniform(name);
  glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void ShaderProgram::UploadInt(const std::string& name, i32 i)
{
  auto location = m_pimpl->RetrieveUniform(name);
  glUniform1i(location, i);
}

void ShaderProgram::UploadFloat(const std::string& name, float i)
{
  auto location = m_pimpl->RetrieveUniform(name);
  glUniform1f(location, i);
}

[[maybe_unused]] bool ShaderProgram::IsValid() const
{
  return glIsProgram(m_pimpl->renderer_id);
}

bool ShaderProgram::IsBound() const
{
  return m_pimpl->IsBound();
}

void ShaderProgram::Unbind()
{
  if (IsBound())
    glUseProgram(0);
}
