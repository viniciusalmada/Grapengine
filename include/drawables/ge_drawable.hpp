#ifndef GRAPHICENGINE3D_GE_DRAWABLE_HPP
#define GRAPHICENGINE3D_GE_DRAWABLE_HPP

enum class Shaders;

class Drawable
{
public:
  Drawable(Shaders){};

  virtual ~Drawable() = default;

  virtual void Draw() const = 0;
};

#endif // GRAPHICENGINE3D_GE_DRAWABLE_HPP
