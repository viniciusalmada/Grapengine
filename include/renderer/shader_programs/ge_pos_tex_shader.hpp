#ifndef GRAPENGINE_POS_TEX_SHADER_HPP
#define GRAPENGINE_POS_TEX_SHADER_HPP

#include "renderer/ge_ishader_program.hpp"

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>

class PosAndTex2DShader : public IShaderProgram, public ISubscriber<Mat4>
{
public:
  PosAndTex2DShader();
  ~PosAndTex2DShader();

  void Activate() override;
  void Deactivate() override;

  void OnUpdate(Mat4 data) override;
//  void OnUpdate(i32 data) override;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPENGINE_POS_TEX_SHADER_HPP
