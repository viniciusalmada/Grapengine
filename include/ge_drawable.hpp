#ifndef GRAPHICENGINE3D_GE_DRAWABLE_HPP
#define GRAPHICENGINE3D_GE_DRAWABLE_HPP

#include "ge_index_buffer.hpp"
#include "ge_vertex_array.hpp"
#include "ge_vertex_buffer.hpp"

class Drawable
{
public:
//  GE3D Drawable(float x, float y, float w, float h);
  GE3D Drawable(float x, float y, float radius);
  virtual ~Drawable();

  void Draw() const;

private:
  float position_x;
  float position_y;
  float radius;
//  float width;
//  float height;
  std::shared_ptr<VertexArray> vao;
  std::shared_ptr<VertexBuffer> vbo;
  std::shared_ptr<IndexBuffer> ibo;
};

#endif // GRAPHICENGINE3D_GE_DRAWABLE_HPP
