#ifndef GRAPENGINE_MATERIAL_SHADER_HPP
#define GRAPENGINE_MATERIAL_SHADER_HPP

#include "drawables/ge_color.hpp"
#include "renderer/ge_ishader_program.hpp"

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>

namespace GE
{
  class MaterialShader final : public IShaderProgram
  {
  public:
    MaterialShader();
    ~MaterialShader() override;

    void Activate() override;
    void Deactivate() override;

    void UpdateModelMatrix(Mat4 model) override;
    void UpdateViewProjectionMatrix(Mat4 viewProj) override;
    void UpdateTexture(int id) override;

    void UpdateAmbientColor(Color color);
    void UpdateAmbientStrength(f32 strength);

    void UpdateLightPosition(std::vector<Vec3> pos);
    void UpdateLightColor(std::vector<Color> color);
    void UpdateLightStrength(std::vector<f32> strength);

    [[nodiscard]] Ref<BufferLayout> GetLayout() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_MATERIAL_SHADER_HPP
