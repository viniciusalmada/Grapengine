#include "ge_buffer_handler.hpp"

using namespace GE;

void BufferHandler::UpdatePosition(VerticesData& vd, const Mat4& modelMatrix)
{
  auto& vertices = vd.GetData();
  std::ranges::for_each(vertices,
                        [&](VertexStruct& vs) { vs.position = modelMatrix * vs.position; });
}
