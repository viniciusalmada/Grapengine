#ifndef GRAPENGINE_DRAWABLE_HPP
#define GRAPENGINE_DRAWABLE_HPP

enum class Shaders;

class Drawable
{
public:
  Drawable(Shaders){};

  virtual ~Drawable() = default;

  virtual void Draw() const = 0;
};

#endif // GRAPENGINE_DRAWABLE_HPP
