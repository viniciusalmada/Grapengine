#ifndef GRAPENGINE_POS_TEX_SHADER_HPP
#define GRAPENGINE_POS_TEX_SHADER_HPP

#include "renderer/ge_ishader_program.hpp"

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>

namespace GE
{
  class PosAndTex2DShader final : public IShaderProgram
  {
  public:
    PosAndTex2DShader();
    ~PosAndTex2DShader() override;

    void Activate() override;
    void Deactivate() override;

    void UpdateModelMatrix(Mat4 model) override;
    void UpdateViewProjectionMatrix(Mat4 viewProj) override;
    void UpdateTexture(int id) override;

    void UpdateLightPosition(Vec3 pos);
    void UpdateAmbientColor(Vec3 color);
    void UpdateAmbientStrength(f32 strength);

    [[nodiscard]] Ref<BufferLayout> GetLayout() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_POS_TEX_SHADER_HPP
