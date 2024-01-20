#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include <renderer/ge_shader.hpp>

using namespace GE;

namespace
{
  const std::string V_SHADER = R"glsl(
    #version 330 core
    
    layout (location = 0) in vec3 in_position;
    layout (location = 1) in vec2 in_texture_coord;
    layout (location = 2) in float in_use_color;
    layout (location = 3) in vec4 in_color;

    out vec2 out_texture_coords;
    out float out_use_color;
    out vec4 out_color;

    uniform mat4 u_VP;

    void main()
    {
      gl_Position = (u_VP) * vec4(in_position, 1.0);
      out_texture_coords = in_texture_coord;
      out_use_color = in_use_color;
      out_color = in_color;
    }
)glsl";

  const std::string F_SHADER = R"glsl(
    #version 330 core

    in vec2 out_texture_coords;
    in float out_use_color;
    in vec4 out_color;

    out vec4 fragColor;

    uniform sampler2D img_texture;
    uniform sampler2D color_texture;

    void main()
    {
      if (out_use_color > 0.5)
        fragColor = texture2D(color_texture, vec2(0,0)) * out_color;
      else
        fragColor = texture2D(img_texture, out_texture_coords);
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
  // TODO: TEMP
  {
    Activate();
    m_pimpl->shader->UploadInt("color_texture", 1);
  }
}

PosAndTex2DShader::~PosAndTex2DShader() = default;

void PosAndTex2DShader::Activate()
{
  m_pimpl->shader->Bind();
  m_pimpl->shader->UploadInt("img_texture", 0);

}

void PosAndTex2DShader::Deactivate()
{
  m_pimpl->shader->Unbind();
}

void PosAndTex2DShader::OnUpdate(Mat4 data)
{
  Activate();
  m_pimpl->shader->UploadMat4F("u_VP", data);
}
