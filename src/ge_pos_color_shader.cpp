#include "renderer/shader_programs/ge_pos_color_shader.hpp"

#include <renderer/ge_shader.hpp>

namespace
{
  const std::string V_SHADER = R"glsl(
    #version 330 core

    layout (location = 0) in vec3 in_position;
    layout (location = 1) in vec4 in_color;

    out vec4 out_color;

    uniform float width;
    uniform float height;

    void main()
    {
        gl_Position = vec4(
                        in_position.x / (width/2) - 1.0,
                        -(in_position.y / (height/2) - 1.0),
                        in_position.z,
                        1.0);
        out_color = in_color;
    }
)glsl";

  const std::string F_SHADER = R"glsl(
    #version 330 core

    in vec4 out_color;

    out vec4 fragColor;

    void main()
    {
        fragColor = out_color;
    }
)glsl";
}

struct PosAndColorShader::Impl
{
  Scope<Shader> shader;
};

PosAndColorShader::PosAndColorShader() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = MakeScope<Shader>(V_SHADER, F_SHADER);
}

PosAndColorShader::~PosAndColorShader() = default;

void PosAndColorShader::Activate()
{
  m_pimpl->shader->Bind();
}

void PosAndColorShader::Deactivate()
{
  m_pimpl->shader->Unbind();
}

void PosAndColorShader::OnUpdate(Vec2 data)
{
  Activate();
  m_pimpl->shader->UploadFloat("width", data.x);
  m_pimpl->shader->UploadFloat("height", data.y);
}
