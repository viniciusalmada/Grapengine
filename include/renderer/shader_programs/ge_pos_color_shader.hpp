#ifndef GRAPHICENGINE3D_GE_POS_COLOR_SHADER_HPP
#define GRAPHICENGINE3D_GE_POS_COLOR_SHADER_HPP

#include "renderer/ge_ishader_program.hpp"

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>

class PosAndColorShader : public IShaderProgram, public ISubscriber<Vec2>
{
public:
  PosAndColorShader();
  ~PosAndColorShader();

  void Activate() override;
  void Deactivate() override;

  void OnUpdate(Vec2 data) override;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_POS_COLOR_SHADER_HPP
