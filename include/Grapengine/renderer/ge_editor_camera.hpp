#ifndef GE_EDITOR_CAMERA_HPP
#define GE_EDITOR_CAMERA_HPP

#include "core/ge_macros.hpp"

namespace GE
{
  class EditorCamera
  {
  public:
    EditorCamera(float fov, float aspectRatio);
    ~EditorCamera();

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GE_EDITOR_CAMERA_HPP
