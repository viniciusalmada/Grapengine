#ifndef GRAPENGINE_POS_TEX_SHADER_HPP
#define GRAPENGINE_POS_TEX_SHADER_HPP

#include "renderer/ge_ishader_program.hpp"

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>
namespace GE
{
  class PosAndTex2DShader : public IShaderProgram
  {
  public:
    PosAndTex2DShader();
    ~PosAndTex2DShader();

    void Activate() override;
    void Deactivate() override;

    void UpdateModelMatrix(Mat4 model);
    void UpdateViewProjectionMatrix(Mat4 viewProj);
    void UpdateTexture(int id);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_POS_TEX_SHADER_HPP
