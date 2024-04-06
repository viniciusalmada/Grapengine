#ifndef GRAPENGINE_POS_TEX_SHADER_HPP
#define GRAPENGINE_POS_TEX_SHADER_HPP

#include "drawables/ge_color.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"

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

    [[nodiscard]] Ref<BufferLayout> GetLayout() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_POS_TEX_SHADER_HPP
