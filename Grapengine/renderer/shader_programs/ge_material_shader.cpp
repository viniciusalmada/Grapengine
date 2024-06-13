#include "renderer/shader_programs/ge_material_shader.hpp"

#include "profiling/ge_profiler.hpp"
#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_shader_data_types.hpp"

#include <drawables/ge_color.hpp>
#include <renderer/ge_shader.hpp>

using namespace GE;

MaterialShader::MaterialShader()
{
  GE_PROFILE;
  m_shader =
    Shader::Make("assets/shaders/Material.vshader.glsl", "assets/shaders/Material.fshader.glsl");
}

MaterialShader::~MaterialShader() = default;

void MaterialShader::Activate()
{
  m_shader->Bind();
}

void MaterialShader::Deactivate()
{
  m_shader->Unbind();
}

void MaterialShader::UpdateViewProjectionMatrix(const Mat4& viewProj)
{
  Activate();
  m_shader->UploadMat4F("u_VP", viewProj);
}

void MaterialShader::UpdateTexture(int id)
{
  Activate();
  m_shader->UploadInt("u_texture", id);
}

void GE::MaterialShader::UpdateAmbientColor(Color color)
{
  m_shader->UploadVec3("u_ambientColor", color.ToVec3());
}

void GE::MaterialShader::UpdateAmbientStrength(f32 strength)
{
  m_shader->UploadFloat("u_ambientStrength", strength);
}

void GE::MaterialShader::UpdateLightPosition(const std::vector<Vec3>& pos)
{
  m_shader->UploadVec3Array("u_lightPos", pos);
}

void GE::MaterialShader::UpdateLightColor(const std::vector<Vec3>& colors)
{
  m_shader->UploadVec3Array("u_lightColor", colors);
}

void GE::MaterialShader::UpdateLightStrength(const std::vector<f32>& strength)
{
  m_shader->UploadFloatArray("u_lightStrength", strength);
}

Ptr<MaterialShader> MaterialShader::Make()
{
  return MakeRef<MaterialShader>();
}

void MaterialShader::UpdateAmbientLight(Color color, f32 strength)
{
  UpdateAmbientColor(color);
  UpdateAmbientStrength(strength);
}

void MaterialShader::UpdateLightSpots(const std::vector<std::tuple<Vec3, Color, f32>>& lightSpots)
{
  std::vector<Vec3> positions;
  positions.reserve(lightSpots.size());
  std::vector<Vec3> colors;
  colors.reserve(lightSpots.size());
  std::vector<f32> strenghts;
  strenghts.reserve(lightSpots.size());
  for (const auto& [p, c, s] : lightSpots)
  {
    positions.push_back(p);
    colors.push_back(c.ToVec3());
    strenghts.push_back(s);
  }

  UpdateLightPosition(positions);
  UpdateLightColor(colors);
  UpdateLightStrength(strenghts);
}

void MaterialShader::ClearAmbientLight()
{
  UpdateAmbientLight(Colors::WHITE, 1.0f);
}

void MaterialShader::ClearLightSpots()
{
  UpdateLightSpots({});
}
