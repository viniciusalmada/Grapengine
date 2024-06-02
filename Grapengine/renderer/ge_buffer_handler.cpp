#include "ge_buffer_handler.hpp"

#include "profiling/ge_profiler.hpp"

using namespace GE;

void BufferHandler::UpdatePosition(VerticesData& vd, const Mat4& modelMatrix)
{
  GE_PROFILE;
  auto& vertices = vd.GetData();
  std::ranges::for_each(vertices,
                        [&](VertexStruct& vs) { vs.position = modelMatrix * vs.position; });

  std::ranges::for_each(vertices,
                        [&](VertexStruct& vs) {
                          vs.normal =
                            (modelMatrix.Inverse().Transpose().ToMat3() * vs.normal).Normalize();
                        });
}
