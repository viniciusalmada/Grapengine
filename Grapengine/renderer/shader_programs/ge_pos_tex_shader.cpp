#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_shader_data_types.hpp"

#include <drawables/ge_color.hpp>
#include <renderer/ge_shader.hpp>

using namespace GE;

PosAndTex2DShader::PosAndTex2DShader()
{
  m_shader = Shader::Make("assets/shaders/PositionAndTex2D.vshader.glsl",
                          "assets/shaders/PositionAndTex2D.fshader.glsl");
}

PosAndTex2DShader::~PosAndTex2DShader() = default;

void PosAndTex2DShader::Activate()
{
  m_shader->Bind();
}

void PosAndTex2DShader::Deactivate()
{
  m_shader->Unbind();
}

void PosAndTex2DShader::UpdateModelMatrix(Mat4 data)
{
  Activate();
  m_shader->UploadMat4F("u_M", data);
}

void PosAndTex2DShader::UpdateViewProjectionMatrix(Mat4 viewProj)
{
  Activate();
  m_shader->UploadMat4F("u_VP", viewProj);
}

void PosAndTex2DShader::UpdateTexture(int id)
{
  Activate();
  m_shader->UploadInt("u_texture", id);
}

Ref<BufferLayout> GE::PosAndTex2DShader::GetLayout() const
{
  auto buffer_elements = BufferLayout::BuildElementsList( //
    {
      std::make_pair(DataPurpose::POSITION, ShaderDataType::Float3),           // position
      std::make_pair(DataPurpose::TEXTURE_COORDINATE, ShaderDataType::Float2), // texture
      std::make_pair(DataPurpose::COLOR, ShaderDataType::Float4),              // color
    });
  return MakeRef<BufferLayout>(buffer_elements);
}
