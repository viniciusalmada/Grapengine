#include "renderer/shader_programs/ge_material_shader.hpp"

#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_shader_data_types.hpp"

#include <drawables/ge_color.hpp>
#include <renderer/ge_shader.hpp>

using namespace GE;

MaterialShader::MaterialShader()
{
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

void MaterialShader::UpdateModelMatrix(Mat4 data)
{
  Activate();
  m_shader->UploadMat4F("u_M", data);
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

Ref<BufferLayout> GE::MaterialShader::GetLayout() const
{
  auto buffer_elements = BufferLayout::BuildElementsList( //
    {
      std::make_pair(DataPurpose::POSITION, ShaderDataType::Float3),           // position
      std::make_pair(DataPurpose::TEXTURE_COORDINATE, ShaderDataType::Float2), // texture
      std::make_pair(DataPurpose::COLOR, ShaderDataType::Float4),              // color
      std::make_pair(DataPurpose::NORMAL, ShaderDataType::Float3),             // normal
    });

  return BufferLayout::Make(buffer_elements);
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
