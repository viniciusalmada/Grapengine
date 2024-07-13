#ifndef GRAPENGINE_POS_TEX_SHADER_HPP
#define GRAPENGINE_POS_TEX_SHADER_HPP

#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_shader.hpp"

namespace GE
{
  class PosAndTex2DShader final : public IShaderProgram
  {
  public:
    PosAndTex2DShader();
    ~PosAndTex2DShader() override;

    void Activate() override;
    void Deactivate() override;

    void UpdateViewProjectionMatrix(const Mat4& viewProj, const Vec3& viewPosition) override;
    void UpdateTexture(int id) override;

  private:
    Ptr<Shader> m_shader;
  };
}
#endif // GRAPENGINE_POS_TEX_SHADER_HPP
