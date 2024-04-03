#ifndef GE_EDITOR_CAMERA_HPP
#define GE_EDITOR_CAMERA_HPP

#include "core/ge_macros.hpp"

#include <math/ge_vector.hpp>

namespace GE
{
  class TimeStep;
  class Event;

  class EditorCamera
  {
  public:
    EditorCamera();
    EditorCamera(f32 fov, f32 aspectRatio);
    ~EditorCamera();

    void OnUpdate(TimeStep ts) const;
    void OnEvent(Event& event);

    [[nodiscard]] Mat4 GetViewProjection() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GE_EDITOR_CAMERA_HPP
