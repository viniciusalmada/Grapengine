#ifndef GRAPENGINE_MATERIAL_SHADER_HPP
#define GRAPENGINE_MATERIAL_SHADER_HPP

#include "drawables/ge_color.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_shader.hpp"

namespace GE
{
  class MaterialShader final : public IShaderProgram
  {
  public:
    static Ptr<MaterialShader> Make();

    MaterialShader();
    ~MaterialShader() override;

    void Activate() override;
    void Deactivate() override;

    void UpdateViewProjectionMatrix(const Mat4& viewProj) override;
    void UpdateTexture(int id) override;

    /**
     * Update ambient light properties
     * @param color light color
     * @param strength light strenght limited from 0 to 10
     */
    void UpdateAmbientLight(Color color, f32 strength);
    void ClearAmbientLight();

    /**
     *
     * @param lightSpots lights properties
     */
    void UpdateLightSpots(const std::vector<std::tuple<Vec3, Color, f32>>& lightSpots);
    void ClearLightSpots();

  private:
    void UpdateAmbientColor(Color color);
    void UpdateAmbientStrength(f32 strength);

    void UpdateLightPosition(const std::vector<Vec3>& pos);
    void UpdateLightColor(const std::vector<Vec3>& color);
    void UpdateLightStrength(const std::vector<f32>& strength);

    Ptr<Shader> m_shader;
  };
}
#endif // GRAPENGINE_MATERIAL_SHADER_HPP
