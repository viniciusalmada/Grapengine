#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include <renderer/ge_shader.hpp>

namespace
{
  const std::string V_SHADER = R"glsl(
    #version 330 core
    
    layout (location = 0) in vec3 in_position;
    layout (location = 1) in vec2 in_texture_coord;
    
    out vec2 out_texture_coords;
    
    uniform mat4 u_model;
    //uniform mat4 u_view;
    //uniform mat4 u_proj;
    uniform mat4 u_VP;
    
    void main()
    {
        gl_Position = (u_VP) * vec4(in_position, 1.0);
        out_texture_coords = in_texture_coord;
    }
)glsl";

  const std::string F_SHADER = R"glsl(
    #version 330 core
    
    in vec2 out_texture_coords;
    
    out vec4 fragColor;
    
    uniform sampler2D dice_texture;
    
    void main()
    {
        fragColor = texture2D(dice_texture, out_texture_coords);
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
    m_pimpl->shader->UploadInt("dice_texture", 0);
  }
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

void PosAndTex2DShader::OnUpdate(Mat4 data)
{
  Activate();
  m_pimpl->shader->UploadMat4F("u_VP", data);
}

// void PosAndTex2DShader::OnUpdate(i32 data)
//{
//   m_pimpl->shader->UploadInt("dice_texture", data);
// }
