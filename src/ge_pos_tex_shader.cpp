#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_shader_data_types.hpp"

#include <renderer/ge_shader.hpp>

using namespace GE;

struct PosAndTex2DShader::Impl
{
  Ref<Shader> shader;
};

PosAndTex2DShader::PosAndTex2DShader() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = Shader::Make("assets/shaders/PositionAndTex2D.vshader.glsl",
                                 "assets/shaders/PositionAndTex2D.fshader.glsl");
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

Ref<BufferLayout> GE::PosAndTex2DShader::GetLayout() const
{
  return MakeRef<BufferLayout>(BufferLayout::BuildElementsList( //
    {
      ShaderDataType::Float3, // position
      ShaderDataType::Float2, // texture
      ShaderDataType::Float4, // color
      ShaderDataType::Float3, // normal
    }));
}

void GE::PosAndTex2DShader::UpdateAmbientColor(Vec3 color)
{
  m_pimpl->shader->UploadVec3("u_ambientColor", color);
}

void GE::PosAndTex2DShader::UpdateAmbientStrength(f32 strength)
{
  m_pimpl->shader->UploadFloat("u_ambientStrength", strength);
}

void GE::PosAndTex2DShader::UpdateLightPosition(Vec3 pos)
{
  m_pimpl->shader->UploadVec3("u_lightPos", pos);
}
