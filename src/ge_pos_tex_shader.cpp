#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include <renderer/ge_shader.hpp>

using namespace GE;

namespace
{
  const std::string V_SHADER = R"glsl(
    #version 330 core
    
    layout (location = 0) in vec3 in_position;
    layout (location = 1) in vec2 in_texture_coord;
    layout (location = 2) in vec4 in_color;

    out vec2 out_texture_coords;
    out vec4 out_color;

    uniform mat4 u_M;
    uniform mat4 u_VP;

    void main()
    {
      gl_Position = (u_VP) * u_M * vec4(in_position, 1.0);
      out_texture_coords = in_texture_coord;
      out_color = in_color;
    }
)glsl";

  const std::string F_SHADER = R"glsl(
    #version 330 core

    in vec2 out_texture_coords;
    in vec4 out_color;

    out vec4 fragColor;

    uniform sampler2D u_texture;

    void main()
    {
      fragColor = texture2D(u_texture, out_texture_coords) * out_color;
    }
)glsl";
}

struct PosAndTex2DShader::Impl
{
  Scope<Shader> shader;
};

PosAndTex2DShader::PosAndTex2DShader() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = MakeScope<Shader>(V_SHADER, F_SHADER);
}

PosAndTex2DShader::~PosAndTex2DShader() = default;

void PosAndTex2DShader::Activate()
{
  m_pimpl->shader->Bind();
}

void PosAndTex2DShader::Deactivate()
{
  m_pimpl->shader->Unbind();
}

void PosAndTex2DShader::UpdateModelMatrix(Mat4 data)
{
  Activate();
  m_pimpl->shader->UploadMat4F("u_M", data);
}

void PosAndTex2DShader::UpdateViewProjectionMatrix(Mat4 viewProj)
{
  Activate();
  m_pimpl->shader->UploadMat4F("u_VP", viewProj);
}

void PosAndTex2DShader::UpdateTexture(int id)
{
  Activate();
  m_pimpl->shader->UploadInt("u_texture", id);
}
