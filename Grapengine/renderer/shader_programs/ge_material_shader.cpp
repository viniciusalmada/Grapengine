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

  { // TODO: Only for test
    Activate();
    UpdateAmbientColor(Colors::WHITE);
    UpdateAmbientStrength(0.25f);

    UpdateLightPosition({ Vec3{}, Vec3{ 5, 5, 5 } });
    UpdateLightColor({ Colors::WHITE, Colors::WHITE });
    UpdateLightStrength({ 1.0f, 1.0f });
  }
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

void MaterialShader::UpdateViewProjectionMatrix(Mat4 viewProj)
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

void GE::MaterialShader::UpdateLightColor(std::vector<Color> color)
{
  std::vector<Vec3> colors_vec;
  std::ranges::transform(color,
                         std::back_inserter(colors_vec),
                         [](auto&& c) { return c.ToVec3(); });
  m_shader->UploadVec3Array("u_lightColor", colors_vec);
}

void GE::MaterialShader::UpdateLightStrength(const std::vector<f32>& strength)
{
  m_shader->UploadFloatArray("u_lightStrength", strength);
}
