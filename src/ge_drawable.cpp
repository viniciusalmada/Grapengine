#include "ge_drawable.hpp"

#include <ge_renderer.hpp>

constexpr auto CP = 25;

Drawable::Drawable(float x, float y, float rad) :
    position_x(x),
    position_y(y),
    //    width(w),
    //    height(h),
    radius(rad),
    vao(std::make_shared<VertexArray>()),
    vbo(nullptr),
    ibo(nullptr)
{
#ifdef QUAD
  vao->Bind();

  vbo = std::make_shared<VertexBuffer>(nullptr, 4 * sizeof(SimpleVertexData), vao->GetID());

  std::array<SimpleVertexData, 4> positions = {
    SimpleVertexData{ { x, y, 0.0f }, { 0.f, 0.f, 1.0f, 1.0f } },
    SimpleVertexData{ { x + w, y, 0.0f }, { 0.f, 0.f, 1.0f, 1.0f } },
    SimpleVertexData{ { x + w, y + h, 0.0f }, { 0.f, 0.f, 1.0f, 1.0f } },
    SimpleVertexData{ { x, y + h, 0.0f }, { 0.f, 0.f, 1.0f, 1.0f } },
  };
  vbo->UpdateData(positions.data(), sizeof(positions));

  u32 indices[] = { 0, 1, 2, 2, 3, 0 };
  ibo = std::make_shared<IndexBuffer>(indices, 6, vao->GetID());

  vao->SetVertexBuffer(vbo);
  vao->SetIndexBuffer(ibo);
#else
  vao->Bind();

  vbo = std::make_shared<VertexBuffer>(nullptr, (CP + 1) * sizeof(SimpleVertexData), vao->GetID());

  constexpr Vec4 color{ 0.f, 0.f, 1.0f, 1.0f };
  auto* positions = new SimpleVertexData[CP + 1];
  positions[0] = {
    SimpleVertexData{ { x, y, 0.0f }, color },
  };

  u32* indices = new u32[CP * 3];
  u32 count = 0;
  u32 first_index = 1;
  u32 sec_index = 2;

  for (u32 i = 0; i < CP; ++i)
  {
    const float angle =
      static_cast<float>(i) / static_cast<float>(CP) * 2 * std::numbers::pi_v<float>;
    const float circle_x = cos(angle) * rad + position_x;
    const float circle_y = sin(angle) * rad + position_y;
    positions[i + 1].position = Vec3(circle_x, circle_y, 0.0f);
    positions[i + 1].color = color;

    indices[count++] = 0;
    indices[count++] = first_index;
    indices[count++] = sec_index;

    first_index += 1;
    sec_index += 1;
  }

  indices[(CP * 3) - 1] = 1;

  vbo->UpdateData(positions, (CP + 1) * sizeof(SimpleVertexData));

  ibo = std::make_shared<IndexBuffer>(indices, CP * 3, vao->GetID());

  vao->SetVertexBuffer(vbo);
  vao->SetIndexBuffer(ibo);

  delete[] positions;
  delete[] indices;
#endif
}

void Drawable::Draw() const
{
  Renderer::DrawIndexed(vao, CP * 3);
}
Drawable::~Drawable() = default;
