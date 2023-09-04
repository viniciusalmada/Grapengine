#include "ge_shader.hpp"

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
  uint32_t GetGLShaderType(ShaderType type)
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

  std::tuple<uint32_t, bool> Compile(const std::string& src, ShaderType type)
  {
    uint32_t shader_type = GetGLShaderType(type);

    unsigned int shader = glCreateShader(shader_type);
    const char* chars = src.c_str();
    glShaderSource(shader, 1, &chars, nullptr);

    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      int max_length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<char> info_log;
      info_log.reserve(max_length);
      glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());

      std::string shader_name = GetGLShaderName(type);
      printf("Failure at compiling the %s shader\n", shader_name.c_str());
      fprintf(stderr, "%s\n", info_log.data());

      glDeleteShader(shader);
    }
    return std::tuple<unsigned int, bool>{ shader, success == 1 };
  }

  unsigned int CreateProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
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

    int is_linked = 0;
    glGetProgramiv(renderer_id, GL_LINK_STATUS, &is_linked);
    if (!is_linked)
    {
      int max_length = 0;
      glGetProgramiv(renderer_id, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<char> info_log;
      info_log.reserve(max_length);
      glGetProgramInfoLog(renderer_id, max_length, &max_length, info_log.data());

      printf("Failure at linking program!\n");
      fprintf(stderr, "%s", info_log.data());

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

struct Shader::Impl
{
  uint32_t renderer_id{ 0 };
  std::unordered_map<std::string, int> uniforms;

  [[nodiscard]] bool IsBound() const
  {
    int curr_program = -1;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curr_program);
    if (curr_program <= 0)
      return false;

    return static_cast<decltype(renderer_id)>(curr_program) == renderer_id;
  }

  int RetrieveUniform(const std::string& name)
  {
    if (!IsBound())
      std::cerr << "Shader not bound!!" << std::endl;
  check:
    if (uniforms.contains(name))
      return uniforms[name];

    int location = glGetUniformLocation(renderer_id, name.c_str());
    if (location == -1)
      std::cerr << "Invalid uniform name!!" << std::endl;

    uniforms[name] = location;
    goto check;
  }
};

Shader::Shader(std::string&& vertexSrc, std::string&& fragmentSrc) :
    m_pimpl(std::make_unique<Impl>())
{
  m_pimpl->renderer_id = CreateProgram(vertexSrc, fragmentSrc);
}

void Shader::Bind()
{
  glUseProgram(m_pimpl->renderer_id);
}

Shader::~Shader() = default;

void Shader::UploadMat4F(const std::string& name, const Mat4& mat)
{
  UploadMat4F(name, mat.ValuePtr());
}

void Shader::UploadMat4F(const std::string& name, const float* data)
{
  auto location = m_pimpl->RetrieveUniform(name);
  glUniformMatrix4fv(location, 1, GL_FALSE, data);
}
