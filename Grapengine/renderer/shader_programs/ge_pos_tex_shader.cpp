#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

#include "profiling/ge_profiler.hpp"
#include "renderer/ge_shader.hpp"
#include "renderer/ge_shader_data_types.hpp"

using namespace GE;

PosAndTex2DShader::PosAndTex2DShader()
{
  GE_PROFILE;
  m_shader = Shader::Make("Assets/shaders/PositionAndTex2D.vshader.glsl",
                          "Assets/shaders/PositionAndTex2D.fshader.glsl");
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

void PosAndTex2DShader::UpdateTexture(int id)
{
  Activate();
  m_shader->UploadInt("u_texture", id);
}

void PosAndTex2DShader::UpdateViewProjectionMatrix(const Mat4& viewProj, const Vec3& /*viewPosition*/)
{
  Activate();
  m_shader->UploadMat4F("u_VP", viewProj);
}
